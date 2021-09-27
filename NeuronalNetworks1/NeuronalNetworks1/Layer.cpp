#include "Layer.h"

Layer::Layer():weightMatrix(row, std::vector<double>(row))
{
	nodeCount = 0;
	
}

//Adding a node to the layer
void Layer::addNode(Node node)
{
	nodes.push_back(node);
	addToWeightMatrix(node.weights);
	nodeCount++;
}

//Adding the node's set of weights to the matrix of all weights.
void Layer::addToWeightMatrix(std::vector<double> nodeWeights)
{
	//We know that the number of the next layer's nodes will be equal to the number of weights coming from this current node.
	nextLayerSize = nodeWeights.size();

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
