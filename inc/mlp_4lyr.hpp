#ifndef MLP_4LYR_HPP
#define MLP_4LYR_HPP


#include <iostream>
#include <array> // Added for  idsp::c_vector
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <type_traits>
#include <numeric>

#include "idsp_addons.hpp"

constexpr size_t USE_PRESET = 1;

typedef float mlp_float_t;
// using mlp_float_t = double;


template <size_t IN_SIZE, size_t H1_SIZE, size_t H2_SIZE, size_t H3_SIZE, size_t H4_SIZE, size_t OUT_SIZE>
class MLP_4LYR {
public:
    MLP_4LYR(size_t epochs);
    idsp::c_vector<mlp_float_t, OUT_SIZE> forward(const idsp::c_vector<mlp_float_t, IN_SIZE>& inputs, bool linear_output = false);
    void train(
            const idsp::c_vector<idsp::c_vector<mlp_float_t, IN_SIZE>, 99>& inputs, 
            const idsp::c_vector<idsp::c_vector<mlp_float_t, OUT_SIZE>, 99>& targets, 
            mlp_float_t learning_rate, int epochs
            );
    // void update(
    //         const idsp::c_vector<mlp_float_t, IN_SIZE>& input, 
    //         const idsp::c_vector<mlp_float_t, OUT_SIZE>& target, 
    //         mlp_float_t learning_rate
    //         );
    void update(mlp_float_t learning_rate, int epochs);
    idsp::c_vector<mlp_float_t, OUT_SIZE> generate_output();
    idsp::c_vector<mlp_float_t, OUT_SIZE> generate_output_from_input(idsp::c_vector<mlp_float_t, IN_SIZE> ins);
    float generate_channel_output(int idx);
    void fill_input_vec(int idx, mlp_float_t f) { this->net_in[idx] = f; this->generate_output(); }
    void clear_data();
    void accumulate_data(const idsp::c_vector<mlp_float_t, IN_SIZE>& inputs, const idsp::c_vector<mlp_float_t, OUT_SIZE>& targets);
    void retrain(mlp_float_t learning_rate, int epochs);
    void set_training_amount(size_t amount) { training_epochs = amount; }
    idsp::c_vector<mlp_float_t, IN_SIZE> find_closest_data_set(const idsp::c_vector<mlp_float_t, OUT_SIZE>& target);

private:
    size_t training_epochs;

    idsp::c_vector<mlp_float_t, IN_SIZE> net_in;

    idsp::c_vector<idsp::c_vector<mlp_float_t, H1_SIZE>, IN_SIZE> weight_in_h1;
    idsp::c_vector<idsp::c_vector<mlp_float_t, H2_SIZE>, H1_SIZE> weight_h1_h2;
    idsp::c_vector<idsp::c_vector<mlp_float_t, H3_SIZE>, H2_SIZE> weight_h2_h3;
    idsp::c_vector<idsp::c_vector<mlp_float_t, H4_SIZE>, H3_SIZE> weight_h3_h4;
    idsp::c_vector<idsp::c_vector<mlp_float_t, OUT_SIZE>, H4_SIZE> weight_h4_out;

    idsp::c_vector<mlp_float_t, H1_SIZE> bias_h1;
    idsp::c_vector<mlp_float_t, H2_SIZE> bias_h2;
    idsp::c_vector<mlp_float_t, H3_SIZE> bias_h3;
    idsp::c_vector<mlp_float_t, H4_SIZE> bias_h4;
    idsp::c_vector<mlp_float_t, OUT_SIZE> bias_out;

    idsp::c_vector<idsp::c_vector<mlp_float_t, IN_SIZE>, 99> accumulated_inputs;
    idsp::c_vector<idsp::c_vector<mlp_float_t, OUT_SIZE>, 99> accumulated_targets;
    size_t accumulated_data_size;

    void initialize_weights_and_biases();

    
    // Activation functions
    inline mlp_float_t tanh_activation(mlp_float_t x) {
        return std::tanh(x);
    }

    inline mlp_float_t tanh_derivative(mlp_float_t x) {
        return 1.0 - std::tanh(x) * std::tanh(x);
    }

    inline mlp_float_t get_random_bipolar_normalised() {
        return ((mlp_float_t)rand() / RAND_MAX) * 2 - 1;
    }

    // Mean Squared Error loss function
    mlp_float_t mean_squared_error(const  idsp::c_vector<mlp_float_t, 6>& predicted, const  idsp::c_vector<mlp_float_t, 6>& target) {  
        mlp_float_t error = 0.0;
        for (size_t i = 0; i < predicted.size(); ++i) {
            error += (predicted[i] - target[i]) * (predicted[i] - target[i]);
        }
        return error / predicted.size();
    }
};



// Include the template implementation file
#include "mlp_4lyr.tpp"

#endif // MLP_4LYR_HPP