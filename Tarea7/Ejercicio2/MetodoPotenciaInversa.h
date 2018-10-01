#include <iostream>
#include <vector>

using namespace std;

class MetodoPotenciaInversa
{
private:
public:
	MetodoPotenciaInversa();
	~MetodoPotenciaInversa();
	static bool abs_compare(double a, double b);
	static double producto_punto(vector<double> vec1, vector<double> vec2);
	static vector<double> producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M);
	static vector<double> resta_vectores(vector<double> vecA, vector<double>& vecB, int& N);
	static double norma_uno(vector<double>& x);
	static double norma_infinito(vector<double>& x);
	static double norma_dos(vector<double> x, int N);
	static void normaliza_vector(vector<double>& x, int N);
	static vector<double> resuelve_sistema_triangular_superior_completo(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M);
	static vector<double> resuelve_sistema_triangular_inferior_sparse(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M);
	static bool resuelve_sistema_LU(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int& N);
	static bool factoriza_LU(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U);
	static bool metodo_potencia_inversa(vector<vector<double>>& A, vector<double>& x, double& eigenvalor, int& N, double& tolerancia, int& maxIter, int& iteraciones);
};