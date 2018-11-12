#include <bits/stdc++.h>
#include "AlgebraLineal.h"

using namespace std;

const double epsMaquina = numeric_limits<double>::epsilon();

double evalua_funcion_1x(double x)
{
	return 1.0/x;
}

double evalua_funcion_sinx_x(double x)
{
	if (x == 0)
		return 1;
	else
		return sin(x)/x;
}

int main(int argc, char const *argv[])
{
	double pi=3.14159265358979323846264338327950;
	int maxIter;

	cout << "\nIntegración por el método de Romberg\n";

	maxIter = atoi(argv[1]);

	cout << "\nFunción 1/x entre 1 y 10\n\tÁrea = ";
	cout << AlgebraLineal::integracion_numerica_romberg(evalua_funcion_1x, 1, 10, epsMaquina, maxIter) << endl;

	cout << "\nFunción sin(x)/x entre -pi y pi\n\tÁrea = ";
	cout << AlgebraLineal::integracion_numerica_romberg(evalua_funcion_sinx_x, -1.0*pi, pi, epsMaquina, maxIter) << endl;

	return 0;
}