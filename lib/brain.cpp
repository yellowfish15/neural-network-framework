#include <cstdio>
#include <vector>
#include "brain.hpp"
#include "dataset.hpp"
#include "utilities.hpp"

BasicModel::BasicModel(const std::vector<int>& config, const double L = 0.01) : numLayers(config.size()), sizes(config), lRate(L) {
    for(int i = 0; i < numLayers; i++) {
        neurons.push_back(new ColumnVector(config[i]));
        neurons[i]->randomize();
        errors.push_back(new ColumnVector(config[i]));
    }
    for(int i = 1; i < numLayers; i++) {
        biases.push_back(new ColumnVector(config[i]));
        weights.push_back(new Matrix(config[i], config[i-1]));
        biases[i-1]->randomize();
        weights[i-1]->randomize();
    }
}

void BasicModel::predict(const std::vector<double>& input) {
    neurons[0]->set(input);
    for(int i = 1; i < numLayers; i++) {
        multiply(weights[i-1], neurons[i-1], neurons[i]);
        add(biases[i-1], neurons[i]);
        sigmoid(neurons[i]);
    }
}

void BasicModel::train(const std::vector<double>& input, const std::vector<double>& output) {
    BasicModel::predict(input);
    errors[numLayers-1]->set(output);
    subtract(neurons[numLayers-1], errors[numLayers-1], errors[numLayers-1]);

    // backpropagation
    for(int lx = numLayers-1; lx > 0; lx--) {
        dsigmoid(neurons[lx]);
        multiply(errors[lx], neurons[lx]);

        // calculate error for previous level
        for(int i = 0; i < sizes[lx-1]; i++) {
            double partials = 0;
            for(int j = 0; j < sizes[lx]; j++)
                partials += neurons[lx]->matrix[j][0]*weights[lx-1]->matrix[j][i];
            errors[lx-1]->matrix[i][0] = partials;
        }
        for(int i = 0; i < sizes[lx]; i++) {
            double delta = lRate * neurons[lx]->matrix[i][0];
            for(int j = 0; j < sizes[lx-1]; j++)
                weights[lx-1]->matrix[i][j] -= delta*neurons[lx-1]->matrix[j][0];
            biases[lx-1]->matrix[i][0] -= delta;
        }
    }
}

// K: # of data sets
// epochs: # of epochs to run (finish entire data set)
void BasicModel::fit(const DataSet& data, int epochs) {
    for(int i = 0; i < epochs; i++)
        for(int k = 0; k < data.N; k++)
            BasicModel::train(data.inputs[k], data.outputs[k]);
}

void BasicModel::predictAndPrint(const std::vector<double>& input) {
    BasicModel::predict(input);

    printf("->");
    for(int i = 0; i < input.size(); i++)
        printf(" %.4f", input[i]);
    printf("\n<-");
    for(int i = 0; i < sizes[numLayers-1]; i++)
        printf(" %.4f", neurons[numLayers-1]->matrix[i][0]);
    printf("\n\n");
}