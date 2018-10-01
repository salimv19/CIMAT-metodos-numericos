#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include "MetodoPotencia.h"

using namespace std;

MetodoPotencia::MetodoPotencia()
{
}

MetodoPotencia::~MetodoPotencia()
{
}

bool MetodoPotencia::abs_compare(double a, double b)
{
    return (fabs(a) < fabs(b));
}

double MetodoPotencia::producto_punto(vector<double> vec1, vector<double> vec2)
{
	double productoPunto;

	productoPunto = 0;

	for (int i=0; i < vec1.size(); i++)
		productoPunto = productoPunto + vec1[i]*vec2[i];

	return productoPunto;
}

vector<double> MetodoPotencia::producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M)
{
	vector<double> res(M);
	for (int i=0; i < N; i++)
		res[i] = MetodoPotencia::producto_punto(A[i], vec);
	return res;
}


/*vector<double> MetodoPotencia::resta_vectores(vector<double> vecA, vector<double>& vecB, int& N)
{
	vector<double> resta(N);

	for (int i=0; i < N; i++)
	{
		resta[i] = vecA[i] - vecB[i];
	}

	return resta;
}*/

/*double MetodoPotencia::norma_uno(vector<double>& x)
{
	double norma;
	norma = 0;
	for (int i=0; i < x.size(); i++)
	{
		norma = norma + fabs(x[i]);
	}
	return norma;
}

double MetodoPotencia::norma_infinito(vector<double>& x)
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

/*double MetodoPotencia::norma_dos(vector<double> x, int N)
{
	double norma;

	norma = 0;
	for (int i=0; i < N; i++)
	{
		norma = norma + pow(fabs(x[i]),2);
	}

	return sqrt(norma);
}*/

void MetodoPotencia::normaliza_vector(vector<double>& x, int N)
{
	double maximo;// cout << max_element(x.begin(), x.end()) << " ";

	maximo = x[distance(x.begin(), max_element(x.begin(), x.end(), abs_compare))]; //cout << maximo << endl;

	for (int i=0; i < N; i++)
		x[i] = 1.0 * x[i] / maximo;
}

bool MetodoPotencia::metodo_potencia(vector<vector<double>>& A, vector<double>& x, double& eigenvalor, int& N, double& tolerancia, int& maxIter, int& iteraciones)
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
		MetodoPotencia::normaliza_vector(aux, N);
		iter = iter + 1;
		x = MetodoPotencia::producto_matriz_vector(A, aux, N, N);

		eigenvalor = MetodoPotencia::producto_punto(aux, x)/MetodoPotencia::producto_punto(aux, aux);// cout << eigenvalor << endl;
		//for (auto ix:x) cout << ix << " "; cout << endl;

	} while (fabs(fabs(eigenvalor) - fabs(eigValAnt)) > tolerancia && iter < maxIter);

	if (iter >= maxIter)
		resp = false;

	MetodoPotencia::normaliza_vector(x, N);// for (auto ix:x) cout << ix << " "; cout << endl;
	iteraciones = iter;

	return resp;
}