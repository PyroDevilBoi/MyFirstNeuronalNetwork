#include "Layer.h"

namespace neural_net
{
	LayerDense::LayerDense(const int inputsNumber, const int neuronsNumber, double bias)
	{
		Utilities::rng.Matrix(inputsNumber, neuronsNumber, -1.0, 1.0, weights);
		LOG("(dense layer init) initialized with matrix: " << std::endl << weights);
		biases.fillVec(neuronsNumber, bias);
		LOG("(dense layer init)'s biases initialized with bia values: " << std::endl << biases);
	}

	LayerDense::~LayerDense()
	{
	}

	void LayerDense::forward(Utilities::nMatrix& inputs)
	{
		Utilities::MatrixDot(inputs, weights, output);
		LOG("Inputs * Weight matrix: " << std::endl << output);
		Utilities::MatrixAdd(output, biases);
		LOG("Adding the biases, the output of this layers is: " << std::endl << output);


	}
}
