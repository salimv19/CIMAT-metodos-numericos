#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static double norma_dos(vector<double> x, int N);
	static vector<double> producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M);
	static void gradiente_conjugado(vector<vector<double>>& A, vector<double>& b, vector<double>& x, vector<double>& error, int& N, int& iteraciones);
	static void gradiente_conjugado_sparse(vector<map<int,double>>& A, vector<double>& b, vector<double>& x, vector<double>& residuo, int& N, int& iteraciones);
	static void gradiente_conjugado_precondicionado_jacobi_sparse(vector<map<int,double>>& A, vector<double>& b, vector<double>& x, vector<double>& residuo, int& N, int& iteraciones);
	static void producto_matriz_sparse_vector(vector<map<int,double>>& A, vector<double>& vec, vector<double>& prod, int& filas);
	static bool resuelve_sistema_LU(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int& N);
};