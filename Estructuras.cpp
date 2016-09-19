#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>
#include <sstream>
#include<conio.h>
#include<windows.h>

int preg = 1;
int cantExams = 1;
int x = 1;
struct MarqX* insertarPreguntasX();
void menu();
/* DECLARACION DE VARIABLES
     * numPreg  ->  numero de pregunta
     * pregunta ->  la pregunta en si
     * resp     ->  respuesta correcta de la pregunta
     * respEst  ->  respuesta ingresada por el estudiante
     * tipo     ->  tipo de pregunta  ( marque x  ,  respuesta breve )
     * nomSec   ->  nombre de la seccion ( geografia, historia, geometria, numeros reales )
     * valor    ->  cantidad de puntos que va a valer esa pregunta
     * estado   ->  estado de la pregunta (correcta, incorrecta, incompleta)
     * porcentaje -> porcentaje de acierto con la respuesta correcta
     */
using namespace std;

struct Examen
{
    string nombre,profe;
    int total_puntos,correctas,malas,nota,numExam;
    // poner las referencias hacia las listas de los dos tipos de preguntas
    struct Secciones*listaSecciones[];
    struct Examen * sig;
}*cabezaExamen;

// preguntas de marque con x
struct MarqX
{
    string numPreg,tipo,nomSec,estado,pregunta,resp,respEst;
    string opciones[5];
    int valor;
    struct MarqX* sig;
    struct MarqX* ant;

}*cabezaX;

//preguntas de respuesta breve
struct RespCort
{
    string numPreg,resp,respEst,tipo,nomSec,pregunta,estado;
    int valor;
    float porcentaje;
    struct RespCort* sig;
    struct RespCort* ant;

}*cabezaRC;

//secciones
struct Secciones
{
    string nombre = "";
    struct RespCort* preguntascortas[10];
    struct MarqX* preguntasx[10];
    struct Secciones* sig;
}*cabezaSec;


struct Examen listaExamenes[10];
// Función que inserta nuevos examenes al final de la lista de examenes
void insertarExamenes()
{
    //se crea un nodo nuevo con la información del examen por crear
    struct Examen* nn;
    nn = new struct Examen;
    string nom,pro;  // nombre del examen, profesor

    //se piden los datos al usuario
    cout << "Digite el nombre del Examen" << endl;
    getline(cin,nom);
    cout << "Digite el nombre del profe" << endl;
    getline(cin,pro);

    //se llenan los datos
    nn->numExam = cantExams;
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
    cantExams ++ ;
}

//Función que imprime los examenes creados en el sistema
void imprimirListaExamenes()
{
    struct Examen* temp = cabezaExamen; // se crea un temporal local para no modificar los datos originales
    while (temp != NULL)
    {
        cout <<temp->numExam << ") " << temp->nombre << endl; //se imprime el nombre de los examenes en el sistema
        temp = temp->sig;
    }
}

// Función que inserta nuevas preguntas de respuesta corta al final de la lista de preguntas de respuesta corta
struct RespCort* insertarPreguntasCortas()
{
    cout<<"=================================================================\n=\t    Insercion de preguntas de Respuesta Breve \t\t=\n=================================================================\n";
    //se crea un nodo nuevo con la información de la pregunta por crear
    struct RespCort* nn;
    struct RespCort* act;
    struct RespCort* ant;
    act = cabezaRC;
    ant = NULL;
    nn = new struct RespCort;
    string pre; // pregunta, respuesta, valor de respuesta
    string res;
    string val;
    //se piden los datos al usuario
    cout << "Escriba la pregunta que desea ingresar." << endl;
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
    nn->estado = "incompleta";
    nn->valor = valor;
    nn->porcentaje = 0;
    nn->numPreg = preg;
    nn->sig = NULL;
    nn->ant = NULL;

    //se enlaza el nuevo nodo al final de la lista
     if (!cabezaRC || cabezaRC->valor > nn->valor){
     nn->sig = cabezaRC;
     nn->ant = NULL;//era 0
     if (cabezaRC)
        cabezaRC->ant = nn;
        cabezaRC = nn;
        }
     else {
     RespCort *temp = cabezaRC;

     while (temp->sig && temp->sig->valor <= nn->valor)
        temp = temp->sig;

     nn->sig= temp->sig;
     nn->ant = temp;
     temp->sig = nn;
     if (nn->sig)
        nn->sig->ant = nn;
  }
    preg ++;
}
//Funcion que crea secciones en un examen

struct Secciones*insertarSecciones()
{
    cout<<"=================================================================\n=\t\t\tInsercion de Secciones \t\t\t=\n=================================================================\n";
    //se crea un nodo nuevo con la información del examen por crear
    struct Secciones* nn;
    struct RespCort* cort;
    struct MarqX* equis;
    nn = new struct Secciones;
    cort = new struct RespCort;
    equis = new struct MarqX;
    bool mas = true;

    char otra,tipo;

    string nom;  // nombre del examen

    //se piden los datos al usuario
    cout << "Digite el nombre de la Seccion" << endl;
    getline(cin,nom);
    while (mas == true){
        cout << "Desea ingresar una pregunta? Y/N" << endl;
        otra = getche();
        if ((otra == 'Y') || (otra == 'y')){
            mas = true;
            continue;}
        else if ((otra == 'N') || (otra == 'n'))   // \falta_validar_ya_que_si_ingresa_una_letra
            break;
            //mas = false;                          //   \diferente_a_esas_va_a_seguir_y_no_va_a_hacer_lo_que_se_necesita
        else
        {
            cout<<"\n\nDebe de ingresar una de las opciones indicadas. La seccion no se guardo, intentalo de nuevo./n"<<endl;
            Sleep(2000);
            insertarSecciones();
        }
        cout << "Qué tipo de pregunta desea agregar?/n1) Marque con X/n2) Respuesta Corta" << endl;
        tipo = getche();
        if (tipo == '1'){
            mas = true;
            continue;}
        else if ((otra == 'N') || (otra == 'n'))   // \falta_validar_ya_que_si_ingresa_una_letra
            break;
            //mas = false;                          //   \diferente_a_esas_va_a_seguir_y_no_va_a_hacer_lo_que_se_necesita
        else
        {
            cout<<"\n\nDebe de ingresar una de las opciones indicadas. La seccion no se guardo, intentalo de nuevo./n"<<endl;
            Sleep(2000);
            insertarSecciones();
        }
        cort = insertarPreguntasCortas();
        equis = insertarPreguntasX();
    }
    //se llenan los datos
    nn->nombre = nom;
    nn->preguntascortas[0] = cort;
    nn->sig = NULL;

    //se enlaza el nuevo nodo al final de la lista
    if (cabezaSec == NULL)
        cabezaSec = nn;
    else
    {
        nn->sig = cabezaSec;
        cabezaSec = nn;
    }
}

//Función que imprime las preguntas de respuesta corta creadas en el sistema y su respectiva respuesta correcta.
void imprimirSecciones()
{
    struct Secciones* temp = cabezaSec;

    while (temp != NULL)
    {
        cout << temp->nombre << endl;
        //for (int i = 0; i < 5; i++){
        cout << temp->preguntascortas[0]->pregunta << endl;
        //}
        temp = temp->sig;
    }
}

//Función que imprime las preguntas de respuesta corta creadas en el sistema y su respectiva respuesta correcta.
void imprimirListaPreguntasRC()
{
    struct RespCort* temp = cabezaRC;

    while (temp != NULL)
    {
        //cout << temp->pregunta << endl;
        //cout << temp->resp << endl;
        cout << temp->valor << endl;
        temp = temp->sig;
    }
}

//Funciòn que sirve para responder preguntas de Respuesta Corta
void responderRC(RespCort*cabezaRC)
{
    string respuesta;
    int contador = 0;
    double coin = (cabezaRC->resp.length()*60)/100; // porcentaje mínimo de semejanza en la respuesta para acertar o fallar la pregunta.

    if (cabezaRC != NULL)
        {
            cout << cabezaRC->pregunta << "(" << cabezaRC->valor << "pts)" << endl;
            cout << "Digite su respuesta plz..." << endl;   //se introduce la respuesta a la pregunta
            getline(cin,respuesta);

            for(int i = 0; respuesta[i]; i++)
                respuesta[i] = tolower(respuesta[i]); //se transforma la respuesta a caracteres en minuscula.

            cabezaRC->respEst = respuesta;  //se guarda la respuesta en el nodo correspondiente

            for (int x = 0; cabezaRC->resp[x] != '\0' ;x++) //ciclo que revisa caracter por caracter para validar la respuesta.
                if (cabezaRC->resp[x] == respuesta[x])
                    contador++;     //se lleva un contador con la cantidad de caracteres similares
            if (contador > coin)
                {
                cabezaRC->estado = "correcta";  //se guarda la pregunta como "correcta" si la cantidad de coincidencias es mayor al 60% de la pregunta.
                cabezaRC->porcentaje = (contador*100)/cabezaRC->resp.length();
                } //se guarda el porcentaje de acierto para desplegarlo más adelante.
            else
            {
                cabezaRC->estado = "incorrecta";    //se guarda la pregunta como "incorrecta" si la cantidad de coincidencias es menor al 60% de la pregunta.
                cabezaRC->porcentaje = (contador*100)/cabezaRC->resp.length();//se guarda el porcentaje de acierto para desplegarlo más adelante.
            }
        }

        cout << "Respuesta Introducida = "+ cabezaRC->respEst <<endl;
        cout << "Respuesta Correcta = " + cabezaRC->resp <<endl;
        cout << "Estado de la pregunta = "+ cabezaRC->estado << endl;
        cout << "Porcentaje de igualdad de la respuesta = ";
        cout << cabezaRC->porcentaje;
        cout << "%" << endl;
}

// Función que inserta nuevas preguntas de marcar con x al final de la lista de preguntas de marque con x.
struct MarqX* insertarPreguntasX()
{
    system("cls");
    cout<<"=================================================================\n=\t    Insercion de preguntas de Seleccion Unica\t\t=\n=================================================================\n";

    //se crea un nodo nuevo con la información de la pregunta por crear
    struct MarqX* nn;
    nn = new struct MarqX;
    string res,val,pre;
    char otra;
    bool mas = true;

    //se piden los datos al usuario
    cout << "Escriba la pregunta que desea ingresar." << endl;
    cout<<"\t";
    getline(cin,pre);
    for (int x = 0; mas != false; x++){
        cout << "\nEscriba una OPCION de respuesta para la pregunta (una debe ser la correcta)." << endl;
        cout<<"\t";
        getline(cin,res);
        nn->opciones[x] = res;
        cout << "\nDesea agregar mas opciones de respuesta? Y/N" << endl;
        otra=getche();
        if ((otra == 'Y') || (otra == 'y'))
            mas = true;
        else if ((otra == 'N') || (otra == 'n'))   // \falta_validar_ya_que_si_ingresa_una_letra
            break;
            //mas = false;                          //   \diferente_a_esas_va_a_seguir_y_no_va_a_hacer_lo_que_se_necesita
        else
        {
            cout<<"\n\nDebe de ingresar una de las opciones indicadas. La pregunta ingresada no se guardo, intentalo de nuevo./n"<<endl;
            Sleep(2000);
            insertarPreguntasX();
        }
    }
    cout << "\nEscriba la opcion correcta de la pregunta." << endl;
    getline(cin,res);
    nn->resp = res;

    cout << "\nEscriba el valor de la pregunta." << endl;
    getline(cin,val);
    int valor = atoi(val.c_str());

    //se llenan los datos
    nn->pregunta = pre;
    nn->resp = res;
    nn->respEst  = "";
    nn->tipo = "X";
    nn->nomSec = "";
    nn->estado = "incompleta";
    nn->valor = valor;
    nn->sig = NULL;
    nn->ant = NULL;

    //se enlaza el nuevo nodo al final de la lista
    if (!cabezaX || cabezaX->valor > nn->valor){
     nn->sig = cabezaX;
     nn->ant = NULL;//era 0
     if (cabezaX)
        cabezaX->ant = nn;
        cabezaX = nn;
        }
     else {
     MarqX *temp = cabezaX;

     while (temp->sig && temp->sig->valor <= nn->valor)
        temp = temp->sig;

     nn->sig= temp->sig;
     nn->ant = temp;
     temp->sig = nn;
     if (nn->sig)
        nn->sig->ant = nn;
  }
    x ++;

    cout<<"Desea ingresar otra pregunta? Y / N"<<endl;
    otra=getche();
    if ((otra == 'Y') || (otra == 'y'))
        insertarPreguntasX();
    else if ((otra == 'N') || (otra == 'n'))   // \falta_validar_ya_que_si_ingresa_una_letra
        menu();
    else
    {
        cout<<"\nDebe de ingresar una de las opciones indicadas. Si desea agregar mas pregutas debera ingresar nuevamente."<<endl;
        Sleep(2000);
        insertarPreguntasX();
    }
}

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

void responderX(MarqX*cabezaX)
{
    string respuesta;

    if (cabezaX != NULL){
        cout << cabezaX->pregunta << "(" << cabezaX->valor << "pts)" << endl;
        for (int x = 0; cabezaX->opciones[x] != "" ;x++){ //ciclo que revisa caracter por caracter para validar la respuesta.
            cout << x+1 << ") " << cabezaX->opciones[x] << endl;
        }
        cout << "Digite su respuesta." << endl;   //se introduce la respuesta a la pregunta
        getline(cin,respuesta);

        cabezaX->respEst = respuesta;  //se guarda la respuesta en el nodo correspondiente

        if (respuesta == cabezaX->resp)
            cabezaX->estado = "correcta";  //se guarda la pregunta como "correcta" si la cantidad de coincidencias es mayor al 60% de la pregunta.
        else

            cabezaX->estado = "incorrecta";    //se guarda la pregunta como "incorrecta" si la cantidad de coincidencias es menor al 60% de la pregunta.

        //Codigo para despues...
        cout << "Respuesta Introducida = "+ cabezaX->respEst <<endl;
        cout << "Respuesta Correcta = " + cabezaX->resp <<endl;
        cout << "Estado de la pregunta = "+ cabezaX->estado << endl;
    }
}
void editSecSelecUnic()// editar nombre de las secciones de seleccion unica marque con x
{
    struct MarqX* temp = cabezaX;
    cout<<"Necesito acceder a nombre para cambiarlo -> geografia biologia o cosas asi"<<endl;
}
void editSecRespCort()// editar nombre de las secciones de respuesta corta
{
    struct RespCort* temp = cabezaRC;
    cout<<"Necesito acceder a nombre para cambiarlo -> geografia biologia o cosas asi"<<endl;
}
void editPregSelecUnic() //editar preguntas de seleccion unica
{
    struct MarqX* temp = cabezaX;
}
void delPregMarqX()
{
    struct MarqX* temp= cabezaX;
    int numPreg = 1;
    int cont=1;
    if (temp == NULL)
        cout<<"No hay preguntas creadas."<<endl;
    else
    {
        while (temp!= NULL)
        {
            cout<<numPreg<<") "<<temp->pregunta<<endl;
            for (int x=0; x<5;x++)
            {
                cout<<"     "<<cont<<") "<<cabezaX->opciones[x]<<endl;
                cont++;
            }
            temp=temp->sig;
            numPreg++;
        }
    }
}
void menu()
{
        system("cls");
        char op,opEdit,opDel,opExam;
        cout<<"=================================================================\n=\t\t\t  Menu principal\t\t\t=\n=================================================================\n";
        cout<<"=\t[1]. Crear Examen / Secciones      \t\t\t\t\t=\n=\t[2]. Modificar Preguntas / Secciones\t\t\t=\n=\t[3]. Borrar Preguntas / Secciones\t\t\t=\n=\t[4]. Realizar Examen      \t\t\t\t=\n=\t[5]. Salir\t\t\t\t\t\t=\n=\t\t\t\t\t\t\t\t\n=\t";
        op = getche(); //obtener opcion
        cout <<endl;
        switch(op){
            case '1':
                {
                    cout<<"Mostrar lista de nombres de Examenes y secciones disponibles";
                    opExam = getche();
                    switch(opExam)
                    {
                    case '1':
                        {
                            break;
                        }
                    }
                    break;
                }
            case '2':
                {
                    system("cls");
                    cout<<"=================================================================\n=\t\t\t  Menu de edicion\t\t\t=\n=================================================================\n";
                    cout<<"=\t[1]. Modificar nombre de secciones de Seleccion Unica\t=\n=\t[2]. Modificar nombre de secciones de Respuesta Corta\t=\n=\t[3]. Modificar preguntas de Seleccion Unica\t\t=\n=\t[4]. Modificar preguntas de Respuesta Breve\t\t=\n=\t[5]. Menu principal\t\t\t\t\t=\n=\t\t\t\t\t\t\t\t\n=\t";
                    opEdit = getche();
                    cout <<endl;
                    switch(opEdit)
                    {
                        case '1':
                            {
                                editSecSelecUnic();
                                break;
                            }
                        case '2':
                            {
                                editSecRespCort();
                                break;
                            }
                        case '3':
                            {
                                editPregSelecUnic();
                                break;
                            }
                        case '4':
                            {
                                cout<<"Editar preg resp cort";
                                break;
                            }
                        case '5':
                            {
                                menu();
                                break;
                            }
                        default:
                            {
                                cout<<"\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n* \t\tLa opcion ingresada no es correcta\t\t* \n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
                                system("pause");
                                menu();
                                break;
                            }
                    }
                    break;
                }
            case '3':
                {
                    system("cls");
                    cout<<"=================================================================\n=\t\t\t  Menu de eliminacion\t\t\t=\n=================================================================\n";
                    cout<<"=\t[1]. Eliminar secciones de Seleccion Unica\t\t=\n=\t[2]. Eliminar secciones de Respuesta Corta\t\t=\n=\t[3]. Eliminar preguntas de Seleccion Unica\t\t=\n=\t[4]. Eliminar preguntas de Respuesta Breve\t\t=\n=\t[5]. Menu principal\t\t\t\t\t=\n=\t\t\t\t\t\t\t\t\n=\t";
                    opDel = getche();
                    cout <<endl;
                    switch(opDel)
                    {
                        case '1':
                            {
                                cout<<"Falta relajado compa...";
                                break;
                            }
                        case '2':
                            {
                                //eliminar
                                break;
                            }
                        case '3':
                            {
                                //eliminar
                                break;
                            }
                        case '4':
                            {
                                //eliminar
                                break;
                            }
                        case '5':
                            {
                                menu();
                                break;
                            }
                        default:
                            {
                                cout<<"\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n* \t\tLa opcion ingresada no es correcta\t\t* \n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
                                system("pause");
                                menu();
                                break;
                            }
                    }
                    break;
                }
            case '4':
                {
                    cout<<"Realizar examen";
                    break;
                }
            case '5':
                {
                    cout<<"Gracias ";
                    exit(0);
                    break;
                }
            default:
                {
                    cout<<"\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n* \t\tLa opcion ingresada no es correcta\t\t* \n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * \n";
                    system("pause");
                    menu();
                    //exit(0);
                    break;
                }
        }
    return;
}


void insertExamenManual(string pro,string nom, string pre,string res,string tipo,string nomSec,int valor)
{
    //esta pendiente.
    struct Examen* nnE;
    nnE = new struct Examen;

    nnE->numExam = cantExams;
    nnE->nombre = nom;
    nnE->profe  = pro;
    nnE->total_puntos = 0;
    nnE->correctas  = 0;
    nnE->malas  = 0;
    nnE->nota  = 0;
    nnE->sig = NULL;

    //se enlaza el nuevo nodo al final de la lista
    if (cabezaExamen == NULL)
        cabezaExamen = nnE;
    else
    {
        nnE->sig = cabezaExamen;
        cabezaExamen = nnE;
    }
    cantExams ++ ;
    struct MarqX* nnX;
    nnX = new struct MarqX;

    nnX->pregunta = pre;
    nnX->resp = res;
    nnX->respEst  = "";
    nnX->tipo = "X";
    nnX->nomSec = "Geografia";
    nnX->estado = "incompleta";
    nnX->valor = valor;
    nnX->sig = NULL;
    nnX->ant = NULL;

    //se enlaza el nuevo nodo al final de la lista
    if (!cabezaX || cabezaX->valor > nnX->valor){
     nnX->sig = cabezaX;
     nnX->ant = NULL;//era 0
     if (cabezaX){
        cabezaX->ant = nnX;
        cabezaX = nnX;}
    }
     else {
         MarqX *temp = cabezaX;

         while (temp->sig && temp->sig->valor <= nnX->valor)
            temp = temp->sig;

         nnX->sig= temp->sig;
         nnX->ant = temp;
         temp->sig = nnX;
         if (nnX->sig)
            nnX->sig->ant = nnX;
    }
}
int main()
{
    //string pro,string nom, string pre,string res,string tipo,string nomSec,int valor)
    //insertExamenManual("Gretel Rodriguez","Cuantos continentes hay en la actualidad?",);
    //insertarSecciones();
    //insertarExamenes();
    //insertarExamenes();
    //Sleep(300);
    //imprimirSecciones();

    insertarPreguntasX();
    //insertarPreguntasCortas();
    /*insertarPreguntasCortas();
    insertarPreguntasCortas();
    insertarPreguntasCortas();
    imprimirListaPreguntasRC();*/



    return 0;
}
