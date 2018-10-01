#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include "MetodoPotenciaInversa.h"

using namespace std;

const double epsMaquina = numeric_limits<double>::epsilon();

MetodoPotenciaInversa::MetodoPotenciaInversa()
{
}

MetodoPotenciaInversa::~MetodoPotenciaInversa()
{
}

bool MetodoPotenciaInversa::abs_compare(double a, double b)
{
    return (fabs(a) < fabs(b));
}

double MetodoPotenciaInversa::producto_punto(vector<double> vec1, vector<double> vec2)
{
	double productoPunto;

	productoPunto = 0;

	for (int i=0; i < vec1.size(); i++)
		productoPunto = productoPunto + vec1[i]*vec2[i];

	return productoPunto;
}

vector<double> MetodoPotenciaInversa::producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M)
{
	vector<double> res(M);
	for (int i=0; i < N; i++)
		res[i] = MetodoPotenciaInversa::producto_punto(A[i], vec);
	return res;
}


/*vector<double> MetodoPotenciaInversa::resta_vectores(vector<double> vecA, vector<double>& vecB, int& N)
{
	vector<double> resta(N);

	for (int i=0; i < N; i++)
	{
		resta[i] = vecA[i] - vecB[i];
	}

	return resta;
}*/

/*double MetodoPotenciaInversa::norma_uno(vector<double>& x)
{
	double norma;
	norma = 0;
	for (int i=0; i < x.size(); i++)
	{
		norma = norma + fabs(x[i]);
	}
	return norma;
}

double MetodoPotenciaInversa::norma_infinito(vector<double>& x)
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
}*/

/*double MetodoPotenciaInversa::norma_dos(vector<double> x, int N)
{
	double norma;

	norma = 0;
	for (int i=0; i < N; i++)
	{
		norma = norma + pow(fabs(x[i]),2);
	}

	return sqrt(norma);
}*/

void MetodoPotenciaInversa::normaliza_vector(vector<double>& x, int N)
{
	double maximo;// cout << max_element(x.begin(), x.end()) << " ";

	maximo = x[distance(x.begin(), max_element(x.begin(), x.end(), abs_compare))]; //cout << maximo << endl;

	for (int i=0; i < N; i++)
		x[i] = 1.0 * x[i] / maximo;
}

vector<double> MetodoPotenciaInversa::resuelve_sistema_triangular_superior_completo(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
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

vector<double> MetodoPotenciaInversa::resuelve_sistema_triangular_inferior_sparse(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
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

bool MetodoPotenciaInversa::factoriza_LU(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U)
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

bool MetodoPotenciaInversa::resuelve_sistema_LU(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int& N)
{
	vector<vector<double>> L(N, vector<double>(N)), U(N, vector<double>(N));
	vector<double> y;
	bool resp;

	resp = true;

	if (MetodoPotenciaInversa::factoriza_LU(A, L, U))
	{
		y = MetodoPotenciaInversa::resuelve_sistema_triangular_inferior_sparse(L, b, N, N);
		x = MetodoPotenciaInversa::resuelve_sistema_triangular_superior_completo(U, y, N, N);
	}
	else
		resp = false;

	return resp;
}

bool MetodoPotenciaInversa::metodo_potencia_inversa(vector<vector<double>>& A, vector<double>& x, double& eigenvalor, int& N, double& tolerancia, int& maxIter, int& iteraciones)
{
	vector<double> aux;
	double eigValAnt;
	int iter;
	bool resp;

	iter = 0;
	resp = true;

	do
	{
		eigValAnt = eigenvalor;
		aux = x;
		MetodoPotenciaInversa::normaliza_vector(aux, N);
		iter = iter + 1;
		if (MetodoPotenciaInversa::resuelve_sistema_LU(A, aux, x, N))
		{
			eigenvalor = MetodoPotenciaInversa::producto_punto(aux, aux)/MetodoPotenciaInversa::producto_punto(aux, x);
		}
		else
		{
			eigenvalor = 0.0;
			eigValAnt = 0.0;
		}

	} while (fabs(fabs(eigenvalor) - fabs(eigValAnt)) > tolerancia && iter < maxIter);

	if (iter >= maxIter)
		resp = false;

	MetodoPotenciaInversa::normaliza_vector(x, N);// for (auto ix:x) cout << ix << " "; cout << endl;
	iteraciones = iter;

	return resp;
}