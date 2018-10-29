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

double producto_punto(vector<double> vec1, vector<double> vec2)
{
	double productoPunto;

	productoPunto = 0;

	for (int i=0; i < vec1.size(); i++)
		productoPunto = productoPunto + vec1[i]*vec2[i];

	return productoPunto;
}

vector<double> AlgebraLineal::producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M)
{
	vector<double> res(M);
	for (int i=0; i < N; i++)
		res[i] = producto_punto(A[i], vec);
	return res;
}

vector<vector<double>> AlgebraLineal::producto_matriz_matriz(vector<vector<double>>& A, vector<vector<double>>& B, int& N, int& M, int& L)
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

vector<double> resuelve_sistema_triangular_superior_completo(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector<double> x(N);
	double suma;
	
	for (int i=0; i < N; i++)
	{
		if (matriz[N-1-i][N-1-i] != 0)
		{
			suma = 0;
			for (int j=0; j < i; j++)
			{
				suma = suma + matriz[N-1-i][N-1-j]*x[N-1-j];
			}
			x[N-1-i] = (b[N-1-i] - suma)/matriz[N-1-i][N-1-i];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
			break;
		}
	}

	return x;
}

vector<double> resuelve_sistema_triangular_inferior_sparse(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector<double> x(N);
	double suma;
	
	for (int i=0; i < N; i++)
	{
		if (matriz[i][i] != 0)
		{
			suma = 0;
			for (int j=0; j < i; j++)
			{
				suma = suma + matriz[i][j]*x[j];
			}
			x[i] = (b[i] - suma)/matriz[i][i];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
			break;
		}
	}

	return x;
}

bool factoriza_LU(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U)
{
	double suma;
	int i;
	bool resp;

	resp = true;
	i = 0;

	for (int i=0; i < A.size(); i++)
	{
		L[i][i] = 1.0;

		suma = 0.0;
		for (int k=0; k <= i-1; k++)
			suma = suma + L[i][k]*U[k][i];
		U[i][i] = A[i][i] - suma;

		if (fabs(U[i][i]) > epsMaquina)
		{
			for (int j=i+1; j < A[i].size(); j++)
			{
				suma = 0.0;
				for (int k=0; k <= i-1 ; k++)
					suma = suma + L[i][k]*U[k][j];
				U[i][j] = A[i][j] - suma;
			}

			for (int j=i+1; j < A[i].size(); j++)
			{
				suma = 0.0;
				for (int k=0; k <= i-1 ; k++)
					suma = suma + L[j][k]*U[k][i];
				L[j][i] = (A[j][i] - suma)/U[i][i];
			}
		}
		else
		{
			cout << "\n\tERROR. No se pudo factorizar LU\n\n";
			resp = false;
			break;
		}
	}

	return resp;
}

bool AlgebraLineal::invierte_matriz(vector<vector<double>>& A, vector<vector<double>>& inversa)
{
	int N;
	bool resp;

	resp = true;
	N = A.size();

	vector<vector<double>> L(N, vector<double>(N)), U(N, vector<double>(N));
	vector<double> canonico(N), x, y;

	if (factoriza_LU(A, L, U))
	{
		for (int i=0; i < N; i++)
		{
			canonico[i] = 1;

			y = resuelve_sistema_triangular_inferior_sparse(L, canonico, N, N);
			x = resuelve_sistema_triangular_superior_completo(U, y, N, N);

			for (int j=0; j < N; j++)
				inversa[j][i] = x[j];

			canonico[i] = 0;
		}
	}
	else
	{
		resp = false;
	}

	return resp;
}