#include <iostream>
#include <string>
#include <vector>
#include "IOMatrices.h"
#include "AlgebraLineal.h"

using namespace std;

int main()
{
	vector<vector<double>> matrizA;
	vector<double> b, error;
	string nombreArchivoMatriz, nombreArchivoVector;
	double tolerancia;
	int N, M, maxIter, iteraciones;

	cout << "\nMÉTODO DE GRADIENTE CONJUGADO\n\n";

	cout << "Nombre del archivo de la matriz A: ";
	cin >> nombreArchivoMatriz;
	cout << "Nombre del archivo del vector b: ";
	cin >> nombreArchivoVector;

	if (IOMatrices::lee_matriz_completa("Matrices/" + nombreArchivoMatriz, matrizA, N, N) && IOMatrices::lee_vector("Matrices/" + nombreArchivoVector, b, N))
	{
		vector<double> x(N);

		AlgebraLineal::gradiente_conjugado(matrizA, b, x, error, N, iteraciones);

		cout << "\n\tIteraciones = " << iteraciones << endl;
		cout << "\n\tError = " << AlgebraLineal::norma_dos(error, N)/N << endl;

		if (N <= 10)
		{
			cout << "\nx = \n";
			IOMatrices::imprime_vector(x);
			cout << endl;
		}
		else
			cout << "\n\t||x||_2 = " << AlgebraLineal::norma_dos(x, N) << "\n\n";
	}
	else
		cout << "\nERROR. No se pudo leer el archivo\n\n";

	return 0;
}