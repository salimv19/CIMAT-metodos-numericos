#include <bits/stdc++.h>
#include "AlgebraLineal.h"

using namespace std;

int main(int argc, char const *argv[])
{
	vector<double> x, y;
	double xIni, xFin, paso, area;
	int nPuntos;

	cout << "\nIntegración por Newton-Cotes (Simpson 3/8)\n\n";

	nPuntos = atoi(argv[1]);
	xIni = atof(argv[2]);
	xFin = atof(argv[3]);

	nPuntos = (nPuntos/3)*3 + 1;

	AlgebraLineal::muestrea_funcion_1x(x, y, paso, xIni, xFin, nPuntos);

	area = AlgebraLineal::integracion_numerica_simpson_38(y, paso, nPuntos);

	cout << " Área = " << area << endl << endl;

	cout << " Error = " << fabs(log(xFin) - log(xIni) - area) << endl << endl;

	return 0;
}