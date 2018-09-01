#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <algorithm>
#include <vector>
//#include <typeinfo>
//#include <map>

using namespace std;


void imprime_vector(vector<double> vec)
{
	for (int i=0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

void imprime_matriz_diagonal_superior(vector<vector<double>>& matriz, int& N, int& M)
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

vector<double> lee_matriz_diagonal(string nombreArchivo, int& N, int& M)
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

vector<vector<double>> lee_matriz_triangular_superior(string nombreArchivo, int& N, int& M)
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

vector<vector<double>> lee_matriz_triangular_inferior(string nombreArchivo, int& N, int& M)
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

vector<double> resuelve_sistema_diagonal(vector<double>& matriz, vector<double>& b, int& N)
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
		}
	}

	return x;
}

vector<double> resuelve_sistema_triangular_superior(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
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
			x[i] = (b[i] - suma)/matriz[N-1-i][0];
		}
		else
		{
			cout << "\tERROR. Los elementos de la diagonal contienen ceros\n";
		}
	}

	return x;
}

vector<double> resuelve_sistema_triangular_inferior(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M)
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
		}
	}

	return x;
}

vector<string> lee_nuevo_email(string nombreArchivo, vector<string>& diccionario)
{
	vector<string> palabras, nuevasPalabras;
	string palabra;
	ifstream entrada (nombreArchivo.c_str());

	if (entrada.is_open())
	{
	  	while (!entrada.eof())
		{
			entrada >> palabra;
			
			if (palabra.length() > 3)
	  		{
	  			palabras.push_back(palabra);
	  		}
	  	}
	  	entrada.close();
	}
	else
  		cout << "ERROR al leer archivo\n";

	return nuevasPalabras;
}

void imprime_resultados(vector<string>& palabras, vector<double>& probabilidades)
{
	string cadena;

	for (int i=0; i < palabras.size(); i++)
	{
		cadena.append(" \"");
		cadena.append(palabras[i]);
		cadena.append("\"");
	}

	cout << "P(spam |" << cadena << ") = " << probabilidades[0] << endl;
	cout << "P(no spam |" << cadena << ") = " << probabilidades[1] << endl;

	if (probabilidades[0] > probabilidades[1])
	{
		cout << "\n\tEl e-mail se considera SPAM\n" << endl;
	}
	else
	{
		cout << "\n\tEl e-mail se considera NO SPAM\n" << endl;
	}
}

int main()
{
	vector<double> matrizD, b, x;
	vector<vector<double>> matrizTS, matrizTI, matrizC;
	int N, M;

	/*matrizD = lee_matriz_diagonal("TAREA2_MATRICES/DIAG_MAT500.txt", N, M);
	b = lee_vector("TAREA2_MATRICES/DIAG_VEC500.txt", M);
	x = resuelve_sistema_diagonal(matrizD, b, N);*/

	/*matrizTS = lee_matriz_triangular_superior("TAREA2_MATRICES/TSUP_MAT500.txt", N, M);
	b = lee_vector("TAREA2_MATRICES/TSUP_VEC500.txt", M);
	x = resuelve_sistema_triangular_superior(matrizTS, b, N, M);*/

	matrizTI = lee_matriz_triangular_inferior("TAREA2_MATRICES/TINF_MAT4.txt", N, M); imprime_matriz_diagonal_superior(matrizTI, N, M);
	b = lee_vector("TAREA2_MATRICES/TINF_VEC4.txt", M);
	x = resuelve_sistema_triangular_inferior(matrizTI, b, N, M);

	imprime_matriz_diagonal_superior(matrizTI, N, M);
	imprime_vector(x);

	return 0;
}