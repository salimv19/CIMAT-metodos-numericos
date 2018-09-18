#include <iostream>
#include "AlgebraLineal.h"

/*
Salim Vargas Hernández
Programación y Algoritmos
Tarea 3
Redes neuronales
Septiembre 2018
*/

using namespace std;

AlgebraLineal::AlgebraLineal()
{
}

AlgebraLineal::~AlgebraLineal()
{
}

double AlgebraLineal::norma_uno(vector<double>& x)
{
	double norma;
	norma = 0;
	for (int i=0; i < x.size(); i++)
	{
		norma = norma + fabs(x[i]);
	}
	return norma;
}

double AlgebraLineal::norma_infinito(vector<double>& x)
{
	double norma;
	norma = 0;
	for (int i=0; i < x.size(); i++)
	{
		if (fabs(x[i]) > norma)
		{
			norma = fabs(x[i]);
		}
	}
	return norma;
}

double AlgebraLineal::producto_punto(vector<double>& vec1, vector<double>& vec2)
{
	double productoPunto;

	productoPunto = 0;

	for (int i=0; i < vec1.size(); i++)
		productoPunto = productoPunto + vec1[i]*vec2[i];

	return productoPunto;
}

vector<int> AlgebraLineal::encuentra_mayor_matriz(vector<vector<double>>& matriz, int& N, int& M, int& fila, int& columna)
{
	vector<int> posicion;
	double mayor;

	posicion = {0,0};
	mayor = 0.0;

	for (int i=fila; i < N; i++)
	{
		for (int j=columna; j < M; j++)
		{
			if (fabs(matriz[i][j]) > mayor)
			{
				posicion = {i,j};
				mayor = fabs(matriz[i][j]);
			}
		}
	}

	return posicion;
}

vector<double> AlgebraLineal::resuelve_sistema_diagonal_sparse(vector<double>& matriz, vector<double>& b, int& N)
{
	vector<double> x(N);
	
	for (int i=0; i < N; i++)
	{
		if (matriz[i] != 0)
		{
			x[i] = b[i]/matriz[i];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
			break;
		}
	}

	return x;
}

vector<double> AlgebraLineal::resuelve_sistema_triangular_superior_sparse(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector<double> x(N);
	double suma;
	
	for (int i=0; i < N; i++)
	{
		if (matriz[N-1-i][0] != 0)
		{
			suma = 0;
			for (int j=0; j < i; j++)
			{
				suma = suma + matriz[N-1-i][i-j]*x[N-1-j];
			}
			x[N-1-i] = (b[N-1-i] - suma)/matriz[N-1-i][0];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
			break;
		}
	}

	return x;
}

vector<double> AlgebraLineal::resuelve_sistema_triangular_superior_completo(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector<double> x(N);
	double suma;
	
	for (int i=0; i < N; i++)
	{
		if (matriz[N-1-i][N-1-i] != 0)
		{
			suma = 0;
			for (int j=0; j < i; j++)
			{
				suma = suma + matriz[N-1-i][N-1-j]*x[N-1-j];
			}
			x[N-1-i] = (b[N-1-i] - suma)/matriz[N-1-i][N-1-i];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
			break;
		}
	}

	return x;
}

vector<double> AlgebraLineal::resuelve_sistema_triangular_inferior_sparse(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector<double> x(N);
	double suma;
	
	for (int i=0; i < N; i++)
	{
		if (matriz[i][i] != 0)
		{
			suma = 0;
			for (int j=0; j < i; j++)
			{
				suma = suma + matriz[i][j]*x[j];
			}
			x[i] = (b[i] - suma)/matriz[i][i];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
			break;
		}
	}

	return x;
}

void AlgebraLineal::eliminacion_gaussiana(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	double factor;

	for (int i=0; i < N-1; i++)
	{
		for (int j=i+1; j < N; j++)
		{
			if (matriz[i][i] != 0)
			{
				factor = matriz[j][i]/matriz[i][i];
				for (int k=i; k < N; k++)
				{
					matriz[j][k] = matriz[j][k] - matriz[i][k]*factor;
				}
				b[j] = b[j] - b[i]*factor;
			}
			else
			{
				cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
				break;
			}
		}
	}
}

void AlgebraLineal::intercambia_renglon_columna(vector<vector<double>>& matriz, vector<int>& indices, vector<double>& b, int& N, int& M, int& renglonA, int& columnaA, int& renglonB, int& columnaB)
{
	vector<double> auxRenglon;
	double aux;
	int auxi;

	//Intercambio de renglón
	auxRenglon = matriz[renglonA];
	matriz[renglonA] = matriz[renglonB];
	matriz[renglonB] = auxRenglon;

	aux = b[renglonA];
	b[renglonA] = b[renglonB];
	b[renglonB] = aux;

	//Intercambio de columna
	for (int i=0; i < M; i++)
	{
		aux = matriz[i][columnaA];
		matriz[i][columnaA] = matriz[i][columnaB];
		matriz[i][columnaB] = aux;
	}
	auxi = indices[columnaA];
	indices[columnaA] = indices[columnaB];
	indices[columnaB] = auxi;
}

vector<int> AlgebraLineal::eliminacion_gaussiana_pivoteo(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector <int> indices(N), indMayor;
	double factor;

	iota(indices.begin(), indices.end(), 0);

	for (int i=0; i < N-1; i++)
	{
		//Pivoteo
		indMayor = encuentra_mayor_matriz(matriz, N, M, i, i);
		if (indMayor[0] != i & indMayor[1] != i)
		{
			intercambia_renglon_columna(matriz, indices, b, N, M, i, i, indMayor[0], indMayor[1]);
		}
		//Eliminacion gaussiana
		for (int j=i+1; j < N; j++)
		{
			if (matriz[i][i] != 0)
			{
				factor = matriz[j][i]/matriz[i][i];
				for (int k=i; k < N; k++)
				{
					matriz[j][k] = matriz[j][k] - matriz[i][k]*factor;
				}
				b[j] = b[j] - b[i]*factor;
			}
			else
			{
				cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
				break;
			}
		}
	}

	return indices;
}

