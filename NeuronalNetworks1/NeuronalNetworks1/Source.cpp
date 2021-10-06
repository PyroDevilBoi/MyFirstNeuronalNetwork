
#include "Layer.h"


struct activation_relu {
	matrix operator()(const matrix& inputs) {
		matrix output(inputs.size(), row(inputs[0].size(), 0));
		for (size_t i = 0; i < inputs.size(); i++)
			for (size_t j = 0; j < inputs[i].size(); j++)
				output[i][j] = std::max(0.0, inputs[i][j]);
		return output;
	}
};

// Dynamic matrix outputting
std::ostream& operator<<(std::ostream& os, const matrix& m) noexcept {
	for (auto& row : m) {
		for (auto& item : row)
			os << item << " ";
		os << "\n";
	}return os;
}

std::ostream& operator<<(std::ostream& os, const  row& dr) {
	os << " [";
	for (auto& item : dr)
		os << std::setw(15) << item << " ";
	os << "]\n";
	return os;
}


int main()
{
	// Input layers with neuron values: each row is a batch of inputs and every batch contains the values of the input neurons
	matrix inputLayer{
		row{1, 2, 3, 2.5},
		row{2.0, 5.0, -1.0, 2.0},
		row{-1.5, 2.7, 3.3, -0.8}
	};

	row testBiases1{ 0.5, 0.3, 0.1, 0.7, 0.9 };
	row testBiases2{ 0.1, 0.9, 0.1, 0.4 };
	
	auto x = spiral_data(100, 3);

	Layer hiddenLayer1(4,5);
	//hiddenLayer1.biases = testBiases1;
	activation_relu activation1;

	hiddenLayer1.forwardPass(inputLayer);
	std::cout << "\n\n" << hiddenLayer1.outputLayer();

	auto activationOutput = activation1(hiddenLayer1.outputLayer());

	std::cout << " \n\n " << activationOutput;

	//Layer hiddenLayer2(5,4);
	//hiddenLayer2.biases = testBiases2;

	//hiddenLayer1.forwardPass(inputLayer);
	//std::cout<< "\n\n" << hiddenLayer1.outputLayer();

	//hiddenLayer2.forwardPass(hiddenLayer1.output);
	//std::cout << "\n" << hiddenLayer2.outputLayer();

	system("pause");


	return 0;

}