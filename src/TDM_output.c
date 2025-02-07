/* tdm.c
Written by Noe Heuclin 2025. some functions are copied/adapted from Daniel Collins i2s example for rp2040 pio
 */

#include "TDM_output.h"
#include "pins.h"
#include "TDM_output.pio.h"

#include <math.h>

#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/irq.h"

static pio_tdm* tdm_ptr; 

static void set_tdm_ptr(pio_tdm* ptr){
    tdm_ptr=ptr;
}

static float pio_div(float freq, uint16_t* div, uint8_t* frac) {
    float clk   = (float)clock_get_hz(clk_sys);
    float ratio = clk / freq;
    float d;
    float f = modff(ratio, &d);
    *div    = (uint16_t)d;
    *frac   = (uint8_t)(f * 256.0f);

    // Use post-converted values to get actual freq after any rounding
    float result = clk / ((float)*div + ((float)*frac / 256.0f));

    return result;
}

static void calc_clocks(const tdm_config* config, pio_tdm_clocks* clocks) {
    // Try to get a precise ratio between SCK and BCK regardless of how
    // perfect the system_clock divides. First, see what sck we can actually get:
    float sck_desired   = (float)config->fs * (float)config->sck_mult * (float)tdm_sck_program_pio_mult;
    float sck_attained  = pio_div(sck_desired, &clocks->sck_d, &clocks->sck_f);
    clocks->fs_attained = sck_attained / (float)config->sck_mult / (float)tdm_sck_program_pio_mult;

    // Now that we have the closest fs our dividers will give us, we can
    // re-calculate SCK and BCK as correct ratios of this adjusted fs:
    float sck_hz       = clocks->fs_attained * (float)config->sck_mult;
    clocks->sck_pio_hz = pio_div(sck_hz * (float)tdm_sck_program_pio_mult, &clocks->sck_d, &clocks->sck_f);
    float bck_hz       = clocks->fs_attained * (float)config->bit_depth * 2.0f;
    clocks->bck_pio_hz = pio_div(bck_hz * (float)tdm_output_clocks_program_pio_mult, &clocks->bck_d, &clocks->bck_f);
}

static bool validate_sck_bck_sync(pio_tdm_clocks* clocks) {
    float ratio      = clocks->sck_pio_hz / clocks->bck_pio_hz;
    float actual_sck = clocks->sck_pio_hz / (float)tdm_sck_program_pio_mult;
    float actual_bck = clocks->bck_pio_hz / (float)tdm_output_clocks_program_pio_mult;
    printf("Clock speed for SCK: %f (PIO %f Hz with divider %d.%d)\n", actual_sck, clocks->sck_pio_hz, clocks->sck_d, clocks->sck_f);
    printf("Clock speed for BCK: %f (PIO %f Hz with divider %d.%d)\n", actual_bck, clocks->bck_pio_hz, clocks->bck_d, clocks->bck_f);
    printf("Clock Ratio: %f\n", ratio);
    float whole_ratio;
    float fractional_ratio = modff(ratio, &whole_ratio);
    return (fractional_ratio == 0.0f);
}


static void set_calib_data(pio_tdm* tdm, pio_tdm_calib* calibration_data){
    tdm->calibration = *calibration_data; 
    for (size_t j = 0; j< tdm->config.out_number;j++){
        switch (j) {
            case 0:
                for (size_t i = 0; i<8; i++){
                    tdm->calibration1[0][i]= (float)((tdm->calibration.IC1_calib[1][i])-(tdm->calibration.IC1_calib[0][i]));
                    tdm->calibration1[1][i]= (float)(tdm->calibration.IC1_calib[0][i]);
                }
                break;
            case 1:
                for (size_t i = 0; i<8; i++){
                    tdm->calibration2[0][i]= (float)((tdm->calibration.IC2_calib[1][i])-(tdm->calibration.IC2_calib[0][i]));
                    tdm->calibration2[1][i]= (float)(tdm->calibration.IC2_calib[0][i]);
                }
                break;
            case 2:
                for (size_t i = 0; i<8; i++){
                    tdm->calibration3[0][i]= (float)((tdm->calibration.IC3_calib[1][i])-(tdm->calibration.IC3_calib[0][i]));
                    tdm->calibration3[1][i]= (float)(tdm->calibration.IC3_calib[0][i]);
                }
                break;
        }
    }
}

void tdm_interleave(pio_tdm* tdm){
    if (tdm->Ready_to_Interleave==1){
    int32_t sample = 0;
    int32_t count = 0;    
    
        for (size_t k = 0; k< tdm->config.out_number;k++){
            switch (k) {
               case 0:
                    sample = 0;
                    count = 0;
                    for(size_t j = 0; j<TDM_BUFFER_FRAMES; j++) { //j is frame number in block
                        for (size_t i = 0; i < 8 ; i++) {  //i is channel number in frame
                            sample =(int32_t)((tdm->data->tdm_stream1[j][i]*tdm->calibration1[0][i])+tdm->calibration1[1][i]) ; // calib[1][x] stores: (float)(real_positive_5V-real_OV) / calib[0][x] stores (float)real_0V
                            tdm->OutBufPtr1[count] = sample;
                            count++;
                            
                        }
                    }
                    break;
                case 1:
                    sample = 0;
                    count = 0;
                    for(size_t j = 0; j<TDM_BUFFER_FRAMES; j++) { 
                        for (size_t i = 0; i < 8 ; i++) {  
                            sample =(int32_t)((tdm->data->tdm_stream2[j][i]*tdm->calibration2[0][i])+tdm->calibration2[1][i]) ; // calib[1][x] stores: (float)(real_positive_5V-real_OV) / calib[0][x] stores (float)real_0V
                            tdm->OutBufPtr2[count] = sample;
                            count++;
                        }
                    }                
                    break;
                case 2:
                    sample = 0;
                    count = 0;
                    for(size_t j = 0; j<TDM_BUFFER_FRAMES; j++) {
                        for (size_t i = 0; i < 8 ; i++) {  //i is channel number in frame
                            sample =(int32_t)((tdm->data->tdm_stream3[j][i]*tdm->calibration3[0][i])+tdm->calibration3[1][i]) ; // calib[1][x] stores: (float)(real_positive_5V-real_OV) / calib[0][x] stores (float)real_0V
                            tdm->OutBufPtr3[count] = sample;
                            count++;
                        }
                    }   
                    break;
            }
        } 
        tdm->Ready_to_Interleave=0;
        tdm->MoreData=1;
    }    
}

void tdm_interleave2(pio_tdm* tdm){
    if (tdm->Ready_to_Interleave==1){
        int32_t sample = 0;
        int32_t count = 0;    
        for (size_t k = 0; k< tdm->config.out_number;k++){
            switch (k) {
                case 0:
                    sample = 0;
                    count = 0;
                    for(size_t j = 0; j<TDM_BUFFER_FRAMES; j++) { //j is frame number in block
                        for (size_t i = 0; i < 8 ; i++) {  //i is channel number in frame
                            sample =(int32_t)((tdm->data->tdm_stream1[j][i]*tdm->calibration1[0][i])+tdm->calibration1[1][i]) ; // calib[1][x] stores: (float)(real_positive_5V-real_OV) / calib[0][x] stores (float)real_0V                            
                            int32_t iterator ;
                            for(size_t n; n<tdm->config.down_factor; n++){
                                iterator=count+n*tdm->config.down_factor;
                                tdm->OutBufPtr1[iterator] = sample;
                            }
                            count++;                            
                        }
                    }
                    break;
                case 1:
                    sample = 0;
                    count = 0;
                    for(size_t j = 0; j<TDM_BUFFER_FRAMES; j++) { 
                        for (size_t i = 0; i < 8 ; i++) {  
                            sample =(int32_t)((tdm->data->tdm_stream2[j][i]*tdm->calibration2[0][i])+tdm->calibration2[1][i]) ; // calib[1][x] stores: (float)(real_positive_5V-real_OV) / calib[0][x] stores (float)real_0V
                            int32_t iterator ;
                            for(size_t n; n<tdm->config.down_factor; n++){
                                iterator=count+n*tdm->config.down_factor;
                                tdm->OutBufPtr2[iterator] = sample;
                            }
                            count++;                            
                        }
                    }             
                    break;
                case 2:
                    sample = 0;
                    count = 0;
                    for(size_t j = 0; j<TDM_BUFFER_FRAMES; j++) {
                        for (size_t i = 0; i < 8 ; i++) {  //i is channel number in frame
                            sample =(int32_t)((tdm->data->tdm_stream3[j][i]*tdm->calibration3[0][i])+tdm->calibration3[1][i]) ; // calib[1][x] stores: (float)(real_positive_5V-real_OV) / calib[0][x] stores (float)real_0V
                            int32_t iterator ;
                            for(size_t n; n<tdm->config.down_factor; n++){
                                iterator=count+n*tdm->config.down_factor;
                                tdm->OutBufPtr3[iterator] = sample;
                            }
                            count++;                            
                        }
                    }
                    break;
            }
        } 
        tdm->Ready_to_Interleave=0;
        tdm->MoreData=1;
    }    
}

static void tdm_HalfCplt_Callback(){
    for (size_t i = 0; i< tdm_ptr->config.out_number;i++){
       switch (i) {
        case 0:
            tdm_ptr->OutBufPtr1=&(tdm_ptr->output_buffer1[0]); //we're halfway so fill first half
            break;
        case 1:
            tdm_ptr->OutBufPtr2=&(tdm_ptr->output_buffer2[0]); //we're halfway so fill first half
            break;
        case 2:
            tdm_ptr->OutBufPtr3=&(tdm_ptr->output_buffer3[0]); //we're halfway so fill first half
            break;
        }
    }   
    tdm_ptr->Ready_to_Interleave=1;
}

static void tdm_Cplt_Callback(){
    for (size_t i = 0; i< tdm_ptr->config.out_number;i++){
        switch (i) {
            case 0:
                tdm_ptr->OutBufPtr1=&(tdm_ptr->output_buffer1[OCTAL_BUFFER_SIZE]); //we're halfway so fill first half
                break;
            case 1:
                tdm_ptr->OutBufPtr2=&(tdm_ptr->output_buffer2[OCTAL_BUFFER_SIZE]); //we're halfway so fill first half
                break;
            case 2:
                tdm_ptr->OutBufPtr3=&(tdm_ptr->output_buffer3[OCTAL_BUFFER_SIZE]); //we're halfway so fill first half
                break;
        }
    }
    tdm_ptr->Ready_to_Interleave=1;
}

static void tdm_dma_in_handler(void) {
    //By checking which buffer the DMA is currently reading from, 
    //we can identify which buffer it has just finished reading (the completion of which has triggered this interrupt). 
    if (*(int32_t**)dma_hw->ch[tdm_ptr->dma_ch_out_ctrl1].read_addr == &tdm_ptr->output_buffer1[0]) { 
        tdm_Cplt_Callback();   
    }
    else { //we're outputting from second half of buffer 
        tdm_HalfCplt_Callback();
    }
    dma_hw->ints0 = 1u << (tdm_ptr->dma_ch_out_data1);  // clear the IRQ
}

static void dma_double_buffer_init(pio_tdm* tdm, void (*dma_handler)(void)) {
    // Set up DMA for PIO tdm - up to 3 output channels (using 6 DMA channels total)

    for (size_t i = 0; i< tdm_ptr->config.out_number;i++){
        switch (i) {
            default:
                panic("Out number outside of allowed range (1 to 3)");
            case 0:
                tdm->dma_ch_out_ctrl1 = dma_claim_unused_channel(true);
                tdm->dma_ch_out_data1 = dma_claim_unused_channel(true);

                // Control blocks support double-buffering with interrupts on buffer change

                tdm->out_ctrl_blocks1[0] = &tdm->output_buffer1[0];
                tdm->out_ctrl_blocks1[1] = &tdm->output_buffer1[OCTAL_BUFFER_SIZE];

                // DMA tdm OUT control channel - wrap read address every 8 bytes (2 words)  --- Noe mod to 32bytes (2^5) wrap
                // Transfer 1 word at a time, to the out channel read address and trigger.  --- (8words x 4bytes (32bit) data)
                dma_channel_config c = dma_channel_get_default_config(tdm->dma_ch_out_ctrl1);
                channel_config_set_read_increment(&c, true);
                channel_config_set_write_increment(&c, false);
                channel_config_set_ring(&c, false, 3);
                channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
                //channel_config_set_chain_to(&c,tdm->dma_ch_out_data);
                dma_channel_configure(tdm->dma_ch_out_ctrl1, 
                                    &c, 
                                    &dma_hw->ch[tdm->dma_ch_out_data1].al3_read_addr_trig, // al3_read_addr_trig, read_addr, 
                                    tdm->out_ctrl_blocks1,                                 // Source pointer
                                    1, 
                                    false
                );

                c = dma_channel_get_default_config(tdm->dma_ch_out_data1);
                channel_config_set_read_increment(&c, true);
                channel_config_set_write_increment(&c, false);
                //channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
                channel_config_set_chain_to(&c, tdm->dma_ch_out_ctrl1);
                channel_config_set_dreq(&c, pio_get_dreq(tdm->pio, tdm->sm_dout1, true));
                dma_channel_configure(tdm->dma_ch_out_data1,
                                    &c,
                                    &tdm->pio->txf[tdm->sm_dout1],  // Destination pointer aka write address
                                    NULL,                          // Source pointer, will be set by ctrl channel
                                    OCTAL_BUFFER_SIZE,             // Number of transfers
                                    false                          // Start immediately
                );
                break;
            case 1:
                tdm->dma_ch_out_ctrl2 = dma_claim_unused_channel(true);
                tdm->dma_ch_out_data2 = dma_claim_unused_channel(true);

                // Control blocks support double-buffering with interrupts on buffer change

                tdm->out_ctrl_blocks2[0] = &tdm->output_buffer2[0];
                tdm->out_ctrl_blocks2[1] = &tdm->output_buffer2[OCTAL_BUFFER_SIZE];

                // DMA tdm OUT control channel - wrap read address every 8 bytes (2 words)  --- Noe mod to 32bytes (2^5) wrap
                // Transfer 1 word at a time, to the out channel read address and trigger.  --- (8words x 4bytes (32bit) data)
                c = dma_channel_get_default_config(tdm->dma_ch_out_ctrl2);
                channel_config_set_read_increment(&c, true);
                channel_config_set_write_increment(&c, false);
                channel_config_set_ring(&c, false, 3);
                channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
                //channel_config_set_chain_to(&c,tdm->dma_ch_out_data);
                dma_channel_configure(tdm->dma_ch_out_ctrl2, 
                                    &c, 
                                    &dma_hw->ch[tdm->dma_ch_out_data2].al3_read_addr_trig, // al3_read_addr_trig, read_addr, 
                                    tdm->out_ctrl_blocks2,                                 // Source pointer
                                    1, 
                                    false
                );

                c = dma_channel_get_default_config(tdm->dma_ch_out_data2);
                channel_config_set_read_increment(&c, true);
                channel_config_set_write_increment(&c, false);
                //channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
                channel_config_set_chain_to(&c, tdm->dma_ch_out_ctrl2);
                channel_config_set_dreq(&c, pio_get_dreq(tdm->pio, tdm->sm_dout2, true));
                dma_channel_configure(tdm->dma_ch_out_data2,
                                    &c,
                                    &tdm->pio->txf[tdm->sm_dout2],  // Destination pointer aka write address
                                    NULL,                          // Source pointer, will be set by ctrl channel
                                    OCTAL_BUFFER_SIZE,             // Number of transfers
                                    false                          // Start immediately
                );
                break;            
            case 2:
                tdm->dma_ch_out_ctrl3 = dma_claim_unused_channel(true);
                tdm->dma_ch_out_data3 = dma_claim_unused_channel(true);

            // Control blocks support double-buffering with interrupts on buffer change

                tdm->out_ctrl_blocks3[0] = &tdm->output_buffer3[0];
                tdm->out_ctrl_blocks3[1] = &tdm->output_buffer3[OCTAL_BUFFER_SIZE];
                
                // DMA tdm OUT control channel - wrap read address every 8 bytes (2 words)  --- Noe mod to 32bytes (2^5) wrap
                // Transfer 1 word at a time, to the out channel read address and trigger.  --- (8words x 4bytes (32bit) data)
                c = dma_channel_get_default_config(tdm->dma_ch_out_ctrl3);
                channel_config_set_read_increment(&c, true);
                channel_config_set_write_increment(&c, false);
                channel_config_set_ring(&c, false, 3);
                channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
                //channel_config_set_chain_to(&c,tdm->dma_ch_out_data);
                dma_channel_configure(tdm->dma_ch_out_ctrl3, 
                                    &c, 
                                    &dma_hw->ch[tdm->dma_ch_out_data3].al3_read_addr_trig, // al3_read_addr_trig, read_addr, 
                                    tdm->out_ctrl_blocks3,                                 // Source pointer
                                    1, 
                                    false
                );

                c = dma_channel_get_default_config(tdm->dma_ch_out_data3);
                channel_config_set_read_increment(&c, true);
                channel_config_set_write_increment(&c, false);
                //channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
                channel_config_set_chain_to(&c, tdm->dma_ch_out_ctrl3);
                channel_config_set_dreq(&c, pio_get_dreq(tdm->pio, tdm->sm_dout3, true));
                dma_channel_configure(tdm->dma_ch_out_data3,
                                    &c,
                                    &tdm->pio->txf[tdm->sm_dout3],  // Destination pointer aka write address
                                    NULL,                          // Source pointer, will be set by ctrl channel
                                    OCTAL_BUFFER_SIZE,             // Number of transfers
                                    false                          // Start immediately
                );
                break;           
        }
    }

    dma_channel_set_irq0_enabled(tdm->dma_ch_out_data1, true); //set the irq to first dma channel hopefully all channels stay in sync if not then need to poll which channel triggers the interrupt
    irq_set_exclusive_handler(DMA_IRQ_0, dma_handler);
    irq_set_enabled(DMA_IRQ_0, true); 
    for (size_t i = 0; i< tdm_ptr->config.out_number;i++){
        switch (i) {
            default:
                panic("Out number outside of allowed range (1 to 3)");
            case 0:
                dma_channel_start(tdm->dma_ch_out_ctrl1);  // This will trigger-start the out chan
                break;
            case 1:
                dma_channel_start(tdm->dma_ch_out_ctrl2);  // This will trigger-start the out chan
                break;
            case 2:
                dma_channel_start(tdm->dma_ch_out_ctrl3);  // This will trigger-start the out chan
                break;
       }
    }
}

static void tdm_sync_program_init(PIO pio, const tdm_config* config, pio_tdm* tdm, pio_tdm_clocks* clocks) {
    uint offset  = 0;
    tdm->pio     = pio;
    tdm->sm_mask = 0;

    calc_clocks(config, clocks);
        // Check that SCK and BCK are in perfect whole ratio
    if (!validate_sck_bck_sync(clocks)) {
            /* There are lots of possible causes for this, a few are:
             *  - You are running a system clock frequency that doesn't divide well at all into SCK or BCK
             *  - You are running a 24-bit tdm with a 256x SCK multiplier 
             *  - You have mucked with the PIO ratios or done something silly.
             */
        panic("SCK and BCK are not in sync.");
    }
    
    tdm->config  = *config;
    tdm->clocks  = *clocks; //dereference pointer 

    // SCK block (MCLK)
    tdm->sm_sck = pio_claim_unused_sm(pio, true);
    tdm->sm_mask |= (1u << tdm->sm_sck);
    offset = pio_add_program(pio, &tdm_sck_program);
    tdm_sck_program_init(pio, tdm->sm_sck, offset, tdm->config.sck_pin);
    pio_sm_set_clkdiv_int_frac(pio, tdm->sm_sck, tdm->clocks.sck_d, tdm->clocks.sck_f);
    
    for(size_t i = 0; i<tdm->config.out_number; i++){
        switch(i){
            default:
                panic("Out Number outside of allowed range (1 to 3)");

            case 0:
                // Out block 1, tdm master program generates FCK BCK TX 
                tdm->sm_dout1 = pio_claim_unused_sm(pio, true);
                tdm->sm_mask |= (1u << tdm->sm_dout1);
                offset = pio_add_program(pio, &tdm_output_clocks_program);
                tdm_out_with_clocks_program_init(pio, tdm->sm_dout1, offset, tdm->config.bit_depth, tdm->config.dout_pin[0], tdm->config.clock_pin_base);
                pio_sm_set_clkdiv_int_frac(pio, tdm->sm_dout1, tdm->clocks.bck_d, tdm->clocks.bck_f);
                break;
            case 1:
                // Out block 2, no clocks generate only TX
                tdm->sm_dout2 = pio_claim_unused_sm(pio, true);
                tdm->sm_mask |= (1u << tdm->sm_dout2);
                offset = pio_add_program(pio, &tdm_output_no_clocks_program);
                tdm_out_no_clocks_program_init(pio, tdm->sm_dout2, offset, tdm->config.bit_depth, tdm->config.dout_pin[1]);
                pio_sm_set_clkdiv_int_frac(pio, tdm->sm_dout2, tdm->clocks.bck_d, tdm->clocks.bck_f);
                break;
            case 2: 
                // Out block 3, no clocks generate only TX
                tdm->sm_dout3 = pio_claim_unused_sm(pio, true);
                tdm->sm_mask |= (1u << tdm->sm_dout3);
                offset = pio_add_program(pio, &tdm_output_no_clocks_program);
                tdm_out_no_clocks_program_init(pio, tdm->sm_dout3, offset, tdm->config.bit_depth, tdm->config.dout_pin[2]);
                pio_sm_set_clkdiv_int_frac(pio, tdm->sm_dout3, tdm->clocks.bck_d, tdm->clocks.bck_f);
                break;
        }
    }
}

float tdm_program_start_synched(PIO pio, const tdm_config* config, pio_tdm* tdm, pio_tdm_clocks* clocks, pio_tdm_calib* calibration, pio_tdm_data* data ) {
   
    if (((uint32_t)tdm & 0x7) != 0) {
        panic("pio_tdm argument must be 8-byte aligned!");
    }

    set_tdm_ptr(tdm);
    
    tdm->OutBufPtr1 = &tdm->output_buffer1[0];
    tdm->OutBufPtr2 = &tdm->output_buffer2[0];
    tdm->OutBufPtr3 = &tdm->output_buffer3[0];
    tdm->data = data;
    tdm_sync_program_init(pio, config, tdm, clocks);

    set_calib_data(tdm, calibration);

    dma_double_buffer_init(tdm, tdm_dma_in_handler);
    pio_enable_sm_mask_in_sync(tdm->pio, tdm->sm_mask);
    float process_fs = tdm->clocks.fs_attained/(float)tdm->config.down_factor;
    return(process_fs); //clocks->fs_attained
}

