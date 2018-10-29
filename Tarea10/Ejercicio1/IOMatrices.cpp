#include <iostream>
#include <fstream>
#include "IOMatrices.h"

using namespace std;

IOMatrices::IOMatrices()
{
}

IOMatrices::~IOMatrices()
{
}

bool IOMatrices::lee_vector(string nombreArchivo, vector<double>& vector, int& N)
{
	//vector<double> vector;
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
  		return false;
	
	return true;
}

vector<double> IOMatrices::lee_matriz_diagonal_sparse(string nombreArchivo, int& N, int& M)
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

vector<vector<double>> IOMatrices::lee_matriz_triangular_superior_sparse(string nombreArchivo, int& N, int& M)
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

vector<vector<double>> IOMatrices::lee_matriz_triangular_inferior_sparse(string nombreArchivo, int& N, int& M)
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

bool IOMatrices::lee_matriz_completa(string nombreArchivo, vector<vector<double>>& matriz, int& N, int& M)
{
	vector<double> renglon;
	double auxNum;
	bool lectura;
	ifstream entrada (nombreArchivo.c_str());

	lectura = false;

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
	  	lectura = true;
	}
	else
  		cout << "ERROR al leer archivo\n";
	
	return lectura;
}

void IOMatrices::imprime_matriz_diagonal_superior_sparse(vector<vector<double>>& matriz, int& N, int& M)
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

void IOMatrices::imprime_matriz_diagonal_inferior_sparse(vector<vector<double>>& matriz, int& N, int& M)
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

void IOMatrices::imprime_matriz_completa(vector<vector<double>>& matriz, int& N, int& M)
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

void IOMatrices::imprime_vector(vector<double> vec)
{
	for (int i=0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

