#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>

using namespace std;
//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
struct Examen
{
    string nombre;
    string profe;
    int total_puntos,correctas,malas,nota;
    // poner las referencias hacia las listas de los dos tipos de preguntas
};

// preugntas de marque con x
struct nodoMarqX 
{
    /* numPreg  ->  numero de pregunta
     * resp     ->  respuesta correcta de la pregunta
     * respEst  ->  respuesta ingresada por el estudiante
     * tipo     ->  tipo de pregunta  ( marque x  ,  respuesta breve )
     * nomSec   ->  nombre de la seccion ( geografia, historia, geometria, numeros reales )
     * valor    ->  cantidad de puntos que va a valer esa pregunta
     */
    string numPreg,resp,respEst,tipo,nombSec;
    string opciones[];
    int valor;
    struct nodoMarqX* sig;
    
}*cabezaMarqX;
//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//preguntas de respuesta breve
struct nodoRespCort
{
    /* numPreg  ->  numero de pregunta
     * resp     ->  respuesta correcta de la pregunta
     * respEst  ->  respuesta ingresada por el estudiante
     * tipo     ->  tipo de pregunta  ( marque x  ,  respuesta breve )
     * nomSec   ->  nombre de la seccion ( geografia, historia, geometria, numeros reales )
     * valor    ->  cantidad de puntos que va a valer esa pregunta
     */
    string numPreg,resp,respEst,tipo,nomSec;
    int porcAcierto = 60;
    int valor;
    
}*cabezaRespCort;

//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main() 
{
    cout<<"Aqui se llaman las varas";
    return 0;
}

