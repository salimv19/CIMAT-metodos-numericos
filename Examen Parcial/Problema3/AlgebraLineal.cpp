#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
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

vector<double> AlgebraLineal::columna_indice(vector<vector<double>>& A, int& N, int& indice)
{
	vector<double> vec(N);

	for (int i=0; i < N; i++)
		vec[i] = A[i][indice];

	return vec;
}

vector<vector<double>> AlgebraLineal::matriz_identidad(int& N)
{
	vector<vector<double>> I(N, vector<double>(N));

	for (int i=0; i < N; i++)
		I[i][i] = 1.0;

	return I;
}

vector<vector<double>> AlgebraLineal::inicializa_ortonormal(int N, int M)
{
	vector<vector<double>> X(N, vector<double>(M));

	for (int i=0; i < min(N, M); i++)
		X[i][i] = 1.0;

	return X;
}

vector<double> AlgebraLineal::resta_vectores(vector<double> vecA, vector<double> vecB, int& N)
{
	vector<double> resta(N);

	for (int i=0; i < N; i++)
	{
		resta[i] = vecA[i] - vecB[i];
	}

	return resta;
}

double AlgebraLineal::producto_punto(vector<double> vec1, vector<double> vec2)
{
	double productoPunto;

	productoPunto = 0;

	for (int i=0; i < vec1.size(); i++)
		productoPunto = productoPunto + vec1[i]*vec2[i];

	return productoPunto;
}

void AlgebraLineal::normaliza_vector(vector<double>& x, int N)
{
	double maximo;

	maximo = x[distance(x.begin(), max_element(x.begin(), x.end(), abs_compare))];

	for (int i=0; i < N; i++)
		x[i] = 1.0 * x[i] / maximo;
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

void normaliza_vector_2(vector<double>& x, int N)
{
	double norma;

	norma = AlgebraLineal::norma_dos(x, N);

	for (int i=0; i < N; i++)
		x[i] = 1.0 * x[i] / norma;
}

vector<double> AlgebraLineal::proyeccion_vector_vector(vector<double>& vecA, vector<double> vecB, int& N)
{
	vector<double> proy(N);
	double factor;

	factor = AlgebraLineal::producto_punto(vecA, vecB) / pow(AlgebraLineal::norma_dos(vecB, N),2);
	
	for (int i=0; i < N; i++)
		proy[i] = factor * vecB[i];

	return proy;
}

double AlgebraLineal::norma_frobenius(vector<vector<double>>& matriz, int& N, int& M)
{
	double norma;

	norma = 0;

	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			norma = norma + pow(fabs(matriz[i][j]), 2);

	norma = sqrt(norma);

	return norma;
}

vector<vector<double>> AlgebraLineal::resta_matrices(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M)
{
	vector<vector<double>> C(N, vector<double>(M));

	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			C[i][j] = A[i][j] - B[i][j];

	return C;
}

vector<double> AlgebraLineal::producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M)
{
	vector<double> res(M);
	for (int i=0; i < N; i++)
		res[i] = AlgebraLineal::producto_punto(A[i], vec);
	return res;
}

vector<vector<double>> AlgebraLineal::producto_matriz_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L)
{
	vector<vector<double>> C(N, vector<double>(L));
	double suma;

	for (int i=0; i < N; i++)
		for (int j=0; j < L; j++)
		{
			suma = 0;
			for (int r=0; r < M; r++)
				suma = suma + A[i][r]*B[r][j];
			C[i][j] = suma;
		}

	return C;
}

vector<vector<double>> AlgebraLineal::producto_matrizT_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L)
{
	vector<vector<double>> C(N, vector<double>(L));
	double suma;

	for (int i=0; i < N; i++)
		for (int j=0; j < L; j++)
		{
			suma = 0;
			for (int r=0; r < M; r++)
				suma = suma + A[r][i]*B[r][j];
			C[i][j] = suma;
		}

	return C;
}

vector<vector<double>> AlgebraLineal::matriz_triangular_superior(vector<vector<double>>& A, int& N)
{
	vector<vector<double>> S(N, vector<double>(N));

	for (int i=0; i < N - 1; i++)
		for (int j=i+1; j < N; j++)
			S[i][j] = A[i][j];

	return S;
}

vector<int> AlgebraLineal::maximo_absoluto_matriz(vector<vector<double>>& A, int& N, int& M)
{
	vector<int> posicion(2);
	double maximo;

	maximo = 0;
	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			if (fabs(A[i][j]) > maximo)
			{
				maximo = fabs(A[i][j]);
				posicion = {i,j};
			}

	return posicion;
}

vector<vector<double>> AlgebraLineal::ortogonalizacion_gram_schmidt(vector<vector<double>>& A, int& N, int& M) 
{
	vector<vector<double>> U(N, vector<double>(M));
	vector<double> vecU, vecV;
	int j;

	for (int i=0; i < M; i++)
	{
		vecV = AlgebraLineal::columna_indice(A, N, i);
		vecU = vecV;
		
		j = 0;
		while (i > j)
		{
			vecU = AlgebraLineal::resta_vectores(vecU, AlgebraLineal::proyeccion_vector_vector(vecV, AlgebraLineal::columna_indice(U, N, j), N),N);
			j = j + 1;
		}

		for (int j=0; j < N; j++)
			U[j][i] = vecU[j];
	}

	return U;
}

bool AlgebraLineal::metodo_potencia(vector<vector<double>>& A, vector<double>& x, double& eigenvalor, int& N, double& tolerancia, int maxIter, int& iteraciones)
{
	vector<double> aux;
	double eigValAnt;
	int iter;
	bool resp;

	iter = 0;
	resp = true;

	do
	{
		eigValAnt = eigenvalor;
		aux = x;
		AlgebraLineal::normaliza_vector(aux, N);
		iter = iter + 1;
		x[0] = A[0][0]*aux[0] + A[0][1]*aux[1] + A[0][2]*aux[2];
		x[1] = A[1][0]*aux[0] + A[1][1]*aux[1] + A[1][2]*aux[2] + A[1][3]*aux[3];
		for (int j=2; j < N-2; j++)
			x[j] = A[j][j-2]*aux[j-2] + A[j][j-1]*aux[j-1] + A[j][j]*aux[j] + A[j][j+1]*aux[j+1] + A[j][j+2]*aux[j+2];
		x[N-2] = A[N-2][N-4]*aux[N-4] + A[N-2][N-3]*aux[N-3] + A[N-2][N-2]*aux[N-2] + A[N-2][N-1]*aux[N-1];
		x[N-1] = A[N-1][N-3]*aux[N-3] + A[N-1][N-2]*aux[N-2] + A[N-1][N-1]*aux[N-1];
		//x = AlgebraLineal::producto_matriz_vector(A, aux, N, N);

		eigenvalor = AlgebraLineal::producto_punto(aux, x)/AlgebraLineal::producto_punto(aux, aux);

	} while (fabs(fabs(eigenvalor) - fabs(eigValAnt)) > tolerancia && iter < maxIter);

	if (iter >= maxIter)
		resp = false;

	normaliza_vector_2(x, N);
	iteraciones = iter;

	return resp;
}

bool AlgebraLineal::metodo_jacobi_eigenvalores(vector<vector<double>>& A, vector<vector<double>>& C, vector<vector<double>>& P, int& N, double& tolerancia, int& maxIter)
{
	vector<vector<double>> S, B, P_i;
	vector<int> posMax;
	double m, theta, pi = 3.1415926535897932384626433832795;
	int iter, k, l;
	bool converge;

	C = A;
	P = AlgebraLineal::matriz_identidad(N);

	iter = 0;
	converge = false;

	do
	{
		S = AlgebraLineal::matriz_triangular_superior(C, N);
		posMax = AlgebraLineal::maximo_absoluto_matriz(S, N, N);
		k = posMax[0];
		l = posMax[1];

		if (fabs(C[k][l]) > tolerancia)
		{
			if (C[l][l] == C[k][k])
				theta = pi/4;
			else
				theta = atan2(2*C[k][l], (C[l][l] - C[k][k]));


			P_i = AlgebraLineal::matriz_identidad(N);
			P_i[k][k] = cos(theta);
			P_i[l][l] = cos(theta);
			P_i[l][k] = sin(theta);
			P_i[k][l] = -1.0*sin(theta);

			B = AlgebraLineal::producto_matriz_matriz(C, P_i, N, N, N);
			C = AlgebraLineal::producto_matrizT_matriz(P_i, B, N, N, N);

			P = AlgebraLineal::producto_matriz_matriz(P, P_i, N, N, N);
		}
		else
		{
			converge = true;
		}

		iter = iter + 1;

	} while(!converge && iter < maxIter);

	return converge;
}

bool AlgebraLineal::eigenvectores_subespacio(vector<vector<double>>& A, int& N, vector<vector<double>>& X, vector<vector<double>>& C, int& M, double& tolerancia, int& maxIter)
{
	vector<vector<double>> B(N, vector<double>(M)), D, Q, R, auxA, proy;
	vector<double> phi;
	double lambda, tolJacobi;
	int iter, itPotencia, itJacobi;
	bool converge;

	tolJacobi = 1e-5;
	itJacobi = 100;

	iter = 0;
	converge = false;

	do
	{
		iter = iter + 1;
		// X^T * A * X = C
		for (int i=0; i < M; i++)
		{
			B[0][i] = A[0][0]*X[0][i] + A[0][1]*X[1][i] + A[0][2]*X[2][i];
			B[1][i] = A[1][0]*X[0][i] + A[1][1]*X[1][i] + A[1][2]*X[2][i] + A[1][3]*X[3][i];
			for (int j=2; j < N-2; j++)
				B[j][i] = A[j][j-2]*X[j-2][i] + A[j][j-1]*X[j-1][i] + A[j][j]*X[j][i] + A[j][j+1]*X[j+1][i] + A[j][j+2]*X[j+2][i];
			B[N-2][i] = A[N-2][N-4]*X[N-4][i] + A[N-2][N-3]*X[N-3][i] + A[N-2][N-2]*X[N-2][i] + A[N-2][N-1]*X[N-1][i];
			B[N-1][i] = A[N-1][N-3]*X[N-3][i] + A[N-1][N-2]*X[N-2][i] + A[N-1][N-1]*X[N-1][i];
		}
		//B = AlgebraLineal::producto_matriz_matriz(A, X, N, N, M);
		C = AlgebraLineal::producto_matrizT_matriz(X, B, M, N, M);

		//Encontramos los eigenvectores de C por el método de Jacobi
		AlgebraLineal::metodo_jacobi_eigenvalores(C, D, Q, M, tolJacobi, itJacobi); cout << iter << " - "; for (int ind=0; ind < M; ind++) cout << D[ind][ind] << " "; cout << endl;
		// R = C - D
		R = AlgebraLineal::resta_matrices(C, D, M, M);
		if (AlgebraLineal::norma_frobenius(R, M, M) <= tolerancia)
		{
			converge = true;
		}
		else
		{
			// Iteración X = X * Q
			X = AlgebraLineal::producto_matriz_matriz(X, Q, N, M, N);
			//Nos aseguramos que X sea ortonormal
			X = AlgebraLineal::ortogonalizacion_gram_schmidt(X, N, M);

			//auxA = A;
			for (int vec=0; vec < M; vec++)
			{
				phi = AlgebraLineal::columna_indice(X, N, vec);
				//Quitamos las proyecciones de los eigenvectores anteriores
				for (int j=0; j < vec; j++)
				{
					phi = AlgebraLineal::resta_vectores(phi, AlgebraLineal::proyeccion_vector_vector(phi, AlgebraLineal::columna_indice(X, N, j), N),N);
				}
				//Realizamos una iteración del método de la potencia
				AlgebraLineal::metodo_potencia(A, phi, lambda, N, tolerancia, 1, itPotencia);

				//Reemplazamos el nuevo vector en X
				for (int i=0; i < N; i++)
					X[i][vec] = phi[i];
			}

			//Nos aseguramos que X sea ortonormal
			X = AlgebraLineal::ortogonalizacion_gram_schmidt(X, N, M);
		}
	} while(!converge && iter < maxIter);

	return converge;
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

/*bool resuelve_sistema_LU(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int& N)
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
}*/

bool metodo_potencia_inversa(vector<vector<double>>& L, vector<vector<double>>& U, vector<double>& x, double& eigenvalor, int& N, double& tolerancia, int maxIter, int& iteraciones)
{
	vector<double> aux, y;
	double eigValAnt;
	int iter;
	bool resp;

	iter = 0;
	resp = true;

	do
	{
		eigValAnt = eigenvalor;
		aux = x;
		AlgebraLineal::normaliza_vector(aux, N);
		iter = iter + 1;

		y = resuelve_sistema_triangular_inferior_sparse(L, aux, N, N);
		x = resuelve_sistema_triangular_superior_completo(U, y, N, N);
		
		eigenvalor = AlgebraLineal::producto_punto(aux, aux)/AlgebraLineal::producto_punto(aux, x);
		

	} while (fabs(fabs(eigenvalor) - fabs(eigValAnt)) > tolerancia && iter < maxIter);

	if (iter >= maxIter)
		resp = false;

	normaliza_vector_2(x, N);
	iteraciones = iter;

	return resp;
}

bool AlgebraLineal::eigenvectores_menores_subespacio(vector<vector<double>>& A, int& N, vector<vector<double>>& X, vector<vector<double>>& C, int& M, double& tolerancia, int& maxIter)
{
	vector<vector<double>> B(N, vector<double>(M)), D, Q, R, auxA, proy, L(N, vector<double>(N)), U(N, vector<double>(N));
	vector<double> phi;
	double lambda, tolJacobi;
	int iter, itPotencia, itJacobi;
	bool converge;

	tolJacobi = 1e-5;
	itJacobi = 100;

	factoriza_LU(A, L, U);

	iter = 0;
	converge = false;

	do
	{
		iter = iter + 1;
		// X^T * A * X = C
		for (int i=0; i < M; i++)
		{
			B[0][i] = A[0][0]*X[0][i] + A[0][1]*X[1][i] + A[0][2]*X[2][i];
			B[1][i] = A[1][0]*X[0][i] + A[1][1]*X[1][i] + A[1][2]*X[2][i] + A[1][3]*X[3][i];
			for (int j=2; j < N-2; j++)
				B[j][i] = A[j][j-2]*X[j-2][i] + A[j][j-1]*X[j-1][i] + A[j][j]*X[j][i] + A[j][j+1]*X[j+1][i] + A[j][j+2]*X[j+2][i];
			B[N-2][i] = A[N-2][N-4]*X[N-4][i] + A[N-2][N-3]*X[N-3][i] + A[N-2][N-2]*X[N-2][i] + A[N-2][N-1]*X[N-1][i];
			B[N-1][i] = A[N-1][N-3]*X[N-3][i] + A[N-1][N-2]*X[N-2][i] + A[N-1][N-1]*X[N-1][i];
		}
		//B = AlgebraLineal::producto_matriz_matriz(A, X, N, N, M);
		C = AlgebraLineal::producto_matrizT_matriz(X, B, M, N, M);

		//Encontramos los eigenvectores de C por el método de Jacobi
		AlgebraLineal::metodo_jacobi_eigenvalores(C, D, Q, M, tolJacobi, itJacobi); cout << iter << " - "; for (int ind=0; ind < M; ind++) cout << D[ind][ind] << " "; cout << endl;
		// R = C - D
		R = AlgebraLineal::resta_matrices(C, D, M, M);
		if (AlgebraLineal::norma_frobenius(R, M, M) <= tolerancia)
		{
			converge = true;
		}
		else
		{
			// Iteración X = X * Q
			X = AlgebraLineal::producto_matriz_matriz(X, Q, N, M, N);
			//Nos aseguramos que X sea ortonormal
			X = AlgebraLineal::ortogonalizacion_gram_schmidt(X, N, M);

			//auxA = A;
			for (int vec=0; vec < M; vec++)
			{
				phi = AlgebraLineal::columna_indice(X, N, vec);
				//Quitamos las proyecciones de los eigenvectores anteriores
				for (int j=0; j < vec; j++)
				{
					phi = AlgebraLineal::resta_vectores(phi, AlgebraLineal::proyeccion_vector_vector(phi, AlgebraLineal::columna_indice(X, N, j), N),N);
				}
				//Realizamos una iteración del método de la potencia
				//AlgebraLineal::metodo_potencia(A, phi, lambda, N, tolerancia, 1, itPotencia);
				metodo_potencia_inversa(L, U, phi, lambda, N, tolerancia, 1, itPotencia);

				//Reemplazamos el nuevo vector en X
				for (int i=0; i < N; i++)
					X[i][vec] = phi[i];
			}

			//Nos aseguramos que X sea ortonormal
			X = AlgebraLineal::ortogonalizacion_gram_schmidt(X, N, M);
		}
	} while(!converge && iter < maxIter);

	return converge;
}