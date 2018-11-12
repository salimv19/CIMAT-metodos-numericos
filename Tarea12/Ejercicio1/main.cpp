#include <bits/stdc++.h>
#include "AlgebraLineal.h"

using namespace std;

int main(int argc, char const *argv[])
{
	vector<double> x, y;
	double xIni, xFin, paso, area;
	int nPuntos;

	cout << "\nIntegración por Newton-Cotes (trapecio)\n\n";

	nPuntos = atoi(argv[1]);
	xIni = atof(argv[2]);
	xFin = atof(argv[3]);

	AlgebraLineal::muestrea_funcion_1x(x, y, paso, xIni, xFin, nPuntos);

	area = AlgebraLineal::integracion_numerica_trapecio(y, paso, nPuntos);

	cout << " Área = " << area << endl << endl;

	cout << " Error = " << fabs(log(xFin) - log(xIni) - area) << endl << endl;

	return 0;
}