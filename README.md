# Neural Network Framework

## Description
This is a neural network framework built in C++. 
There are three header files that come in this framework:
- ```brain.hpp"```
    - contains the ```BasicModel``` class
- ```"dataset.hpp"```
    - contains the ```DataSet``` class
- ```"utilities.hpp"```
    - contains the ```Matrix``` class
    - contains the ```ColumnVector``` class (child of ```Matrix```)
    - contains global functions associated with necessary matrix computations

## Compilation
To get started with using the framework, reference ```main.cpp```.

*Compilation for Windows:*
In the terminal, enter ```g++ -o main *.cpp lib/*.cpp``` to compile the source code.
Then, enter ```./main``` to run ```main.cpp```.

## Core Classes

### BasicModel
The basic model constitutes a crude neural network and uses the sigmoid function as the activation function for each neuron.

Parameters required to define the model include:
- ```const int N```: The number of layers in the model (including input and output layers)
- ```const int * S```: The size of each layer in an integer array
- ```const double L```: The learning rate of the model (default is 0.03)

### DataSet
The data set takes in a training data file, which follows the format specified below.

The first line of the file contains the space-separated integers ```N I O```, which describe the number of samples in the data set, input size of each sample, and output size of each sample respectively.

For each of the ```N``` samples:
- Line 1 contains ```I``` input values (separated by spaces)
- Line 2 contains ```O``` output desired output values (separated by spaces)


