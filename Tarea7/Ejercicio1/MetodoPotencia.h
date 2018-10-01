#include <iostream>
#include <vector>

using namespace std;

class MetodoPotencia
{
private:
public:
	MetodoPotencia();
	~MetodoPotencia();
	static bool abs_compare(double a, double b);
	static double producto_punto(vector<double> vec1, vector<double> vec2);
	static vector<double> producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M);
	static vector<double> resta_vectores(vector<double> vecA, vector<double>& vecB, int& N);
	static double norma_uno(vector<double>& x);
	static double norma_infinito(vector<double>& x);
	static double norma_dos(vector<double> x, int N);
	static void normaliza_vector(vector<double>& x, int N);
	static bool metodo_potencia(vector<vector<double>>& A, vector<double>& x, double& eigenvalor, int& N, double& tolerancia, int& maxIter, int& iteraciones);
};