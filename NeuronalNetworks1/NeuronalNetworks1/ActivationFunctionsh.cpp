#include "ActivationFunctionsh.h"

neural_net::activationReLU::activationReLU()
{
	
}

neural_net::activationReLU::~activationReLU()
{
}

void neural_net::activationReLU::forward(Utilities::nMatrix & inputs)
{
	this->inputs = inputs;
	output = Utilities::matrixCapMin(0.0, inputs);
}


//Derivative of ReLU: if inputs > 0, the derivative is 1, else it is 0.
//dValues is the subsequent partial derivatives that come from the next layer backwards to this relu function
// ReLU's inputs are the "inputs" matrix which are used to derivate ReLU.
// the result will be a matrix containing 1 and 0 elements: 1 for the inputs that were greater than 0 and 0 for the ones below 0. 
// that result matrix will be multiplied by the dValues, but since we multiply 1s and 0s with the dValues,
// we could just iterate through our inputs that are on the same index as dvalues and make the lesser or equal than 0 values 0.
void neural_net::activationReLU::backward(Utilities::nMatrix & dValues)
{
	
	derivativeInputs = dValues;
	

	for (unsigned int i = 0; i < inputs.m.size(); i++)
	{
		for (unsigned int j = 0; j < inputs.m[i].v.size(); j++)
		{
			if (inputs.m[i].v[j] <= 0)
			{
				derivativeInputs.m[i].v[j] = 0;
			}
		}
	}
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

void neural_net::categoricalCrossEntropy::backward(Utilities::nMatrix & dValues, Utilities::nMatrix & target_class)
{
	//cap values in case they're 0?
	Utilities::nMatrix safety;


	//sample size
	int samples = dValues.m.size();

	//label size
	int labels = dValues.m[0].v.size();

	derivativeInputs = Utilities::softDiv(target_class, dValues);
	derivativeInputs = Utilities::multElement(derivativeInputs, -1);
	derivativeInputs = Utilities::divElement(derivativeInputs, samples);
}

void neural_net::categoricalCrossEntropy::backward(Utilities::nMatrix & dValues, Utilities::nVector & target_class)
{
	//sample size
	int samples = dValues.m.size();

	//label size
	int labels = dValues.m[0].v.size();

	//the target class vector transformed into a matrix
	Utilities::nMatrix temp;

	temp = Utilities::eyefy(target_class);
	temp = Utilities::multElement(temp, -1);
	derivativeInputs = Utilities::softDiv(temp, dValues);
	derivativeInputs = Utilities::divElement(derivativeInputs, samples);
}

