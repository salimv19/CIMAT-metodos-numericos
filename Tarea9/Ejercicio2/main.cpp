#include <iostream>
#include <string>
#include <vector>
#include "IOMatrices.h"
#include "AlgebraLineal.h"

using namespace std;

int main()
{
	vector<vector<double>> matrizA, Q, R, D;
	string nombreArchivo;
	double error;
	int N, M;

	cout << "Nombre del archivo: ";
	cin >> nombreArchivo;

	if (IOMatrices::lee_matriz_completa("Matrices_tarea09/" + nombreArchivo, matrizA, N, M))
	{
		cout << "\n\tFACTORIZACIÓN QR\n";
		AlgebraLineal::factorizacion_QR(matrizA, Q, R, N, M);
		cout << "\n\tMATRIZ Q\n";
		IOMatrices::imprime_matriz_completa(Q, N, M);
		cout << "\n\tMATRIZ R\n";
		IOMatrices::imprime_matriz_completa(R, M, N);

		D = AlgebraLineal::resta_matrices(matrizA, AlgebraLineal::producto_matriz_matriz(Q, R, N, M, N), N, M);
		error = AlgebraLineal::norma_frobenius(D, N, M);

		cout << "\n\t|| A - Q*R || = " << error << endl << endl;
	}
	else
		cout << "\nERROR. No se pudo leer el archivo\n\n";

	return 0;
}