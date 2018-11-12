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

bool resuelve_sistema_LU(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int& N)
{
	vector<vector<double>> L(N, vector<double>(N)), U(N, vector<double>(N));
	vector<double> y;
	bool resp;

	resp = true;

	if (factoriza_LU(A, L, U))
	{
		y = resuelve_sistema_triangular_inferior_sparse(L, b, N, N);
		x = resuelve_sistema_triangular_superior_completo(U, y, N, N);
	}
	else
		resp = false;

	return resp;
}

void coeficientes_vandermonde(vector<double>& x, vector<double>& y, vector<double>& coeficientes, int N, int grado)
{
	vector<vector<double>> vandermonde(N, vector<double>(grado+1));

	for (int i=0; i < N; i++)
		for (int j=0; j <= grado; j++)
			vandermonde[i][j] = pow(x[i],j);

	resuelve_sistema_LU(vandermonde, y, coeficientes, N);
}

double AlgebraLineal::integracion_numerica_interpolacion_vandermonde(vector<double>& x, vector<double>& y, int N, int grado, double a, double b)
{
	vector<double> coeficientes;
	double area;

	coeficientes_vandermonde(x, y, coeficientes, N, grado);

	area = 0;
	for (int i=0; i <= grado; i++)
	{
		area = area + 1.0*coeficientes[i]*( pow(b,i+1) - pow(a,i+1) )/(i+1);
	}

	return area;
}