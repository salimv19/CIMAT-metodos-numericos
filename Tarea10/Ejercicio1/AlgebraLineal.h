#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static vector<double> resta_vectores(vector<double> vecA, vector<double> vecB, int& N);
	static double producto_punto(vector<double> vec1, vector<double> vec2);
	static double norma_dos(vector<double> x, int N);
	static vector<double> producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M);
	static void gradiente_conjugado(vector<vector<double>>& A, vector<double>& b, vector<double>& x, vector<double>& error, int& N, int& iteraciones);
};