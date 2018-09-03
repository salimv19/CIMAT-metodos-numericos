#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <algorithm>
#include <vector>
#include <cmath>
#include <numeric>
//#include <typeinfo>
//#include <map>

using namespace std;

template <typename T>
void imprime_vector(vector<T>& vec)
{
	for (int i=0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

double norma_uno(vector<double>& x)
{
	double norma;
	norma = 0;
	for (int i=0; i < x.size(); i++)
	{
		norma = norma + fabs(x[i]);
	}
	return norma;
}

double norma_infinito(vector<double>& x)
{
	double norma;
	norma = 0;
	for (int i=0; i < x.size(); i++)
	{
		if (fabs(x[i]) > norma)
		{
			norma = fabs(x[i]);
		}
	}
	return norma;
}

void imprime_matriz_diagonal_superior_sparse(vector<vector<double>>& matriz, int& N, int& M)
{
	cout << endl;
	for (int i=0; i < N; i++)
	{
		for (int j=0; j < M; j++)
		{
			if (j < i)
			{
				cout << "\t    0\t";
			}
			else
			{
				cout << "\t" << matriz[i][j-i] << "   ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

void imprime_matriz_diagonal_inferior_sparse(vector<vector<double>>& matriz, int& N, int& M)
{
	cout << endl;
	for (int i=0; i < N; i++)
	{
		for (int j=0; j < M; j++)
		{
			if (j > i)
			{
				cout << "\t    0\t";
			}
			else
			{
				cout << "\t" << matriz[i][j] << "   ";
			}
		}
		cout << endl;
	}
	cout << endl;
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

vector<int> encuentra_mayor_matriz(vector<vector<double>>& matriz, int& N, int& M, int& fila, int& columna)
{
	vector<int> posicion;
	double mayor;

	posicion = {0,0};
	mayor = 0.0;

	for (int i=fila; i < N; i++)
	{
		for (int j=columna; j < M; j++)
		{
			if (fabs(matriz[i][j]) > mayor)
			{
				posicion = {i,j};
				mayor = fabs(matriz[i][j]);
			}
		}
	}

	return posicion;
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

vector<double> lee_matriz_diagonal_sparse(string nombreArchivo, int& N, int& M)
{
	vector<double> matriz;
	double auxNum;
	ifstream entrada (nombreArchivo.c_str());

	if (entrada.is_open())
	{
  		entrada >> N;
  		entrada >> M;
	  	for (int i=0; i < N; i++)
	  	{
	  		entrada >> auxNum;
	  		matriz.push_back(auxNum);
	  	}
	  	entrada.close();
	}
	else
  		cout << "ERROR al leer archivo\n";
	
	return matriz;
}

vector<vector<double>> lee_matriz_triangular_superior_sparse(string nombreArchivo, int& N, int& M)
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
	  		for (int j=i; j < M; j++)
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

vector<vector<double>> lee_matriz_triangular_inferior_sparse(string nombreArchivo, int& N, int& M)
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
	  		for (int j=0; j <= i; j++)
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

vector<double> resuelve_sistema_triangular_superior_sparse(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector<double> x(N);
	double suma;
	
	for (int i=0; i < N; i++)
	{
		if (matriz[N-1-i][0] != 0)
		{
			suma = 0;
			for (int j=0; j < i; j++)
			{
				suma = suma + matriz[N-1-i][i-j]*x[N-1-j];
			}
			x[N-1-i] = (b[N-1-i] - suma)/matriz[N-1-i][0];
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

void eliminacion_gaussiana(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	double factor;

	for (int i=0; i < N-1; i++)
	{
		for (int j=i+1; j < N; j++)
		{
			if (matriz[i][i] != 0)
			{
				factor = matriz[j][i]/matriz[i][i];
				for (int k=i; k < N; k++)
				{
					matriz[j][k] = matriz[j][k] - matriz[i][k]*factor;
				}
				b[j] = b[j] - b[i]*factor;
			}
			else
			{
				cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
				break;
			}
		}
	}
}

void intercambia_renglon_columna(vector<vector<double>>& matriz, vector<int>& indices, vector<double>& b, int& N, int& M, int& renglonA, int& columnaA, int& renglonB, int& columnaB)
{
	vector<double> auxRenglon;
	double aux;
	int auxi;

	//Intercambio de renglón
	auxRenglon = matriz[renglonA];
	matriz[renglonA] = matriz[renglonB];
	matriz[renglonB] = auxRenglon;

	aux = b[renglonA];
	b[renglonA] = b[renglonB];
	b[renglonB] = aux;

	//Intercambio de columna
	for (int i=0; i < M; i++)
	{
		aux = matriz[i][columnaA];
		matriz[i][columnaA] = matriz[i][columnaB];
		matriz[i][columnaB] = aux;
	}
	auxi = indices[columnaA];
	indices[columnaA] = indices[columnaB];
	indices[columnaB] = auxi;
}

vector<int> eliminacion_gaussiana_pivoteo(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
{
	vector <int> indices(N), indMayor;
	double factor;

	iota(indices.begin(), indices.end(), 0);

	for (int i=0; i < N-1; i++)
	{
		//Pivoteo
		indMayor = encuentra_mayor_matriz(matriz, N, M, i, i);
		if (indMayor[0] != i & indMayor[1] != i)
		{
			intercambia_renglon_columna(matriz, indices, b, N, M, i, i, indMayor[0], indMayor[1]);
		}
		//Eliminacion gaussiana
		for (int j=i+1; j < N; j++)
		{
			if (matriz[i][i] != 0)
			{
				factor = matriz[j][i]/matriz[i][i];
				for (int k=i; k < N; k++)
				{
					matriz[j][k] = matriz[j][k] - matriz[i][k]*factor;
				}
				b[j] = b[j] - b[i]*factor;
			}
			else
			{
				cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
				break;
			}
		}
	}

	return indices;
}

int main()
{
	vector<double> matrizD, b, x;
	vector<vector<double>> matrizTS, matrizTI, matrizC;
	vector<int> indices;
	int N, M, tipo;

	cout << "\n1. Diagonal\n" << "2. Triangular inferior\n" << "3. Triangular superior\n" << "4. Completo\n" << "Tipo de sistema a resolver: ";
	cin >> tipo;

	switch (tipo)
	{
		case 1:
		{
			cout << "\nSistema DIAG4\n";
			matrizD = lee_matriz_diagonal_sparse("TAREA2_MATRICES/DIAG_MAT4.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/DIAG_VEC4.txt", M);
			x = resuelve_sistema_diagonal_sparse(matrizD, b, N);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			cout << "\nSistema DIAG100\n";
			matrizD = lee_matriz_diagonal_sparse("TAREA2_MATRICES/DIAG_MAT100.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/DIAG_VEC100.txt", M);
			x = resuelve_sistema_diagonal_sparse(matrizD, b, N);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			cout << "\nSistema DIAG500\n";
			matrizD = lee_matriz_diagonal_sparse("TAREA2_MATRICES/DIAG_MAT500.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/DIAG_VEC500.txt", M);
			x = resuelve_sistema_diagonal_sparse(matrizD, b, N);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			break;
		}
		case 2:
		{
			cout << "\nSistema TINF4\n";
			matrizTI = lee_matriz_triangular_inferior_sparse("TAREA2_MATRICES/TINF_MAT4.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/TINF_VEC4.txt", M);
			x = resuelve_sistema_triangular_inferior_sparse(matrizTI, b, N, M);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			cout << "\nSistema TINF100\n";
			matrizTI = lee_matriz_triangular_inferior_sparse("TAREA2_MATRICES/TINF_MAT100.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/TINF_VEC100.txt", M);
			x = resuelve_sistema_triangular_inferior_sparse(matrizTI, b, N, M);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			cout << "\nSistema TINF500\n";
			matrizTI = lee_matriz_triangular_inferior_sparse("TAREA2_MATRICES/TINF_MAT500.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/TINF_VEC500.txt", M);
			x = resuelve_sistema_triangular_inferior_sparse(matrizTI, b, N, M);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			break;
		}
		case 3:
		{
			cout << "\nSistema TSUP4\n";
			matrizTS = lee_matriz_triangular_superior_sparse("TAREA2_MATRICES/TSUP_MAT4.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/TSUP_VEC4.txt", M);
			x = resuelve_sistema_triangular_superior_sparse(matrizTS, b, N, M);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			cout << "\nSistema TSUP100\n";
			matrizTS = lee_matriz_triangular_superior_sparse("TAREA2_MATRICES/TSUP_MAT100.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/TSUP_VEC100.txt", M);
			x = resuelve_sistema_triangular_superior_sparse(matrizTS, b, N, M);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			cout << "\nSistema TSUP500\n";
			matrizTS = lee_matriz_triangular_superior_sparse("TAREA2_MATRICES/TSUP_MAT500.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/TSUP_VEC500.txt", M);
			x = resuelve_sistema_triangular_superior_sparse(matrizTS, b, N, M);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			break;
		}
		case 4:
		{
			cout << "\nSistema FULL4\n";
			matrizC = lee_matriz_completa("TAREA2_MATRICES/FULL_MAT4.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/FULL_VEC4.txt", M);
			cout << "Eliminación gaussiana" << endl;
			eliminacion_gaussiana(matrizC, b, N, M);
			x = resuelve_sistema_triangular_superior_completo(matrizC, b, N, M);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;
			matrizC = lee_matriz_completa("TAREA2_MATRICES/FULL_MAT4.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/FULL_VEC4.txt", M);
			indices = eliminacion_gaussiana_pivoteo(matrizC, b, N, M);
			x = resuelve_sistema_triangular_superior_completo(matrizC, b, N, M);
			cout << "Eliminación gaussiana con pivoteo" << endl;
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			cout << "\nSistema FULL100\n";
			matrizC = lee_matriz_completa("TAREA2_MATRICES/FULL_MAT100.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/FULL_VEC100.txt", M);
			cout << "Eliminación gaussiana" << endl;
			eliminacion_gaussiana(matrizC, b, N, M);
			x = resuelve_sistema_triangular_superior_completo(matrizC, b, N, M);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;
			matrizC = lee_matriz_completa("TAREA2_MATRICES/FULL_MAT100.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/FULL_VEC100.txt", M);
			indices = eliminacion_gaussiana_pivoteo(matrizC, b, N, M);
			x = resuelve_sistema_triangular_superior_completo(matrizC, b, N, M);
			cout << "Eliminación gaussiana con pivoteo" << endl;
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			cout << "\nSistema FULL500\n";
			matrizC = lee_matriz_completa("TAREA2_MATRICES/FULL_MAT500.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/FULL_VEC500.txt", M);
			cout << "Eliminación gaussiana" << endl;
			eliminacion_gaussiana(matrizC, b, N, M);
			x = resuelve_sistema_triangular_superior_completo(matrizC, b, N, M);
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;
			matrizC = lee_matriz_completa("TAREA2_MATRICES/FULL_MAT500.txt", N, M);
			b = lee_vector("TAREA2_MATRICES/FULL_VEC500.txt", M);
			indices = eliminacion_gaussiana_pivoteo(matrizC, b, N, M);
			x = resuelve_sistema_triangular_superior_completo(matrizC, b, N, M);
			cout << "Eliminación gaussiana con pivoteo" << endl;
			cout << "\tNorma uno: " << norma_uno(x) << endl;
			cout << "\tNorma infinito: " << norma_infinito(x) << endl;

			break;
		}
	}

	return 0;
}