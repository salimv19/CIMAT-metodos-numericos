#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <algorithm>
#include <vector>
//#include <typeinfo>
//#include <map>

using namespace std;


void imprime_vector(vector<string> vec)
{
	for (int i=0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

void imprime_matriz_diagonal(vector<vector<double>>& matriz)
{
	//bla bla bla
}

vector<string> lee_emails(string nombreArchivo, int& nEmails)
{
	vector<string> palabras, email;
	string linea, palabra;
	ifstream entrada (nombreArchivo.c_str());

	if (entrada.is_open())
	{
  		entrada >> nEmails;
	  	while (!entrada.eof())
	  	{
	  		getline(entrada, linea);
	  		entrada >> 
	  	}
	  	entrada.close();
	}
	else
  		cout << "ERROR al leer archivo\n";
  sort(palabras.begin(), palabras.end());

  return palabras;
}

vector<string> lee_nuevo_email(string nombreArchivo, vector<string>& diccionario)
{
	vector<string> palabras, nuevasPalabras;
	string palabra;
	ifstream entrada (nombreArchivo.c_str());

	if (entrada.is_open())
	{
	  	while (!entrada.eof())
		{
			entrada >> palabra;
			palabra = quita_caracteres(palabra);
	  		transform(palabra.begin(), palabra.end(), palabra.begin(), ::tolower);
			
			if (palabra.length() > 3 & find(palabras.begin(), palabras.end(), palabra) == palabras.end())
	  		{
	  			palabras.push_back(palabra);
	  		}
	  	}
	  	entrada.close();
	}
	else
  		cout << "ERROR al leer archivo\n";
	
	sort(palabras.begin(), palabras.end());
	interseca_diccionarios(palabras, diccionario, nuevasPalabras);

	return nuevasPalabras;
}

void imprime_resultados(vector<string>& palabras, vector<double>& probabilidades)
{
	string cadena;

	for (int i=0; i < palabras.size(); i++)
	{
		cadena.append(" \"");
		cadena.append(palabras[i]);
		cadena.append("\"");
	}

	cout << "P(spam |" << cadena << ") = " << probabilidades[0] << endl;
	cout << "P(no spam |" << cadena << ") = " << probabilidades[1] << endl;

	if (probabilidades[0] > probabilidades[1])
	{
		cout << "\n\tEl e-mail se considera SPAM\n" << endl;
	}
	else
	{
		cout << "\n\tEl e-mail se considera NO SPAM\n" << endl;
	}
}

int main()
{
	

	return 0;
}