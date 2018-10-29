#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include "IOMatrices.h"
#include "AlgebraLineal.h"

using namespace std;

const double epsMaquina = numeric_limits<double>::epsilon();

AlgebraLineal::AlgebraLineal()
{
}

AlgebraLineal::~AlgebraLineal()
{
}

bool abs_compare(double a, double b)
{
    return (fabs(a) < fabs(b));
}

vector<double> AlgebraLineal::resta_vectores(vector<double> vecA, vector<double> vecB, int& N)
{
	vector<double> resta(N);

	for (int i=0; i < N; i++)
	{
		resta[i] = vecA[i] - vecB[i];
	}

	return resta;
}

double AlgebraLineal::producto_punto(vector<double> vec1, vector<double> vec2)
{
	double productoPunto;

	productoPunto = 0;

	for (int i=0; i < vec1.size(); i++)
		productoPunto = productoPunto + vec1[i]*vec2[i];

	return productoPunto;
}

double AlgebraLineal::norma_dos(vector<double> x, int N)
{
	double norma;

	norma = 0;
	for (int i=0; i < N; i++)
	{
		norma = norma + pow(fabs(x[i]),2);
	}

	return sqrt(norma);
}

vector<double> AlgebraLineal::producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M)
{
	vector<double> res(M);
	for (int i=0; i < N; i++)
		res[i] = AlgebraLineal::producto_punto(A[i], vec);
	return res;
}



void AlgebraLineal::gradiente_conjugado(vector<vector<double>>& A, vector<double>& b, vector<double>& x, vector<double>& residuo, int& N, int& iteraciones)
{
	vector<double> direccion(N), auxVec;
	double normaResiduo, nuevaNormaResiduo, alpha, beta;
	int iter;

	residuo = AlgebraLineal::resta_vectores(AlgebraLineal::producto_matriz_vector(A, x, N, N), b, N);
	for (int i=0; i < N; i++)
		direccion[i] = -1*residuo[i];

	iter = 0;
	normaResiduo = AlgebraLineal::norma_dos(residuo, N);
	while (normaResiduo > epsMaquina && iter < N)
	{
		iter = iter + 1;

		auxVec = AlgebraLineal::producto_matriz_vector(A, direccion, N, N);
		alpha = pow(normaResiduo,2) / AlgebraLineal::producto_punto(direccion, auxVec);

		//Se aplica un for en lugar de métodos de la clase para ejecutar todo en un sólo ciclo y sin crear más vectores
		//El código es incluso más claro de esta forma, incluso es más facilmente paralelizable
		for (int i=0; i < N; i++)
		{
			x[i] = x[i] + alpha*direccion[i];
			residuo[i] = residuo[i] + alpha*auxVec[i];
		}

		nuevaNormaResiduo = AlgebraLineal::norma_dos(residuo, N);

		beta = pow(nuevaNormaResiduo, 2) / pow(normaResiduo, 2);

		//Se aplica un for en lugar de métodos de la clase para ejecutar todo en un sólo ciclo y sin crear más vectores
		//El código es incluso más claro de esta forma, incluso es más facilmente paralelizable
		for (int i=0; i < N; i++)
			direccion[i] = -1*residuo[i] + beta*direccion[i];

		normaResiduo = nuevaNormaResiduo;
	}

	iteraciones = iter - 1;
}