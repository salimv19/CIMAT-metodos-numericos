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
Splines cúbicos naturales
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

vector<double> muestrea_funcion(double funcion(double), double& inicio, double& fin, int& nPuntos, vector<double>& x, vector<double>& deltaX)
{
	vector<double> y(nPuntos);
	double paso;

	paso = (fin - inicio)/(nPuntos - 1);

	for (int i=0; i < nPuntos; i++)
	{
		x[i] = inicio + 1.0*i*paso;
		y[i] = funcion(inicio + 1.0*i*paso);
	}

	for (int i=0; i < nPuntos - 1; i++)
		deltaX[i] = x[i+1] - x[i];

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

int main()
{
	vector<vector<double>> matrizA;
	vector<double> y, alpha, beta, gamma, x, yPrueba, ajustados;
	double xIni, xFin;
	int N, nPrueba;

	xIni = -3.0;
	xFin = 3.0;
	N = 15;
	nPrueba = 128;

	vector<double> puntos(N), h(N-1), b(N-2), sigma(N), xPrueba(nPrueba), hPrueba(nPrueba-1);

	y = muestrea_funcion(normal_estandar, xIni, xFin, N, puntos, h);

	matrizA = sistema_tridiagonal_splines(normal_estandar, N-2, b, h, y);

	factoriza_tridiagonal(matrizA, alpha, beta, gamma);

	x = resuelve_sistema_tridiagonal(matrizA, b, alpha, beta, gamma, N-2);

	sigma[0] = 0.0;
	for (int i=0; i < N-2; i++)
		sigma[i+1] = x[i];
	sigma[N-1] = 0.0;

	yPrueba = muestrea_funcion(normal_estandar, xIni, xFin, nPrueba, xPrueba, hPrueba);

	ajustados = aproxima_splines(xPrueba, nPrueba, sigma, h, puntos, y);

	grafica_solucion(xPrueba, ajustados, false, puntos, y);

	return 0;
}