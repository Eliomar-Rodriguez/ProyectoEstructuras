#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>
#include <sstream>
#include<conio.h>
#include<windows.h>

int cantExams = 1,cantSec =0,x = 1;
struct MarqX* insertarPreguntasX(int numP);
struct Secciones*insertarSecciones();
void menu();
/* DECLARACION DE VARIABLES
     * numPreg  ->  numero de pregunta
     * pregunta ->  la pregunta que se ingresa
     * resp     ->  respuesta correcta de la pregunta
     * respEst  ->  respuesta ingresada por el estudiante
     * nomSec   ->  nombre de la seccion ( geografia, historia, geometria, numeros reales )
     * valor    ->  cantidad de puntos que va a valer esa pregunta
     * estado   ->  estado de la pregunta (correcta, incorrecta, incompleta)
     * porcentaje -> porcentaje de acierto con la respuesta correcta
     */
using namespace std;

struct Examen
{
    string nombre,profe;
    int total_puntos,correctas,malas,nota,numExam,totSec;
    struct Secciones* listaSecciones;
    struct Examen * sig;
}*cabezaExamen;

// preguntas de marque con x
struct MarqX
{

    string nomSec,estado,pregunta,resp,respEst;
    string opciones[7];
    int valor,numPreg = 0;
    struct MarqX* sig;
    struct MarqX* ant;

}*cabezaX;

//preguntas de respuesta breve
struct RespCort
{
    string resp,respEst,nomSec,pregunta,estado;
    int valor,numPreg = 0;
    float porcentaje;
    struct RespCort* sig;
    struct RespCort* ant;

}*cabezaRC;

//secciones
struct Secciones
{
    string nombre = "";
    int numSec =0,cantPregX=0,cantPregC=0;  ///cantPregX y cantPregC se utilizan como un tipo de lenght de cada lista de preguntas
    struct RespCort* preguntasCortas = NULL;
    struct MarqX* preguntasX = NULL;
    struct Secciones* sig;
}*cabezaSec;

// Función que inserta nuevos examenes al final de la lista de examenes
struct Examen*insertarExamenes()
{
    //se crea un nodo nuevo con la información del examen por crear

    struct Examen* nn;
    struct Secciones* sect;
    sect = new struct Secciones;
    nn = new struct Examen;
    string nom,pro,nomb;  // nombre del examen, profesor
  // nombre del examen, profesor
    char otra;
    bool mas = true;
    nn->totSec =0;
    int ss = 0;
    //se piden los datos al usuario
    cout << "Digite el nombre del Examen" << endl;
    getline(cin,nom);
    cout << "Digite el nombre del profe" << endl;
    getline(cin,pro);

    while (mas == true){
            cout << "Desea ingresar una seccion? Y/N" << endl;
            otra = getche();
            cout << "\n";
            if ((otra == 'Y') || (otra == 'y')){
                nn->totSec++; /// total de secciones
                sect = insertarSecciones();
                if (nn->listaSecciones == NULL){
                    nn->listaSecciones = sect;
                    cabezaSec = sect;}
                else{
                    cabezaSec->sig = sect; // ->listaSecciones;
                    sect->sig = NULL;
                    cabezaSec = sect;
                    }
                }
            else if ((otra == 'N') || (otra == 'n'))
                break;
            else
            {
                cout<<"\n\nDebe de ingresar una de las opciones indicadas. El exmamen no se guardo, intentalo de nuevo.\n"<<endl;
                Sleep(2000);
                insertarExamenes();
            }
        }

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
void imprimirListaExamenes()    /// lo mas seguro es que se elimine
{
    struct Examen* temp = cabezaExamen;// se crea un temporal local para no modificar los datos originales
    while (temp != NULL)
    {
        cout << temp->numExam << ") " << temp->nombre << endl; //se imprime el nombre de los examenes en el sistema
        while(temp->listaSecciones != NULL){//SE CAE PORQUE SE DESBORDA LA LISTA DE PREGUNTASCORTAS...
            if (temp->listaSecciones->preguntasX != NULL){
            cout << temp->listaSecciones->numSec <<") "<< temp->listaSecciones->nombre << endl;
            cout << temp->listaSecciones->preguntasX->numPreg <<") "<< temp->listaSecciones->preguntasX->pregunta << endl;
            temp->listaSecciones->preguntasX = temp->listaSecciones->preguntasX->sig;}
            else break;
            }
        temp = temp->sig;
    }
}

// Función que inserta nuevas preguntas de respuesta corta al final de la lista de preguntas de respuesta corta
struct RespCort* insertarpreguntasCortas(int numP)
{
    cout<<"=================================================================\n=\t    Insercion de preguntas de Respuesta Breve \t\t=\n=================================================================\n";
    //se crea un nodo nuevo con la información de la pregunta por crear
    struct RespCort* nn;
    //struct RespCort* act;
    struct RespCort* ant;
    //act = cabezaRC;
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
    int valor = atoi(val.c_str());

    //se llenan los datos
    nn->pregunta = pre;
    nn->resp = res;
    nn->respEst  = "";
    nn->nomSec = "";
    nn->estado = "incompleta";
    nn->valor = valor;
    nn->porcentaje = 0;
    nn->numPreg = numP;
    nn->sig = NULL;
    nn->ant = NULL;
    return nn;
}
//Funcion que crea secciones en un examen

struct Secciones*insertarSecciones()
{
    cout<<"=================================================================\n=\t\t\tInsercion de Secciones \t\t\t=\n=================================================================\n";
    //se crea un nodo nuevo con la información del examen por crear
    struct Secciones* nn;
    struct RespCort* cort;
    struct MarqX* equis;
    //struct Examen *tempExam = cabezaExamen;
    nn = new struct Secciones;
    cort = new struct RespCort;
    equis = new struct MarqX;
    bool mas = true;
    char otra,tipo;

    string nom;  // nombre del examen
    int ex = 0,rc = 0,pregX=1,pregC=1;
    nn->numSec = cantSec+1;
    //se piden los datos al usuario
    cout << "Digite el nombre de la Seccion" << endl;
    getline(cin,nom);
        //se llenan los datos
    nn->nombre = nom;
    nn->sig = NULL;
    cout << "Que tipo de seccion desea agregar?\n1) Seleccion Unica\n2) Respuesta Corta" << endl;
    tipo = getche();
    cout << "\n";
    if (tipo == '1'){
        while (mas == true){
            cout << "Desea ingresar una pregunta? Y/N" << endl;
            otra = getche();
            cout << "\n";
            if ((otra == 'Y') || (otra == 'y')){
                nn->cantPregX++;
                equis = insertarPreguntasX(pregX);
                if (nn->preguntasX == NULL){
                    nn->preguntasX = equis;
                    cabezaX = equis;}
                else{
                    cabezaX->sig = equis; // ->listaSecciones;
                    equis->sig = NULL;
                    equis->ant = cabezaX;
                    cabezaX = equis;
                }
                pregX++;
            }
            else if ((otra == 'N') || (otra == 'n'))
                break;
            else
            {
                cout<<"\n\nDebe de ingresar una de las opciones indicadas. La seccion no se guardo, intentalo de nuevo.\n"<<endl;
                Sleep(2000);
                insertarSecciones();
            }
        }
    }
    else if (tipo == '2'){
        while (mas == true){
            cout << "Desea ingresar una pregunta? Y/N" << endl;
            otra = getche();
            cout << "\n";
            if ((otra == 'Y') || (otra == 'y')){
                nn->cantPregC++;
                cort = insertarpreguntasCortas(pregC);

                if (nn->preguntasCortas == NULL){
                    nn->preguntasCortas = cort;
                    cabezaRC = cort;}
                else{
                    cabezaRC->sig = cort; // ->listaSecciones;
                    cort->sig = NULL;
                    cort->ant = cabezaRC;
                    cabezaRC = cort;
                    }
                pregC++;
                }
            else if ((otra == 'N') || (otra == 'n'))
                break;
            else
                {
                cout<<"\n\nDebe de ingresar una de las opciones indicadas. La seccion no se guardo, intentalo de nuevo.\n"<<endl;
                Sleep(2000);
                insertarSecciones();
                }
            }
    }
    else
        {
        cout<<"\n\nDebe de ingresar una de las opciones indicadas. La seccion no se guardo, intentalo de nuevo.\n"<<endl;
        Sleep(2000);
        insertarSecciones();
        }

    cantSec++;
    return nn;
    ///comentario de insertar ordenado
    /*///inseetar ordenado
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
        nn->sig->ant = nn;*/
}

//Función que imprime las preguntas de respuesta corta creadas en el sistema y su respectiva respuesta correcta.
void imprimirSecciones()    /// lo mas seguro es que se elimine
{
    struct Secciones* temp = cabezaSec;
    //int i = 0;

    while (temp != NULL)
    {
        cout <<temp->numSec << endl;
        /* PUEDE SER UTIL
        while (temp->preguntasX[i]->sig != NULL){
            //cout << temp->preguntasCortas[i]->pregunta << endl;
            cout << temp->preguntasX[i]->pregunta << endl;
            i++;
        }*/
        temp = temp->sig;
    }
}

//Función que imprime las preguntas de respuesta corta creadas en el sistema y su respectiva respuesta correcta.
void imprimirListaPreguntasRC() /// no se ocupara creo
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

/// Función que inserta nuevas preguntas de marcar con x al final de la lista de preguntas de marque con x.
struct MarqX* insertarPreguntasX(int numP)
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
            Sleep(1000);
            return insertarPreguntasX(numP);
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
    nn->nomSec = "";
    nn->numPreg=numP;
    nn->estado = "incompleta";
    nn->valor = valor;
    nn->sig = NULL;
    nn->ant = NULL;

    x ++;

    return nn;
}


/// imprimir la lista de preguntas de marque con x
void imprimirListaPreguntasX()  /// lo mas seguro es que se elimine
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

/// responder preguntas de marque con x
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



/// editar preguntas de marque con x
void editPregSelecUnic()//falta editar
{
    struct MarqX* temp = cabezaX;
}

/// editar preguntas de respuesta corta
void editPregRespCort() //falta editar
{
    struct Examen* tempExam = cabezaExamen;
    int opExam,opSecc,delPreg;
    struct RespCort* temp= cabezaRC;
    int numPreg = 1,y=0,x=0,z=0,h=0;

    while(tempExam!=NULL)
    {
        if (tempExam->numExam != 0)//validacion para que no imprima puros 0)
            cout<< tempExam->numExam << ") "<< tempExam->nombre <<endl;
        tempExam=tempExam->sig;
    }
    cout<<"Seleccione el examen en cual desea eliminar preguntas."<<endl;
    cin>>opExam;
    tempExam = cabezaExamen;

    while((tempExam!=NULL) && (tempExam->numExam!= opExam))
    {
        tempExam=tempExam->sig;
    }
    if ((tempExam==NULL)||(tempExam->numExam!= opExam))
    {
        cout<<"La opcion ingresada no se encuentra dentro de las opciones disponibles, intentalo de nuevo."<<endl;
        editPregRespCort();
    }
    else if ((tempExam!=NULL)&&(tempExam->numExam == opExam))  // encuentra el examen y procede a mostrar la lista de secciones que tiene ese examen
    {
            while(y < tempExam->totSec){
                if ((tempExam->listaSecciones->sig!=NULL)&&(tempExam->listaSecciones->sig->numSec != 0)){
                    cout<< tempExam->listaSecciones->numSec<< ") "<< tempExam->listaSecciones->sig->nombre <<endl;
                }
                y++;
            }
        cout<<"Seleccione la seccion en la cual desea eliminar preguntas."<<endl;
        cin>>opSecc;
        while((x < tempExam->totSec)&&(opSecc!=tempExam->listaSecciones->numSec))
        {
            x++;
        }
        if ((x == tempExam->totSec)||(tempExam->listaSecciones->numSec!= opSecc))    // sino encuentra la seccion indicada
        {
            cout<<"La opcion ingresada no se encuentra dentro de las opciones disponibles, intentalo de nuevo."<<endl;
            editPregRespCort();
        }
        else if ((x < tempExam->totSec)&&(opSecc == tempExam->listaSecciones->numSec))  // aqui ya encontro la seccion en la cual quiero eliminar preguntas
        {
            /// se imprimiran todas las preguntas de respuesta corta aqui
            while((tempExam->listaSecciones->preguntasCortas!=NULL)&&(z < tempExam->listaSecciones->cantPregC)) /// buscando preguntas resp cort para mostrarlas
            {
                if ((tempExam->listaSecciones->preguntasCortas!=NULL)&&(tempExam->listaSecciones->preguntasCortas->numPreg != 0))
                    cout << tempExam->listaSecciones->preguntasCortas->numPreg<<") "<<tempExam->listaSecciones->preguntasCortas->pregunta<<" ("<<tempExam->listaSecciones->preguntasCortas->valor<<" pts)"<<endl;
                z++;
            }
            cout<<"Seleccione la pregunta que desea eliminar."<<endl;
            cin>>delPreg;
            while((tempExam->listaSecciones->preguntasCortas != NULL) && (h < tempExam->listaSecciones->cantPregC) && (delPreg != tempExam->listaSecciones->preguntasCortas->numPreg))  // buscando que la resp ingresada sea una de las preguntas
            {
                h++;//quite el -1 al final
            }
            if ((tempExam->listaSecciones->preguntasCortas == NULL) || ((h == tempExam->listaSecciones->cantPregC) && (tempExam->listaSecciones->preguntasCortas->numPreg != delPreg)))    // sino encuentra la pregunta indicada
            {
                cout<<"La opcion ingresada no se encuentra dentro de las opciones disponibles, intentalo de nuevo."<<endl;
                editPregRespCort();
            }
            ///aqui ya encontro la pregunta y hay que eliminarla
            //pregRest = h;//0     //tempExam->listaSecciones[x]->cantPregC - (h+1);
            if ((tempExam->listaSecciones->preguntasCortas != NULL) && (h < tempExam->listaSecciones->cantPregC) && (tempExam->listaSecciones->preguntasCortas->numPreg == delPreg))
            {
                while ((tempExam->listaSecciones->preguntasCortas!=NULL)&&(h < tempExam->listaSecciones->cantPregC)){
                    tempExam->listaSecciones->preguntasCortas=tempExam->listaSecciones->preguntasCortas;    ///eliminando la pregunta de la lista
                    h++;
                }
                tempExam->listaSecciones->preguntasCortas=NULL;
            }
        }
    }

    return;
}



/*
/// editar el nombre las secciones disponibles
void editSecciones()
{
    string name;
    struct Examen* tempExam = cabezaExamen;
    int opExam,opSecc,delPreg;
    struct RespCort* temp= cabezaRC;
    int numPreg = 1,y=0,x=0,z=0,h=0;

    while(tempExam!=NULL)
    {
        if (tempExam->numExam != 0)//validacion para que no imprima puros 0)
            cout<< tempExam->numExam << ") "<< tempExam->nombre <<endl;
        tempExam=tempExam->sig;
    }
    cout<<"Seleccione el examen en cual desea eliminar preguntas."<<endl;
    cin>>opExam;
    tempExam = cabezaExamen;

    while((tempExam!=NULL) && (tempExam->numExam!= opExam))
    {
        tempExam=tempExam->sig;
    }
    if ((tempExam==NULL)||(tempExam->numExam!= opExam))
    {
        cout<<"La opcion ingresada no se encuentra dentro de las opciones disponibles, intentalo de nuevo."<<endl;
        editSecciones();
    }
    else if ((tempExam!=NULL)&&(tempExam->numExam == opExam))  // encuentra el examen y procede a mostrar la lista de secciones que tiene ese examen
    {
            while(y < tempExam->totSec){
                if ((tempExam->listaSecciones!=NULL)&&(tempExam->listaSecciones->numSec != 0)){
                    cout<< tempExam->listaSecciones->numSec<< ") "<< tempExam->listaSecciones->nombre <<endl;
                }
                y++;
            }
        cout<<"Seleccione la seccion en la cual desea eliminar preguntas."<<endl;
        cin>>opSecc;
        while((x < tempExam->totSec)&&(opSecc!=tempExam->listaSecciones->numSec))
        {
            x++;
        }
        if ((x == tempExam->totSec)||(tempExam->listaSeccione->numSec!= opSecc))    // sino encuentra la seccion indicada
        {
            cout<<"La opcion ingresada no se encuentra dentro de las opciones disponibles, intentalo de nuevo."<<endl;
            editSecciones();
        }
        else if ((x < tempExam->totSec)&&(opSecc == tempExam->listaSecciones->numSec))  // aqui ya encontro la seccion en la cual quiero cambiar el nombre
        {
            cout<<"Ingrese el nuevo nombre que le va a asignar a esta seccion."<<endl;
            cin>>name;
            tempExam->listaSecciones->nombre = name;
        }
    }

    return;
}
*/

/// eliminar preguntas de respuesta corta
void delPregRespCort(){
    struct Examen* tempExam = cabezaExamen;
    int opExam,opSecc,delPreg;
    struct RespCort* temp= cabezaRC;
    int numPreg = 1,y=0,x=0,z=0,h=0;

    while(tempExam!=NULL)
    {
        if (tempExam->numExam != 0)//validacion para que no imprima puros 0)
            cout<< tempExam->numExam << ") "<< tempExam->nombre <<endl;
        tempExam=tempExam->sig;
    }
    cout<<"Seleccione el examen en cual desea eliminar preguntas."<<endl;
    cin>>opExam;

    tempExam=cabezaExamen;

    while((tempExam!=NULL) && (tempExam->numExam!= opExam))
    {
        tempExam=tempExam->sig;
    }
    if ((tempExam==NULL)||(tempExam->numExam!= opExam))
    {
        cout<<"La opcion ingresada no se encuentra dentro de las opciones disponibles, intentalo de nuevo."<<endl;
        delPregRespCort();
    }
    else if ((tempExam!=NULL)&&(tempExam->numExam == opExam))  // encuentra el examen y procede a mostrar la lista de secciones que tiene ese examen
    {
        if (tempExam->listaSecciones==NULL){
            cout <<"El examen seleccionado se encuentra vacio, intentalo nuevamente."<<endl;
            delPregRespCort();
        }
        while(tempExam->listaSecciones!=NULL){
            if ((tempExam->listaSecciones!=NULL)&&(tempExam->listaSecciones->numSec != 0)){
                cout<< tempExam->listaSecciones->numSec<< ") "<< tempExam->listaSecciones->nombre <<endl;
            }
            tempExam->listaSecciones = tempExam->listaSecciones->sig;
            y++;
        }
        cout<<"imprime las secciones"<<endl;

        cout<<"Seleccione la seccion en la cual desea eliminar preguntas."<<endl;
        cin>>opSecc;
        while((x < tempExam->totSec)&&(opSecc!=tempExam->listaSecciones->numSec))
        {
            tempExam->listaSecciones = tempExam->listaSecciones->sig;
            x++;
        }
        if ((x == tempExam->totSec)||(tempExam->listaSecciones->numSec!= opSecc))    // sino encuentra la seccion indicada
        {
            cout<<"La opcion ingresada no se encuentra dentro de las opciones disponibles, intentalo de nuevo."<<endl;
            delPregRespCort();
        }
        else if ((x < tempExam->totSec)&&(opSecc == tempExam->listaSecciones->numSec))  // aqui ya encontro la seccion en la cual quiero eliminar preguntas
        {
            /// se imprimiran todas las preguntas de respuesta corta aqui
            while((tempExam->listaSecciones->preguntasCortas!=NULL)&&(z < tempExam->listaSecciones->cantPregC)) /// buscando preguntas resp cort para mostrarlas
            {
                if ((tempExam->listaSecciones->preguntasCortas!=NULL)&&(tempExam->listaSecciones->preguntasCortas->numPreg != 0))

                    cout << tempExam->listaSecciones->preguntasCortas->numPreg<<") "<<tempExam->listaSecciones->preguntasCortas->pregunta<<" ("<<tempExam->listaSecciones->preguntasCortas->valor<<" pts)"<<endl;

                tempExam->listaSecciones->preguntasCortas = tempExam->listaSecciones->preguntasCortas->sig;
                z++;
            }
            /*
            cout<<"Seleccione la pregunta que desea eliminar."<<endl;
            cin>>delPreg;
            while((tempExam->listaSecciones[x]->preguntasCortas[h] != NULL) && (h < tempExam->listaSecciones[x]->cantPregC) && (delPreg != tempExam->listaSecciones[x]->preguntasCortas[h]->numPreg))  // buscando que la resp ingresada sea una de las preguntas
            {
                h++;//quite el -1 al final
            }
            if ((tempExam->listaSecciones[x]->preguntasCortas[h] == NULL) || ((h == tempExam->listaSecciones[x]->cantPregC) && (tempExam->listaSecciones[x]->preguntasCortas[h]->numPreg != delPreg)))    // sino encuentra la pregunta indicada
            {
                cout<<"La opcion ingresada no se encuentra dentro de las opciones disponibles, intentalo de nuevo."<<endl;
                delPregRespCort();
            }
            ///aqui ya encontro la pregunta y hay que eliminarla
            //pregRest = h;//0     //tempExam->listaSecciones[x]->cantPregC - (h+1);
            if ((tempExam->listaSecciones[x]->preguntasCortas[h] != NULL) && (h < tempExam->listaSecciones[x]->cantPregC) && (tempExam->listaSecciones[x]->preguntasCortas[h]->numPreg == delPreg))
            {
                while ((tempExam->listaSecciones[x]->preguntasCortas[h+1]!=NULL)&&(h < tempExam->listaSecciones[x]->cantPregC)){
                    tempExam->listaSecciones[x]->preguntasCortas[h]=tempExam->listaSecciones[x]->preguntasCortas[h+1];    ///eliminando la pregunta de la lista
                    h++;
                }
                tempExam->listaSecciones[x]->preguntasCortas[h]=NULL;
            }*/
        }
    }

    return;
}



/// eliminar preguntas de marque con x


bool buscarSec(int n){
    struct Examen *tempExam = cabezaExamen;
    while ((tempExam->listaSecciones != NULL)&&(tempExam->listaSecciones->numSec != NULL))
    {
        tempExam->listaSecciones = tempExam->listaSecciones->sig;
    }
    if ((tempExam->listaSecciones!=NULL)&&(tempExam->listaSecciones->numSec == n))
        return true;
    else if ((tempExam->listaSecciones == NULL)&&(tempExam->listaSecciones->numSec != n))
        return false;
}

/// eliminar preguntas de marque con x
struct Examen *delPregMarqX()
{
    struct Examen* tempExam = cabezaExamen;
    struct Examen *auxiliar = cabezaExamen;
    struct Secciones *auxiliar2 = cabezaSec;
    struct Secciones *auxiliar3 = cabezaSec;
    struct MarqX *anterior = cabezaX;
    struct MarqX * pregDel;
    int opExam,delPreg,opSec;  // almacenara la pregunta a eliminar
    int numPreg=1,y=0,x=0,z=0,h=0;  //numero de pregunta, variables para las posiciones
    string opSec2,delPreg2;

    while(tempExam!=NULL)
    {
        if (tempExam->numExam != 0)//validacion para que no imprima puros 0)
            cout<< tempExam->numExam << ") "<< tempExam->nombre <<endl;
        tempExam=tempExam->sig;
    }
    cout<<"Seleccione el examen en cual desea eliminar preguntas."<<endl;
    cin>>opExam;

    while(auxiliar!=NULL)
    {
        if (auxiliar->numExam == opExam)  // encuentra el examen y procede a mostrar la lista de secciones que tiene ese examen
        {
            if (auxiliar->listaSecciones == NULL)
            {
                cout<<"Este examen esta vacio por lo que no posee secciones."<<endl;
                menu();
            }
            while (y < auxiliar->totSec){
                if ((auxiliar->listaSecciones!=NULL)&&(auxiliar->listaSecciones->numSec != 0)){
                    cout<< auxiliar->listaSecciones->numSec<< ") "<< auxiliar->listaSecciones->nombre <<endl;
                }
                auxiliar->listaSecciones= auxiliar->listaSecciones->sig;
                y++;
            }
            cout << "Seleccione la seccion en la cual desea eliminar preguntas."<<endl;
            cin >> opSec2;
            opSec = atoi(opSec2.c_str());
            while (auxiliar2 != NULL)
            {
                if (auxiliar2->numSec == opSec)  // aqui ya encontro la seccion en la cual quiero eliminar preguntas
                {
                    while(z < auxiliar2->cantPregX){
                        if ((auxiliar2->preguntasX != NULL)&&(auxiliar2->preguntasX->numPreg != 0)){
                            cout<< auxiliar2->preguntasX->numPreg<< ") "<< auxiliar2->preguntasX->pregunta <<" ("<< auxiliar2->preguntasX->valor<<" pts)"<<endl;
                            }
                        auxiliar2->preguntasX = auxiliar2->preguntasX->sig;
                        z++;
                        }
                    cout << "Digite la pregunta por eliminar" << endl;
                    cin >> delPreg2;
                    delPreg = atoi(delPreg2.c_str());
                   // auxiliar2 = cabezaSec;
                    cout << "ACM1PT" << endl;
                    while (auxiliar->listaSecciones->preguntasX != NULL)
                    {
                        cout << "ACM1PT1" << endl;
                        if (auxiliar->listaSecciones->preguntasX->numPreg == delPreg)
                        {
                            cout << "ACM1PT2" << endl;
                            if (auxiliar->listaSecciones->preguntasX->ant == NULL){ // ojo con el sig/ant...
                                cout << "ACM1PT3" << endl;
                                pregDel = auxiliar->listaSecciones->preguntasX;
                                //cabezaX = auxiliar2->preguntasX->sig;
                                //anterior->sig->ant = NULL;
                                free(pregDel);
                            }
                            /*else if (//caso 2, en el medio)
                            {

                            }*/
                            else // caso 3, en el final...
                                {

                                }
                        }

                        else
                            {
                            cout<<"La opcion ingresada no se encuentra dentro de las opciones disponibles, intentalo de nuevo."<<endl;
                            delPregMarqX();
                            }
                        auxiliar->listaSecciones->preguntasX = auxiliar->listaSecciones->preguntasX->sig;
                    }
                }
                else
                {
                    cout << "La vaina no se encuentra en el systmem..." << endl;
                    break;
                }
                auxiliar2 = auxiliar2->sig;
            }
        }
        auxiliar = auxiliar->sig;
    }
    cout << "La huevada ha sido removida..." << endl;
}


/// menu principal
void menu()
{
        //system("cls");
        char op,opEdit,opDel,opExam;
        cout<<"=================================================================\n=\t\t\t  Menu principal\t\t\t=\n=================================================================\n";
        cout<<"=\t[1]. Crear Examen / Secciones\t\t\t\t=\n=\t[2]. Modificar Preguntas / Secciones\t\t\t=\n=\t[3]. Borrar Preguntas / Secciones\t\t\t=\n=\t[4]. Realizar Examen      \t\t\t\t=\n=\t[5]. Salir\t\t\t\t\t\t=\n=\t\t\t\t\t\t\t\t\n=\t";
        op = getche(); //obtener opcion
        cout <<endl;
        switch(op){
            case '1':
                {
                    //cout<<"Mostrar lista de nombres de Examenes y secciones disponibles";
                    /*opExam = getche();
                    switch(opExam)
                    {
                    case '1':
                        {
                            break;
                        }
                    }
                    break;*/

                    insertarExamenes();
                    break;
                }
            case '2':
                {
                    system("cls");
                    cout<<"=================================================================\n=\t\t\t  Menu de edicion\t\t\t=\n=================================================================\n";
                    cout<<"=\t[1]. Modificar el nombre de secciones\t=\n=\t[2]. Modificar preguntas de Seleccion Unica\t\t=\n=\t[3]. Modificar preguntas de Respuesta Breve\t\t=\n=\t[4]. Menu principal\t\t\t\t\t=\n=\t\t\t\t\t\t\t\t\n=\t";
                    opEdit = getche();
                    cout <<endl;
                    switch(opEdit)
                    {
                        case '1':
                            {
                                //editSecciones();
                                break;
                            }
                        case '2':
                            {
                                //editPregSelecUnic();
                                break;
                            }
                        case '3':
                            {
                                //editPregRespCort();
                                break;
                            }
                        case '4':
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
                    cout<<"=\t[1]. Eliminar secciones\t\t=\n=\t[2]. Eliminar preguntas de Seleccion Unica\t\t=\n=\t[3]. Eliminar preguntas de Respuesta Breve\t\t=\n=\t[4]. Menu principal\t\t\t\t\t=\n=\t\t\t\t\t\t\t\t\n=\t";
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
                                //delPregMarqX();
                                break;
                            }
                        case '3':
                            {
                                //delPregRespCort();
                                break;
                            }
                        case '4':
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
                    cout<<"Gracias por usar este sistema.";
                    exit(1);
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

/// insertar examen de manera manual (solo se ejecuta una vez)
void insertExamenManual(string pro,string nom, string pre,string res,string nomSec,int valor)
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
    //string pro,string nom, string pre,string res,string nomSec,int valor)
    //insertExamenManual("Gretel Rodriguez","Cuantos continentes hay en la actualidad?",);
    //menu();
    //insertarSecciones();
    insertarExamenes();
    //insertarExamenes();
    //imprimirSecciones();

    //delPregMarqX();

    //imprimirListaExamenes();
    //delPregRespCort();
    //delPregRespCort();
    //delPregRespCort();
    //delPregRespCort();
    //delPregMarqX();

    delPregMarqX();
    imprimirListaExamenes();
    //delPregMarqX();
    //delPregRespCort();
    //insertarpreguntasX();
    //insertarpreguntasCortas();
    /*insertarpreguntasCortas();
    insertarpreguntasCortas();
    insertarpreguntasCortas();
    imprimirListaPreguntasRC();*/

    return 0;
}
