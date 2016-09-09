#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>

using namespace std;

struct Examen
{
    string nombre;
    string profe;
    int total_puntos,correctas,malas;
    // poner las referencias hacia las listas de los dos tipos de preguntas
};

struct nodoMarqX 
{
    string respEst,tipo,nomSec,resp;
    string opciones[];
    struct nodoMarqX* sig;
    
}*cabezaMarqX;


int main() 
{
    cout<<"Aqui se llaman las varas";
    return 0;
}

