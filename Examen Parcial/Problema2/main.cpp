#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ctime>
#include "IOMatrices.h"
#include "AlgebraLineal.h"

using namespace std;

int main(int argc, char** argv)
{
	vector<map<int,double>> matrizA;
	vector<double> b;
	string nombreArchivoMatriz, nombreArchivoVector;
	clock_t inicio, fin;
	int N, M, iteraciones;

	nombreArchivoMatriz = argv[1];
	nombreArchivoVector = argv[2];

	if (IOMatrices::lee_matriz_sparse("Matrices/" + nombreArchivoMatriz, matrizA, N, N) && IOMatrices::lee_vector("Matrices/" + nombreArchivoVector, b, N))
	{
		cout << "\nMÉTODO DE GRADIENTE CONJUGADO\n";

		vector<double> x(N), error(N);

		//AlgebraLineal::gradiente_conjugado_precondicionado_jacobi_sparse(matrizA, b, x, error, N, iteraciones);
		inicio = clock();
		AlgebraLineal::gradiente_conjugado_sparse(matrizA, b, x, error, N, iteraciones);
		fin = clock();

		cout << "\n\tIteraciones = " << iteraciones << endl;
		cout << "\n\tError = " << AlgebraLineal::norma_dos(error, N)/N << endl;
		cout << "\n\tTiempo de ejecución = " << (double)(fin - inicio) / CLOCKS_PER_SEC << " segundos\n";

		if (N <= 10)
		{
			cout << "\nx = \n";
			IOMatrices::imprime_vector(x);
			cout << endl;
		}
		else
			cout << "\n\t||x||_2 = " << AlgebraLineal::norma_dos(x, N) << "\n\n";

		

		cout << "\nSOLUCIÓN POR FACTORIZACIÓN LU\n";
		vector<vector<double>> Acompleta(N, vector<double>(N));
		for (int i=0; i < N; i++)
			for (auto val:matrizA[i])
				Acompleta[i][val.first] = val.second;

		//IOMatrices::imprime_matriz_completa(Acompleta, N, N);
		inicio = clock();
		AlgebraLineal::resuelve_sistema_LU(Acompleta, b, x, N);
		fin = clock();

		cout << "\n\tTiempo de ejecución = " << (double)(fin - inicio) / CLOCKS_PER_SEC << " segundos\n";

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