#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include "AlgebraLineal.h"

using namespace std;

const double epsMaquina = numeric_limits<double>::epsilon();

AlgebraLineal::AlgebraLineal()
{
}

AlgebraLineal::~AlgebraLineal()
{
}

void AlgebraLineal::muestrea_funcion_1x(vector<double>& x, vector<double>& y, double& paso, double a, double b, int nPuntos)
{
	x.clear();
	y.clear();

	paso = 1.0*(b - a)/(nPuntos-1);

	for (int i=0; i < nPuntos; i++)
	{
		x.push_back(a + paso*i);
		y.push_back(1.0/x[i]);
	}
}

double AlgebraLineal::integracion_numerica_simpson_13(vector<double>& y, double dx, int nPuntos)
{
	double area;
	int i;

	area = 0;
	i = 0;
	while (i < nPuntos-2)
	{
		area = area + 1.0*(y[i] + 4*y[i+1] + y[i+2])*dx/3;
		i = i + 2;
	}

	return area;
}