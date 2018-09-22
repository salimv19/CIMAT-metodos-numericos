#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include "IOMatrices.h"

/*
Salim Vargas Hernández
Programación y Algoritmos
Tarea 6
Método de Jacobi y Gauss-Seidel
Septiembre 2018
*/

using namespace std;

double producto_punto(vector<double> vec1, vector<double> vec2)
{
	double productoPunto;

	productoPunto = 0;

	for (int i=0; i < vec1.size(); i++)
		productoPunto = productoPunto + vec1[i]*vec2[i];

	return productoPunto;
}

vector<double> producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M)
{
	vector<double> res(M);
	for (int i=0; i < N; i++)
		res[i] = producto_punto(A[i], vec);
	return res;
}


vector<double> resta_vectores(vector<double> vecA, vector<double>& vecB, int& N)
{
	vector<double> resta(N);

	for (int i=0; i < N; i++)
	{
		resta[i] = vecA[i] - vecB[i];
	}

	return resta;
}

double norma_uno(vector<double>& x)
{
	double norma;
	norma = 0;
	for (int i=0; i < x.size(); i++)
	{
		norma = norma + fabs(x[i]);
	}
	return norma;
}

double norma_infinito(vector<double>& x)
{
	double norma;
	norma = 0;
	for (int i=0; i < x.size(); i++)
	{
		if (fabs(x[i]) > norma)
		{
			norma = fabs(x[i]);
		}
	}
	return norma;
}

double norma_dos(vector<double> x, int N)
{
	double norma;

	norma = 0;
	for (int i=0; i < N; i++)
	{
		norma = norma + pow(fabs(x[i]),2);
	}

	return norma;
}

bool metodo_jacobi(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int& N, int& maxIt, double& tolerancia)
{
	vector<double> aux(N);
	double suma, diferenciaR;
	int iter;
	bool converge;

	converge = true;
	iter = 0;
	do
	{
		iter = iter + 1;

		for (int i=0; i < N; i++)
		{
			suma = 0.0;
			for (int j=0; j < N; j++)
			{
				if (i != j)
				{
					suma = suma + A[i][j]*x[j];
				}
			}
			if (A[i][i] != 0)
			{
				aux[i] = (b[i] - suma)/A[i][i];
			}
			else
				converge = false;
		}

		diferenciaR = norma_dos(resta_vectores(aux, x, N), N)/norma_dos(x, N);

		x = aux;
	}
	while(diferenciaR > tolerancia && iter < maxIt);

	if (iter == maxIt)
		converge = false;

	return converge;
}

bool metodo_gauss_seidel(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int& N, int& maxIt, double& tolerancia)
{
	vector<double> aux(N);
	double sumaA, sumaB, diferenciaR;
	int iter;
	bool converge;

	converge = true;
	iter = 0;
	do
	{
		iter = iter + 1;

		for (int i=0; i < N; i++)
		{
			sumaA = 0.0;
			for (int j=0; j <= i-1; j++)
			{
				sumaA = sumaA + A[i][j] * aux[j];
			}
			sumaB = 0.0;
			for (int j=i+1; j < N; j++)
			{
				sumaB = sumaB + A[i][j] * x[j];
			}

			if (A[i][i] != 0)
			{
				aux[i] = (b[i] - sumaA - sumaB)/A[i][i];
			}
			else
				converge = false;
		}

		diferenciaR = norma_dos(resta_vectores(aux, x, N), N)/norma_dos(x, N);

		x = aux;
	}
	while(diferenciaR > tolerancia && iter < maxIt);

	if (iter == maxIt)
		converge = false;

	return converge;
}

int main()
{
	vector<vector<double>> matrizA;
	vector<double> b;
	double tolerancia;
	int N, M, maxIt;

	maxIt = 1000;
	tolerancia = 1e-16;

	matrizA = IOMatrices::lee_matriz_completa("TAREA06_SISTEMAS/FULL_MAT4.txt", N, M);
	b = IOMatrices::lee_vector("TAREA06_SISTEMAS/FULL_VEC4.txt", N);

	vector<double> x(N);

	if(metodo_jacobi(matrizA, b, x, N, maxIt, tolerancia))
	{
		cout << "\n\tMÉTODO DE JACOBI\n";
		cout << "\n\t||x||_1 = " << norma_uno(x) << endl;
		cout << "\t||x||_inf = " << norma_infinito(x) << endl;
		cout << "\n\t||Ax - b||_2 = " << norma_dos(resta_vectores(producto_matriz_vector(matrizA, x, N, M), b, M), M) << endl << endl;
	}

	if(metodo_gauss_seidel(matrizA, b, x, N, maxIt, tolerancia))
	{
		cout << "\n\n\tMÉTODO DE GAUSS-SEIDEL\n";
		cout << "\n\t||x||_1 = " << norma_uno(x) << endl;
		cout << "\t||x||_inf = " << norma_infinito(x) << endl;
		cout << "\n\t||Ax - b||_2 = " << norma_dos(resta_vectores(producto_matriz_vector(matrizA, x, N, M), b, M), M) << endl << endl;
	}

	return 0;
}
