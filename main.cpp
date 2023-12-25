#include <chrono>
#include <cstdio>
#include <vector>

#include "lib/brain.hpp"
#include "lib/dataset.hpp"

int main() {
    // timer for benchmarking
    auto start = std::chrono::high_resolution_clock::now();

    // set up model
    DataSet data("./data.in");
    BasicModel brain(std::vector<int>{2, 4, 1}, 0.03);
    
    // train model
    brain.fit(data, 1000000);

    // print the results of each sample
    for(int i = 0; i < data.N; i++)
        brain.predictAndPrint(data.inputs[i]);

    // process timer data
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    printf("Time Taken (ms): %ld\n", duration);
}