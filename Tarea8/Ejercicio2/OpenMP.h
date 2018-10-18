#include <iostream>
#include <vector>

using namespace std;

class OpenMP
{
private:
public:
	OpenMP();
	~OpenMP();
	static vector<double> suma_vectores(vector<double>& A, vector<double>& B, int& N, int& t);
	static vector<double> suma_vectores_serie(vector<double>& A, vector<double>& B, int& N);
	static vector<double> producto_vectores_eae(vector<double>& A, vector<double>& B, int& N, int& t);
	static vector<double> producto_vectores_eae_serie(vector<double>& A, vector<double>& B, int& N);
	static double producto_punto(vector<double>& A, vector<double>& B, int& N, int& t);
	static double producto_punto_serie(vector<double>& A, vector<double>& B, int& N);
	static vector<double> producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M, int& t);
	static vector<double> producto_matriz_vector_serie(vector<vector<double>>& A, vector<double>& vec, int& N, int& M);
	static vector<vector<double>> producto_matriz_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L, int& t);
	static vector<vector<double>> producto_matriz_matriz_serie(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L);
	static void prueba_openmp(int x);
};