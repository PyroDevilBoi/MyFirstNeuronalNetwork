#pragma once
#include "NeuralUtilities.h"










namespace neural_net
{
	struct activationReLU
	{
		Utilities::nMatrix output;
		activationReLU();
		~activationReLU();
		void forward(Utilities::nMatrix& inputs);


	};


	struct activationSoftmax
	{
		Utilities::nMatrix output;
		activationSoftmax();
	    ~activationSoftmax();
		void forward(Utilities::nMatrix& inputs);
	};
}