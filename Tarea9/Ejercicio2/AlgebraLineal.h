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
	static vector<double> resta_vectores(vector<double> vecA, vector<double> vecB, int& N);
	static double producto_punto(vector<double> vec1, vector<double> vec2);
	static double norma_dos(vector<double> x, int N);
	static double norma_frobenius(vector<vector<double>>& matriz, int& N, int& M);
	static vector<vector<double>> resta_matrices(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M);
	static vector<double> proyeccion_vector_vector(vector<double>& vecA, vector<double> vecB, int& N);
	static vector<vector<double>> producto_matriz_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L);
	static vector<vector<double>> producto_matrizT_matriz(vector<vector<double>>& A, vector<vector<double>> B, int& N, int& M, int& L);
	static vector<vector<double>> ortogonalizacion_gram_schmidt(vector<vector<double>>& A, int& N, int& M) ;
	static void factorizacion_QR(vector<vector<double>>& A, vector<vector<double>>& Q, vector<vector<double>>& R, int& N, int& M);
};