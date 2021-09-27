#pragma once
#include <vector>
#include <string>
#include <iostream>


class Node {

public:


	//Node name
	std::string name;


	//Preceeding nodes.
	std::vector<Node> inputs;

	//The weight for the succeeding nodes.
	std::vector<double> weights;
	
	float* weightsSet;

	//The amount of nodes in the succeeding layer.
	int nextLayerNeuronCount;

	//The bias.
	int bias;

	//Input node initial value OR output value for regular node.
	double value;

	//Mostly made for debugging purposes, check if the node is the final one to output its value.
	bool isFinal;


	//Hidden/output node constructor
	Node(std::string name, std::vector<Node> layerNodes, int bias, int nextLayerNeuronCount, bool isFinal);

	//Input node constructor
	Node(std::string name, double value, int nextLayerNeuronCount);

	//Store the weights of the neuron for the next layer of neurons.
	void addWeights(int nextLayerNeuronCount);

	//Node output
	double nodeOutput(int count);
	

};
