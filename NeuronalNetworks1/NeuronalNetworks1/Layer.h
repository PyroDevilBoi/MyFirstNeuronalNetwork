#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "Node.h"


class Layer {

public:

	std::vector<Node> nodes;
	int nodeCount = 0;



	Layer();
	void addNode(Node node);
	double returnNodeValue(int count);
	void returnAllNodeValues();
};