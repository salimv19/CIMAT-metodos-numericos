#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
#include "AlgebraLineal.h"

using namespace std;

const double epsMaquina = numeric_limits<double>::epsilon();

AlgebraLineal::AlgebraLineal()
{
}

AlgebraLineal::~AlgebraLineal()
{
}

void imprime_vec_de_vec(vector<vector<double>> datos)
{
	cout << endl;
	for (auto vec:datos)
	{
		for (int i=0; i < vec.size(); i++)
			cout << "\t" << vec[i];
		cout << endl;
	}
}

double AlgebraLineal::integracion_numerica_romberg(double f(double), double a, double b, double epsilon, int maxIter)
{
	vector<vector<double>> aproximaciones;
	vector<double> aproxVec;
	double h, suma;
	int iter;

	iter = 0;
	h = b - a;
	aproxVec.push_back( 1.0*(f(a) + f(b))/(2*h) );
	aproximaciones.push_back(aproxVec);
	aproxVec.clear();

	do
	{
		iter = iter + 1;
		h = 1.0*h/2;

		suma = 0;
		for (int k=1; k <= pow(2, iter-1); k++)
			suma = suma + f( a + (2.0*k - 1)*h );

		aproxVec.push_back( 0.5*aproximaciones[iter-1][0] + h*suma );

		for (int j=1; j <= iter; j++)
			aproxVec.push_back( ( pow(4,j)*aproxVec[j-1] - aproximaciones[iter-1][j-1] )/(pow(4, j) - 1) );

		aproximaciones.push_back(aproxVec);
		aproxVec.clear();
		
	} while ( fabs(aproximaciones[iter][iter]-aproximaciones[iter][iter-1]) > epsilon && iter < maxIter);

	//imprime_vec_de_vec(aproximaciones);

	return aproximaciones[iter][iter];
}