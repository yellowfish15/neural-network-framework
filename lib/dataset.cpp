#include <cstdlib>
#include <cstdio>
#include "dataset.hpp"
#include <vector>

DataSet::DataSet(const char * fName) {
    FILE *fp;
    if((fp = fopen(fName, "r+")) == NULL) {
        fprintf(stderr, "The specified file does not exist!\n");
        std::exit(1);
    }
    if(fp == NULL) {
        fprintf(stderr, "Error reading file!\n");
        std::exit(1);
    }
    int ret = fscanf(fp, "%d %d %d", &N, &I, &O);
    if(ret != 3) {
        fprintf(stderr, "Invalid metadata format in data file, line 1!\n");
        std::exit(1);
    }
    // read each sample
    for(int sample = 0; sample < N; sample++) {
        std::vector<double> input(I);
        std::vector<double> output(O);
        
        // read input of each sample
        for(int i = 0; i < I; i++)
            fscanf(fp, "%lf", &input[i]);
        for(int i = 0; i < O; i++)
            fscanf(fp, "%lf", &output[i]);
        
        inputs.push_back(input);
        outputs.push_back(output);
    }
}
