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

vector<double> lee_vector(string nombreArchivo, int& N)
{
	vector<double> vector;
	double auxNum;
	ifstream entrada (nombreArchivo.c_str());

	if (entrada.is_open())
	{
  		entrada >> N;
	  	for (int i=0; i < N; i++)
	  	{
	  		entrada >> auxNum;
	  		vector.push_back(auxNum);
	  	}
	  	entrada.close();
	}
	else
  		cout << "ERROR al leer archivo\n";
	
	return vector;
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
	vector<double> coeficientes, ajustados;

	data = lee_csv("normal_data.csv");

	for (auto l:data)
	{
		for (auto x:l)
		{
			cout << x << " ";
		}
		cout << endl;
	}

	coeficientes = interpolacion_lineal(data[data.size()-1][0], 4.09, data[data.size()-1][1], data[data.size()-1][data[0].size()]);

	for (int i=0; i < 10; i++)
	{
		ajustados.push_back(ajusta_valor(coeficientes, 4.0+0.01*i));
	}



	return 0;
}