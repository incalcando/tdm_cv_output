/* TDM_output.h
    written by Noe Heuclin 2025
*/
#include <stdio.h>
#include "hardware/pio.h"
#include"pins.h"

#ifndef TDM_TEST_TDM_H
#define TDM_TEST_TDM_H


typedef struct tdm_config {
    uint32_t fs;
    uint32_t sck_mult;
    uint8_t  down_factor;
    uint8_t  bit_depth;
    uint8_t  sck_pin;
    uint8_t  clock_pin_base; // FCK pin, BCK must be the next consecutive pin
    uint8_t  dout_pin[3];  
    uint8_t  out_number;
}tdm_config;

typedef struct pio_tdm_calib {
    int32_t IC1_calib[2][8];
    int32_t IC2_calib[2][8];
    int32_t IC3_calib[2][8];
}pio_tdm_calib;

typedef struct pio_tdm_clocks {
    // Clock computation results
    float fs_attained;
    float sck_pio_hz;
    float bck_pio_hz;

    // PIO divider ratios to obtain the computed clocks above
    uint16_t sck_d;
    uint8_t  sck_f;
    uint16_t bck_d;
    uint8_t  bck_f;
}pio_tdm_clocks;

typedef struct pio_tdm_data{
    float tdm_stream1[TDM_BUFFER_FRAMES][TDM_CHANNELS]; // array to store data to interleave and send to octodac
    float tdm_stream2[TDM_BUFFER_FRAMES][TDM_CHANNELS]; 
    float tdm_stream3[TDM_BUFFER_FRAMES][TDM_CHANNELS]; 
}pio_tdm_data;

// NOTE: Use __attribute__ ((aligned(8))) on this struct or the DMA wrap won't work!
// WARNING do not move any variable in this list, the order in which they're listed matters to the data alignmenent for DMA
typedef struct pio_tdm {
    PIO        pio;
    uint8_t    sm_mask;
    uint8_t    sm_sck;

    uint       dma_ch_out_ctrl1;
    uint       dma_ch_out_data1;
    int32_t*   out_ctrl_blocks1[2]; 
    int32_t    output_buffer1[OCTAL_BUFFER_SIZE * 2];

    uint       dma_ch_out_ctrl2;
    uint       dma_ch_out_data2;
    int32_t*   out_ctrl_blocks2[2]; 
    int32_t    output_buffer2[OCTAL_BUFFER_SIZE * 2];

    uint       dma_ch_out_ctrl3;
    uint       dma_ch_out_data3;
    int32_t*   out_ctrl_blocks3[2]; 
    int32_t    output_buffer3[OCTAL_BUFFER_SIZE * 2];

    int32_t*   OutBufPtr1;
    int32_t*   OutBufPtr2;
    int32_t*   OutBufPtr3;

    uint8_t    sm_dout1;
    uint8_t    sm_dout2;
    uint8_t    sm_dout3;

    volatile uint8_t Ready_to_Interleave; //fairly certain this doesn't need to be volatile anymore
    volatile uint8_t MoreData;

    tdm_config     config;
    pio_tdm_clocks clocks;
    pio_tdm_calib  calibration;
    pio_tdm_data*   data;

    float  calibration1[2][8];
    float  calibration2[2][8];
    float  calibration3[2][8];
}pio_tdm;


static void set_tdm_ptr(pio_tdm* ptr);
static bool validate_sck_bck_sync(pio_tdm_clocks* clocks);
//void tdm_out_serialise_data(float** input, float** calib, int32_t* output,  size_t num_frames);
static void set_calib_data(pio_tdm* tdm, pio_tdm_calib* calibration);
void tdm_interleave(pio_tdm* tdm);
void tdm_interleave2(pio_tdm* tdm);
static void tdm_HalfCplt_Callback(void);
static void tdm_Cplt_Callback(void);
static void tdm_dma_in_handler(void);
static void dma_double_buffer_init( pio_tdm* tdm, void (*dma_handler)(void));
static void tdm_sync_program_init(PIO pio, const tdm_config* config, pio_tdm* tdm, pio_tdm_clocks* clocks);
float tdm_program_start_synched(PIO pio, const tdm_config* config, pio_tdm* tdm, pio_tdm_clocks* clocks,pio_tdm_calib* calibration, pio_tdm_data* data);


#endif  // TDM_TEST_TDM_H
