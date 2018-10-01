#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>

/*
Salim Vargas Hernández
Métodos numéricos
Tarea 6
Interpolación con elemento finito
Septiembre 2018
*/

using namespace std;

template <typename T>
void imprime_vector(vector<T> vec)
{
	for (int i=0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

double normal_estandar(double x)
{
	return exp(-1.0*pow(x,2));
}

vector<double> muestrea_funcion(double funcion(double), double& inicio, double& fin, int& nPuntos, vector<double>& x)
{
	vector<double> y(nPuntos);
	double paso;

	paso = (fin - inicio)/(nPuntos - 1);

	for (int i=0; i < nPuntos; i++)
	{
		x[i] = inicio + 1.0*i*paso;
		y[i] = funcion(inicio + 1.0*i*paso);
	}

	return y;
}

void grafica_solucion(vector<double>& xAjustados, vector<double>& yAjustados, bool graficaReal, vector<double> xReal, vector<double> yReal)
{
	string comando, xVec, yVec;

	comando = "python plot.py ";
	xVec = "-x ";
	yVec = "-y ";

	for (int i=0; i < xAjustados.size(); i++)
	{
		xVec = xVec + to_string(xAjustados[i]) + " ";
		yVec = yVec + to_string(yAjustados[i]) + " ";
	}
	comando = comando + xVec + yVec;
	if (graficaReal)
	{
		xVec = "-xT ";
		yVec = "-yT ";
		for (int i=0; i < xReal.size(); i++)
		{
			xVec = xVec + to_string(xReal[i]) + " ";
			yVec = yVec + to_string(yReal[i]) + " ";
		}
		comando = comando + "-t 1 " + xVec + yVec;
	}
	else
		comando = comando + "-t 0";

	system(comando.c_str());
}

bool factoriza_tridiagonal(vector<vector<double>>& A, vector<double>& alpha, vector<double>& beta, vector<double>& gamma)
{
	bool resp;

	resp = true;
	beta.push_back(A[0][1]);
	if (fabs(beta[0]) > 0)
	{
		for (int i=1; i < A.size(); i++)
		{
			alpha.push_back(A[i-1][0]/beta[i-1]);
			gamma.push_back(A[i][2]/beta[i-1]);
			beta.push_back(A[i-1][1]-1.0*A[i][2]*A[i-1][0]/beta[i-1]);
			if (fabs(beta[i]) == 0)
			{
				resp = false;
				break;
			}
		}
	}
	else
		resp = false;


	return resp;
}

void revisa_factorizacion(vector<vector<double>>& A, vector<double>& alpha, vector<double>& beta, vector<double>& gamma, int& N)
{
	for (int i=1; i < N; i++)
	{
		cout << alpha[i-1]*beta[i-1]*gamma[i-1] + beta[i] << endl;
		cout << alpha[i-1]*beta[i-1] << endl;
		cout << beta[i-1]*gamma[i-1] << endl << endl;
	}
}

vector<double> resuelve_sistema_tridiagonal(vector<vector<double>>& A, vector<double>& b, vector<double>& alpha, vector<double>& beta, vector<double>& gamma, int N)
{
	vector<double> x(N), y(N), z(N);

	z[0] = b[0];
	for (int i=1; i < N; i++)
		z[i] = b[i] - alpha[i-1]*z[i-1];
	for (int i=0; i < N; i++)
		y[i] = z[i]/beta[i];
	x[N-1] = y[N-1];
	for (int i=N-2; i >= 0; i--)
		x[i] = y[i] - gamma[i]*x[i+1];

	return x;
}

vector<vector<double>> sistema_tridiagonal_splines(double funcion(double), int N, vector<double>& b, vector<double>& h, vector<double>& y)
{
	vector<vector<double>> A(N, vector<double>(3));

	for (int i=0; i < N-1; i++)
	{
		A[i][0] = h[i+1];
	}

	for (int i =0; i < N-1; i++)
	{
		A[i+1][2] = h[i+1];
	}

	for (int i=0; i < N; i++)
	{
		A[i][1] = 2*(h[i] + h[i+1]);
		b[i] = 6*((y[i+2]-y[i+1])/h[i+1] - (y[i+1]-y[i])/h[i]);
	}
	
	return A;
}

double calcula_spline(double val, int i, vector<double>& sigma, vector<double>& h, vector<double>& x, vector<double>& y)
{
	double spline;

	spline = sigma[i]/6.0 * (pow(x[i+1] - val, 3)/h[i] - h[i]*(x[i+1] - val));
	spline = spline + sigma[i+1]/6.0 * (pow(val - x[i], 3)/h[i] - h[i]*(val - x[i]));
	spline = spline + y[i]/h[i]*(x[i+1] - val) + y[i+1]/h[i]*(val - x[i]);

	return spline;
}

vector<double> aproxima_splines(vector<double>& valores, int& N, vector<double>& sigma, vector<double>& h, vector<double>& x, vector<double>& y)
{
	vector<double> ajustados(N);
	int indice;

	indice = 0;

	for (int i=0; i < N; i++)
	{
		while (valores[i] > x[indice+1] && indice < (x.size()-1))
			indice = indice + 1;

		ajustados[i] = calcula_spline(valores[i], indice, sigma, h, x, y);
	}

	return ajustados;
}

void imprime_aprox_splines(vector<double>& x, vector<double>& y, vector<double>& sigma, vector<double>& h)
{
	cout << endl;
	for (int i=0; i < x.size()-1; i++)
	{
		cout << x[i] << " - " << calcula_spline(x[i], i, sigma, h, x, y) << " vs. " << y[i] << endl;
		cout << x[i+1] << " - " << calcula_spline(x[i+1], i, sigma, h, x, y) << " vs. " << y[i+1] << endl << endl;
	}
}

double ajusta_elemento_finito_lineal(double valor, vector<double>& x, vector<double>& y, int indice)
{
	double psi;

	psi = (valor - x[indice])/(x[indice + 1] - x[indice]);

	return y[indice]*(1 - psi) + y[indice+1]*(psi);
}

vector<double> aproxima_elemento_finito_lineal(vector<double>& valores, int& N, vector<double>& x, vector<double>& y)
{
	vector<double> ajustados(N);
	int indice;

	indice = 0;

	for (int i=0; i < N; i++)
	{
		while(valores[i] > x[indice + 1] && indice < x.size()-2)
			indice = indice + 1;

		ajustados[i] = ajusta_elemento_finito_lineal(valores[i], x, y, indice);
	}

	return ajustados;
}

double ajusta_elemento_finito_cuadratico(double valor, vector<double>& x, vector<double>& y, int indice)
{
	double psi;

	psi = (valor - x[indice])/(x[indice + 2] - x[indice]);

	return y[indice]*(1 - 3*psi + 2*psi*psi) + y[indice+1]*(4*psi - 4*psi*psi) + y[indice+2]*(-psi + 2*psi*psi);
}

vector<double> aproxima_elemento_finito_cuadratico(vector<double>& valores, int& N, vector<double>& x, vector<double>& y)
{
	vector<double> ajustados(N);
	int indice;

	indice = 0;

	for (int i=0; i < N; i++)
	{
		while(valores[i] > x[indice + 2] && indice < x.size()-3)
			indice = indice + 2;

		ajustados[i] = ajusta_elemento_finito_cuadratico(valores[i], x, y, indice);
	}

	return ajustados;
}

double ajusta_elemento_finito_cubico(double valor, vector<double>& x, vector<double>& y, int indice)
{
	double psi;

	psi = (valor - x[indice])/(x[indice + 3] - x[indice]);

	return y[indice]*(1 - 11.0*psi/2 + 9*psi*psi - 9.0/2*psi*psi*psi) + y[indice+1]*(9*psi - 45.0/2*pow(psi,2) + 27.0/2*pow(psi,3)) + y[indice+2]*(-9.0/2*psi + 18*pow(psi,2) - 27.0/2*pow(psi,3)) + y[indice+3]*(psi - 9.0/2*pow(psi,2) + 9.0/2*pow(psi,3));
}

vector<double> aproxima_elemento_finito_cubico(vector<double>& valores, int& N, vector<double>& x, vector<double>& y)
{
	vector<double> ajustados(N);
	int indice;

	indice = 0;

	for (int i=0; i < N; i++)
	{
		while(valores[i] > x[indice + 3] && indice < x.size()-4)
			indice = indice + 3;

		ajustados[i] = ajusta_elemento_finito_cubico(valores[i], x, y, indice);
	}

	return ajustados;
}

int main()
{
	vector<vector<double>> matrizA;
	vector<double> y, yPrueba, ajustados;
	double xIni, xFin;
	int N, nPrueba;

	xIni = -3.0;
	xFin = 3.0;
	N = 13;
	nPrueba = 128;

	vector<double> x(N), xPrueba(nPrueba);

	y = muestrea_funcion(normal_estandar, xIni, xFin, N, x);

	yPrueba = muestrea_funcion(normal_estandar, xIni, xFin, nPrueba, xPrueba);

	ajustados = aproxima_elemento_finito_lineal(xPrueba, nPrueba, x, y);

	grafica_solucion(xPrueba, ajustados, true, x, y);

	ajustados = aproxima_elemento_finito_cuadratico(xPrueba, nPrueba, x, y);

	grafica_solucion(xPrueba, ajustados, true, x, y);

	ajustados = aproxima_elemento_finito_cubico(xPrueba, nPrueba, x, y);

	grafica_solucion(xPrueba, ajustados, true, x, y);

	return 0;
}