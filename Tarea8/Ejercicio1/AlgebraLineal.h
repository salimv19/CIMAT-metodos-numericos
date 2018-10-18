#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static vector<vector<double>> producto_matriz_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L);
	static vector<vector<double>> producto_matrizT_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L);
	static vector<vector<double>> matriz_triangular_superior(vector<vector<double>>& A, int& N);
	static vector<int> maximo_absoluto_matriz(vector<vector<double>>& A, int& N, int& M);
	static vector<vector<double>> matriz_identidad(int& N);
	static bool metodo_jacobi_eigenvalores(vector<vector<double>>& A, vector<vector<double>>& C, vector<vector<double>>& P, int& N, double& tolerancia, int& maxIter);
};