#pragma once
#include "NeuralUtilities.h"


//Inspired by https://github.com/HippozHipos/neural-net

namespace neural_net
{

	class LayerDense {

	public:

		Utilities::nMatrix weights;
		Utilities::nMatrix output;
		Utilities::nVector biases;

		LayerDense(const int inputsNumber, const int neuronsNumber, double bias = 0.0);
		~LayerDense();
		void forward(Utilities::nMatrix& inputs);


	};
}