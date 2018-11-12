#include <iostream>
#include <vector>

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static void llena_tabla_polinomios(vector<vector<double>>& coeficientes, vector<double>& x, vector<double>& y, int N);
	static double interpola_nuevo_dato(vector<vector<double>>& coeficientes, vector<double>& x, double xNuevo, int N);
};