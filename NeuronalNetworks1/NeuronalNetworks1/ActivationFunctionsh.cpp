#include "ActivationFunctionsh.h"

neural_net::activationReLU::activationReLU()
{
	
}

neural_net::activationReLU::~activationReLU()
{
}

void neural_net::activationReLU::forward(Utilities::nMatrix & inputs)
{
	output = Utilities::matrixCapMin(0.0, inputs);
}

neural_net::activationSoftmax::activationSoftmax()
{
}

neural_net::activationSoftmax::~activationSoftmax()
{
}

void neural_net::activationSoftmax::forward(Utilities::nMatrix & inputs)
{
	Utilities::nMatrix negateMatr = Utilities::matrixMinusMaxInAxis(inputs, 1);
	output = Utilities::matrixExp(inputs);
	output = Utilities::matrixNormalizeInAxis(output, 1);
}
