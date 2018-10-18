#include <iostream>
#include <string>
#include <vector>
#include "IOMatrices.h"
#include "AlgebraLineal.h"

using namespace std;

int main()
{
	vector<vector<double>> matrizA, D, P;
	string nombreArchivo;
	double tolerancia;
	int N, M, maxIter;

	cout << "Nombre del archivo: ";
	cin >> nombreArchivo;

	if (IOMatrices::lee_matriz_completa("Matrices_tarea09/" + nombreArchivo, matrizA, N, N))
	{
		cout << "Número de eigenvalores: ";
		cin >> M;
		cout << "Tolerancia: ";
		cin >> tolerancia;
		cout << "Máximo de iteraciones: ";
		cin >> maxIter;
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
	}
	else
		cout << "\nERROR. No se pudo leer el archivo\n\n";

	return 0;
}