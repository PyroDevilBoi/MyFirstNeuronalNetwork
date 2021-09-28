#include "Node.h"
#include <iostream>
#include <vector>
#include "Layer.h"

/*TODO:

Make layers create themselves with the dot product from the weights and inputs + bias.

Put the weights of each input in a matrix and do a dot product between the matrix and the vector to find the new layer's neurons.

Depending on how many new neurons we want in the new layer, 

we will have a corresponding amount of rows in that matrix (1 row per new neuron) 

and the collumns equal to the number of inputs (1 set of weights from each input)*/

int main()
{
	

	//Input nodes: value and next layer count
	Node x0("x0", 1, 3);
	Node x1("x1", 2, 3);
	Node x2("x2", 3, 3);
	Node x3("x3", 2.5, 3);

	

	//Input layer
	Layer Input;
	Input.addNode(x0);
	Input.addNode(x1);
	Input.addNode(x2);
	Input.addNode(x3);


	//Input.outputWeightsMatrix();
	Input.calculateNewLayer();

	/*
	// Hidden layer nodes or output nodes: layer + bias
	Node y0("y0", Input.nodes, 2, 0, true);
	Node y1("y1", Input.nodes, 3, 0, true);
	Node y2("y2", Input.nodes, 0.5, 0, true);

	// Hidden layer
	Layer y;
	y.addNode(y0);
	y.addNode(y1);
	y.addNode(y2);
	std::cout<< y.returnNodeValue(0);
	*/

	system("pause");


	return 0;

}