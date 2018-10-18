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

vector<double> AlgebraLineal::columna_indice(vector<vector<double>>& A, int& N, int& indice)
{
	vector<double> vec(N);

	for (int i=0; i < N; i++)
		vec[i] = A[i][indice];

	return vec;
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

void normaliza_vector_2(vector<double>& x, int N)
{
	double norma;

	norma = AlgebraLineal::norma_dos(x, N);

	for (int i=0; i < N; i++)
		x[i] = 1.0 * x[i] / norma;
}

double AlgebraLineal::norma_frobenius(vector<vector<double>>& matriz, int& N, int& M)
{
	double norma;

	norma = 0;

	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			norma = norma + pow(fabs(matriz[i][j]), 2);

	norma = sqrt(norma);

	return norma;
}

vector<vector<double>> AlgebraLineal::resta_matrices(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M)
{
	vector<vector<double>> C(N, vector<double>(M));

	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			C[i][j] = A[i][j] - B[i][j];

	return C;
}

vector<double> AlgebraLineal::proyeccion_vector_vector(vector<double>& vecA, vector<double> vecB, int& N)
{
	vector<double> proy(N);
	double factor;

	factor = AlgebraLineal::producto_punto(vecA, vecB) / pow(AlgebraLineal::norma_dos(vecB, N),2);
	
	for (int i=0; i < N; i++)
		proy[i] = factor * vecB[i];

	return proy;
}

vector<vector<double>> AlgebraLineal::producto_matriz_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L)
{
	vector<vector<double>> C(N, vector<double>(L));
	double suma;

	for (int i=0; i < N; i++)
		for (int j=0; j < L; j++)
		{
			suma = 0;
			for (int r=0; r < M; r++)
				suma = suma + A[i][r]*B[r][j];
			C[i][j] = suma;
		}

	return C;
}

vector<vector<double>> AlgebraLineal::producto_matrizT_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L)
{
	vector<vector<double>> C(N, vector<double>(L));
	double suma;

	for (int i=0; i < N; i++)
		for (int j=0; j < L; j++)
		{
			suma = 0;
			for (int r=0; r < M; r++)
				suma = suma + A[r][i]*B[r][j];
			C[i][j] = suma;
		}

	return C;
}

vector<vector<double>> AlgebraLineal::ortogonalizacion_gram_schmidt(vector<vector<double>>& A, int& N, int& M) 
{
	vector<vector<double>> U(N, vector<double>(M));
	vector<double> vecU, vecV;
	int j;

	for (int i=0; i < M; i++)
	{
		vecV = AlgebraLineal::columna_indice(A, N, i);
		vecU = vecV;
		
		j = 0;
		while (i > j)
		{
			vecU = AlgebraLineal::resta_vectores(vecU, AlgebraLineal::proyeccion_vector_vector(vecV, AlgebraLineal::columna_indice(U, N, j), N),N);
			j = j + 1;
		}

		normaliza_vector_2(vecU, N);

		for (int j=0; j < N; j++)
			U[j][i] = vecU[j];
	}

	return U;
}

void AlgebraLineal::factorizacion_QR(vector<vector<double>>& A, vector<vector<double>>& Q, vector<vector<double>>& R, int& N, int& M)
{
	Q = AlgebraLineal::ortogonalizacion_gram_schmidt(A, N, M);
	R = AlgebraLineal::producto_matrizT_matriz(Q, A, M, N, M);
}