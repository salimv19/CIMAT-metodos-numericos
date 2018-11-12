#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static void muestrea_funcion_1x(vector<double>& x, vector<double>& y, double& paso, double a, double b, int nPuntos);
	static double integracion_numerica_simpson_13(vector<double>& y, double dx, int nPuntos);
};