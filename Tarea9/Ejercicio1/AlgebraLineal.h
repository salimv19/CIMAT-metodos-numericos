#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static vector<double> columna_indice(vector<vector<double>>& A, int& N, int& indice);
	static vector<vector<double>> matriz_identidad(int& N);
	static vector<vector<double>> inicializa_ortonormal(int N, int M);
	static vector<double> resta_vectores(vector<double> vecA, vector<double> vecB, int& N);
	static double producto_punto(vector<double> vec1, vector<double> vec2);
	static void normaliza_vector(vector<double>& x, int N);
	static double norma_dos(vector<double> x, int N);
	static vector<double> proyeccion_vector_vector(vector<double>& vecA, vector<double> vecB, int& N);
	static double norma_frobenius(vector<vector<double>>& matriz, int& N, int& M);
	static vector<vector<double>> resta_matrices(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M);
	static vector<vector<double>> producto_escalar_matriz(vector<vector<double>>& A, double& c, int& N, int& M);
	static vector<double> producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M);
	static vector<vector<double>> producto_vector_vectorT(vector<double>& vecA, vector<double> vecB, int& N, int& M);
	static vector<vector<double>> producto_matriz_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L);
	static vector<vector<double>> producto_matrizT_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L);
	static vector<vector<double>> matriz_triangular_superior(vector<vector<double>>& A, int& N);
	static vector<int> maximo_absoluto_matriz(vector<vector<double>>& A, int& N, int& M);
	static vector<vector<double>> ortogonalizacion_gram_schmidt(vector<vector<double>>& A, int& N, int& M) ;
	static vector<double> resuelve_sistema_triangular_superior_completo(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M);
	static vector<double> resuelve_sistema_triangular_inferior_sparse(vector<vector<double>>& matriz, vector<double>& b, int& N, int& M);
	static bool factoriza_LU(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U);
	static bool resuelve_sistema_LU(vector<vector<double>>& A, vector<double>& b, vector<double>& x, int& N);
	static bool metodo_potencia(vector<vector<double>>& A, vector<double>& x, double& eigenvalor, int& N, double& tolerancia, int maxIter, int& iteraciones);
	static bool metodo_jacobi_eigenvalores(vector<vector<double>>& A, vector<vector<double>>& C, vector<vector<double>>& P, int& N, double& tolerancia, int& maxIter);
	static bool eigenvectores_subespacio(vector<vector<double>>& A, int& N, vector<vector<double>>& X, vector<vector<double>>& C, int& M, double& tolerancia, int& maxIter);
	static bool eigenvectores_menores_subespacio(vector<vector<double>>& A, int& N, vector<vector<double>>& X, vector<vector<double>>& C, int& M, double& tolerancia, int& maxIter);
};