// Copyright (c) 2024 Noe Heuclin
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#include "../inc/PCM1681.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"

/******************************************************************************/
/****************************** REGISTER MAPPING ******************************/
/******************************************************************************/
/* FMTx bits register */
#define PCM1681_FORMAT_REG 9
#define PCM1681_TDM_FORMAT_MASK 0b00000111 //b3-b2-b1-b0 are FMTx bitsset to 0111 for LJ tdm 

#define PCM1681_MUTE_REG 7
#define PCM1681_ENABLE_REG 8

/* Software reset register */
#define PCM1681_RESET_REG  10
#define PCM1681_RESET_MASK 0b10000000 

#define PCM1681_OVERSAMPLING_REG 12
#define PCM1681_WIDE_SAMPLING_MASK 0b10000000 
// Write 1 byte to the specified register
void i2c_reg_write(i2c_inst_t *i2c, const uint8_t addr, const uint8_t reg, uint8_t *buf, const uint8_t nbytes) {

    uint8_t msg[nbytes + 1];

    // Check to make sure caller is sending 1 or more bytes
   /*if (nbytes < 1) {
        return 0;
    } */

    // Append register address to front of data packet
    msg[0] = reg;
    for (int i = 0; i < nbytes; i++) {
        msg[i + 1] = buf[i];
    }

    // Write data to register(s) over I2C
    i2c_write_blocking(i2c, addr, msg, (nbytes + 1), false);
    
}
// Read byte(s) from specified register. If nbytes > 1, read from consecutive
// registers.
void i2c_reg_read(i2c_inst_t *i2c, uint8_t addr, uint8_t reg, uint8_t *buf, const uint8_t nbytes) {

    // Check to make sure caller is asking for 1 or more bytes
    /*if (nbytes < 1) {
        return 0;
    }*/

    // Read data from register(s) over I2C

    i2c_write_blocking(i2c, addr, &reg, 1, true);
    
    i2c_read_blocking(i2c, addr, buf, nbytes, false);
}

uint8_t PCM1681_read_reg_i2c(uint8_t reg, PCM1681_t *octoDAC){
    uint8_t value;
	i2c_reg_read(octoDAC->i2c, octoDAC->PCM1681_addr, reg, &value, 1);
    
	return value;
}

void PCM1681_write_reg_i2c(uint8_t reg, uint8_t data, PCM1681_t *octoDAC){
	i2c_reg_write(octoDAC->i2c, octoDAC->PCM1681_addr, reg, &data,1);
}

void PCM1681_modify_reg_i2c(uint8_t reg, uint8_t mask, PCM1681_t *octoDAC){ //only reads and toggle 0 to 1 in mask then write
    uint8_t val = PCM1681_read_reg_i2c(reg, octoDAC);
    val=val|mask;
    PCM1681_write_reg_i2c(reg, val, octoDAC);
}

void PCM1681_reset(PCM1681_t *octoDAC){
    uint8_t reg_val=0b10000000;
    PCM1681_modify_reg_i2c(PCM1681_RESET_REG,PCM1681_RESET_MASK,octoDAC);
    //PCM1681_write_reg_i2c(PCM1681_RESET_REG, reg_val, octoDAC);
    sleep_ms(20);

    PCM1681_read_reg_i2c(PCM1681_RESET_REG,octoDAC);
}

void PCM1681_set_mode(PCM1681_t *octoDAC){
    if(octoDAC->mode==PCM1681_MODE_LJ_TDM){ //only mode implemented for now
        PCM1681_modify_reg_i2c(PCM1681_FORMAT_REG,PCM1681_TDM_FORMAT_MASK,octoDAC);
    }
}

void PCM1681_init(uint8_t addr, i2c_inst_t *i2c, PCM1681_t* octoDAC) {
    
	octoDAC->PCM1681_addr = addr;
	octoDAC->i2c = i2c;
	octoDAC->bit_depth =   PCM1681_CONFIG_BIT_DEPTH_24B_32B_FRAME;
	octoDAC->sample_rate = PCM1681_CONFIG_FS_48K;
    octoDAC->mode=         PCM1681_MODE_LJ_TDM;
    
}

void PCM1681_mute(PCM1681_t *octoDAC){
    PCM1681_write_reg_i2c(PCM1681_MUTE_REG, 0xFF, octoDAC);
}

void PCM1681_disable_outputs(PCM1681_t *octoDAC){
    
    /*uint8_t reg_val=0b00000011;
    PCM1681_modify_reg_i2c(19,reg_val,octoDAC);*/

    PCM1681_write_reg_i2c(19, 0x03, octoDAC);
    PCM1681_write_reg_i2c(PCM1681_ENABLE_REG, 0xFF, octoDAC);
}

void PCM1681_enable_outputs(PCM1681_t *octoDAC){
    
    /*uint8_t reg_val=0b00000000;
    PCM1681_modify_reg_i2c(19,reg_val,octoDAC);*/
    PCM1681_write_reg_i2c(19, 0x00, octoDAC);
    PCM1681_write_reg_i2c(PCM1681_ENABLE_REG, 0x00, octoDAC);
}

void PCM1681_unmute(PCM1681_t *octoDAC){
    PCM1681_write_reg_i2c(PCM1681_MUTE_REG, 0x00, octoDAC);
}

void PCM1681_wideoversampling(PCM1681_t *octoDAC){
    PCM1681_modify_reg_i2c(PCM1681_OVERSAMPLING_REG,PCM1681_WIDE_SAMPLING_MASK,octoDAC);
}

void PCM1681_setup(uint8_t device_ID, i2c_inst_t *i2c, PCM1681_t *octoDAC){

    PCM1681_init(device_ID, i2c, octoDAC);
    PCM1681_reset(octoDAC);
    PCM1681_mute(octoDAC);
    PCM1681_disable_outputs(octoDAC);
    PCM1681_set_mode(octoDAC);
    PCM1681_wideoversampling(octoDAC);

}

void PCM1681_start(PCM1681_t *octoDAC){
    PCM1681_enable_outputs(octoDAC);
    PCM1681_unmute(octoDAC);
}