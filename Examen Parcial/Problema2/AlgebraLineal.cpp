#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <map>
#include "IOMatrices.h"
#include "AlgebraLineal.h"

using namespace std;

const double epsMaquina = numeric_limits<double>::epsilon();

AlgebraLineal::AlgebraLineal()
{
}

AlgebraLineal::~AlgebraLineal()
{
}

bool abs_compare(double a, double b)
{
    return (fabs(a) < fabs(b));
}

void resta_vectores(vector<double>& vecA, vector<double>& vecB, vector<double>& resta, int& N)
{
	for (int i=0; i < N; i++)
	{
		resta[i] = vecA[i] - vecB[i];
	}
}

double producto_punto(vector<double> vec1, vector<double> vec2)
{
	double productoPunto;

	productoPunto = 0;

	for (int i=0; i < vec1.size(); i++)
		productoPunto = productoPunto + vec1[i]*vec2[i];

	return productoPunto;
}

double AlgebraLineal::norma_dos(vector<double> x, int N)
{
	double norma;

	norma = 0;
	for (int i=0; i < N; i++)
	{
		norma = norma + pow(fabs(x[i]),2);
	}

	return sqrt(norma);
}

/*vector<double> AlgebraLineal::producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M)
{
	vector<double> res(M);
	for (int i=0; i < N; i++)
		res[i] = producto_punto(A[i], vec);
	return res;
}*/

void AlgebraLineal::producto_matriz_sparse_vector(vector<map<int,double>>& A, vector<double>& vec, vector<double>& prod, int& filas)
{
	double suma;
	for (int i=0; i < filas; i++)
	{
		suma = 0.0;
		for (auto valor:A[i])
			suma = suma + valor.second * vec[valor.first];
		prod[i] = suma;
	}
}

/*void gradiente_conjugado_precondicionado_jacobi(vector<vector<double>>& A, vector<double>& b, vector<double>& x, vector<double>& residuo, int& N, int& iteraciones)
{
	vector<double> direccion(N), auxVec, nuevoResiduo(N), residuoPrecondicionado(N), nuevoResiduoPrecondicionado(N);
	double alpha, beta;
	int iter;

	residuo = resta_vectores(producto_matriz_vector(A, x, N, N), b, N);
	for (int i=0; i < N; i++)
		residuoPrecondicionado[i] = 1.0*residuo[i]/A[i][i];

	direccion = residuoPrecondicionado;

	iter = 0;
	normaResiduo = norma_dos(residuo, N);
	while (normaResiduo > epsMaquina && iter < N)
	{
		iter = iter + 1;

		auxVec = producto_matriz_vector(A, direccion, N, N);
		alpha = producto_punto(residuo, residuoPrecondicionado) / producto_punto(direccion, auxVec);

		//Se aplica un for en lugar de métodos de la clase para ejecutar todo en un sólo ciclo y sin crear más vectores
		//El código es incluso más claro de esta forma, incluso es más facilmente paralelizable
		for (int i=0; i < N; i++)
		{
			x[i] = x[i] + alpha*direccion[i];
			nuevoResiduo[i] = residuo[i] - alpha*auxVec[i];
		}

		for (int i=0; i < N; i++)
			nuevoResiduoPrecondicionado = 1.0*nuevoResiduo[i]/A[i][i];

		beta = producto_punto(nuevoResiduo, nuevoResiduoPrecondicionado) / producto_punto(residuo, residuoPrecondicionado);

		//Se aplica un for en lugar de métodos de la clase para ejecutar todo en un sólo ciclo y sin crear más vectores
		//El código es incluso más claro de esta forma, incluso es más facilmente paralelizable
		for (int i=0; i < N; i++)
			direccion[i] = nuevoResiduo[i] + beta*direccion[i];

		residuo = nuevoResiduo;
		residuoPrecondicionado = nuevoResiduoPrecondicionado;
		normaResiduo = norma_dos(residuo, N);
	}

	iteraciones = iter - 1;
}*/

void AlgebraLineal::gradiente_conjugado_sparse(vector<map<int,double>>& A, vector<double>& b, vector<double>& x, vector<double>& residuo, int& N, int& iteraciones)
{
	vector<double> direccion(N), auxVec(N);
	double normaResiduo, nuevaNormaResiduo, alpha, beta;
	int iter;

	producto_matriz_sparse_vector(A, x, auxVec, N);
	resta_vectores(auxVec, b, residuo, N);
	for (int i=0; i < N; i++)
		direccion[i] = -1*residuo[i];

	iter = 0;
	normaResiduo = norma_dos(residuo, N);
	while (1.0*normaResiduo/(N*N) > epsMaquina && iter < N)
	{
		iter = iter + 1;

		producto_matriz_sparse_vector(A, direccion, auxVec, N);
		alpha = pow(normaResiduo,2) / producto_punto(direccion, auxVec);

		//Se aplica un for en lugar de métodos de la clase para ejecutar todo en un sólo ciclo y sin crear más vectores
		//El código es incluso más claro de esta forma, incluso es más facilmente paralelizable
		for (int i=0; i < N; i++)
		{
			x[i] = x[i] + alpha*direccion[i];
			residuo[i] = residuo[i] + alpha*auxVec[i];
		}

		nuevaNormaResiduo = norma_dos(residuo, N);

		beta = pow(nuevaNormaResiduo, 2) / pow(normaResiduo, 2);

		//Se aplica un for en lugar de métodos de la clase para ejecutar todo en un sólo ciclo y sin crear más vectores
		//El código es incluso más claro de esta forma, incluso es más facilmente paralelizable
		for (int i=0; i < N; i++)
			direccion[i] = -1*residuo[i] + beta*direccion[i];

		normaResiduo = nuevaNormaResiduo;
	}

	iteraciones = iter - 1;
}

void AlgebraLineal::gradiente_conjugado_precondicionado_jacobi_sparse(vector<map<int,double>>& A, vector<double>& b, vector<double>& x, vector<double>& residuo, int& N, int& iteraciones)
{
	vector<double> direccion(N), auxVec(N), nuevoResiduo(N), residuoPrecondicionado(N), nuevoResiduoPrecondicionado(N);
	map<int,double> mapAux;
	double alpha, beta, normaResiduo;
	int iter;

	producto_matriz_sparse_vector(A, x, auxVec, N);
	resta_vectores(auxVec, b, residuo, N);
	for (int i=0; i < N; i++)
	{
		mapAux = A[i];
		residuoPrecondicionado[i] = 1.0*residuo[i]/mapAux[i];
	}

	direccion = residuoPrecondicionado;

	iter = 0;
	normaResiduo = norma_dos(residuo, N);
	while (normaResiduo > epsMaquina && iter < N)
	{
		iter = iter + 1;

		producto_matriz_sparse_vector(A, direccion, auxVec, N);
		alpha = producto_punto(residuo, residuoPrecondicionado) / producto_punto(direccion, auxVec);

		//Se aplica un for en lugar de métodos de la clase para ejecutar todo en un sólo ciclo y sin crear más vectores
		//El código es incluso más claro de esta forma, incluso es más facilmente paralelizable
		for (int i=0; i < N; i++)
		{
			x[i] = x[i] + alpha*direccion[i];
			nuevoResiduo[i] = residuo[i] - alpha*auxVec[i];
		}

		for (int i=0; i < N; i++)
		{
			mapAux = A[i];
			nuevoResiduoPrecondicionado[i] = 1.0*nuevoResiduo[i]/mapAux[i];
		}

		beta = producto_punto(nuevoResiduo, nuevoResiduoPrecondicionado) / producto_punto(residuo, residuoPrecondicionado);

		//Se aplica un for en lugar de métodos de la clase para ejecutar todo en un sólo ciclo y sin crear más vectores
		//El código es incluso más claro de esta forma, incluso es más facilmente paralelizable
		for (int i=0; i < N; i++)
			direccion[i] = nuevoResiduo[i] + beta*direccion[i];

		residuo = nuevoResiduo;
		residuoPrecondicionado = nuevoResiduoPrecondicionado;
		normaResiduo = norma_dos(residuo, N);
	}

	iteraciones = iter - 1;
}

vector<double> resuelve_sistema_triangular_superior_completo(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
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

vector<double> resuelve_sistema_triangular_inferior_sparse(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
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

bool factoriza_LU(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U)
{
	double suma;
	int i;
	bool resp;

	resp = true;
	i = 0;

	for (int i=0; i < A.size(); i++)
	{
		L[i][i] = 1.0;

		suma = 0.0;
		for (int k=0; k <= i-1; k++)
			suma = suma + L[i][k]*U[k][i];
		U[i][i] = A[i][i] - suma;

		if (fabs(U[i][i]) > epsMaquina)
		{
			for (int j=i+1; j < A[i].size(); j++)
			{
				suma = 0.0;
				for (int k=0; k <= i-1 ; k++)
					suma = suma + L[i][k]*U[k][j];
				U[i][j] = A[i][j] - suma;
			}

			for (int j=i+1; j < A[i].size(); j++)
			{
				suma = 0.0;
				for (int k=0; k <= i-1 ; k++)
					suma = suma + L[j][k]*U[k][i];
				L[j][i] = (A[j][i] - suma)/U[i][i];
			}
		}
		else
		{
			cout << "\n\tERROR. No se pudo factorizar LU\n\n";
			resp = false;
			break;
		}
	}

	return resp;
}

bool AlgebraLineal::resuelve_sistema_LU(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int& N)
{
	vector<vector<double>> L(N, vector<double>(N)), U(N, vector<double>(N));
	vector<double> y;
	bool resp;

	resp = true;

	if (factoriza_LU(A, L, U))
	{
		y = resuelve_sistema_triangular_inferior_sparse(L, b, N, N);
		x = resuelve_sistema_triangular_superior_completo(U, y, N, N);
	}
	else
		resp = false;

	return resp;
}