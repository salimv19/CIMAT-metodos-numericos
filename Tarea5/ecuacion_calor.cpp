#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

/*
Salim Vargas Hernández
Programación y Algoritmos
Tarea 5
Factorización de Cholesky LDL'
Septiembre 2018
*/

using namespace std;

template <typename T>
void imprime_vector(vector<T> vec)
{
	for (int i=0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

void grafica_solucion(vector<vector<double>>& puntos)
{
	//
}

bool factoriza_tridiagonal(vector<vector<double>>& A, vector<double>& alpha, vector<double>& beta, vector<double>& gamma)
{
	bool resp;

	resp = true;
	beta.push_back(A[0][1]);
	if (fabs(beta[0]) > 0)
	{
		for (int i=1; i < A.size(); i++)
		{
			alpha.push_back(A[i-1][0]/beta[i-1]);
			gamma.push_back(A[i][2]/beta[i-1]);
			beta.push_back(A[i-1][1]-1.0*A[i][2]*A[i-1][0]/beta[i-1]);
			if (fabs(beta[i]) == 0)
			{
				resp = false;
				break;
			}
		}
	}
	else
		resp = false;


	return resp;
}

void revisa_factorizacion(vector<vector<double>>& A, vector<double>& alpha, vector<double>& beta, vector<double>& gamma, int& N)
{
	for (int i=1; i < N; i++)
	{
		cout << alpha[i-1]*beta[i-1]*gamma[i-1] + beta[i] << endl;
		cout << alpha[i-1]*beta[i-1] << endl;
		cout << beta[i-1]*gamma[i-1] << endl << endl;
	}
}

vector<double> resuelve_sistema_tridiagonal(vector<vector<double>>& A, vector<double>& b, vector<double>& alpha, vector<double>& beta, vector<double>& gamma, int& N)
{
	vector<double> x(N), y(N), z(N);

	z[0] = b[0];
	for (int i=1; i < N; i++)
		z[i] = b[i] - alpha[i-1]*z[i-1];
	for (int i=0; i < N; i++)
		y[i] = z[i]/beta[i];
	x[N-1] = y[N-1];
	for (int i=N-2; i >= 0; i--)
		x[i] = y[i] - gamma[i]*x[i+1];

	return x;
}

vector<vector<double>> sistema_calor_tridiagonal(int& N, vector<double>& b, double& Q, double& k, double& dx)
{
	vector<vector<double>> A(N, vector<double>(3));
	double cCalor;

	cCalor = Q*dx*dx/k;
	A[N-1][1] = 2;
	b[N-1] = cCalor;
	for (int i=0; i < N-1; i++)
	{
		A[i][0] = -1;
		A[i][1] = 2;
		A[i+1][2] = -1;

		b[i] = cCalor;
	}
	
	return A;
}

int main()
{
	vector<vector<double>> matrizA, puntos;
	vector<double> x, alpha, beta, gamma;
	double Q, k, dx, toler;
	int N, iter;

	Q = 5.0;
	k = 2.0;
	N = 2;
	iter = 0;
	toler = 1e-2;

	do
	{
		dx = 9.0/(N+1);
		vector<double> b(N);
		matrizA = sistema_calor_tridiagonal(N, b, Q, k, dx);

		factoriza_tridiagonal(matrizA, alpha, beta, gamma);

		x = resuelve_sistema_tridiagonal(matrizA, b, alpha, beta, gamma, N);

		puntos.push_back(x);

		N = N*2;
		iter = iter + 1;
		alpha.clear();
		beta.clear();
		gamma.clear();
	} while(fabs(x[N/2-1] - x[N/2]) > toler);

	grafica_solucion(puntos);

	cout << x[N/4] << endl;

	cout << iter << endl;

	return 0;
}