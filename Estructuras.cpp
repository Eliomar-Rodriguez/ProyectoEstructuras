#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>
#include <sstream>

using namespace std;
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
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
     * pregunta ->  la pregunta en si
     * resp     ->  respuesta correcta de la pregunta
     * respEst  ->  respuesta ingresada por el estudiante
     * tipo     ->  tipo de pregunta  ( marque x  ,  respuesta breve )
     * nomSec   ->  nombre de la seccion ( geografia, historia, geometria, numeros reales )
     * valor    ->  cantidad de puntos que va a valer esa pregunta
     * estado   ->  estado de la pregunta (correcta, incorrecta, incompleta)
     * opciones ->  posibles respuestas a la pregunta (es variable, pueden haber 3,4,5, "n" numero de opciones)
     */
    string numPreg,tipo,nomSec,estado,pregunta,resp,respEst;
    string opciones[5];
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
     * estado   ->  estado de la pregunta (correcta, incorrecta, incompleta)
     * porcentaje -> porcentaje de acierto con la respuesta correcta
     */
    string numPreg,resp,respEst,tipo,nomSec,pregunta,estado;
    int valor;
    float porcentaje;
    struct RespCort* sig;
    
}*cabezaRC;

//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


// Función que inserta nuevos examenes al final de la lista de examenes
void insertarExamenes()
{
    //se crea un nodo nuevo con la información del examen por crear
    struct Examen* nn;
    nn = new struct Examen; 
    string nom;
    string pro;
    
    //se piden los datos al usuario
    cout << "Digite el nombre del Examen" << endl;
    getline(cin,nom);
    cout << "Digite el nombre del profe" << endl;
    getline(cin,pro);
    
    //se llenan los datos
    nn->nombre = nom;
    nn->profe  = pro;
    nn->total_puntos = 0;
    nn->correctas  = 0;
    nn->malas  = 0;
    nn->nota  = 0;
    nn->sig = NULL;

    //se enlaza el nuevo nodo al final de la lista
    if (cabezaExamen == NULL)
        cabezaExamen = nn;
    else
    {
        nn->sig = cabezaExamen;
        cabezaExamen = nn;
    }
}

//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//Función que imprime los examenes creados en el sistema
void imprimirListaExamenes()
{
    struct Examen* temp = cabezaExamen; // se crea un temporal local para no modificar los datos originales

    while (temp != NULL)
    {
        cout << temp->nombre << endl; //se imprime el nombre de los examenes en el sistema
        temp = temp->sig;
    }
}

//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

// Función que inserta nuevas preguntas de respuesta corta al final de la lista de preguntas de respuesta corta
void insertarPreguntasCortas()
{
    //se crea un nodo nuevo con la información de la pregunta por crear
    struct RespCort* nn;
    nn = new struct RespCort; 
    string pre;
    string res;
    string val;

    //se piden los datos al usuario
    cout << "Escriba la pregunta." << endl;
    getline(cin,pre);
    cout << "Escriba la respuesta de la pregunta." << endl;
    getline(cin,res);
    for(int i = 0; res[i]; i++) 
          res[i] = tolower(res[i]);
    cout << "Escriba el valor de la pregunta." << endl;
    getline(cin,val);
    int valor = atoi(val.c_str()); ;
    
    //se llenan los datos
    nn->pregunta = pre;
    nn->resp = res;
    nn->respEst  = "";
    nn->tipo = "Corta";
    nn->nomSec = "";
    nn->estado = "Incompleta";
    nn->valor = valor;
    nn->porcentaje = 0;
    nn->sig = NULL;

    //se enlaza el nuevo nodo al final de la lista
    if (cabezaRC == NULL)
        cabezaRC = nn;
    else
    {
        nn->sig = cabezaRC;
        cabezaRC = nn;
    }
}
//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


//Función que imprime las preguntas de respuesta corta creadas en el sistema y su respectiva respuesta correcta.
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

//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

//Funciòn que sirve para responder preguntas de Respuesta Corta
void responderRC(RespCort*cabezaRC)
{
    string respuesta;
    int contador = 0;
    double coin = (cabezaRC->resp.length()*60)/100; // porcentaje mínimo de semejanza en la respuesta para acertar o fallar la pregunta.
    
    if (cabezaRC != NULL){
        cout << cabezaRC->pregunta << endl;
        cout << "Digite su respuesta plz..." << endl;   //se introduce la respuesta a la pregunta
        getline(cin,respuesta);

        for(int i = 0; respuesta[i]; i++) 
          respuesta[i] = tolower(respuesta[i]); //se transforma la respuesta a caracteres en minuscula.

        cabezaRC->respEst = respuesta;  //se guarda la respuesta en el nodo correspondiente
        
        for (int x = 0; cabezaRC->resp[x] != '\0' ;x++) //ciclo que revisa caracter por caracter para validar la respuesta.
            if (cabezaRC->resp[x] == respuesta[x])
                contador++;     //se lleva un contador con la cantidad de caracteres similares
        if (contador > coin){
            cabezaRC->estado = "correcta";  //se guarda la pregunta como "correcta" si la cantidad de coincidencias es mayor al 60% de la pregunta.
            cabezaRC->porcentaje = (contador*100)/cabezaRC->resp.length();} //se guarda el porcentaje de acierto para desplegarlo más adelante.
        else
        {
            cabezaRC->estado = "incorrecta";    //se guarda la pregunta como "incorrecta" si la cantidad de coincidencias es menor al 60% de la pregunta.
            cabezaRC->porcentaje = (contador*100)/cabezaRC->resp.length();} //se guarda el porcentaje de acierto para desplegarlo más adelante.
        }
        
        cout << "Respuesta Introducida = "+ cabezaRC->respEst <<endl;
        cout << "Respuesta Correcta = " + cabezaRC->resp <<endl;
        cout << "Estado de la pregunta = "+ cabezaRC->estado << endl;
        cout << "Porcentaje de igualdad de la respuesta = ";
        cout << cabezaRC->porcentaje;
        cout << "%" << endl;
}
//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx


// Función que inserta nuevas preguntas de marcar con x al final de la lista de preguntas de marque con x.
void insertarPreguntasX()
{
    //se crea un nodo nuevo con la información de la pregunta por crear
    struct MarqX* nn;
    nn = new struct MarqX; 
    string pre;
    string res;
    string val;
    bool mas = true;
    string otra = "";

    //se piden los datos al usuario
    cout << "Escriba la pregunta." << endl;
    getline(cin,pre);
    for (int x = 0; mas != false; x++){
        cout << "Escriba una opción de respuesta para la pregunta." << endl;
        getline(cin,res);
        nn->opciones[x] = res;
        cout << "Desea agregar otra opción de respuesta? Y/N" << endl;
        getline(cin,otra);
        if ((otra == "Y") || (otra == "y"))
            mas = true;
        else if ((otra == "N") || (otra == "n"))
            mas = false;    
    }
    cout << "Escriba la opción correcta de la pregunta." << endl;
    getline(cin,res);
    nn->resp = res;
    
    cout << "Escriba el valor de la pregunta." << endl;
    getline(cin,val);
    int valor = atoi(val.c_str());
    
    //se llenan los datos
    nn->pregunta = pre;
    nn->resp = res;
    nn->respEst  = "";
    nn->tipo = "X";
    nn->nomSec = "";
    nn->estado = "Incompleta";
    nn->valor = valor;
    nn->sig = NULL;

    //se enlaza el nuevo nodo al final de la lista
    if (cabezaX == NULL)
        cabezaX = nn;
    else
    {
        nn->sig = cabezaX;
        cabezaX = nn;
    }
}
//\xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//Función que imprime las preguntas de marcar con x creadas en el sistema y su respectiva respuesta correcta.
void imprimirListaPreguntasX()
{
    struct MarqX* temp = cabezaX;

    while (temp != NULL)
    {
        cout << temp->pregunta << endl;
        cout << temp->resp << endl;
        for (int i = 0; i < 5; i++){
            cout << temp->opciones[i] << endl;
        }
        temp = temp->sig;
    }
}


int main() 
{
    //insertarExamenes();
    //imprimirListaExamenes();
    //insertarPreguntasCortas();
    //responderRC(cabezaRC);
    //imprimirListaPreguntasRC();
    insertarPreguntasX();
    imprimirListaPreguntasX();
    return 0;
}