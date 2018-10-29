#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "IOMatrices.h"
#include "AlgebraLineal.h"

using namespace std;

const double epsMaquina = numeric_limits<double>::epsilon();

int main()
{
	vector<vector<double>> D, P;
	string nombreArchivo;
	double tolerancia;
	int N, M, maxIter;

	cout.precision(19);

	N = 2000;
	vector<vector<double>> matrizA(N, vector<double>(N));
	for (int i=0; i < N; i++)
		matrizA[i][i] = 56;
	for (int i=0; i < N-1; i++)
	{
		matrizA[i][i+1] = -10;
		matrizA[i+1][i] = -10;
	}
	for (int i=0; i < N-2; i++)
	{
		matrizA[i][i+2] = -6;
		matrizA[i+2][i] = -6;
	}
	//IOMatrices::imprime_matriz_completa(matrizA, N, N);
	
	M = 10;
	tolerancia = epsMaquina;
	maxIter = 10000000;
	P = AlgebraLineal::inicializa_ortonormal(N, M);
	if (AlgebraLineal::eigenvectores_menores_subespacio(matrizA, N, P, D, M, tolerancia, maxIter))
	{
		cout << "\nEigenvalores\n\t";
		for (int i=0; i < M; i++)
			cout << D[i][i] << " ";
		cout << endl;
	}
	else
		cout << "\nERROR. No convergió el método de iteraciones en el subespacio\n\n";

	P = AlgebraLineal::inicializa_ortonormal(N, M);
	if (AlgebraLineal::eigenvectores_subespacio(matrizA, N, P, D, M, tolerancia, maxIter))
	{
		cout << "\nEigenvalores\n\t";
		for (int i=0; i < M; i++)
			cout << D[i][i] << " ";
		cout << endl;
	}
	else
		cout << "\nERROR. No convergió el método de iteraciones en el subespacio\n\n";
	

	return 0;
}