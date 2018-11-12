#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static double integracion_cuadratura_gaussiana(double f(double), double a, double b, int n);
};