
#include "Layer.h"
#include "NeuralUtilities.h"
#include "ActivationFunctionsh.h"


//Inspired by: https://github.com/HippozHipos/neural-net

int main()
{
	//output 10 digits
	std::cout.precision(10);

	//input matrix with batches
	Utilities::nMatrix x;

	//matrix size: 3 neurons per batch
	const int size = 3;

	//fill input matrix with random values from -1 to 1
	Utilities::rng.Matrix(size, size, -1.0, 1.0, x);

	//initialize first layer:  3 inputs per batch    and 3 layer neurons per batch
	neural_net::LayerDense layer1 = neural_net::LayerDense(size, size);

	//Pass the input matrix into the new layer
	layer1.forward(x);

	//create activation function relu for first layer
	neural_net::activationReLU reLU1;

	//pass the inputs*weights + bias result through reLu
	reLU1.forward(layer1.output);

	//create activation function softmax for output
	neural_net::activationSoftmax softMax1;

	//create a new layer (in this case it will be the output layer) and pass previous layers' relu'd outputs as inputs * random weights

	neural_net::LayerDense layer2 = neural_net::LayerDense(size, size);

	layer2.forward(reLU1.output);

	//pass the output of the previous layer
	softMax1.forward(layer2.output);


	

	// Input layers with neuron values: each row is a batch of inputs and every batch contains the values of the input neurons
	
	system("pause");


	return 0;

}