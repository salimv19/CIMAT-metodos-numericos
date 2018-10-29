#include <iostream>
#include <vector>
#include <map>

using namespace std;

class IOMatrices
{
private:
public:
	IOMatrices();
	~IOMatrices();
	static bool lee_vector(string nombreArchivo, vector<double>& vector, int& N);
	static bool lee_matriz_completa(string nombreArchivo, vector<vector<double>>& matriz, int& N, int& M);
	static bool lee_matriz_sparse(string nombreArchivo, vector<map<int,double>>& matriz, int& N, int& M);
	static vector<double> lee_matriz_diagonal_sparse(string nombreArchivo, int& N, int& M);
	static vector<vector<double>> lee_matriz_triangular_superior_sparse(string nombreArchivo, int& N, int& M);
	static vector<vector<double>> lee_matriz_triangular_inferior_sparse(string nombreArchivo, int& N, int& M);
	static void imprime_vector(vector<double> vec);
	static void imprime_matriz_completa(vector<vector<double>>& matriz, int& N, int& M);
	static void imprime_matriz_diagonal_superior_sparse(vector<vector<double>>& matriz, int& N, int& M);
	static void imprime_matriz_diagonal_inferior_sparse(vector<vector<double>>& matriz, int& N, int& M);
};
