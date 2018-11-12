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

double AlgebraLineal::integracion_cuadratura_gaussiana(double f(double), double a, double b, int n)
{
	vector<double> pesos, x;
	double area;

	if (n >= 2 && n <= 4)
	{
		switch (n)
		{
			case 2:
			{
				x = {-1.0*sqrt(1.0/3), sqrt(1.0/3)};
				pesos = {1, 1};
				break;
			}
			case 3:
			{
				x = {-1.0*sqrt(3.0/5), 0, sqrt(3.0/5)};
				pesos = {5.0/9, 8.0/9, 5.0/9};
				break;
			}
			case 4:
			{
				x = {-1.0*sqrt((3 + 2*sqrt(6.0/5))/7.0), -1.0*sqrt((3 - 2*sqrt(6.0/5))/7.0), sqrt((3 - 2*sqrt(6.0/5))/7.0), sqrt((3 + 2*sqrt(6.0/5))/7.0)};
				pesos = {(18 - sqrt(30))/36.0, (18 + sqrt(30))/36.0, (18 + sqrt(30))/36.0, (18 - sqrt(30))/36.0};
				break;
			}
		}

		if (a != -1 || b != 1)
			for (int i=0; i < n; i++)
				x[i] = (b-a)/2.0*x[i] + (a + b)/2.0;

		area = 0;
		for (int i=0; i < n; i++)
			area = area + pesos[i]*f(x[i]);

		if (a != -1 || b != 1)
			area = (b-a)/2.0*area;
	}
	else
		area = NAN;

	return area;
}