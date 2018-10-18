#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <ctime>
#include <climits>
#include <algorithm>
#include "OpenMP.h"

using namespace std;

vector<double> genera_vector_aleatorio(int& N)
{
	vector<double> vector(N);

	for (int i=0; i < N; i++)
		vector[i] = rand();

	return vector;
}

vector<vector<double>> genera_matriz_aleatoria(int& N, int& M)
{
	vector<vector<double>> matriz(N, vector<double>(M));

	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			matriz[i][j] = rand();

	return matriz;
}

void imprime_resultados(double& tiempoParalelo, double& tiempoSerie, int& n)
{
	cout << "\tTiempo de ejecución en paralelo = " << tiempoParalelo << " segundos\n";
	cout << "\tTiempo de ejecución en serie = " << tiempoSerie << " segundos\n";
	cout << "\tSpeed-up = " << tiempoSerie/tiempoParalelo << endl;
	cout << "\tEficiencia = " << 100.0*tiempoSerie/(1.0*n*tiempoParalelo) << "%\n\n";
}

void compara_operacion_vector_vector(int& operacion)
{
	vector<double> vectorA, vectorB, vectorC;
	clock_t inicio, fin;
	double prodPunto, tiempoParalelo, tiempoSerie;
	int N, cores;

	cout << "Dimensión de los vectores: ";
	cin >> N;
	cout << "Número de threads: ";
	cin >> cores;

	vectorA = genera_vector_aleatorio(N);
	vectorB = genera_vector_aleatorio(N);

	switch (operacion)
	{
		case 1:
		{
			inicio = clock();
			vectorC = OpenMP::suma_vectores(vectorA, vectorB, N, cores);
			fin = clock();
			tiempoParalelo = double(fin - inicio)/CLOCKS_PER_SEC;
			inicio = clock();
			vectorC = OpenMP::suma_vectores_serie(vectorA, vectorB, N);
			fin = clock();
			tiempoSerie = double(fin - inicio)/CLOCKS_PER_SEC;
			imprime_resultados(tiempoParalelo, tiempoSerie, cores);
			break;
		}
		case 2:
		{
			inicio = clock();
			vectorC = OpenMP::producto_vectores_eae(vectorA, vectorB, N, cores);
			fin = clock();
			tiempoParalelo = double(fin - inicio)/CLOCKS_PER_SEC;
			inicio = clock();
			vectorC = OpenMP::producto_vectores_eae_serie(vectorA, vectorB, N);
			fin = clock();
			tiempoSerie = double(fin - inicio)/CLOCKS_PER_SEC;
			imprime_resultados(tiempoParalelo, tiempoSerie, cores);
			break;
		}
		case 3:
		{
			inicio = clock();
			prodPunto = OpenMP::producto_punto(vectorA, vectorB, N, cores);
			fin = clock();
			tiempoParalelo = double(fin - inicio)/CLOCKS_PER_SEC;
			inicio = clock();
			prodPunto = OpenMP::producto_punto_serie(vectorA, vectorB, N);
			fin = clock();
			tiempoSerie = double(fin - inicio)/CLOCKS_PER_SEC;
			imprime_resultados(tiempoParalelo, tiempoSerie, cores);
			break;
		}
	}
}

void compara_operacion_matriz_vector(int& operacion)
{
	vector<vector<double>> matriz;
	vector<double> vectorA, vectorB;
	clock_t inicio, fin;
	double tiempoParalelo, tiempoSerie;
	int N, M, cores;

	cout << "Dimensión 1 de la matriz: ";
	cin >> N;
	cout << "Dimensión 2 de la matriz: ";
	cin >> M;
	cout << "Número de threads: ";
	cin >> cores;

	matriz = genera_matriz_aleatoria(N, M);
	vectorA = genera_vector_aleatorio(M);

	switch (operacion)
	{
		case 4:
		{
			inicio = clock();
			vectorB = OpenMP::producto_matriz_vector(matriz, vectorA, N, M, cores);
			fin = clock();
			tiempoParalelo = double(fin - inicio)/CLOCKS_PER_SEC;
			inicio = clock();
			vectorB = OpenMP::producto_matriz_vector_serie(matriz, vectorA, N, M);
			fin = clock();
			tiempoSerie = double(fin - inicio)/CLOCKS_PER_SEC;
			imprime_resultados(tiempoParalelo, tiempoSerie, cores);
			break;
		}
	}
}

void compara_operacion_matriz_matriz(int& operacion)
{
	vector<vector<double>> matrizA, matrizB, matrizC;
	vector<double> vector;
	clock_t inicio, fin;
	double tiempoParalelo, tiempoSerie;
	int N, M, L, cores;

	cout << "Dimensión 1 de la matriz 1: ";
	cin >> N;
	cout << "Dimensión 2 de la matriz 1: ";
	cin >> M;
	cout << "Dimensión 2 de la matriz 2: ";
	cin >> L;
	cout << "Número de threads: ";
	cin >> cores;

	matrizA = genera_matriz_aleatoria(N, M);
	matrizB = genera_matriz_aleatoria(M, L);

	switch (operacion)
	{
		case 5:
		{
			inicio = clock();
			matrizC = OpenMP::producto_matriz_matriz(matrizA, matrizB, N, M, L, cores);
			fin = clock();
			tiempoParalelo = double(fin - inicio)/CLOCKS_PER_SEC;
			inicio = clock();
			matrizC = OpenMP::producto_matriz_matriz_serie(matrizA, matrizB, N, M, L);
			fin = clock();
			tiempoSerie = double(fin - inicio)/CLOCKS_PER_SEC;
			imprime_resultados(tiempoParalelo, tiempoSerie, cores);
			break;
		}
	}
}

bool operaciones()
{
	string resp;
	int operacion;
	bool continuar;

	cout << "\nOPERACIONES DISPONIBLES:\n";
	cout << "1. Suma de vectores\n";
	cout << "2. Producto de vectores (elemento a elemento)\n";
	cout << "3. Producto punto\n";
	cout << "4. Multiplicación matriz-vector\n";
	cout << "5. Multiplicación matriz-matriz\n";
	cout << "\nOperación a realizar: ";
	cin >> operacion;

	if (operacion == 1 || operacion == 2 || operacion == 3)
	{
		compara_operacion_vector_vector(operacion);
	}
	else if (operacion == 4)
	{
		compara_operacion_matriz_vector(operacion);
	}
	else if (operacion == 5)
	{
		compara_operacion_matriz_matriz(operacion);
	}
	else
		cout << "\nOpción desconocida\n";

	cout << "¿Hacer una nueva operación?(Y/n): ";
	cin >> resp;
	if (resp == "Y" || resp == "y")
		continuar = true;
	else
		continuar = false;

	return continuar;
}

int main()
{
	bool continuar;

	srand(time(NULL));

	//OpenMP::prueba_openmp(1);
	do
	{
		continuar = operaciones();
	} while (continuar);

	return 0;
}