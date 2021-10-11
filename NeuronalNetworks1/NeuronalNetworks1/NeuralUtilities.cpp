#include "NeuralUtilities.h"


namespace Utilities
{
	RandomC::RandomC()
	{
		std::random_device randomSeed;
		std::mt19937 randomEngine(randomSeed);
		randomEngine = randomEngine;
	}
	RandomC::~RandomC() {};

	RandomC& RandomC::Get()
	{
		static RandomC random;
		return random;
	}

	int RandomC::Range(const int lower, const int upper)
	{
		std::uniform_int_distribution<int> distribution(lower, upper);
		return distribution(randomEngine);
	}

	double RandomC::Range(const double lower, const double upper)
	{
		std::uniform_real_distribution<double> distribution(lower, upper);
		return distribution(randomEngine);
	}

	void RandomC::Matrix(const  int rows, const  int cols, const double lower, const double upper, nMatrix& outmat)
	{
		for (unsigned int i = 0; i < rows; i++)
		{
			nVector tempVec;
			for (unsigned int j = 0; j < cols; j++)
			{
				tempVec.v.push_back(Range(lower, upper));
			}
			outmat.m.push_back(tempVec);
		}
	}

	void RandomC::Vector(const unsigned int size, const double lower, const double upper, nVector& outvec)
	{
		for (unsigned int i = 0; i < size; i++)
			outvec.v.push_back(Range(lower, upper));
	}
}