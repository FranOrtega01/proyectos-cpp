#ifndef MENUREPORTES_H_INCLUDED
#define MENUREPORTES_H_INCLUDED

#include "JugadorClases.h"

void punto1();
void punto2();
void punto3();

void menuReportes(){
    int opc;

    while(true){
        system("cls");
        cout << "MENU REPORTES" << endl;
        cout << "----------------------------------" << endl;
        cout << "1) INFORMAR LA CANTIDAD DE JUGADORES QUE PRACTICAN UN DEPORTE" << endl;
        cout << "2) INFORMAR EL CLAUSTRO CON MAS JUGADORES" << endl;
        cout << "3) INFORMAR LA CANTIDAD DE ALUMNOS REGISTRADOS EN UN TIPO DEPORTE ESPECIFICO" << endl;
        cout << "----------------------------------" << endl;
        cout << "0) VOLVER AL MENU" << endl;
        cout << "Seleccione una de las opciones: ";
        cin >> opc;
        switch(opc){
            case 1:
                // Dado un número de deporte que se ingresa por teclado
                // informar la cantidad de jugadores que lo practican.
                punto1();
                break;
            case 2:
                // Informar el claustro con más jugadores.
                punto2();
                break;
            case 3:
                // Dado un tipo de deporte,
                // informar la cantidad de alumnos que están registrados en algún deporte de ese tipo.
                punto3();
                break;
            case 0:
                return;
            default:
                cout << "Opcion invalida." << endl;
                system("pause");
                break;
            }
        }
    }

void punto1(){
    system("cls");
    ArchivoJugadores file;
    Jugador aux;

    int nDeporte, contadorJugadores = 0;
    cout << "Ingrese numero de deporte: " ;
    cin >> nDeporte;

    int cantidadRegistros = file.cantidadRegistros();
    int i;
    for(i=0; i<cantidadRegistros; i++){
        // if(file.leerRegistro(i).getDeporte() == nDeporte ) // Variable en una linea;
        aux = file.leerRegistro(i);
        if(aux.getDeporte() == nDeporte){
            contadorJugadores++;
        }

    }
    cout << "LA CANTIDAD DE JUGADORES QUE PRACTICAN EL DEPORTE SON: " << contadorJugadores << endl;
    system("pause");
}

int buscarMaximo(int vector[], int tam){
    int pos = 0;
    int maximo = vector[pos];
    int posMaximo = 0;

    for(int i = 0; i < tam; i++){
        if(vector[pos] > maximo){
            maximo = vector[pos];
            posMaximo = pos;
        }
    }
    return posMaximo;
}

void punto2(){
    system("cls");
    ArchivoJugadores file;
    Jugador aux;

    int cantClaustros[4]={}; // ={} Inicializa el vector en 0 -> [0, 0, 0, 0];
    int i, tam;
    tam = file.cantidadRegistros();
    for(i=0; i<tam; i++){
        aux = file.leerRegistro(i);

        // Todos los aux que yo mire tienen un claustro de 1-4. Mi vector va de 0 a 3.
        // Le sumo 1 a la posicion claustro - 1 de mi vector

        cantClaustros[aux.getClaustro()-1]++;
    }

    // Buscar maximo devuelve la posicion con el maximo. Si devuelve por ejemplo 0, mi claustro con mas jugadores es el 1.
    // Para saber la cantidad de jugadores pregunto el valor del vector en la posicion del maximo.
    // Ej: buscarMaximo devuelve 3 (claustro 4) y la cantidad de jugadores del calustro 4 es cantClaustro[3].

    // Opcion 1 - Buscar maximo aca:
    int pos = 0;
    int maximo = cantClaustros[pos];
    int posMaximo = 0;

    for(int i = 0; i < tam; i++){
        if(cantClaustros[pos] > maximo){
            maximo = cantClaustros[pos];
            posMaximo = pos;
        }
    }
    cout << "El claustro con mas jugadores es el " << posMaximo + 1 << "con " << maximo << "jugadores" << endl;

    // Opcion 2 - Buscar maximo con una funcion:

    // int posicionMaximo = buscarMaximo(cantClaustros, 4);
    // cout << "El claustro con mas jugadores es el " << posicionMaximo + 1 << "con " << cantClaustros[posicionMaximo] << endl;


    system("pause");
}

void punto3(){
    /*
        - Ingreso tipo.
        - Leo uno a uno el alumno (ALUMNOS ES JUGADOR CON CLAUSTRO = 2) y me fijo su deporte.
        - Busco con buscarRegsitro el deporte con esa id en el archivoJugadores
        - si el deporte es de tipo == al tipo que pregunte, sumar el contador
        - Mostrar el contador
    */
system("cls");
    ArchivoJugadores fileJugadores;
    ArchivoDeportes fileDeporte;
    Jugador aux;
    Deporte auxDeporte;
    int tipo;
    cout << "Ingrese el tipo de deporte: ";
    cin >> tipo;

    int cantTipo = 0;

    int tamJugadores =  fileJugadores.cantidadRegistros();
    for(int i = 0; i < tamJugadores; i++){

        // Si es alumno hace todo eso
        if(fileJugadores.leerRegistro(i).getClaustro() == 2){
            int idDeporte = fileJugadores.leerRegistro(i).getDeporte();
            // fileDeporte.buscarRegistro(id) devuelve el DEPORTE que corresponda a esa id.
            int posDeporte = fileDeporte.buscarRegistro(idDeporte);
            auxDeporte = fileDeporte.leerRegistro(posDeporte) ;
            if(auxDeporte.getTipoDeporte() == tipo) cantTipo++;
        }
    }

    cout << "hay " <<cantTipo<< "de ALUMNOS registrados en un deporte de tipo " << tipo <<endl;
    system("pause");
}


#endif // MENUREPORTES_H_INCLUDED
