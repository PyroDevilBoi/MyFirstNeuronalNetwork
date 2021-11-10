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

// Inspired by https://github.com/HippozHipos/neural-net

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



#define crossentropylimitL 1 * pow(10, - 7 )
#define crossentropylimitH 1 - crossentropylimitL

namespace Utilities
{

	//Vector
	struct nVector
	{
		std::vector<double> v;
		

		void fillVec(const unsigned int size, const double numberFilling)
		{
			v.clear();
			

			for (unsigned int i = 0; i < size; i++)
			{
				v.push_back(numberFilling);
			}
		}

		friend std::ostream& operator <<(std::ostream& out, const nVector& vec)
		{
			out << "[";
			for (unsigned int i = 0; i < vec.v.size(); i++)
			{
				if (i % vec.v.size() == vec.v.size() - 1)
				{
					std::cout << vec.v[i] << "]";
				}

				else

				{
					std::cout << vec.v[i] << ", ";
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

			for (unsigned int i = 0; i < rows; i++)
			{
				nVector currentVec;
				for (unsigned int j = 0; j < cols; j++)
				{
					currentVec.v.push_back(num);
				}
				m.push_back(currentVec);
			}
		}


		//Matrix transpose
		nMatrix transpose()
		{
			nMatrix newMatrix;
		//	newMatrix.m.reserve(m[0].v.size());
			// m[i].v.size()
			// m.size()
			for (unsigned int i = 0; i < m[0].v.size(); i++)
			{
				nVector currentVec;
				for (unsigned int j = 0; j < m.size(); j++)
				{
					currentVec.v.push_back(m[j].v[i]);
				}
				newMatrix.m.push_back(currentVec);
			}

			return newMatrix;

		}

		//Only for matrices that have the same shape/size
		void copyMat(nMatrix& m2)
		{
			
			m.reserve(m2.m.size());

			for (unsigned int i = 0; i < m2.m.size(); i++)
			{
				nVector clone;
				for (unsigned int j = 0; j < m2.m[i].v.size(); j++)
				{
					clone.v.push_back(m2.m[i].v[j]);
				}
				m.push_back(clone);
			}
		}

		friend std::ostream& operator <<(std::ostream& out, const nMatrix& mat)
		{
			out << "[" << std::endl << std::endl;
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				out << "[";
				for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
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

	//Class for random numbers;

	class RandomC {
	private:
		std::mt19937 _randomEngine;
		RandomC();
		RandomC(const RandomC&) = delete;
		~RandomC();

	public:
		static RandomC& Get();
		int Range(const int min, const int max);
		double Range(const double min, const double max);
		void Matrix(const int rows, const int cols, const double lower, const double upper, nMatrix& outvec);
		void Vector(const unsigned int size, const double lower, const double upper, nVector& outvec);

	};
	static RandomC& rng = RandomC::Get();




	//Utility calculations for Vectors
	inline double vectorDot(nVector& v1, nVector& v2)
	{
		if (v1.v.size() != v2.v.size())
			throw std::exception();

		double result = 0;
		for (unsigned int i = 0; i < v1.v.size(); i++)
		{
			result += v1.v[i] * v2.v[i];
		}
		return result;
	}

	//for calculating categoricalcrossentropy function
	inline nVector negLog(nVector& v)
	{
		nVector result;

		for (unsigned int i = 0; i < v.v.size(); i++)
		{
			result.v.push_back(-log(v.v[i]));
		}

		return result;
	}

	inline double mean(nVector& v)
	{
		double sum = 0;
		for (unsigned int i = 0; i < v.v.size(); i++)
		{
			sum += v.v[i];
		}

		return sum / v.v.size();
	}

	inline double vectorMax(nVector& v)
	{
		double max = v.v[0];
		for (unsigned int i = 0; i < v.v.size(); i++)
		{
			max = MAX(max, v.v[i]);
		}

		return max;

	}

	inline double vectorMin(nVector& v)
	{
		double min = v.v[0];
		for (unsigned int i = 0; i < v.v.size(); i++)
		{
			min = MAX(min, v.v[i]);
		}

		return min;

	}

	inline nVector capMaxValue(const double maxVal, const nVector& v)
	{
		nVector newVec;
		
		for (unsigned int i = 0; i < v.v.size(); i++)
		{
			newVec.v.push_back(MIN(maxVal, v.v[i]));
		}

		return newVec;
	}

	inline nVector capMinValue(const double minVal, const nVector& v)
	{
		nVector newVec;

		for (unsigned int i = 0; i < v.v.size(); i++)
		{
			newVec.v.push_back(MAX(minVal, v.v[i]));
		}

		return newVec;
	}

	inline nVector vectorExpE(const nVector& v)
	{
		nVector newVec;

		for (unsigned int i = 0; i < v.v.size(); i++)
		{
			newVec.v[i] = pow(EULERS_NUMBER, v.v[i]);
		}

		return newVec;
	}

	inline double vectorSum(const nVector& v)
	{
		
		double sum = 0;

		for (unsigned int i = 0; i < v.v.size(); i++)
		{
			sum += v.v[i];
			
		}

		return sum;
	}

	inline nVector normalizeVec(const nVector& v)
	{
		nVector clone;
		double sum = vectorSum(v);

		for (unsigned int i = 0; i < v.v.size(); i++)
		{
			clone.v.push_back(v.v[i] / sum);
		}

		return clone;
	}


	//Utility calculations for Matrices


	inline void MatrixDot(const nMatrix& m1, const nMatrix& m2,  nMatrix& out)
	{
		//Check if the number of cols in the first matrix is equal to the number of rows of the second matrix.
		if (m1.m[0].v.size() && m2.m.size())
		{
			if (m1.m[0].v.size() != m2.m.size())
			{
				LOG("Shape mismatch: " << "matrix1 columns: " << m1.m[0].v.size() << ", " << "matrix2 rows: " << m2.m.size());
				throw std::exception();
			}
		}

		unsigned int m1x = 0; unsigned int m1y = 0; unsigned int m2y = 0; //m2y = m1x

		while (out.m.size() < m1.m.size())
		{
			nVector tempv;
			while (tempv.v.size() < m2.m[0].v.size())
			{
				double total = 0.0;
				while (m1x < m1.m[0].v.size())
				{
					total += m1.m[m1y].v[m1x] * m2.m[m1x].v[m2y];
					m1x++;
				}
				tempv.v.push_back(total);
				m1x = 0;
				m2y < m2.m[0].v.size() - 1 ? m2y++ : m2y = 0;
			}
			m1y < m1.m.size() - 1 ? m1y++ : m1y = 0;
			out.m.push_back(tempv);
			
			
		}
	}

	inline void MatrixAdd(nMatrix& m, const nVector v)
	{
		if (m.m[0].v.size() != v.v.size())
		{
			LOG("Shape mismatch: " << "matrix1 columns: " << m.m[0].v.size() << ", " << "vector elements" << v.v.size());
			throw std::exception();
		}

		for (unsigned int i = 0; i < m.m.size(); i++)
		{
			for (unsigned int j = 0; j < v.v.size(); j++)
			{
				m.m[i].v[j] += v.v[i];
			}
		}
	}


	//caps the max value in the matrix
	inline nMatrix matrixCapMax(const double value, const nMatrix& inmat)
	{
		nMatrix  outmat;
		for (unsigned int i = 0; i < inmat.m.size(); i++)
		{
			nVector tempv;
			for (unsigned int j = 0; j < inmat.m[i].v.size(); j++)
			{
				tempv.v.push_back(MIN(value, inmat.m[i].v[j]));
			}
			outmat.m.push_back(tempv);
		}
		return outmat;
	}


	//caps the min value in the matrix
	inline nMatrix matrixCapMin(const double value, const nMatrix& inmat)
	{
		nMatrix  outmat;
		for (unsigned int i = 0; i < inmat.m.size(); i++)
		{
			nVector tempv;
			for (unsigned int j = 0; j < inmat.m[i].v.size(); j++)
			{
				tempv.v.push_back(MAX(value, inmat.m[i].v[j]));
			}
			outmat.m.push_back(tempv);
		}
		return outmat;
	}


	//axis = 0 means max value in each row
	//axis = 1 means max value in each column
	inline nVector matrixGetMaxInAxis(const nMatrix& mat, const int axis)
	{
		nVector tempv;

		if (axis == 0)
		{
			for (unsigned int i = 0; i < mat.m[0].v.size(); i++)
			{
				tempv.v.push_back(mat.m[0].v[i]);
				for (unsigned int j = 1; j < mat.m.size(); j++)
				{
					tempv.v[i] = MAX(mat.m[j].v[i], tempv.v[i]);
				}
			}
		}
		else if (axis == 1)
		{
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				tempv.v.push_back(mat.m[i].v[0]);
				for (unsigned int j = 1; j < mat.m[i].v.size(); j++)
				{
					tempv.v[i] = MAX(mat.m[i].v[j], tempv.v[i]);
				}
			}
		}
		else
		{
			LOG("axis must be either 0 or 1. Provided was: " << axis);
			throw std::exception();
		}

		return tempv;
	}


	//Return the maximum value of the matrix
	inline double getMax(const nMatrix& m)
	{
		double max;

		max = m.m[0].v[0];

		for (unsigned int i = 0; i < m.m.size(); i++)
		{
			for (unsigned int j = 0; j < m.m[i].v.size(); j++)
			{
				if (m.m[i].v[j] > max)
				{
					max = m.m[i].v[j];
				}
			}
		}

		return max;
	}

	//Return the minimum value of the matrix
	inline double getMin(const nMatrix& m)
	{
		double min;

		min = m.m[0].v[0];

		for (unsigned int i = 0; i < m.m.size(); i++)
		{
			for (unsigned int j = 0; j < m.m[i].v.size(); j++)
			{
				if (m.m[i].v[j] < min)
				{
					min = m.m[i].v[j];
				}
			}
		}

		return min;
	}

	//exponentiate all the elements
	inline nMatrix matrixExp(const nMatrix& mat)
	{
		nMatrix outmat;
		for (unsigned int i = 0; i < mat.m.size(); i++)
		{
			nVector tempv;
			for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
			{
				tempv.v.push_back(pow(EULERS_NUMBER, mat.m[i].v[j]));
			}
			outmat.m.push_back(tempv);
		}
		return outmat;
	}



	inline void removeRowAndCol(nMatrix& mat, const int x ,const int y)
	{


		for(unsigned int i = 0; i < mat.m.size(); i++)
		{
			
			mat.m[i].v.erase(mat.m[i].v.begin() + y);
			
		}
	
		mat.m.erase(mat.m.begin() + x);

	}


	//https://www.e-formule.ro/wp-content/uploads/determinantul-matricei.htm
	//start index with -1
/*
	double matrixDeterminant(const nMatrix& mat, int index)
	{
		// i=0...n: (-1)^(i+2) * a1i * D1i

		if (index == 0)
		{
			return pow(-1, 2) * mat.m[0].v[0] *
		}
		//detResult = pow(-1, index + 2) * mat.m[0].v[index] * matrixDeterminant(, index)
	}
	*/
	


	//divide every element by value
	inline nMatrix matrixDivValue(const double value, const nMatrix& mat, bool denominator)
	{
		nMatrix outmat;

		for (unsigned int i = 0; i < mat.m.size(); i++)
		{
			nVector tempv;
			for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
			{
				if(denominator)
					tempv.v.push_back(mat.m[i].v[j] / value);
				else
					tempv.v.push_back(value / mat.m[i].v[j]);
			}
			outmat.m.push_back(tempv);
		}
		return outmat;

	}

	//minus value from all the elements
	inline nMatrix matrixMinus(const double value, const nMatrix& mat)
	{
		nMatrix outmat;
		for (unsigned int i = 0; i < mat.m.size(); i++)
		{
			nVector tempv;
			for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
			{
				tempv.v.push_back(mat.m[i].v[j] - value);
			}
			outmat.m.push_back(tempv);
		}
		return outmat;
	}


	// 0 = rows, 1 = columns
	inline nMatrix matrixMinusMaxInAxis(const nMatrix& mat, const int axis)
	{
		nMatrix outmat;
		if (axis == 0)
		{
			outmat = mat;
			nVector max = matrixGetMaxInAxis(mat, 0);
			for (unsigned int i = 0; i < mat.m[0].v.size(); i++)
				for (unsigned int j = 0; j < mat.m.size(); j++)
				{
					outmat.m[j].v[i] = mat.m[j].v[i] - max.v[i];
				}
		}
		else if (axis == 1)
		{
			nVector max = matrixGetMaxInAxis(mat, 1);
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				nVector tempv;
				for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
				{
					tempv.v.push_back(mat.m[i].v[j] - max.v[i]);
				}
				outmat.m.push_back(tempv);
			}
		}
		else
		{
			LOG("axis must be either 0 or 1. Provided was: " << axis);
			throw std::exception();
		}
		return outmat;
	}

	//axis 0 means rows are summed 
	//axis 1 means that columns 
	inline nVector matrixSumInAxis(const nMatrix& mat, const int axis)
	{
		nVector tempv;

		if (axis == 0)
		{
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				double total = 0.0;
				for (unsigned int j = 0; j < mat.m[0].v.size(); j++)
				{
					total += mat.m[i].v[j];
				}
				tempv.v.push_back(total);
			}
		}
		else if (axis == 1)
		{
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				tempv.v.push_back(vectorSum(mat.m[i]));
			}
		}
		else
		{
			LOG("axis must be either 0 or 1. Provided was: " << axis);
			throw std::exception();
		}
		return tempv;
	}

	/*axis 0 means rows are summed to normalize
	axis 1 means that columns are summed to normalize*/
	inline nMatrix matrixNormalizeInAxis(const nMatrix& mat, int axis)
	{
		nMatrix outmat;
		if (axis == 0)
		{
			nVector _tempv = matrixSumInAxis(mat, 0);
			nVector tempv;
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
				{
					tempv.v.push_back(mat.m[i].v[j] / _tempv.v[j]);
				}
				outmat.m.push_back(tempv);
			}
		}
		else if (axis == 1)
		{
			for (unsigned int i = 0; i < mat.m.size(); i++)
			{
				nVector tempv;
				double total = vectorSum(mat.m[i]);
				for (unsigned int j = 0; j < mat.m[i].v.size(); j++)
				{
					if (total != 0)
						tempv.v.push_back(mat.m[i].v[j] / total);
					else
						tempv.v.push_back(1.0 / mat.m[i].v.size());
				}
				outmat.m.push_back(tempv);
			}
		}
		else
		{
			LOG("axis must be either 0 or 1. Provided was: " << axis);
			throw std::exception();
		}
		return outmat;
	}

	
	


}
