#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <algorithm>
#include <vector>
#include <cmath>
#include <numeric>
//#include <typeinfo>
//#include <map>

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
		while(indiceB - indiceA > 1)
		{
			indiceM = indiceA + (indiceB - indiceA)/2;
			if (valor > vector[indiceM])
				indiceA = indiceM;
			else
				indiceB = indiceM;
		}
	}
	else
	{
		cout << "\tValor fuera del intervalo\n";
	}
	return indiceA;
}

int hunting_search(vector<double>& vector, double& valor, int indiceAprox)
{
	int indiceH, paso;

	paso = 1;
	if (valor < vector[indiceAprox])
	{
		while (valor < vector[indiceAprox-paso])
		{
			indiceAprox = indiceAprox - paso;
			paso = 2*paso;
		}
		return busqueda_binaria(vector, valor, indiceAprox - paso, indiceAprox);
	}
	else
	{
		while (valor > vector[indiceAprox+paso])
		{
			indiceAprox = indiceAprox + paso;
			paso = 2*paso;
		}
		return busqueda_binaria(vector, valor, indiceAprox, indiceAprox + paso);
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
	
	for (int i=0; i < nFilas; i++)
		vectorBusqueda.push_back(data[i][0]);

	cout << "\nIngrese un valor entre " << vectorBusqueda[0] << " y " << vectorBusqueda[nFilas-1] << ": ";
	cin >> valor;

	indice = busqueda_binaria(vectorBusqueda, valor, 0, nFilas-1);
	coeficientes = interpolacion_lineal(data[indice][0], data[indice+1][0], data[indice][1], data[indice+1][1]);

	cout << "\nEl valor aproximado para x = " << valor << " es ŷ = " << ajusta_valor(coeficientes, valor) << endl;

	cout << "\n¿Aproximar un nuevo valor? Y/n : ";
	cin >> continuar;

	while (continuar == "Y" || continuar == "y")
	{
		cout << "\nIngrese un valor entre " << vectorBusqueda[0] << " y " << vectorBusqueda[nFilas-1] << ": ";
		cin >> valor;

		indice = hunting_search(vectorBusqueda, valor, indice);
		coeficientes = interpolacion_lineal(data[indice][0], data[indice+1][0], data[indice][1], data[indice+1][1]);

		cout << "\nEl valor aproximado para x = " << valor << " es ŷ = " << ajusta_valor(coeficientes, valor) << endl;
		cout << "\n¿Aproximar un nuevo valor? Y/n : ";
		cin >> continuar;
	}

	return 0;
}