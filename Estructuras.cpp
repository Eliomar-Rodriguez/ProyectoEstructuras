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

    string opciones[10];
    int valor,cantOp=0,numPreg=0;

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

void imprimirRespuestas(Examen*Examen2);
// Función que inserta nuevos examenes al final de la lista de examenes
struct Examen*insertarExamenes()
{
    system("cls");
    cout<<"=================================================================\n=\t\t\tInsercion de examenes\t\t\t=\n=================================================================\n";

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
    cout << "Digite el nombre del Examen\n\t";
    getline(cin,nom);
    cout << "\nDigite el nombre del profe\n\t";
    getline(cin,pro);

    while (mas == true){
            cout << "\nDesea ingresar una seccion? Y/N\n\t";
            otra = getche();
            cout << "\n";
            if ((otra == 'Y') || (otra == 'y')){
                nn->totSec++; /// total de secciones
                cout<<endl;
                sect = insertarSecciones();
                if (nn->listaSecciones == NULL){
                    nn->listaSecciones = sect;
                    cabezaSec = sect;
                    ;}
                else{
                    cabezaSec= sect;
                    sect->sig = NULL;
                    cabezaSec = sect;
                    }
                }
            else if ((otra == 'N') || (otra == 'n'))
                menu();
                //break;
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
    menu();
}


// Función que inserta nuevas preguntas de respuesta corta al final de la lista de preguntas de respuesta corta
struct RespCort* insertarpreguntasCortas(int numP)
{
    system("cls");
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
    cout << "Escriba la pregunta que desea ingresar.\n\t";
    getline(cin,pre);
    cout << "\nEscriba la respuesta de la pregunta.\n\t";
    getline(cin,res);
    for(int i = 0; res[i]; i++)
          res[i] = tolower(res[i]);
    cout << "\nscriba el valor de la pregunta.\n\t";
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
    system("cls");
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
    cout << "Digite el nombre de la Seccion\n\t";
    getline(cin,nom);
        //se llenan los datos
    nn->nombre = nom;
    nn->sig = NULL;
    cout << "\nQue tipo de seccion desea agregar?\n\t1) Seleccion Unica\n\t2) Respuesta Corta\n\t";
    tipo = getche();
    cout << "\n";
    if (tipo == '1'){
        while (mas == true){
            cout << "Desea ingresar una pregunta? Y/N\t" << endl;
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
            else if ((otra == 'N') || (otra == 'n')){
                break;

                }
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


//Funcion que sirve para responder preguntas de Respuesta Corta
void responderRC()
{
    struct Examen * inicio = cabezaExamen;
    struct Examen * Examen2 = inicio;
    string respuesta, exa;
    int contador = 0;
    double coin = (Examen2->listaSecciones->preguntasCortas->resp.length()*60)/100; // porcentaje mÃ­nimo de semejanza en la respuesta para acertar o fallar la pregunta.
    while(Examen2!=NULL)
    {
        if (Examen2->numExam!= 0)//validacion para que no imprima puros 0)
            cout<< Examen2->numExam << ") "<< Examen2->nombre <<endl;
        Examen2 = Examen2->sig;
    }
    cout<<"Seleccione el examen en cual desea responder preguntas."<<endl;
    cin>>exa;
    Examen2 = NULL;
    Examen2 = inicio;
    while (Examen2 != NULL)
    {
        while (Examen2->listaSecciones != NULL)
        {
            if (Examen2->listaSecciones->preguntasCortas != NULL)
            {
                contador = 0;
                cout << Examen2->listaSecciones->preguntasCortas->pregunta << "(" << Examen2->listaSecciones->preguntasCortas->valor << "pts)" << endl;
                cin.ignore();
                cout << "Digite su respuesta plz..." << endl;   //se introduce la respuesta a la pregunta
                cin >> respuesta;

                for(int i = 0; respuesta[i]; i++)
                    respuesta[i] = tolower(respuesta[i]); //se transforma la respuesta a caracteres en minuscula.

                Examen2->listaSecciones->preguntasCortas->respEst = respuesta;  //se guarda la respuesta en el nodo correspondiente

                for (int x = 0; Examen2->listaSecciones->preguntasCortas->resp[x] != '\0' ;x++) //ciclo que revisa caracter por caracter para validar la respuesta.
                    if (Examen2->listaSecciones->preguntasCortas->resp[x] == respuesta[x])
                        contador++;     //se lleva un contador con la cantidad de caracteres similares
                if (contador >= coin)
                    {
                    Examen2->listaSecciones->preguntasCortas->estado = "correcta";  //se guarda la pregunta como "correcta" si la cantidad de coincidencias es mayor al 60% de la pregunta.
                    Examen2->listaSecciones->preguntasCortas->porcentaje = (contador*100)/Examen2->listaSecciones->preguntasCortas->resp.length();
                    Examen2->correctas ++;
                    Examen2->total_puntos += Examen2->listaSecciones->preguntasCortas->valor;
                    } //se guarda el porcentaje de acierto para desplegarlo mÃ¡s adelante.
                else
                {
                    Examen2->listaSecciones->preguntasCortas->estado = "incorrecta";    //se guarda la pregunta como "incorrecta" si la cantidad de coincidencias es menor al 60% de la pregunta.
                    Examen2->listaSecciones->preguntasCortas->porcentaje = (contador*100)/Examen2->listaSecciones->preguntasCortas->resp.length();//se guarda el porcentaje de acierto para desplegarlo mÃ¡s adelante.
                    Examen2->malas ++;
                }
            }

            /*cout << "Respuesta Introducida = "+ Examen2->listaSecciones->preguntasCortas->respEst <<endl;
            cout << "Respuesta Correcta = " + Examen2->listaSecciones->preguntasCortas->resp <<endl;
            cout << "Estado de la pregunta = "+ Examen2->listaSecciones->preguntasCortas->estado << endl;
            cout << "Porcentaje de igualdad de la respuesta = ";
            cout << Examen2->listaSecciones->preguntasCortas->porcentaje;
            cout << "%" << endl;
            cout << "Puntos totales del examen = ";
            cout << Examen2->total_puntos <<endl;*/
                if (Examen2->listaSecciones->preguntasCortas->sig == NULL)
                    break;
                Examen2->listaSecciones->preguntasCortas = Examen2->listaSecciones->preguntasCortas->sig;
        }
        if (Examen2->listaSecciones->sig == NULL)
            break;
        Examen2->listaSecciones= Examen2->listaSecciones->sig;
    }
    imprimirRespuestas(Examen2);
}


//Función que inserta nuevas preguntas de marcar con x al final de la lista de preguntas de marque con x.
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
        nn->cantOp++;
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


//responder preguntas de marque con x
void responderX()
{
    struct Examen * inicio = cabezaExamen;
    struct Examen * Examen2 = inicio;
    struct Secciones * inis = cabezaSec;
    string respuesta, exa;
    while(Examen2!=NULL)
    {
        if (Examen2->numExam!= 0)//validacion para que no imprima puros 0)
            cout<< Examen2->numExam << ") "<< Examen2->nombre <<endl;
        Examen2 = Examen2->sig;
    }
    cout<<"Seleccione el examen en cual desea responder preguntas."<<endl;
    cin>>exa;
    Examen2 = NULL;
    Examen2 = inicio;
    while (Examen2 != NULL){
            while (Examen2->listaSecciones != NULL){
                if (Examen2->listaSecciones->preguntasX != NULL){
                    cout << Examen2->listaSecciones->preguntasX->pregunta << "(" << Examen2->listaSecciones->preguntasX->valor << "pts)" << endl;
                    for (int x = 0; Examen2->listaSecciones->preguntasX->opciones[x] != "" ;x++){ //ciclo que revisa caracter por caracter para validar la respuesta.
                        cout << x+1 << ") " << Examen2->listaSecciones->preguntasX->opciones[x] << endl;
                    }
                    cin.ignore();
                    cout << "Digite su respuesta." << endl;   //se introduce la respuesta a la pregunta
                    cin >> respuesta;

                    Examen2->listaSecciones->preguntasX->respEst = respuesta;  //se guarda la respuesta en el nodo correspondiente

                    if (respuesta == Examen2->listaSecciones->preguntasX->resp){
                        Examen2->listaSecciones->preguntasX->estado = "correcta";  //se guarda la pregunta como "correcta" si la cantidad de coincidencias es mayor al 60% de la pregunta.
                        Examen2->correctas ++;
                        Examen2->total_puntos += Examen2->listaSecciones->preguntasX->valor;}
                    else{
                        Examen2->listaSecciones->preguntasX->estado = "incorrecta";    //se guarda la pregunta como "incorrecta" si la cantidad de coincidencias es menor al 60% de la pregunta.
                        Examen2->malas ++;
                        }
                    /*//Codigo para despues...
                    cout << "Respuesta Introducida = "+ Examen2->listaSecciones->preguntasX->respEst <<endl;
                    cout << "Respuesta Correcta = " + Examen2->listaSecciones->preguntasX->resp <<endl;
                    cout << "Estado de la pregunta = "+ Examen2->listaSecciones->preguntasX->estado << endl;
                    cout << "Puntos totales del examen = ";
                    cout << Examen2->total_puntos <<endl;*/
                }
                if (Examen2->listaSecciones->preguntasX->sig == NULL)
                    break;
                Examen2->listaSecciones->preguntasX = Examen2->listaSecciones->preguntasX->sig;
        }
        if (Examen2->listaSecciones->sig == NULL)
            break;
        Examen2->listaSecciones= Examen2->listaSecciones->sig;
    }
    imprimirRespuestas(Examen2);
}


void imprimirRespuestas(Examen*Examen2)
{
    struct Examen * inicio = cabezaExamen;
    string respuesta, exa;
    Examen2 = NULL;
    Examen2 = inicio;
    while (Examen2->listaSecciones != NULL){
                while (Examen2->listaSecciones->preguntasX != NULL){
                    system("cls");
                    cout << "Pregunta = "+ Examen2->listaSecciones->preguntasX->pregunta <<endl;
                    cout << "Valor = ";
                    cout << Examen2->listaSecciones->preguntasX->valor <<endl;
                    cout << "Respuesta Introducida = "+ Examen2->listaSecciones->preguntasX->respEst <<endl;
                    cout << "Respuesta Correcta = " + Examen2->listaSecciones->preguntasX->resp <<endl;
                    cout << "Estado de la pregunta = "+ Examen2->listaSecciones->preguntasX->estado << endl;
                    Sleep(5000);

                if (Examen2->listaSecciones->preguntasX->ant == NULL)
                    break;
                Examen2->listaSecciones->preguntasX = Examen2->listaSecciones->preguntasX->ant;
                }
                while (Examen2->listaSecciones->preguntasCortas != NULL){
                    system("cls");
                    cout << "Pregunta = "+ Examen2->listaSecciones->preguntasCortas->pregunta <<endl;
                    cout << "Valor = ";
                    cout << Examen2->listaSecciones->preguntasCortas->valor <<endl;
                    cout << "Respuesta Introducida = "+ Examen2->listaSecciones->preguntasCortas->respEst <<endl;
                    cout << "Respuesta Correcta = " + Examen2->listaSecciones->preguntasCortas->resp <<endl;
                    cout << "Estado de la pregunta = "+ Examen2->listaSecciones->preguntasCortas->estado << endl;
                    cout << "Porcentaje de igualdad de la respuesta = ";
                    cout << Examen2->listaSecciones->preguntasCortas->porcentaje;
                    cout << "%" << endl;
                    Sleep(5000);

                if (Examen2->listaSecciones->preguntasCortas->ant == NULL)
                    break;
                Examen2->listaSecciones->preguntasCortas = Examen2->listaSecciones->preguntasCortas->ant;
                }
        if (Examen2->listaSecciones->sig == NULL)
            break;
        Examen2->listaSecciones= Examen2->listaSecciones->sig;
    }
    cout << "Puntos totales del examen = ";
    cout << Examen2->total_puntos <<endl;
}


//editar preguntas de marque con x
void editPregSelecUnic()// listo
{
    struct Examen *examAct = cabezaExamen;
    struct Secciones *inicio,*inicio2 = NULL;
    struct MarqX *inicioMX = NULL;

    string preg = "",opcPreg="";

    int opExam,opSec,opPreg,x=0,opResp,op;

    while (examAct!=NULL)
    {
        cout<<examAct->numExam<<") "<<examAct->nombre<<endl;
        examAct=examAct->sig;
    }

    examAct=NULL;
    examAct = cabezaExamen;

    cout<<"Seleccione el examen en el cual desea editar preguntas."<<endl;
    cin>>opExam;
    if (examAct==NULL) /// el examen no tiene secciones
    {
        cout<<"El examen seleccionado no cuenta con secciones"<<endl;
        menu();
    }
    while ((examAct!=NULL)&&(examAct->numExam!=opExam)) /// busca examen elegido
    {
        examAct=examAct->sig;
    }

    if ((examAct!=NULL)&&(examAct->numExam==opExam)) /// encontro el examen
    {
        inicio = examAct->listaSecciones; // guardo posicion inicial de listasecciones

        while(inicio!=NULL) // imprimo
        {
            cout<<inicio->numSec<<") "<<inicio->nombre<<endl;

            inicio = inicio->sig; /// recorro imprimiendo secciones
        }// cierre de while de imprimir las secciones

        //examAct->listaSecciones = inicio;  // como luego de imprimir las secciones quedo en null le mando la primera posicion de lista secciones
        inicio2 = examAct->listaSecciones;
        cout<<"Ingrese la seccion en la cual desea editar preguntas."<<endl;
        cin>>opSec;
        while((inicio2!=NULL)&&(inicio2->numSec!=opSec))
        {
            inicio2=inicio2->sig;
        }//cierre de while

        if ((inicio2!=NULL)&&(inicio2->numSec==opSec)) /// quiere decir que lo encontro la seccion
        {
            if (inicio2==NULL)
            {
                cout<<"La seccion ingresada no posee preguntas."<<endl;
                menu();
            }
            else{
                inicioMX = inicio2->preguntasX;
                while(inicioMX!=NULL)
                {
                    cout<<inicioMX->numPreg<<") "<<inicioMX->pregunta<<" ("<<inicioMX->valor<<" pts)"<<endl;
                    inicioMX = inicioMX->sig;
                }
                cout<<"Ingrese la pregunta a editar."<<endl;
                cin >>opPreg;

                inicioMX=inicio2->preguntasX; // limpio el mae

                while((inicioMX!=NULL)&&(inicioMX->numPreg!=opPreg))
                {
                    inicioMX = inicioMX ->sig;
                }
                if ((inicioMX != NULL)&&(inicioMX->numPreg==opPreg)) /// encontro la preg
                {
                    cout<<"\n[1]. Pregunta\n\t"<<inicioMX->pregunta<<"\n[2]. Opciones de respuesta\n\t"<<endl;
                    while(x<inicioMX->cantOp)
                    {
                        cout<<"\t* "<<inicioMX->opciones[x]<<endl;
                        x++;
                    }
                    cout<<"[3]. Respuesta.\n\t"<< inicioMX->resp <<"\nQue desea editar?\n"<<endl;
                    x = 0;
                    cin>>op;
                    switch(op)
                    {
                    case 1:
                        cout<<"\nIngrese la nueva pregunta"<<endl;
                        getline(cin,preg);
                        getline(cin,preg);
                        inicioMX->pregunta = preg;
                        cout<<"nueva preg: "<<inicioMX->pregunta<<endl; // eliminar
                        break;
                    case 2:
                        while(x<inicioMX->cantOp)
                        {
                            cout<<x+1<<") "<<inicioMX->opciones[x]<<endl;
                            x++;
                        }
                        x=0;
                        cout<<"\nIngrese la opcion de respuesta que desea cambiar."<<endl;
                        cin>>opResp;
                        while((x<inicioMX->cantOp)&&(opResp!=x+1))
                        {
                            x++;
                        }
                        if (x >= inicioMX->cantOp)
                        {
                            cout<<"Opcion no valida, intentalo de nuevo."<<endl;
                            editPregSelecUnic();
                        }
                        else if(opResp==x+1){
                            cout<<"Ingrese la nueva opcion de respuesta."<<endl;
                            getline(cin,opcPreg);
                            getline(cin,opcPreg);
                            inicioMX->opciones[x] = opcPreg;
                            cout<<"nueva resp: "<<inicioMX->opciones[x]<<endl; // eliminar
                            }
                        cout<<"No la encontro"<<endl;
                        break;
                    case 3:
                        cout<<"Ingrese la nueva respuesta"<<endl;
                        getline(cin,inicioMX->resp);
                        getline(cin,inicioMX->resp);
                        cout<<inicioMX->resp;
                        break;
                    default:
                        cout<<"La opcion ingresada no es correcta."<<endl;
                        menu();
                        break;
                    }
                }
            }
        }
        else /// no encontro la seccion
        {
            cout<<"La opcion ingresada no se encuentra dentro de las opciones."<<endl;
            menu();
        }
    }
    else
    {
        cout<<"El examen ingresado no se encuentra dentro de las opciones."<<endl;
    }
}


//editar preguntas de respuesta corta
void editPregRespCort() // listo
{
    struct Examen *examAct = cabezaExamen;
    struct Secciones *inicio,*inicio2 = NULL;
    struct RespCort *inicioRespC1 = NULL;

    string newPreg = "",preg = "";


    int opExam,opSec,opPreg,op;

    while (examAct!=NULL)
    {
        cout<<examAct->numExam<<") "<<examAct->nombre<<endl;
        examAct=examAct->sig;
    }

    examAct=NULL;
    examAct = cabezaExamen;

    cout<<"Seleccione el examen en el cual desea editar preguntas."<<endl;
    cin>>opExam;
    if (examAct==NULL) /// el examen no tiene secciones
    {
        cout<<"El examen seleccionado no cuenta con secciones"<<endl;
        menu();
    }
    while ((examAct!=NULL)&&(examAct->numExam!=opExam)) /// busca examen elegido
    {
        examAct=examAct->sig;
    }

    if ((examAct!=NULL)&&(examAct->numExam==opExam)) /// encontro el examen
    {
        inicio = examAct->listaSecciones; // guardo posicion inicial de listasecciones

        while(inicio!=NULL) // imprimo
        {
            cout<<inicio->numSec<<") "<<inicio->nombre<<endl;

            inicio = inicio->sig; /// recorro imprimiendo secciones
        }// cierre de while de imprimir las secciones

        //examAct->listaSecciones = inicio;  // como luego de imprimir las secciones quedo en null le mando la primera posicion de lista secciones
        inicio2 = examAct->listaSecciones;
        cout<<"Ingrese la seccion a renombrar"<<endl;
        cin>>opSec;
        while((inicio2!=NULL)&&(inicio2->numSec!=opSec))
        {
            inicio2=inicio2->sig;
        }//cierre de while

        if ((inicio2!=NULL)&&(inicio2->numSec==opSec)) /// quiere decir que lo encontro la seccion
        {
            if (inicio2==NULL)
            {
                cout<<"La seccion ingresada no posee preguntas."<<endl;
                menu();
            }
            else{
                inicioRespC1 = inicio2->preguntasCortas;
                while(inicioRespC1!=NULL)
                {
                    cout<<inicioRespC1->numPreg<<") "<<inicioRespC1->pregunta<<" ("<<inicioRespC1->valor<<" pts)"<<endl;
                    inicioRespC1 = inicioRespC1->sig;
                }
                cout<<"Ingrese la pregunta a editar."<<endl;
                cin >>opPreg;

                inicioRespC1=inicio2->preguntasCortas; // limpio el mae

                while((inicioRespC1!=NULL)&&(inicioRespC1->numPreg!=opPreg))
                {
                    inicioRespC1 = inicioRespC1 ->sig;
                }
                if ((inicioRespC1!=NULL)&&(inicioRespC1->numPreg==opPreg)) /// encontro la preg
                {
                    cout<<"Que desea editar?\n[1]. Pregunta\n\t"<<inicioRespC1->pregunta<<"\n[2]. Respuesta\n\t"<<inicioRespC1->resp<<endl;
                    cin>>op;
                    switch(op)
                    {
                    case 1:
                        cout<<"\nIngrese la nueva pregunta"<<endl;
                        getline(cin,preg);
                        getline(cin,preg);
                        inicioRespC1->pregunta = preg;
                        cout<<"nueva preg: "<<inicioRespC1->pregunta<<endl;
                        break;
                    case 2:
                        cout<<"\nIngrese la nueva respuesta"<<endl;
                        getline(cin,preg);
                        getline(cin,preg);
                        inicioRespC1->resp = preg;
                        cout<<"nueva resp: "<<inicioRespC1->resp<<endl;
                        break;
                    default:
                        cout<<"La opcion ingresada no es correcta."<<endl;
                        menu();
                        break;
                    }
                }
            }
        }
        else /// no encontro la seccion
        {
            cout<<"La opcion ingresada no se encuentra dentro de las opciones."<<endl;
            menu();
        }
    }
    else
    {
        cout<<"El examen ingresado no se encuentra dentro de las opciones."<<endl;
    }
}


void editarSecciones() // listo
{
    cout<<"=================================================================\n=\t\t\tRenombrar secciones\t\t\t=\n=================================================================\n";
    struct Examen *auxi1,*examAct = cabezaExamen;
    struct Secciones *inicio,*inicio2 = NULL;
    string name = "";
    int opExam,opSec;

    while (examAct!=NULL)
    {
        cout<<examAct->numExam<<") "<<examAct->nombre<<endl;
        examAct=examAct->sig;
    }//cierre de while de imprimir examenes

    ///limpio este mae para evitar problemas
    examAct=NULL;
    examAct = cabezaExamen;

    cout<<"Seleccione el examen en el cual desea editar preguntas."<<endl;
    cin>>opExam;
    if (examAct==NULL)// el examen no tiene secciones
    {
        cout<<"\nEl examen seleccionado no cuenta con secciones"<<endl;
        menu();
    }
    while ((examAct!=NULL)&&(examAct->numExam!=opExam))
    {
        examAct=examAct->sig;   /// recorro la lista en busca del examen
    }//cierre de while

    if ((examAct!=NULL)&&(examAct->numExam==opExam)) /// quiere decir que lo encontro el examen
    {
        inicio = examAct->listaSecciones; // guardo posicion inicial de listasecciones
        cout<<endl;
        while(inicio!=NULL)
        {
            cout<<inicio->numSec<<") "<<inicio->nombre<<endl;

            inicio = inicio->sig; /// recorro imprimiendo secciones
        }

        inicio2 = examAct->listaSecciones;

        cout<<"Ingrese la seccion a renombrar"<<endl;
        cin>>opSec;

        while((inicio2!=NULL)&&(inicio2->numSec!=opSec))
        {
            inicio2=inicio2->sig;
        }

        if ((inicio2!=NULL)&&(inicio2->numSec==opSec)) /// quiere decir que lo encontro la seccion
        {
            if (inicio2==NULL)
            {
                cout<<"La seccion ingresada no contiene preguntas. "<<endl;
                menu();
            }
            cout<<"\nIngrese el nuevo nombre de la seccion.\n"<<endl;
            getline(cin,name);
            getline(cin,name);
            inicio2->nombre = name;
            cout<<"\nEl nuevo nombre de esta seccion ahora es: "<<inicio2->nombre<<endl;
        }
        else
        {
            cout<<"La seccion ingresada no se encuentra dentro de las opciones."<<endl;
            menu();
        }
    }
    else
    {
        cout<<"El examen ingresado no se encuentra dentro de las opciones."<<endl;
        menu();
    }
}


//eliminar preguntas de respuesta corta
void delPregRespCort(){ // no listo
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


//eliminar preguntas de marque con x
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


//menu principal
void menu() // listo
{
        system("cls");
        char op,opEdit,opDel,opExam;
        cout<<"=================================================================\n=\t\t\t\t\t\t\t\t=\n=\t\tGET (Gestor de Examenes TEC)\t\t\t=\n=\t\t\t\t\t\t\t\t=\n=================================================================\n";

        cout<<"=\t\t\tMenu principal\t\t\t\t=\n=================================================================\n";
        cout<<"=\t[1]. Crear Examen\t\t\t\t\t=\n=\t[2]. Modificar Preguntas / Secciones\t\t\t=\n=\t[3]. Borrar Preguntas / Secciones\t\t\t=\n=\t[4]. Realizar Examen      \t\t\t\t=\n=\t[5]. Salir\t\t\t\t\t\t=\n=\t\t\t\t\t\t\t\t\n=\t";
        op = getche(); //obtener opcion
        cout <<endl;
        switch(op){
            case '1':
                {
                    /// procede a ingresar examen en el cual puede crear la cantidad de secciones que desee y de igual manera crear preguntas dentro de cada seccion
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
                                editarSecciones();
                                break;
                            }
                        case '2':
                            {
                                editPregSelecUnic();
                                break;
                            }
                        case '3':
                            {
                                editPregRespCort();
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
                                delPregMarqX();
                                break;
                            }
                        case '3':
                            {
                                delPregRespCort();
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
                    cout<<"\n\n=================================================================\n=\tGracias por utilizar GET (Gestor de Examenes TEC)\t=\n=================================================================\n";
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


//insertar examen de manera manual (solo se ejecuta una vez)
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

    menu();
    delPregMarqX();
    return 0;
}
