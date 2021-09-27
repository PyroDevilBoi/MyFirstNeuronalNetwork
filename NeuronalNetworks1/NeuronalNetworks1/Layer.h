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

class Layer {

public:
	int row = 64;
	std::vector<Node> nodes;
	std::vector<std::vector<double>> weightMatrix;
	int nodeCount;

	//Amount of weights per set from a node.
	int nextLayerSize;



	Layer();
	void addNode(Node node);
	void addToWeightMatrix(std::vector<double> nodeWeights);
	void outputWeightsMatrix();
	double returnNodeValue(int count);
	void returnAllNodeValues();
};