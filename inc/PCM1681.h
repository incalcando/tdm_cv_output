// Copyright (c) 2024 Noe Heuclin
//
// This software is released under the MIT License. 
// https://opensource.org/licenses/MIT

#ifndef __PCM1681_H
#define __PCM1681_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

typedef enum {
	OUT_0 = 0,
	OUT_1,
    OUT_2,
    OUT_3,
    OUT_4,
    OUT_5,
    OUT_6,
    OUT_7,
	NUM_OUTPUTS
} PCM1681_output_num_t;

typedef enum {
	PCM1681_CONFIG_FS_8K = 8000,
	PCM1681_CONFIG_FS_12K = 12000,
	PCM1681_CONFIG_FS_16K = 16000,
	PCM1681_CONFIG_FS_24K = 24000,
	PCM1681_CONFIG_FS_32K = 32000,
	PCM1681_CONFIG_FS_44_1K = 44100,
	PCM1681_CONFIG_FS_48K = 48000,
} PCM1681_fs_t;

typedef enum {
	PCM1681_CONFIG_BIT_DEPTH_16B_16B_FRAME = 0,
	PCM1681_CONFIG_BIT_DEPTH_24B_32B_FRAME,
} PCM1681_bit_depth_t;

typedef enum {
	PCM1681_MODE_LJ_TDM = 0,
	PCM1681_MODE_LJ_I2S,
} PCM1681_mode_t;

typedef struct {
	uint8_t PCM1681_addr;
	i2c_inst_t *i2c;
	PCM1681_fs_t sample_rate;
	PCM1681_bit_depth_t bit_depth;
    PCM1681_mode_t mode;
} PCM1681_t;

void i2c_reg_write(i2c_inst_t *i2c, 
                const uint8_t addr, 
                const uint8_t reg, 
                uint8_t *buf,
                const uint8_t nbytes);

void i2c_reg_read(   i2c_inst_t *i2c,
                const uint8_t addr,
                const uint8_t reg,
                uint8_t *buf,
                const uint8_t nbytes);

uint8_t PCM1681_read_reg_i2c(uint8_t reg, PCM1681_t *octoDAC);

void PCM1681_write_reg_i2c(uint8_t reg, uint8_t data, PCM1681_t *octoDAC);

void PCM1681_modify_reg_i2c(uint8_t reg, uint8_t mask, PCM1681_t *octoDAC); //only reads and toggle 0 to 1 in mask then write

/* Perform a software reset */
void PCM1681_reset(PCM1681_t *octoDAC);

void PCM1681_set_mode(PCM1681_t *octoDAC);

void PCM1681_mute(PCM1681_t *octoDAC);

void PCM1681_disable_outputs(PCM1681_t *octoDAC);

void PCM1681_enable_outputs(PCM1681_t *octoDAC);

void PCM1681_unmute(PCM1681_t *octoDAC);

void PCM1681_wideoversampling(PCM1681_t *octoDAC);

void PCM1681_init(uint8_t device_ID, i2c_inst_t *i2c, PCM1681_t *octoDAC); //since we can set the address in a number of ways

void PCM1681_setup(uint8_t device_ID, i2c_inst_t *i2c, PCM1681_t *octoDAC);

void PCM1681_start(PCM1681_t *octoDAC);

#endif //__PCM1681_H