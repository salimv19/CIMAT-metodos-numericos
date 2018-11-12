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
	//cout << comando << endl;
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
	vector<vector<double>> coeficientes;
	vector<double> x, y, xPrueba, yPrueba;
	string nombreArchivoMatriz, nombreArchivoVector;
	double xIni, xFin, paso, pasoPrueba;
	int N, nPuntos, NPrueba, nPuntosPrueba;

	cout << "\nINTERPOLACIÓN POR DIFERENCIAS DIVIDIDAS\n\n";

	nPuntos = 6;
	xIni = 0.5;
	xFin = 3.5;
	paso = 1.0*(xFin-xIni)/nPuntos;

	for (int i=0; i < nPuntos+1; i++)
	{
		x.push_back(xIni + paso*i);
		y.push_back(1.0/x[i]);
	}

	N = x.size();

	AlgebraLineal::llena_tabla_polinomios(coeficientes, x, y, N);

	nPuntosPrueba = 19;
	pasoPrueba = 1.0*(xFin-xIni)/nPuntosPrueba;

	for (int i=0; i < nPuntosPrueba+1; i++)
	{
		xPrueba.push_back(xIni + pasoPrueba*i);
		yPrueba.push_back(AlgebraLineal::interpola_nuevo_dato(coeficientes, x, xPrueba[i], N));
	}

	NPrueba = xPrueba.size();

	grafica_muestreo(xPrueba, yPrueba, NPrueba);

	return 0;
}