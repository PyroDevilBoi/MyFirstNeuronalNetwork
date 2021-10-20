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

	//for(i =0; i < class_targets.len; i++)

	//a[i][v[i]]

	//a - softmax outputs matrix


	//pass target vector (index of the vector's elements is output matrix row and each element is the matrix's collumn
	//for(int i = 0; i < target.len; i++)
	// output[i][v[i]] --> element we want
	//if the target vector is passed as a matrix, multiply it by the output matrix and put the non-0 results in a vector

	// target vector: [0, 1, 1] as vector

	// target matrix: [1, 0 ,0]
	//                [0, 1, 0]
	//                [0, 1, 0]

	// step 1 - select target outputs with the target vector
	// step 2 - apply -log n to each of the target outputs
	// step 3 - mean/average of these log'd targets to compute overall loss


	//handles the selected outputs: applies mean/average to them
	struct loss
	{
		Utilities::nVector output;
		loss();
		~loss();
		void forward(Utilities::nVector& inputs);
	};

	//handles the target vector/matrix coming in, clips them so they are non 0 and applies negative log n to the selected outputs
	struct categoricalCrossEntropy
	{
		Utilities::nVector output;
		categoricalCrossEntropy();
		~categoricalCrossEntropy();
		void forward(Utilities::nMatrix& inputs);
		void forward(Utilities::nMatrix& inputs, Utilities::nVector& target_class);
		
	};
}