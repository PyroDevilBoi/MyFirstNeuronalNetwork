#include "Layer.h"


double random(const double& min, const double& max) {
	std::mt19937_64 rng{}; rng.seed(std::random_device{}());
	return std::uniform_real_distribution<>{min, max}(rng);
}

row operator+(const row& r1, const row& r2) {
	row rval(r1.begin(), r1.end());
	for (size_t i = 0; i < rval.size(); i++)
		rval[i] += r2[i];
	return rval;
}

//Matrix transpose
matrix transposeMatrix(const matrix& m)
{
	matrix mat;

	for (size_t i = 0; i < m[0].size(); i++) {
		mat.push_back({});
		for (size_t j = 0; j < m.size(); j++) {
			mat[i].push_back(m[j][i]);
		}
	}return mat;
}

//Matrix multiplication
matrix operator*(const matrix& m1, const matrix& m2) 
{
	matrix result;
	matrix m3 = transposeMatrix(m2);


	for (size_t i = 0; i < m1.size(); i++)
	{
		result.push_back({});

		for (size_t j = 0; j < m3.size(); j++)
		{
			result[i].push_back(std::inner_product(m1[i].begin(), m1[i].end(), m3[j].begin(), 0.0));
		}

	}
	return result;
}


//Matrix addition
matrix operator+(const matrix& m, const row& v)
{
	matrix result;


	for (size_t i = 0; i < m.size(); i++)
	{
		result.push_back({});

		for (size_t j = 0; j < m[i].size(); j++)
		{
			result[i].push_back(m[i][j] + v[i]);
		}
	}

	return result;
}

std::tuple<matrix, row> spiral_data(const size_t& points, const size_t& classes) {
	matrix X(points*classes, row(2, 0));
	row y(points*classes, 0);
	double r, t;
	for (size_t i = 0; i < classes; i++) {
		for (size_t j = 0; j < points; j++) {
			r = double(j) / double(points);
			t = i * 4 + (4 * r);
			X[i*points + j] = row{ r*cos(t*2.5), r*sin(t*2.5) } +row{ random(-0.15,0.15), random(-0.15,0.15) };
			y[i*points + j] = i;
		}
	}
	return std::make_tuple(X, y);
}



//....................................... LAYER METHODS .......................................

//Optimized code:

Layer::Layer(const size_t& inputsNumber, const size_t& thisLayersNeurons) : weightsMat(inputsNumber, row (thisLayersNeurons)), biases(thisLayersNeurons, 0)
{
	for (size_t i = 0; i < thisLayersNeurons; i++)
	{
		for (size_t j = 0; j < inputsNumber; j++)
		{
			weightsMat[j][i] = random(-1.0, 1.0);
		}
	}

}

//Forming the output of the neurons in this layer 
void Layer::forwardPass(const matrix& inputs)
{
	output = inputs * weightsMat + biases;
}


//Output layer
matrix Layer::outputLayer() const
{
	return output;
}

void Layer::displayLayer()
{
	
}




//Old code:
/*
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
*/