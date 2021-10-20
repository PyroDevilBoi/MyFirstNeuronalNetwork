
#include "Layer.h"
#include "NeuralUtilities.h"
#include "ActivationFunctionsh.h"


//Inspired by: https://github.com/HippozHipos/neural-net

int main()
{
	//Target vector
	Utilities::nVector target_vec;

	target_vec.v.push_back(0);
	target_vec.v.push_back(1);
	target_vec.v.push_back(1);



	//output 10 digits
	std::cout.precision(10);

	//input matrix with batches; each line is a new batch of inputs, every collum is the value of that input in the order
	//lines: number of batches            collums: number of neurons          values: input neuron value
	Utilities::nMatrix x;

	//matrix size: 3 neurons per batch
	const int size = 3;

	//fill input matrix with random values from -1 to 1
	Utilities::rng.Matrix(size, size, -1.0, 1.0, x);

	//initialize first hidden layer:  3 inputs per batch    and 3 layer neurons per batch to be created in this layer
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

	neural_net::categoricalCrossEntropy cat;
	neural_net::loss loss1;

	
	std::cout << "========SOFToutput==========" << std::endl;
	//FINAL OUTPUT
	std::cout << std::endl << softMax1.output;

	cat.forward(softMax1.output, target_vec);
	loss1.forward(cat.output);

	std::cout << "========TEST==========" << std::endl;
	std::cout << std::endl << cat.correctConidence;
	std::cout << std::endl << cat.output;
	std::cout << std::endl;
	std::cout << "========lossAVG==========" << std::endl;
	std::cout << std::endl << loss1.output;
	

	

	// Input layers with neuron values: each row is a batch of inputs and every batch contains the values of the input neurons
	
	system("pause");


	return 0;

}