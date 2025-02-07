#include "pins.h"  // aka system def
#include "TDM_output.h"
#include "PCM1681.h"
#include "pico/stdlib.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "hardware/i2c.h"
#include "hardware/irq.h"
#include "hardware/pio.h"
#include "hardware/gpio.h" //needed??
#include "hardware/adc.h"

#include "wrapper.h"
#include "rp2350_adc.h"


// The Important Stuff
__attribute__((aligned(8))) pio_tdm tdm;
const tdm_config tdm_config_default = {24000,                                 // hardware FS, ends up being FCLK frequency (tested from 8000 to 24000 with downsampling =1)
                                       256,                                   // MCLK to hardware FS ratio. 256 for x64 oversampling (tested)/ 512 for x128 (untested yet)
                                       1,                                     // processing downsampling factor (process fs= fardwareFS/downfactor) leave to 1 for now. 
                                       32,                                    // bit depth
                                       TDM_MCLK_PIN,                          // MCLK pin                          
                                       TDM_FCLK_PIN,                          // FCLK pin, BCK pin is next consecutive one 
                                       {TDM_TX_PIN,TDM_TX2_PIN,TDM_TX2_PIN},  // Dout pins, list of 3 ints. if using less than 3 just repeat the last used dout pin
                                       1                                      // number of ICs (1 to 3) only up to 2 with I2C config
                                       };



pio_tdm_calib calibration={{{50000000, 50000000, 50000000, 50000000, 50000000, 50000000, 50000000, 50000000}, //IC1 0V calib data
                            {-1260000000, -1260000000, -1260000000, -1260000000, -1260000000, -1260000000, -1260000000, -1260000000,}}, //IC1 5V calib data    
                            {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}}, //IC2 {{0V},{5V}} calib data
                            {{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}}  //IC3 {{0V},{5V}} calib data
                            }; //// Create one for the whole pio object (up to 3 ICs) IC 1 is filled with average values of current prototype. 

pio_tdm_clocks tdm_clocks_default={0,0,0,0,0,0,0}; //array to store attained clock frequencies. Create one for the whole pio object (up to 3 ICs)
pio_tdm_data   data;     // Create one for the whole pio object (up to 3 ICs)
PCM1681_t      octoDAC1; // Create one of these per 8 channel used (1 IC)

//Cortex Debug Probes
// volatile static int32_t see_val=0; 
// volatile static int32_t see_val2=0; 
// volatile static float see_float=0.f;
// bool on = 0;

static float process(void){}; //dummy DSP function

int main()
{
    //set_sys_clock_khz(132000, true); //required for 48kHz clocking. actually might be for 2040 only
    stdio_init_all();

    //setup I2C port
    i2c_init(TDM_I2C_PORT, 100 * 1000);
    gpio_set_function(TDM_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(TDM_SCL_PIN, GPIO_FUNC_I2C);
    gpio_set_pulls(TDM_SDA_PIN, true, false);
    gpio_set_pulls(TDM_SCL_PIN, true, false);
    gpio_set_drive_strength(TDM_SDA_PIN, GPIO_DRIVE_STRENGTH_12MA);
    gpio_set_drive_strength(TDM_SCL_PIN, GPIO_DRIVE_STRENGTH_12MA);
    gpio_set_slew_rate(TDM_SDA_PIN, GPIO_SLEW_RATE_FAST);
    gpio_set_slew_rate(TDM_SCL_PIN, GPIO_SLEW_RATE_FAST);

    //start TDM clocks
    float process_fs = tdm_program_start_synched(pio0, &tdm_config_default, &tdm, &tdm_clocks_default, &calibration, &data); 
    sleep_ms(50); //let the octodac settle after clocks started
    
    uint8_t dac_addr = 0b01001100; // octo dac I2C address, alt is 0b01001101 is using a 2nd IC. using 3 IC will need either HW control or SPI
    PCM1681_setup(dac_addr,TDM_I2C_PORT, &octoDAC1); //setup octodac over I2C
    sleep_ms(50); // wait for clocks to settle

    //do other setup for audio CV etc


    //start the octodacs this has to be done after all clocking is initialised 
    PCM1681_start(&octoDAC1); 

    init_adc(); //setup the ADC for CV input 0 (pin 26) and CV input 1 (pin 27)

/// JUST A SIGN OF LIFE ROUTINE FOR THE PICO2 BOARD
    gpio_init(25);
    gpio_set_dir(25, GPIO_OUT);
    gpio_init(21);
    gpio_set_dir(21, GPIO_OUT);

    // init_blink_dur(25, 1000000);
    init_blink();

    // gpio_put(25, 1);

    init_mlp(); 

    while(1) {

        static int count = 0;
        gpio_put(25,call_blink(0));
        gpio_put(21,call_blink(1));

        // set_blink_dur(adc_read() * 100);

        if(count > 5000) {
            count = 0;
            float ins[3] = {(float)(read_adc_ch(0) / 4095.0), 
                            (float)(read_adc_ch(1) / 4095.0), 
                            0.0};
            // set_blink_dur(0, (generate_output(ins)[0] * 1000000));
            // set_blink_dur(1, (generate_output(ins)[1] * 1000000));
            set_blink_duration(generate_output(ins));
        }

        count++;

        tdm_interleave(&tdm); //this outputs data to pio through dma at the required rate and sets the MoreData flag to request from DSP engine

        if (tdm.MoreData==1){
            for(size_t j = 0; j<TDM_BUFFER_FRAMES; j++) { //j is frame number in block
                for (size_t i = 0; i < TDM_CHANNELS ; i++) {  //i is channel number in frame
                    data.tdm_stream1[j][i]= process(); // fill the DMA buffer (half of double buffer)

                }
            }
        tdm.MoreData=0; //set the buffer full flag 
        }
    }
    return 0;
}
