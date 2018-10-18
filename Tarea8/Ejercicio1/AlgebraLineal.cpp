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

AlgebraLineal::AlgebraLineal()
{
}

AlgebraLineal::~AlgebraLineal()
{
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

vector<vector<double>> AlgebraLineal::matriz_triangular_superior(vector<vector<double>>& A, int& N)
{
	vector<vector<double>> S(N, vector<double>(N));

	for (int i=0; i < N - 1; i++)
		for (int j=i+1; j < N; j++)
			S[i][j] = A[i][j];

	return S;
}

vector<int> AlgebraLineal::maximo_absoluto_matriz(vector<vector<double>>& A, int& N, int& M)
{
	vector<int> posicion(2);
	double maximo;

	maximo = 0;
	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			if (fabs(A[i][j]) > maximo)
			{
				maximo = fabs(A[i][j]);
				posicion = {i,j};
			}

	return posicion;
}

vector<vector<double>> AlgebraLineal::matriz_identidad(int& N)
{
	vector<vector<double>> I(N, vector<double>(N));

	for (int i=0; i < N; i++)
		I[i][i] = 1.0;

	return I;
}


bool AlgebraLineal::metodo_jacobi_eigenvalores(vector<vector<double>>& A, vector<vector<double>>& C, vector<vector<double>>& P, int& N, double& tolerancia, int& maxIter)
{
	vector<vector<double>> S, B, P_i;
	vector<int> posMax;
	double m, theta, pi = 3.1415926535897932384626433832795;
	int iter, k, l;
	bool converge;

	C = A;
	P = AlgebraLineal::matriz_identidad(N);

	iter = 0;
	converge = false;

	do
	{
		S = AlgebraLineal::matriz_triangular_superior(C, N);
		posMax = AlgebraLineal::maximo_absoluto_matriz(S, N, N);
		k = posMax[0];
		l = posMax[1];

		if (fabs(C[k][l]) > tolerancia)
		{
			if (C[l][l] == C[k][k])
				theta = pi/4;
			else
				theta = atan2(2*C[k][l], (C[l][l] - C[k][k]));


			P_i = AlgebraLineal::matriz_identidad(N);
			P_i[k][k] = cos(theta);
			P_i[l][l] = cos(theta);
			P_i[l][k] = sin(theta);
			P_i[k][l] = -1.0*sin(theta);

			B = AlgebraLineal::producto_matriz_matriz(C, P_i, N, N, N);
			C = AlgebraLineal::producto_matrizT_matriz(P_i, B, N, N, N);

			P = AlgebraLineal::producto_matriz_matriz(P, P_i, N, N, N);
		}
		else
		{
			converge = true;
		}

		iter = iter + 1;

	} while(!converge && iter < maxIter);

	return converge;
}