#include <bits/stdc++.h>
#include "AlgebraLineal.h"

using namespace std;

double evalua_densidad_normal_0_3(double x)
{
	double pi = 3.14159265358979323846264;

	return 1.0/(3*sqrt(2*pi))*exp(-0.5*pow(x/3.0,2));
}

int main()
{
	double area;

	cout << "\nIntegración por Cuadratura Gaussiana\n";

	cout << "\nP(-3/2 < X < 3/2) = " << (0.6915-0.3085) << endl;
	for (int n=2; n <= 4; n++)
	{
		area = AlgebraLineal::integracion_cuadratura_gaussiana(evalua_densidad_normal_0_3, -3.0/2, 3.0/2, n);
		cout << "\tn = " << n << "\tAproximación = " << area << "   \tError = " << fabs((0.6915-0.3085) - area) << endl;
	}

	cout << "\nP(-3 < X < 3) = " << (0.8413-0.1587) << endl;
	for (int n=2; n <= 4; n++)
	{
		area = AlgebraLineal::integracion_cuadratura_gaussiana(evalua_densidad_normal_0_3, -3.0, 3.0, n);
		cout << "\tn = " << n << "\tAproximación = " << area << "   \tError = " << fabs((0.8413-0.1587) - area) << endl;
	}

	cout << "\nP(-9/2 < X < 9/2) = " << (0.9332-0.0668) << endl;
	for (int n=2; n <= 4; n++)
	{
		area = AlgebraLineal::integracion_cuadratura_gaussiana(evalua_densidad_normal_0_3, -9.0/2, 9.0/2, n);
		cout << "\tn = " << n << "\tAproximación = " << area << "   \tError = " << fabs((0.9332-0.0668) - area) << endl;
	}

	cout << "\nP(-9 < X < 9) = " << (0.9987-0.0013) << endl;
	for (int n=2; n <= 4; n++)
	{
		area = AlgebraLineal::integracion_cuadratura_gaussiana(evalua_densidad_normal_0_3, -9.0, 9.0, n);
		cout << "\tn = " << n << "\tAproximación = " << area << "   \tError = " << fabs((0.9987-0.0013) - area) << endl;
	}

	return 0;
}