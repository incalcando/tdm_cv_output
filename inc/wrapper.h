#ifndef WRAPPER_H
#define WRAPPER_H

#define MLP_INS 3
#define MLP_OUTS 6
#define HL_1 8
#define HL_2 7
#define HL_3 6
#define HL_4 8

#ifdef __cplusplus
extern "C" {
#endif

void init_blink();
void init_mlp();
void fill_input_vec(int idx, float f);
float* generate_output(float ins[MLP_INS]);
float generate_channel_output(int idx);
bool call_blink(int idx);
void set_blink_dur(int idx, float dur);
void set_blink_duration(float* dur);
void use_output(float f);

#ifdef __cplusplus
}
#endif

#endif // WRAPPER_H