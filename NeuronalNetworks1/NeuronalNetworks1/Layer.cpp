#include "Layer.h"

Layer::Layer()
{
}

void Layer::addNode(Node node)
{
	nodes.push_back(node);
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
