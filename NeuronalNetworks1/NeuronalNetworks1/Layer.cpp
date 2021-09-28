#include "Layer.h"

// Simple implementation of built-in python zip (credit to the NNfSiX repository)

template<typename T, typename P>
std::vector<std::tuple<T, P>> zip(typename std::vector<T>::iterator firstArrayBegin,
	typename std::vector<P>::iterator secondArrayBegin,
	typename std::vector<P>::const_iterator secondArrayEnd)
{
	const auto size = std::distance(static_cast<decltype(secondArrayEnd)>(secondArrayBegin), secondArrayEnd);
	std::vector<std::tuple<T, P>> zipped;
	zipped.reserve(size);
	while (secondArrayBegin != secondArrayEnd) {
		zipped.emplace_back(*firstArrayBegin++, *secondArrayBegin++);
	}
	return zipped;
}

Layer::Layer():weightMatrix(row, std::vector<double>(row))
{
	nodeCount = 0;
	
}

//Adding a node to the layer
void Layer::addNode(Node node)
{
	//We know that the number of the next layer's nodes will be equal to the number of weights coming from this current node.
	nextLayerSize = node.weights.size();

	nodeInputs.push_back(node.value);
	nodes.push_back(node);
	addToWeightMatrix(node.weights);
	nodeCount++;
}


//Set the biases for the next layer we will create after this one.
void Layer::setNextLayerBias()
{
	for (int i = 0; i < nextLayerSize; i++)
	{
		double bias;
		std::cout << "Enter the new layer's " << i << "th node's bias: ";
		std::cin >> bias;
		nextLayerBiases.push_back(bias);
	}
}

//Multiplication between weights matrix and inputs vector.
std::vector<double> Layer::dotProduct()
{
	std::vector<double> result;
	double sum;

	for (int i = 0; i < nextLayerSize; i++)
	{
		sum = 0;

		for (int j = 0; j < nodeCount; j++)
		{
			sum = sum + weightMatrix[i][j] * nodeInputs[j];
		}
		result.push_back(sum);
	}
	return result;
}

std::vector<double> Layer::vectorSum(std::vector<double> v1, std::vector<double>v2)
{
	std::vector<double> result;

	for (int i = 0; i < nextLayerSize; i++)
	{
		result.push_back(v1[i] + v2[i]);
	}

	return result;
}

void Layer::calculateNewLayer()
{
	std::vector<double> outputs;
	setNextLayerBias();
	outputs = vectorSum(dotProduct(), nextLayerBiases);

	for (int i = 0; i < nextLayerSize; i++)
	{
		std::cout << outputs[i] << " ";
	}
}

//Adding the node's set of weights to the matrix of all weights.
void Layer::addToWeightMatrix(std::vector<double> nodeWeights)
{
	

	for (int i = 0; i < nodeWeights.size(); i++)
	{
		weightMatrix[i][nodeCount] = nodeWeights[i];
	}
}

//Loop through the weights matrix and output it. Each row is a set of weights, each set's order is corresponding to
//the node's order. For example: node 0 will be on the 0th position on each row.

void Layer::outputWeightsMatrix()
{
	for (int i = 0; i < nextLayerSize; i++)
	{
		for (int j = 0; j < nodeCount; j++)
		{
			std::cout << weightMatrix[i][j] << " ";
		}
		std::cout << "\n";
	}
}

double Layer::returnNodeValue(int count)
{
	return nodes[count].nodeOutput(count);
}

void Layer::returnAllNodeValues()
{
	for (int i = 0; i < nodes.size(); i++)
		std::cout << nodes[i].value << " ";
	
}
