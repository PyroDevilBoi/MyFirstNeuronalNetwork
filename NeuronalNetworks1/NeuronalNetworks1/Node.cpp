#include "Node.h"





Node::Node(std::string name, std::vector<Node> layerNodes, int bias, int nextLayerNeuronCount, bool isFinal)
{
	this->name = name;
	inputs = layerNodes;
	this->bias = bias;
	this->isFinal = isFinal;
	
	if(!isFinal)
		addWeights(nextLayerNeuronCount);
}

Node::Node(std::string name, double value, int nextLayerNeuronCount)
{
	this->name = name;
	this->value = value;
	addWeights(nextLayerNeuronCount);
	

}

void Node::addWeights(int nextLayerNeuronCount)
{
	for (int i = 0; i < nextLayerNeuronCount; i++)
	{
		double weight;
		std::cout << "Enter weight from the " << name << " neuron to the next layer's " << i << " neuron";
		std::cin >> weight;
		weights.push_back(weight);
	}
}

double Node::nodeOutput(int count)
{
	if (isFinal)
	{
		for (int i = 0; i < inputs.size(); i++)
		{
			value = value + inputs[i].weights[count] * inputs[i].value;
		}
			
		
	}
	return value + bias;
}
