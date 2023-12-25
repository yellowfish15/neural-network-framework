#include <vector>
#include "dataset.hpp"
#include "utilities.hpp"

// header file for brain library
#ifndef BRAIN_H
#define BRAIN_H

// Basic Feedforward Neural Network
class BasicModel {
    const double lRate; // learning rate
    const std::vector<int> sizes; // number of nodes in each layer
    const int numLayers; // includes input, hidden, and output layers
    // const int * sizes; // sizes of each layer
    std::vector<ColumnVector*> neurons;
    std::vector<ColumnVector*> biases;
    std::vector<Matrix*> weights;
    // for backpropagation
    std::vector<ColumnVector*> errors; // errors in each layer

    public:
        // L = learning rate
        BasicModel(const std::vector<int>& config, const double L);

        ~BasicModel() {
            for(int i = 0; i < numLayers; i++) {
                delete neurons[i];
                delete biases[i];
                delete weights[i];
                delete errors[i];
            }
        }

        void predict(const std::vector<double>& input);
        void train(const std::vector<double>& input, const std::vector<double>& output);
        void fit(const DataSet& data, int epochs);
        void predictAndPrint(const std::vector<double>& input);
};

#endif