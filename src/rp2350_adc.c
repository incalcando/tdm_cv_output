#include "rp2350_adc.h"

void init_adc() {
    adc_init();
    adc_gpio_init(26); // GPIO 26 is connected to ADC0  
    adc_gpio_init(27); // GPIO 26 is connected to ADC0  
  
}

int read_adc_ch(int adc) {
    adc_select_input(adc); // Select ADC0
    return adc_read();
}
