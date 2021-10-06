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



//Defining debug for logging

#define DEBUG 1
#if DEBUG == 1
#define LOG(x) std::cout<<x<<std::endl;
#else
#define LOG(x)
#endif


//Defining Max and Min to get the maximum and minimum values faster
#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b

//Euler's number and PI definitions
#define EULERS_NUMBER pow((1.0 + 1.0 / 10000000.0), 10000000.0)
#define PI 3.14159265359

namespace Utilities
{

	//Vector
	struct nVector
	{
		std::vector<double> v;

		void fillVec(const unsigned int size, const double numberFilling)
		{
			v.clear();

			for (int i = 0; i < size; i++)
			{
				v.push_back(numberFilling);
			}
		}

		friend std::ostream& operator <<(std::ostream& out, const nVector& vec)
		{
			out << "[";
			for (unsigned int i = 0; i < vec.v.size(); i++)
			{
				if (i % vec.v.size() == vec.v.size - 1)
				{
					std::cout << "]";
				}

				else

				{
					std::cout << ", ";
				}
			}

			return out;
		}
	};

	//Matrix
	//Contains a vector of nVectors
	struct nMatrix 
	{
		std::vector<nVector> m;


		//fill matrix
		void fillMat(unsigned int const rows, unsigned int const cols, const double num)
		{
			m.clear();

			for (int i = 0; i < rows; i++)
			{
				nVector currentVec;
				for (int j = 0; j < cols; j++)
				{
					currentVec.v.push_back(num);
				}
				m.push_back(currentVec);
			}
		}

		friend std::ostream& operator <<(std::ostream& out, const nMatrix& mat)
		{
			out << "[" << std::endl << std:endl;
			for (int i = 0; i < mat.m.size(); i++)
			{
				for (int j = 0; j < mat.m[i].size(); j++)
				{
					if (j % mat.m[i].v.size() == mat.m[i].v.size() - 1)
					{
						out << mat.m[i].v[j] << "]" << std::endl << std::endl;
					}
					else
					{
						out << mat.m[i].v[j] << ", ";
					}
				}
			}
			out << "]" << std::endl;
			return out;

		}

	};
}
