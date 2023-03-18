#include <vector>

#ifndef DATASET_H
#define DATASET_H
class DataSet {
    public:
        // N: # of samples in the data set
        // I: # of inputs in each sample
        // O: # of outputs in each sample
        int N, I, O;
        std::vector<std::vector<double>> inputs;
        std::vector<std::vector<double>> outputs;

        DataSet(const char * fName);
};

#endif