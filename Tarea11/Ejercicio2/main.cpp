#include <iostream>
#include <string>
#include <vector>
#include "IOMatrices.h"
#include "AlgebraLineal.h"

using namespace std;

void grafica_muestreo(vector<double>& x, vector<double>& y, int& N)
{
	string comando, xVec, yVec;

	comando = "python plot.py ";
	xVec = "-xV ";
	yVec = "-yV ";
	for (int i=0; i < N; i++)
	{
		xVec = xVec + to_string(x[i]);
		yVec = yVec + to_string(y[i]);
		xVec = xVec + " ";
		yVec = yVec + " ";
	}
	comando = comando + xVec + yVec;
	cout << comando << endl;
	system(comando.c_str());
}

/*void grafica_funcion(int& idFuncion, double& minX, double& maxX, double& x, double& y)
{
	string comando, xVec, yVec;
	double paso;
	int nPuntos;

	nPuntos = 50;
	paso = 1.0*(maxX - minX)/nPuntos;
	comando = "python plot.py ";
	xVec = "-xV ";
	yVec = "-yV ";
	for (int i=0; i < nPuntos + 1 ; i++)
	{
		xVec = xVec + to_string(minX + 1.0*i*paso);
		yVec = yVec + to_string(evalua_funcion(idFuncion, minX + 1.0*i*paso));
		xVec = xVec + " ";
		yVec = yVec + " ";
	}
	comando = comando + xVec + yVec + " -x " + to_string(x) + " -y " + to_string(y);
	system(comando.c_str());
}*/

int main()
{
	vector<double> x, y, xPrueba, yPrueba;
	double xIni, xFin, paso;
	int N, nPuntos;

	cout << "\nINTEGRACIÓN NUMÉRICA POR INTERPOLACIÓN DIRECTA\n\n";

	nPuntos = 9;
	xIni = 1;
	xFin = 2;
	paso = 1.0*(xFin-xIni)/nPuntos;

	for (int i=0; i < nPuntos+1; i++)
	{
		x.push_back(xIni + paso*i);
		y.push_back(1.0/x[i]);
	}

	N = x.size();

	cout << "Área bajo la curva entre x = " << xIni << " y x = " << xFin << ":\n";

	cout << AlgebraLineal::integracion_numerica_interpolacion_vandermonde(x, y, N, N-1, xIni, xFin) << endl;


	return 0;
}