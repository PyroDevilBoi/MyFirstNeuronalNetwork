#include "Layer.h"

namespace neural_net
{
	LayerDense::LayerDense(const int inputsNumber, const int neuronsNumber, double bias)
	{
		Utilities::rng.Matrix(inputsNumber, neuronsNumber, -1.0, 1.0, weights);
		LOG("(dense layer init) initialized with matrix: " << std::endl << weights);
		biases.fillVec(neuronsNumber, bias);
		LOG("(dense layer init)'s biases initialized with bias values: " << std::endl << biases);
	}

	LayerDense::~LayerDense()
	{
	}

	void LayerDense::forward(Utilities::nMatrix& inputs)
	{
		this->inputs = inputs;

		Utilities::MatrixDot(inputs, weights, output);
		LOG("Inputs * Weight matrix: " << std::endl << output);
		Utilities::MatrixAdd(output, biases);
		LOG("Adding the biases, the output of this layers is: " << std::endl << output);


	}
	void LayerDense::backward(Utilities::nMatrix & dValues)
	{
		//The partial derivative with respect to the weights is the inputs so we multiply the dvalues for the chain rule with the inputs
		//to get the partial derivative with respect to the weights
		Utilities::MatrixDot(inputs.transpose(), dValues, dWeights);

		//The same thing for the partial derivatives with respect to the inputs
		Utilities::MatrixDot(dValues, weights.transpose(), dInputs);

		//For the partial derivatives with respect to the biases vector, we will sum the values on the row of the dValues matrix.
		dBiases = Utilities::matrixSumInAxis(dValues, 0);
	}
}
