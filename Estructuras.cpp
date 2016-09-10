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
    struct Examen * sig;
}*cabezaExamen;


// preguntas de marque con x
struct MarqX 
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
    struct MarqX* sig;
    
}*cabezaX;
//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//preguntas de respuesta breve
struct RespCort
{
    /* numPreg  ->  numero de pregunta
     * pregunta ->  la pregunta en si
     * resp     ->  respuesta correcta de la pregunta
     * respEst  ->  respuesta ingresada por el estudiante
     * tipo     ->  tipo de pregunta  ( marque x  ,  respuesta breve )
     * nomSec   ->  nombre de la seccion ( geografia, historia, geometria, numeros reales )
     * valor    ->  cantidad de puntos que va a valer esa pregunta
     * porcAcierto -> porcentaje de igualdad que se acepta para dar por buena una respuesta
     */
    string numPreg,resp,respEst,tipo,nomSec,pregunta;
    int porcAcierto = 60;
    int valor;
    struct RespCort* sig;
    
}*cabezaRC;

//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


void insertarExamenes()
{
    //solicitar memoria
    struct Examen* nn;
    nn = new struct Examen; 
    string nom;
    string pro;
    
    cout << "Digite el nombre del Examen" << endl;
    getline(cin,nom);
    cout << "Digite el nombre del profe" << endl;
    getline(cin,pro);
    
    //lleno datos
    nn->nombre = nom;
    nn->profe  = pro;
    nn->total_puntos = 0;
    nn->correctas  = 0;
    nn->malas  = 0;
    nn->nota  = 0;
    nn->sig = NULL;

    //enlazar
    if (cabezaExamen == NULL)
        cabezaExamen = nn;
    else
    {
        nn->sig = cabezaExamen;
        cabezaExamen = nn;
    }
}

void imprimirListaExamenes()
{
    struct Examen* temp = cabezaExamen;

    while (temp != NULL)
    {
        cout << temp->nombre << endl;
        temp = temp->sig;
    }
}

void insertarPreguntasCortas()
{
    //solicitar memoria
    struct RespCort* nn;
    nn = new struct RespCort; 
    string pre;
    string res;

    cout << "Escriba la pregunta." << endl;
    getline(cin,pre);
    cout << "Escriba la respuesta de la pregunta." << endl;
    getline(cin,res);
    
    //lleno datos
    nn->pregunta = pre;
    nn->resp = res;
    nn->respEst  = "";
    nn->tipo = "Corta";
    nn->nomSec = "";
    nn->porcAcierto = 0;
    nn->valor = 0;
    nn->sig = NULL;

    //enlazar
    if (cabezaRC == NULL)
        cabezaRC = nn;
    else
    {
        nn->sig = cabezaRC;
        cabezaRC = nn;
    }
}

void imprimirListaPreguntasRC()
{
    struct RespCort* temp = cabezaRC;

    while (temp != NULL)
    {
        cout << temp->pregunta << endl;
        cout << temp->resp << endl;
        temp = temp->sig;
    }
}
int main() 
{
    //insertarExamenes();
    //imprimirListaExamenes();
    //insertarPreguntasCortas();
    //imprimirListaPreguntasRC();
    return 0;
}