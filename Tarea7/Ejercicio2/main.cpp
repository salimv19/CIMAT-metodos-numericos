#include <iostream>
#include <string>
#include <vector>
#include "IOMatrices.h"
#include "MetodoPotenciaInversa.h"

using namespace std;

int main()
{
	vector<vector<double>> matrizA;
	string nombreArchivo;
	double eigenvalor, tolerancia;
	int N, M, maxIter, iteraciones;

	cout.precision(10);

	tolerancia = 1e-8;
	maxIter = 1000;

	cout << "Nombre del archivo: ";
	cin >> nombreArchivo;

	matrizA = IOMatrices::lee_matriz_completa("Matrices_tarea07/" + nombreArchivo, N, M);

	vector<vector<double>> L(N, vector<double>(N)), U(N, vector<double>(N));
	vector<double> eigenvector(N);

	for (int i=0; i < N; i++) eigenvector[i] = 1;

	if (MetodoPotenciaInversa::metodo_potencia_inversa(matrizA, eigenvector, eigenvalor, N, tolerancia, maxIter, iteraciones))
	{
		cout << "\tEigenvalor = " << eigenvalor << endl;
		cout << "\tIteraciones = " << iteraciones << endl;
		cout << "\tTolerancia = " << tolerancia << endl << endl;
	}
	else
		cout << "\nERROR. No convergió el método de la potencia\n\n";

	return 0;
}