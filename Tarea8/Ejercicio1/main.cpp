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

	if (IOMatrices::lee_matriz_completa("Matrices_tarea08/" + nombreArchivo, matrizA, N, M))
	{
		cout << "Tolerancia: ";
		cin >> tolerancia;
		cout << "Máximo de iteraciones: ";
		cin >> maxIter;
		if (AlgebraLineal::metodo_jacobi_eigenvalores(matrizA, D, P, N, tolerancia, maxIter))
		{
			cout << "\nEigenvalores\n\t";
			for (int i=0; i < N; i++)
				cout << D[i][i] << " ";
			cout << endl;
		}
		else
			cout << "\nERROR. No convergió el método de Jacobi\n\n";
	}
	else
		cout << "\nERROR. No se pudo leer el archivo\n\n";

	return 0;
}