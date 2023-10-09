#ifndef MENUJUGADORES_H_INCLUDED
#define MENUJUGADORES_H_INCLUDED

#include "DeporteClases.h"
#include "JugadorClases.h"
#include "funciones.h"

void agregarJugador();
void listarJugadorDni();
void mostrarJugadores();
void modificarFechaJugador();
void bajaLogicaJugador();
bool existeDNI(int dni);


void menuJugadores(){
    int opc;

    while(true){
        system("cls");
        cout << "MENU JUGADORES" << endl;
        cout << "----------------------------------" << endl;
        cout << "1) AGREGAR JUGADOR" << endl;
        cout << "2) LISTAR JUGADOR POR DNI" << endl;
        cout << "3) LISTAR TODOS LOS JUGADORES" << endl;
        cout << "4) MODIFICAR FECHA DE INSCRIPCION " << endl;
        cout << "5) ELIMINAR REGISTRO DE JUGADOR" << endl;
        cout << "----------------------------------" << endl;
        cout << "0) VOLVER AL MENU" << endl;
        cout << "Seleccione una de las opciones: ";
        cin >> opc;
        switch(opc){
            case 1:
                agregarJugador();
                break;
            case 2:
                listarJugadorDni();
                break;
            case 3:
                mostrarJugadores();
                break;
            case 4:
                modificarFechaJugador();
                break;
            case 5:
                bajaLogicaJugador();
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


bool existeDNI(int dni){
    ArchivoJugadores file;
    Jugador aux;

    int tam = file.cantidadRegistros();

    for(int i = 0; i < tam; i++){
        if(file.leerRegistro(i).getDni() == dni) return true;
    }
    return false;
}

void agregarJugador(){
    system("cls");
    Jugador nuevoJugador;
    ArchivoJugadores file;

    int dni;
    cout << "DNI: ";
    cin >> dni;

    if(existeDNI(dni)){
        cout << "El dni ya existe" << endl;
        system("pause");
        return;
    }

    nuevoJugador.cargar(dni);
    file.agregarRegistro(nuevoJugador);
}

void listarJugadorDni(){
    system("cls");
    Jugador aux;
    ArchivoJugadores file;

    int dni;
    cout << "Ingrese DNI: ";
    cin >> dni;

    int pos = file.buscarRegistro(dni);

    if(pos == -2){
        cout << "Hubo un error al abrir el archivo.";
        system("pause");
        return ;
    }
    if(pos == -1){
        cout << "Jugador no encontrado";
        system("pause");
        return ;
    }

    aux = file.leerRegistro(pos);
    aux.mostrar();
    system("pause");
}

void mostrarJugadores(){
    system("cls");
    Jugador aux;
    ArchivoJugadores file;

    int cant = file.cantidadRegistros();

    for(int i=0; i<cant;i++){
        aux=file.leerRegistro(i);
        if(aux.getEstado()){
            aux.mostrar();
            cout<<endl;
        }
    }
    system("pause");
}

void modificarFechaJugador(){
   system("cls");
   ArchivoJugadores file;
   Jugador aux;

   int dni;
   cout << "Ingrese DNI: " ;
   cin >> dni;

   int pos = file.buscarRegistro(dni);

   if(pos == -2){
       cout << "Hubo un error al abrir el archivo.";
       system("pause");
       return ;
   }
   if(pos == -1){
       cout << "Jugador no encontrado";
       system("pause");
       return ;
   }
   cout << "Jugador a cambiar: " << endl;
   aux = file.leerRegistro(pos);
   aux.mostrar();
   cout << endl;
   cout << "Nueva fecha: "<< endl;
   aux.setFecha();

   file.sobreescribirRegistro(aux, pos);
}

void bajaLogicaJugador(){
   system("cls");
   ArchivoJugadores file;
   Jugador aux;
   cout << "Ingrese DNI: ";
   int dni;
   cin >> dni;

   int pos = file.buscarRegistro(dni);

   if(pos == -2){
       cout << "Hubo un error al abrir el archivo.";
       system("pause");
       return ;
   }
   if(pos == -1){
       cout << "Jugador no encontrado";
       system("pause");
       return ;
   }

   aux = file.leerRegistro(pos);
   aux.setEstado(false);

   file.sobreescribirRegistro(aux, pos);
}

#endif // MENUJUGADORES_H_INCLUDED
