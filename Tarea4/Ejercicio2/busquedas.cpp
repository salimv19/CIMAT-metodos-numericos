#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>

/*
Salim Vargas Hernández
Métodos numéricos
Tarea 4
Interpolación lineal
Septiembre 2018
*/

using namespace std;

template <typename T>
void imprime_vector(vector<T>& vec)
{
	for (int i=0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

vector<vector<double>> lee_csv(string nombreArchivo)
{
    vector<vector<double>> data;
    ifstream entrada(nombreArchivo);
    int l = 0;
 
    while (entrada)
    {
        l++;
        string s;
        if (!getline(entrada, s))
        	break;
        if (s[0] != '#')
        {
            istringstream ss(s);
            vector<double> record;
 
            while (ss)
            {
                string line;
                if (!getline(ss, line, ','))
                    break;
                try
                {
                    record.push_back(stof(line));
                }
                catch (const std::exception& e)
                {
                    cout << "NaN encontrado en el archivo " << nombreArchivo << " línea " << l << endl;
                    e.what();
                }
            }
            data.push_back(record);
        }
    }
 
    if (!entrada.eof())
    {
        cerr << "No se puede leer el archivo " << nombreArchivo << "\n";
        __throw_invalid_argument("File not found.");
    }
 
    return data;
}

int busqueda_binaria(vector<double>& vector, double& valor, int indiceA, int indiceB)
{
	int indiceM;

	if (valor >= vector[indiceA] && valor <= vector[indiceB])
	{
		//El valor está dentro de los límites de valores del vector
		while(indiceB - indiceA > 1) //Mientras el valor no esté encerrado en un solo intervalo
		{
			indiceM = indiceA + (indiceB - indiceA)/2; //Cálculo del punto medio
			//Ajuste de los límites dependiendo de la posición del valor a buscar
			if (valor > vector[indiceM])
				indiceA = indiceM;
			else
				indiceB = indiceM;
		}
	}
	else
	{
		cout << "\tCUIDADO. Valor fuera del intervalo, se usará extrapolación\n";
		if (valor > vector[indiceB])
			indiceA = indiceB-1; //Extrapolación usando el último intervalo
	}
	return indiceA;
}

int hunting_search(vector<double>& vector, double& valor, int indiceAprox)
{
	int paso, longVec;

	longVec = vector.size();
	paso = 1;
	if (valor >= vector[0] && valor <= vector[longVec - 1])
	{
		if (valor < vector[indiceAprox])
		{
			while (valor < vector[max(indiceAprox - paso, 0)]) //Mientras el nuevo índice aún no abarque al valor buscado
			{
				indiceAprox = max(indiceAprox - paso, 0); //Se usa max para evitar que el índice salga de los límites del vector
				paso = 2*paso;
			}
			//Se realiza búsqueda binaria sobre el intervalo que contiene al valor
			return busqueda_binaria(vector, valor, max(indiceAprox - paso, 0), indiceAprox);
		}
		else
		{
			while (valor > vector[min(indiceAprox + paso, longVec - 1)]) //Mientras el nuevo índice aún no abarque al valor buscado
			{
				indiceAprox = min(indiceAprox + paso, longVec - 1); //Se usa min para evitar que el índice salga de los límites del vector
				paso = 2*paso;
			}
			//Se realiza búsqueda binaria sobre el intervalo que contiene al valor
			return busqueda_binaria(vector, valor, indiceAprox, min(indiceAprox + paso, longVec - 1));
		}
	}
	else
	{
		cout << "\tCUIDADO. Valor fuera del intervalo, se usará extrapolación\n";
		if (valor > vector[longVec - 1])
			return longVec-2; //Extrapolación usando el último intervalo
		else
			return 0; //Extrapolación usando el primer intervalo
	}
}

vector<double> interpolacion_lineal(double x0, double x1, double f0, double f1)
{
	vector<double> coeficientes(2);
	
	coeficientes[0] = f0 - 1.0*x0*(f1-f0)/(x1-x0);
	coeficientes[1] = 1.0*(f1-f0)/(x1-x0);

	return coeficientes;
}

double ajusta_valor(vector<double>& coeficientes, double x)
{
	return coeficientes[0] + coeficientes[1]*x;
}

int main()
{
	vector<vector<double>> data;
	vector<double> vectorBusqueda, coeficientes;
	string continuar;
	double valor;
	int nFilas, nColumnas, indice;

	data = lee_csv("normal_data.csv");

	nFilas = data.size();
	nColumnas = data[0].size();
	
	//El vector de búsqueda estará formado por los números del 0.0 al 4.0 en intervalos de 0.1 [0, 0.1, 0.2, 0.3, ... ,4.0]
	for (int i=0; i < nFilas; i++)
		vectorBusqueda.push_back(data[i][0]);

	cout << "\nIngrese un valor entre " << vectorBusqueda[0] << " y " << vectorBusqueda[nFilas-1] << ": ";
	cin >> valor;

	//Como es el primer valor, se realiza una búsqueda binaria
	indice = busqueda_binaria(vectorBusqueda, valor, 0, nFilas-1);
	//Se obtienen los coeficientes de interpolación lineal para el intervalo en el que se encuentra el valor ingresado
	coeficientes = interpolacion_lineal(data[indice][0], data[indice+1][0], data[indice][1], data[indice+1][1]);

	cout << "\nEl valor aproximado para x = " << valor << " es ŷ = " << ajusta_valor(coeficientes, valor) << endl;

	cout << "\n¿Aproximar un nuevo valor? Y/n : ";
	cin >> continuar;

	while (continuar == "Y" || continuar == "y")
	{
		cout << "\nIngrese un valor entre " << vectorBusqueda[0] << " y " << vectorBusqueda[nFilas-1] << ": ";
		cin >> valor;

		//Se toma el índice anterior como aproximación para el nuevo y se realiza hunting search
		indice = hunting_search(vectorBusqueda, valor, indice);
		//Se obtienen los coeficientes para el nuevo intervalo
		coeficientes = interpolacion_lineal(data[indice][0], data[indice+1][0], data[indice][1], data[indice+1][1]);

		cout << "\nEl valor aproximado para x = " << valor << " es ŷ = " << ajusta_valor(coeficientes, valor) << endl;
		cout << "\n¿Aproximar un nuevo valor? Y/n : ";
		cin >> continuar;
	}

	return 0;
}