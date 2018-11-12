#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static double integracion_numerica_interpolacion_vandermonde(vector<double>& x, vector<double>& y, int N, int grado, double a, double b);
};