#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>

/*
Salim Vargas Hernández
Programación y Algoritmos
Tarea 5
Factorización de Cholesky LDL'
Septiembre 2018
*/

using namespace std;

template <typename T>
void imprime_vector(vector<T> vec)
{
	for (int i=0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

double producto_punto(vector<double> vec1, vector<double> vec2)
{
	double productoPunto;

	productoPunto = 0;

	for (int i=0; i < vec1.size(); i++)
		productoPunto = productoPunto + vec1[i]*vec2[i];

	return productoPunto;
}

vector<double> producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M)
{
	vector<double> res(M);
	for (int i=0; i < N; i++)
		res[i] = producto_punto(A[i], vec);
	return res;
}

vector<double> resuelve_sistema_diagonal_sparse(vector<double>& matriz, vector<double>& b, int& N)
{
	vector<double> x(N);
	
	for (int i=0; i < N; i++)
	{
		if (matriz[i] != 0)
		{
			x[i] = b[i]/matriz[i];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
			break;
		}
	}

	return x;
}

vector<double> resuelve_sistema_triangular_superior_completo(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector<double> x(N);
	double suma;
	
	for (int i=0; i < N; i++)
	{
		if (matriz[N-1-i][N-1-i] != 0)
		{
			suma = 0;
			for (int j=0; j < i; j++)
			{
				suma = suma + matriz[N-1-i][N-1-j]*x[N-1-j];
			}
			x[N-1-i] = (b[N-1-i] - suma)/matriz[N-1-i][N-1-i];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
			break;
		}
	}

	return x;
}

vector<double> resuelve_sistema_triangular_inferior_sparse(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector<double> x(N);
	double suma;
	
	for (int i=0; i < N; i++)
	{
		if (matriz[i][i] != 0)
		{
			suma = 0;
			for (int j=0; j < i; j++)
			{
				suma = suma + matriz[i][j]*x[j];
			}
			x[i] = (b[i] - suma)/matriz[i][i];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
			break;
		}
	}

	return x;
}

void imprime_matriz_completa(vector<vector<double>>& matriz, int& N, int& M)
{
	cout << endl;
	for (int i=0; i < N; i++)
	{
		for (int j=0; j < M; j++)
		{
			cout << "\t" << matriz[i][j];// << " ";
		}
		cout << endl;
	}
	cout << endl;
}

vector<double> lee_vector(string nombreArchivo, int& N)
{
	vector<double> vector;
	double auxNum;
	ifstream entrada (nombreArchivo.c_str());

	if (entrada.is_open())
	{
  		entrada >> N;
	  	for (int i=0; i < N; i++)
	  	{
	  		entrada >> auxNum;
	  		vector.push_back(auxNum);
	  	}
	  	entrada.close();
	}
	else
  		cout << "ERROR al leer archivo\n";
	
	return vector;
}

vector<vector<double>> lee_matriz_completa(string nombreArchivo, int& N, int& M)
{
	vector<vector<double>> matriz;
	vector<double> renglon;
	double auxNum;
	ifstream entrada (nombreArchivo.c_str());

	if (entrada.is_open())
	{
  		entrada >> N;
  		entrada >> M;
	  	for (int i=0; i < N; i++)
	  	{
	  		for (int j=0; j < M; j++)
	  		{
	  			entrada >> auxNum;
	  			renglon.push_back(auxNum);
	  		}
	  		matriz.push_back(renglon);
	  		renglon.clear();
	  	}
	  	entrada.close();
	}
	else
  		cout << "ERROR al leer archivo\n";
	
	return matriz;
}

vector<vector<double>> transpone_matriz(vector<vector<double>>& A, int& N, int& M)
{
	vector<vector<double>> T(M, vector<double>(N));
	for (int i=0; i < N; i++)
		for (int j=0; j < M; j++)
			T[j][i] = A[i][j];

	return T;
}

bool cholesky_modificado(vector<vector<double>>& A, vector<vector<double>>& L, vector<double>& D)
{
	double suma;
	bool simetrica;

	simetrica = true;

	for (int j=0; j < A[0].size(); j++)
	{
		for (int i=j; i < A.size(); i++)
		{
			if (i == j)
			{
				L[i][j] = 1;
				suma = 0;
				for (int k=0; k < i; k++)
				{
					suma = suma + pow(L[i][k], 2)*D[k];
				}
				D[i] = A[i][i] - suma;
			}
			else
			{
				suma = 0;
				for (int k=0; k < j; k++)
				{
					suma = suma + L[j][k]*L[i][k]*D[k];
				}
				if (fabs(D[j]) > 0)
				{
					L[i][j] = (A[i][j] - suma)/D[j];
				}
				else
				{
					simetrica = false;
					break;
				}
			}
			if (!simetrica)
				break;
		}
		if (!simetrica)
			break;
	}

	return simetrica;
}

int main()
{
	vector<vector<double>> matrizA, LT;
	vector<double> b, x, y, z;
	int N, M;

	matrizA = lee_matriz_completa("MAT5-5.txt", N, M);
	b = lee_vector("VEC5.txt", N);

	imprime_matriz_completa(matrizA, N, M);
	vector<vector<double>> L(N, vector<double>(M));
	vector<double> D(N);

	cholesky_modificado(matrizA, L, D);

	LT = transpone_matriz(L, N, M);

	z = resuelve_sistema_triangular_inferior_sparse(L, b, M, N);
	y = resuelve_sistema_diagonal_sparse(D, z, N);
	x = resuelve_sistema_triangular_superior_completo(LT, y, N, M);

	//imprime_vector(producto_matriz_vector(matrizA, x, N, M)); cout << endl << endl;

	//imprime_vector(b); cout << endl << endl; 
	imprime_vector(x);

	return 0;
}
