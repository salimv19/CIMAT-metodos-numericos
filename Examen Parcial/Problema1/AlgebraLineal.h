#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static vector<vector<double>> producto_matriz_matriz(vector<vector<double>>& A, vector<vector<double>>& B, int& N, int& M, int& L);
	static vector<double> producto_matriz_vector(vector<vector<double>>& A, vector<double>& vec, int& N, int& M);
	static bool invierte_matriz(vector<vector<double>>& A, vector<vector<double>>& inversa);

};