#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static double integracion_numerica_romberg(double f(double), double a, double b, double epsilon, int maxIter);

};