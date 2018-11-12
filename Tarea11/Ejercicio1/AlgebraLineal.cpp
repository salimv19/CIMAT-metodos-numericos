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

void AlgebraLineal::llena_tabla_polinomios(vector<vector<double>>& coeficientes, vector<double>& x, vector<double>& y, int N)
{
	coeficientes.clear();

	for (int i=0; i < N; i++)
		coeficientes.push_back({y[i]});

	for (int i=1; i < N; i++)
		for (int j=i; j < N; j++)
			coeficientes[j].push_back( (coeficientes[j][i-1] - coeficientes[j-1][i-1]) / (x[j] - x[j-i]) );
}

double AlgebraLineal::interpola_nuevo_dato(vector<vector<double>>& coeficientes, vector<double>& x, double xNuevo, int N)
{
	double y, prod;

	y = 0;
	for (int i=0; i < N; i++)
	{
		prod = 1.0;
		for (int j=0; j < i; j++)
			prod = prod * (xNuevo - x[j]);
		y = y + coeficientes[i][i]*prod;
	}

	return y;
}