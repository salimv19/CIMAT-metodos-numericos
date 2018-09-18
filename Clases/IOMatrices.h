#include <iostream>
#include <vector>

/*
Salim Vargas Hernández
Programación y Algoritmos
Tarea 3
Redes neuronales
Septiembre 2018
*/

using namespace std;

class AlgebraLineal
{
private:
public:
	AlgebraLineal();
	~AlgebraLineal();
	static double producto_punto(vector<double>& vec1, vector<double>& vec2);
};