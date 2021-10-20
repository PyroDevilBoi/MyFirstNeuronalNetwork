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

neural_net::loss::loss()
{
}

neural_net::loss::~loss()
{
}

neural_net::categoricalCrossEntropy::categoricalCrossEntropy()
{
}

neural_net::categoricalCrossEntropy::~categoricalCrossEntropy()
{
}



void neural_net::categoricalCrossEntropy::forward(Utilities::nMatrix& inputs, Utilities::nVector& target_class)
{
	//a[i][v[i]]

	for (unsigned int i = 0; i < target_class.v.size(); i++)
	{
		output.v.push_back(inputs.m[i].v[target_class.v[i]]);
	}
}

