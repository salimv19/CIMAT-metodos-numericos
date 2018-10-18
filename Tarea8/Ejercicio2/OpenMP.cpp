#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <omp.h>
#include <stdio.h>
#include "OpenMP.h"

using namespace std;

OpenMP::OpenMP()
{
}

OpenMP::~OpenMP()
{
}

vector<double> OpenMP::suma_vectores(vector<double>& A, vector<double>& B, int& N, int& t)
{
	vector<double> C(N);

	#pragma omp parallel for default(none) shared(A, B, C, N) num_threads(t) schedule(dynamic, 1)
	for (int i=0; i < N; i++)
	{
		//printf("Thread %3d is running on CPU %3d\n", omp_get_thread_num(), sched_getcpu());
		C[i] = A[i] + B[i];
	}

	return C;
}

vector<double> OpenMP::suma_vectores_serie(vector<double>& A, vector<double>& B, int& N)
{
	vector<double> C(N);

	for (int i=0; i < N; i++)
		C[i] = A[i] + B[i];

	return C;
}

vector<double> OpenMP::producto_vectores_eae(vector<double>& A, vector<double>& B, int& N, int& t)
{
	vector<double> C(N);

	#pragma omp parallel for default(none) shared(A, B, C, N)  num_threads(t) schedule(dynamic, 1)
	for (int i=0; i < N; i++)
		C[i] = A[i] * B[i];

	return C;
}

vector<double> OpenMP::producto_vectores_eae_serie(vector<double>& A, vector<double>& B, int& N)
{
	vector<double> C(N);

	for (int i=0; i < N; i++)
		C[i] = A[i] * B[i];

	return C;
}

double OpenMP::producto_punto(vector<double>& A, vector<double>& B, int& N, int& t)
{
	double suma;

	suma = 0;

	#pragma omp parallel for reduction(+:suma) num_threads(t) schedule(dynamic, 1)
	for (int i=0; i < N; i++)
		suma = suma + A[i] * B[i];

	return suma;
}

double OpenMP::producto_punto_serie(vector<double>& A, vector<double>& B, int& N)
{
	double suma;

	suma = 0;

	for (int i=0; i < N; i++)
		suma = suma + A[i] * B[i];

	return suma;
}

vector<double> OpenMP::producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M, int& t)
{
	vector<double> res(M);
	#pragma omp parallel for default(none) shared(A, vec, res, N, t) num_threads(t) schedule(dynamic, 1)
	for (int i=0; i < N; i++)
		res[i] = OpenMP::producto_punto(A[i], vec, N, t);
	return res;
}

vector<double> OpenMP::producto_matriz_vector_serie(vector<vector<double>>& A, vector<double>& vec, int& N, int& M)
{
	vector<double> res(M);
	for (int i=0; i < N; i++)
		res[i] = OpenMP::producto_punto_serie(A[i], vec, N);
	return res;
}

vector<vector<double>> OpenMP::producto_matriz_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L, int& t)
{
	vector<vector<double>> C(N, vector<double>(L));
	double suma;
	int i, j, r;

	//#pragma omp parallel
	//{
		#pragma omp parallel for// default(none) shared(N)
		for (i=0; i < N; i++)
		{
			#pragma omp parallel for// default(none) shared(L)
			for (j=0; j < L; j++)
			{
				suma = 0;
				#pragma omp parallel for reduction(+:suma)  num_threads(t) schedule(dynamic, 1)
				for (r=0; r < M; r++)
					suma = suma + A[i][r]*B[r][j];
				C[i][j] = suma;
			}
		}
	//}

	return C;
}

vector<vector<double>> OpenMP::producto_matriz_matriz_serie(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L)
{
	vector<vector<double>> C(N, vector<double>(L));
	double suma;

	for (int i=0; i < N; i++)
	{
		for (int j=0; j < L; j++)
		{
			suma = 0;
			for (int r=0; r < M; r++)
				suma = suma + A[i][r]*B[r][j];
			C[i][j] = suma;
		}
	}

	return C;
}

void OpenMP::prueba_openmp(int x)
{
	int y;
	y = x + 2;
	#pragma omp parallel num_threads(y * 3)
	{
		cout << "Hola desde OpenMP\n";
	}
}