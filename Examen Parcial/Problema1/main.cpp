#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "IOMatrices.h"
#include "AlgebraLineal.h"

using namespace std;

const double epsMaquina = numeric_limits<double>::epsilon();

int main(int argc, char** argv)
{
	vector<vector<double>> matrizA, inversa;
	vector<double> b, x;
	string nombreArchivoMatriz, nombreArchivoVector;
	int N;

	nombreArchivoMatriz = argv[1];
	nombreArchivoVector = argv[2];

	if (IOMatrices::lee_matriz_completa("Matrices/" + nombreArchivoMatriz, matrizA, N, N) && IOMatrices::lee_vector("Matrices/" + nombreArchivoVector, b, N))
	{
		inversa = matrizA;
		AlgebraLineal::invierte_matriz(matrizA, inversa);

		x = AlgebraLineal::producto_matriz_vector(inversa, b, N, N);

		IOMatrices::crea_archivo_matriz_completa("Matrices/A_inv_" + to_string(N) + ".mtx", inversa, N, N);

		IOMatrices::crea_archivo_vector("Matrices/sol_" + to_string(N) + ".vec", x, N);
	}
	else
		cout << "\nERROR. No se pudo leer el archivo\n\n";

	return 0;
}