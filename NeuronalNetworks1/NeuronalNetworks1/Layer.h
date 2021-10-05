#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iomanip>
#include <cmath>


using matrix = std::vector< std::vector< double> >; 
using row = std::vector< double >;    




double random(const double& min, const double& max);
	


row operator+(const row& r1, const row& r2);

//Matrix transpose
matrix transposeMatrix(const matrix& m);


//Matrix multiplication
matrix operator*(const matrix& m1, const matrix& m2);   //no except

//Matrix addition
matrix operator+(const matrix& m, const row& v);


std::tuple<matrix, row> spiral_data(const size_t& points, const size_t& classes);




class Layer {

public:

	matrix weightsMat, output;
	row biases;


	
	
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
	
	void setNextLayerBias();
	void addToWeightMatrix(std::vector<double> nodeWeights);
	void outputWeightsMatrix();
	std::vector<double> dotProduct();
	std::vector<double> vectorSum(std::vector<double> v1, std::vector<double>v2);
	void calculateNewLayer();
	double returnNodeValue(int count);
	void returnAllNodeValues();
};