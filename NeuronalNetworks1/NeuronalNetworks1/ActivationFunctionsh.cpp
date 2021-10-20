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

void neural_net::loss::forward(Utilities::nVector & inputs)
{
	output = Utilities::mean(inputs);
}

neural_net::categoricalCrossEntropy::categoricalCrossEntropy()
{
}

neural_net::categoricalCrossEntropy::~categoricalCrossEntropy()
{
}

void neural_net::categoricalCrossEntropy::forward(Utilities::nMatrix & inputs, Utilities::nMatrix & target_class)
{
	tempMat = Utilities::matrixCapMin(crossentropylimitL, inputs);
	tempMat = Utilities::matrixCapMax(crossentropylimitH, inputs);

	for (unsigned int i = 0; i < tempMat.m[i].v.size(); i++)
	{
		correctConidence.v.push_back(Utilities::vectorDot(tempMat.m[i], target_class.m[i]));
	}

	output = Utilities::negLog(correctConidence);
}



void neural_net::categoricalCrossEntropy::forward(Utilities::nMatrix& inputs, Utilities::nVector& target_class)
{
	//a[i][v[i]]
	tempMat = Utilities::matrixCapMin(crossentropylimitL, inputs);
	tempMat = Utilities::matrixCapMax(crossentropylimitH, inputs);

	for (unsigned int i = 0; i < target_class.v.size(); i++)
	{
		correctConidence.v.push_back(tempMat.m[i].v[target_class.v[i]]);
	}
	output = Utilities::negLog(correctConidence);
}

