#include "dataset.hpp"
#include "utilities.hpp"
#include <vector>

// header file for brain library
#ifndef BRAIN_H
#define BRAIN_H

class BasicModel {
    const double lRate; // learning rate
    const int numLayers; // includes input, hidden, and output layers
    const int * sizes; // sizes of each layer
    std::vector<ColumnVector> neurons;
    std::vector<ColumnVector> biases;
    std::vector<Matrix> weights;
    // for backpropagation
    std::vector<ColumnVector> errors; // errors in each layer

    public:
        BasicModel(const int N, const int * S, const double L);
        void predict(const std::vector<double>& input);
        void train(const std::vector<double>& input, const std::vector<double>& output);
        void fit(const DataSet& data, int epochs);
        void predictAndPrint(const std::vector<double>& input);
        void destruct();
};

#endif