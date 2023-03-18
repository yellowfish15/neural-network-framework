#include "brain.hpp"
#include "dataset.hpp"
#include <cstdio>
#include "utilities.hpp"

BasicModel::BasicModel(const int N, const int * S, const double L = 0.01) : numLayers(N), sizes(S), lRate(L) {
    for(int i = 0; i < numLayers; i++) {
        neurons.push_back(ColumnVector(sizes[i]));
        neurons[i].randomize();
        errors.push_back(ColumnVector(sizes[i]));
    }
    for(int i = 1; i < numLayers; i++) {
        biases.push_back(ColumnVector(sizes[i]));
        weights.push_back(Matrix(sizes[i], sizes[i-1]));
        biases[i-1].randomize();
        weights[i-1].randomize();
    }
}

void BasicModel::predict(const std::vector<double>& input) {
    neurons[0].set(input);
    for(int i = 1; i < numLayers; i++) {
        multiply(weights[i-1], neurons[i-1], neurons[i]);
        add(biases[i-1], neurons[i]);
        sigmoid(neurons[i]);
    }
}

void BasicModel::train(const std::vector<double>& input, const std::vector<double>& output) {
    BasicModel::predict(input);
    errors[numLayers-1].set(output);
    subtract(neurons[numLayers-1], errors[numLayers-1], errors[numLayers-1]);

    // backpropagation
    for(int lx = numLayers-1; lx > 0; lx--) {
        dsigmoid(neurons[lx]);
        multiply(errors[lx], neurons[lx]);

        // calculate error for previous level
        for(int i = 0; i < sizes[lx-1]; i++) {
            double partials = 0;
            for(int j = 0; j < sizes[lx]; j++)
                partials += neurons[lx].matrix[j][0]*weights[lx-1].matrix[j][i];
            errors[lx-1].matrix[i][0] = partials;
        }
        for(int i = 0; i < sizes[lx]; i++) {
            double delta = lRate * neurons[lx].matrix[i][0];
            for(int j = 0; j < sizes[lx-1]; j++)
                weights[lx-1].matrix[i][j] -= delta*neurons[lx-1].matrix[j][0];
            biases[lx-1].matrix[i][0] -= delta;
        }
    }
}

// K: # of data sets
// epochs: # of epochs to run (finish entire data set)
void BasicModel::fit(const DataSet& data, int epochs) {
    for(int i = 0; i < epochs; i++)
        for(int k = 0; k < data.N; k++)
            BasicModel::train(data.inputs[k], data.inputs[k]);
}

void BasicModel::predictAndPrint(const std::vector<double>& input) {
    BasicModel::predict(input);
    for(int i = 0; i < sizes[numLayers-1]; i++)
        printf("%f ", neurons[numLayers-1].matrix[i][0]);
    printf("\n");
}

// when you are finished, please free the associated memroy
void BasicModel::destruct() {
    for(int i = 0; i < numLayers; i++) {
        neurons[i].destruct();
        errors[i].destruct();
    }
    for(int i = 0; i < numLayers-1; i++) {
        biases[i].destruct();
        weights[i].destruct();
    }
}