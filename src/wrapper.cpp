#include "wrapper.h"
#include "idsp_addons.hpp"
#include "blinker.hpp"
#include "mlp_4lyr.hpp"

static Blinker* blinker[2] = {nullptr, nullptr};

static MLP_4LYR<MLP_INS, HL_1, HL_2, HL_3, HL_4, MLP_OUTS>* mlp = nullptr;
// static MLP_4LYR<MLP_INS, HL_1, HL_2, HL_3, HL_4, MLP_OUTS> mlp2(1000);

void init_mlp() {
    if (mlp == nullptr) {
        mlp = new MLP_4LYR<MLP_INS, HL_1, HL_2, HL_3, HL_4, MLP_OUTS>(1000);
    }
}

void fill_input_vec(int idx, float f) {
    if (mlp != nullptr) {
        mlp->fill_input_vec(idx, (mlp_float_t)f);
    }
}


float* generate_output(float ins[MLP_INS]) {
    idsp::c_vector<mlp_float_t, 3> in_vec {ins[0], ins[1], ins[2]};
    idsp::c_vector<mlp_float_t, 6> out_vec {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    if (mlp != nullptr) {
        out_vec = mlp->generate_output_from_input(in_vec);
    }
    static float out[MLP_OUTS];
    for (int i = 0; i < MLP_OUTS; ++i) {
        out[i] = (out_vec[i] + 1) * 0.5;
    }
    return out;
}

float generate_channel_output(int idx) {
    if (mlp != nullptr) {
        return mlp->generate_channel_output(idx);
    }
    return 0.0;
}

void init_blink() {
    for(int i = 0; i < 2; i++) {
        if (blinker[i] == nullptr) {
            blinker[i] = new Blinker();
            blinker[i]->init();
        }
    }
}

bool call_blink(int idx) {
    if (blinker[idx] != nullptr) {
        return blinker[idx]->blink();
    }
    return 0;
}

void set_blink_dur(int idx, float dur) {
        if (blinker[idx] != nullptr) {
            blinker[idx]->setDur((uint)dur);
        }
}

void set_blink_duration(float* dur) {
    int ch[2] = {0, 4};
    for(int i = 0; i < 2; i++) {
        if (blinker[i] != nullptr) {
            blinker[i]->setDur((uint)(dur[ch[i]] * 1000000));
        }
    }
}

// void use_output(std::array<float, 3> ins) {
//     int count = 0;
//     if (mlp != nullptr) {
//         if(count++ > 100000) {
//             count = 0;
//             fill_input_vec(0, ins[0]);
//             fill_input_vec(1, ins[1]);
//             fill_input_vec(2, ins[2]);
//             float out = generate_channel_output(0);
//             out = out > 1.0 ? 1.0 : out < 0.01 ? 0.01 : out;
//             set_blink_dur(0, generate_channel_output(0) * 10000000);
//         }
//     }
// }



// float get_float(){
//     if(exist){
//         return instrument_ptr->get_float();
//     }
//     return 0.0;
// }


// void prepare_tdm(){
//     std::array<float, 64> data0;
//     std::array<float, 64> data1;
//     std::array<float, 64> data2;
//     if(exist){
//         data0 = instrument_ptr->get_output()[0];
//         data1 = instrument_ptr->get_output()[1];
//     }

//     for(in i=0; i<64; i++){
//         tdm_write_sample(data0[i], device, 3, i);
//         tdm_write_sample(data1[i], device, 2, i);
//     }
// }


// float get_float(){
//     float val = 0;
//     if(exist){
//         val = instrument_ptr->get_float();
//     }
//     return val;
// }

// void tdm_write(){
//     if(exist){
//         tdm_write_sample(getfloat());
//     }
// }