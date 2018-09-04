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

int main()
{
	vector<vector<double>> data;

	data = lee_csv("normal_data.csv");

	for (auto l:data)
	{
		for (auto x:l)
		{
			cout << x << " ";
		}
		cout << endl;
	}

	return 0;
}