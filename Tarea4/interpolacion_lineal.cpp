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

void crea_archivo_errores(vector<vector<double>>& errores, string nombreArchivo)
{
	ofstream salida;
	salida.open(nombreArchivo.c_str());
	for (auto l:errores)
	{
		for (auto x:l)
		{
			salida << x << " ";
		}
		salida << endl;
	}
    salida.close();
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

vector<double> calcula_errores(vector<double>& ajustados, vector<double>& reales)
{
	vector<double> errores;

	for (int i=0; i < ajustados.size(); i++)
	{
		errores.push_back(fabs(ajustados[i] - reales[i+1]));
	}

	return errores;
}

double promedia_error(vector<vector<double>>& errores, int nFilas, int nColumnas)
{
	double suma;
	for (int i=0; i < nFilas; i++)
		for (int j=0; j < nColumnas; j++)
			suma = suma + errores[i][j];
	return suma/(nFilas*nColumnas);
}

int main()
{
	vector<vector<double>> data, errores;
	vector<double> coeficientes, ajustados;
	int nFilas, nColumnas;

	data = lee_csv("normal_data.csv");

	nFilas = data.size();
	nColumnas = data[0].size();
	
	for (int i=0; i < nFilas - 1; i++)
	{
		coeficientes = interpolacion_lineal(data[i][0], data[i+1][0], data[i][1], data[i+1][1]);
		for (int j=0; j < nColumnas-1; j++)
		{
			ajustados.push_back(ajusta_valor(coeficientes, data[i][0]+0.01*j));
		}
		errores.push_back(calcula_errores(ajustados, data[i]));
		ajustados.clear();
	}

	coeficientes = interpolacion_lineal(data[nFilas-1][0], 4.09, data[nFilas-1][1], data[nFilas-1][nColumnas]);
	for (int i=0; i < nColumnas-1; i++)
	{
		ajustados.push_back(ajusta_valor(coeficientes, 4.0+0.01*i));
	}
	errores.push_back(calcula_errores(ajustados, data[nFilas-1]));

	crea_archivo_errores(errores, "error_ajuste.dat");

	cout << "\n\tError promedio = " << promedia_error(errores, nFilas, nColumnas-1) << endl << endl;

	return 0;
}