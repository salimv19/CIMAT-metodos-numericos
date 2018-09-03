#include <iostream>
#include <fstream>
#include <string>
//#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;


template <typename T>
void imprime_vector(vector<T>& vec)
{
	cout << endl;
	for (int i=0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
	cout << endl;
}

double evalua_funcion(int& idFuncion, double x)
{
	switch (idFuncion)
	{
		case 1: return 5.0*x/4 - 0.5;

		case 2: return x*x - 2.0*x - 2.0;

		case 3: return 2.0*x*x*x - 5.0*x*x + 2.0*x + 5.0;

		case 4: return -5.0*sin(x);

		case 5: return 1.0/x;
	}
}

double evalua_derivada(int& idFuncion, double& x)
{
	switch (idFuncion)
	{
		case 1: return 5.0/4;

		case 2: return 2.0*x - 2.0;

		case 3: return 6.0*x*x - 10.0*x + 2.0;

		case 4: return -5.0*cos(x);

		case 5: return -1.0/(x*x);
	}
}

void grafica_funcion(int& idFuncion, double& minX, double& maxX, double& x, double& y)
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
}

int metodo_newton_raphson(int& idFuncion, vector<double>& x, vector<double>& y, double& minX, double& maxX, double& tolX, double& tolY, int& maxIter)
{
	double xAnterior, derivada;
	int iter;

	iter = 0;
	do
	{
		xAnterior = x[iter];
		derivada = evalua_derivada(idFuncion, xAnterior);

		if (derivada != 0.0)
		{
			x.push_back(xAnterior - y[iter]/derivada);
			y.push_back(evalua_funcion(idFuncion, x[iter+1]));
			iter = iter + 1;
		}
		else
		{
			cout << "ERROR. Derivada igual a 0. Punto silla o mínimo/máximo local\n";
			break;
		}
	}while(fabs(y[iter]) > tolY & fabs(x[iter]-xAnterior)/fabs(x[iter]) > tolX & x[iter] >= minX & x[iter] <= maxX & iter < maxIter);

	return iter;
}

int metodo_biseccion(int& idFuncion, double& xA, double& xB, double& x, double& tolX, double& y, double& tolY, int& maxIter)
{
	double yA, yB, xP, yP;
	int iter;

	iter = 0;
	yA = evalua_funcion(idFuncion, xA);
	yB = evalua_funcion(idFuncion, xB);
	if (yA*yB < 0)
	{
		do
		{
			iter = iter + 1;
			xP = (xA + xB)/2.0;
			yP = evalua_funcion(idFuncion, xP);
			if (fabs(yP) <= tolY)
			{
				x = xP;
				y = yP;
				return iter;
			}
			if (yA*yP < 0)
			{
				xB = xP;
				yB = yP;
			}
			else
			{
				xA = xP;
				yA = yP;
			}
			if (yA < yB)
			{
				x = xA;
				y = yA;
			}
			else
			{
				x = xB;
				y = yB;
			}
		}while(fabs(y) > tolY & fabs(xA-xB)/fabs(xA) > tolX & iter < maxIter);
	}
	else
	{
		if (yA*yB > 0)
		{
			cout << "ERROR. Los valores de la función evaluada en los extremos del intervalo tienen el mismo signo\n";
		}
		else
		{
			if (yA == 0)
			{
				x = xA;
				y = yA;
			}
			else
			{
				x = xB;
				y = yB;
			}
		}
	}

	return iter;
}

void imprime_resultados(vector<string>& palabras, vector<double>& probabilidades)
{
	string cadena;

	for (int i=0; i < palabras.size(); i++)
	{
		cadena.append(" \"");
		cadena.append(palabras[i]);
		cadena.append("\"");
	}

	cout << "P(spam |" << cadena << ") = " << probabilidades[0] << endl;
	cout << "P(no spam |" << cadena << ") = " << probabilidades[1] << endl;

	if (probabilidades[0] > probabilidades[1])
	{
		cout << "\n\tEl e-mail se considera SPAM\n" << endl;
	}
	else
	{
		cout << "\n\tEl e-mail se considera NO SPAM\n" << endl;
	}
}

int main()
{
	vector<double> xVec, yVec;
	double tolX, tolY, minX, maxX, x, y;
	int iter, idFuncion, maxIter;

	tolX = 1.0e-6;
	tolY = 1.0e-6;
	maxIter = 50;

	cout << "ID Función: ";
	cin >> idFuncion;

	switch (idFuncion)
	{
		case 1:
		{
			minX = -1.0;
			maxX = 1.0;
			xVec.push_back(0.0);
			break;
		}
		case 2:
		{
			minX = -1.0;
			maxX = 1.0;
			xVec.push_back(0.0);
			break;
		}
		case 3:
		{
			minX = -10.0;
			maxX = 10.0;
			xVec.push_back(0.0);
			break;
		}
		case 4:
		{
			minX = 0.0;
			maxX = 10.0;
			xVec.push_back(0.0);
			break;
		}
		case 5:
		{
			minX = -0.9;
			maxX = 1.0;
			xVec.push_back(0.1);
			break;
		}
	}
	
	yVec.push_back(evalua_funcion(idFuncion, xVec[0]));
	iter = metodo_newton_raphson(idFuncion, xVec, yVec, minX, maxX, tolX, tolY, maxIter);

	cout << "METODO DE NEWTON\n";
	cout << iter << "\n" << xVec[iter] << "\t" << yVec[iter] << endl;

	grafica_funcion(idFuncion, minX, maxX, xVec[iter], yVec[iter]);

	cout << "METODO DE BISECCIÓN\n";
	iter = metodo_biseccion(idFuncion, minX, maxX, x, tolX, y, tolY, maxIter);
	cout << iter << "\n" << x << "\t" << y << endl;

	return 0;
}