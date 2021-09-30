#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Node.h"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <random>

using matrix = std::vector< std::vector< double> >; 
using row = std::vector< double >;    








class Layer {

public:

	matrix weightsMat, output;
	row biases;


	
	std::vector<Node> nodes;
	std::vector<double> nodeInputs;
	std::vector<std::vector<double>> weightMatrix;
	std::vector<double> nextLayerBiases;
	int nodeCount;

	//Amount of weights per set from a node.
	int nextLayerSize;



	Layer(const size_t& inputsNumber, const size_t& thisLayersNeurons);
	void forwardPass(const matrix& inputs);
	matrix outputLayer() const;
	void displayLayer();
	void addNode(Node node);
	void setNextLayerBias();
	void addToWeightMatrix(std::vector<double> nodeWeights);
	void outputWeightsMatrix();
	std::vector<double> dotProduct();
	std::vector<double> vectorSum(std::vector<double> v1, std::vector<double>v2);
	void calculateNewLayer();
	double returnNodeValue(int count);
	void returnAllNodeValues();
};