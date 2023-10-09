#ifndef MENUCONFIGURACION_H_INCLUDED
#define MENUCONFIGURACION_H_INCLUDED

#include "jugadorClases.h"
#include "deporteClases.h"
void bkpJugadores();
void bkpDeportes();
void restJugadores();
void restDeportes();
void datosInicio();

void menuConfiguracion(){
    int opc;
    while(true){
        system("cls");
        cout<<"MENU CONFIGURACION"<<endl;
        cout<<"------------------------------------"<<endl;
        cout<<"1) COPIA DE SEGURIDAD DEL ARCHIVO DE JUGADORES"<<endl;
        cout<<"2) COPIA DE SEGURIDAD DEL ARCHIVO DE DEPORTES"<<endl;
        cout<<"3) RESTAURAR EL ARCHIVO DE JUGADORES"<<endl;
        cout<<"4) RESTAURAR EL ARCHIVO DE DEPORTES"<<endl;
        cout<<"5) ESTABLECER DATOS DE INICIO"<<endl;
        cout<<"------------------------------------"<<endl;
        cout<<"0) VOLVER AL MENU PRINCIPAL"<<endl;
        cin >> opc;
        switch(opc){
            case 1:
                bkpJugadores();
            break;
            case 2:
                bkpDeportes();
            break;
            case 3:
                restJugadores();
            break;
            case 4:
                restDeportes();
            break;
            case 5:
                datosInicio();
            break;
            case 0:
                return;
            break;
        }
    }
}
void bkpJugadores(){
    system("cls");
    ArchivoJugadores bkpFile("jugadores.bkp");
    ArchivoJugadores file;
    Jugador aux;

    int tam = file.cantidadRegistros();

    if(tam == -1){
        cout << "No existe el archivo de datos." << endl;
        system("pause");
        return;
    }

    if( tam == 0){
        cout << "No hay registros para respaldar." << endl;
        system("pause");
        return;
    }

    bkpFile.limpiarArchivo();

    for(int i = 0; i<tam; i++){
        aux = file.leerRegistro(i);
        bkpFile.agregarRegistro(aux);
    }
    cout<< "se ha creado el BACKUP de los datos de los jugadores"<<endl;
    system("pause");

}

void bkpDeportes(){
    system("cls");
    ArchivoDeportes bkpFile("deportes.bkp");
    ArchivoDeportes file;
    Deporte aux;


    int tam = file.cantidadRegistros();

    if(tam == -1){
        cout << "No existe el archivo de datos." << endl;
        system("pause");
        return;
    }

    if( tam == 0){
        cout << "No hay registros para respaldar." << endl;
        system("pause");
        return;
    }

    bkpFile.limpiarArchivo();

    for(int i = 0; i<tam; i++){
        aux = file.leerRegistro(i);
        bkpFile.agregarRegistro(aux);
    }

    cout<< "se ha creado el BACKUP de los datos de los deportes"<<endl;
    system("pause");
}

void restJugadores(){
    system("cls");
    ArchivoJugadores bkpFile("jugadores.bkp");
    ArchivoJugadores file;
    Jugador aux;

    int tam = bkpFile.cantidadRegistros();

    if(tam == -1){
        cout << "No existe el archivo de backup." << endl;
        system("pause");
        return;
    }
    if( tam == 0){
        cout << "No hay registros para restaurar." << endl;
        system("pause");
        return;
    }

    file.limpiarArchivo();

    for(int i = 0; i<tam; i++){
        aux = bkpFile.leerRegistro(i);
        file.agregarRegistro(aux);
    }
    cout<< "se han restaurado los datos de los jugadores"<<endl;
    system("pause");
}

void restDeportes(){
    system("cls");
    ArchivoDeportes bkpFile("deportes.bkp");
    ArchivoDeportes file;
    Deporte aux;

    int tam = bkpFile.cantidadRegistros();

    if(tam == -1){
        cout << "No existe el archivo de backup." << endl;
        system("pause");
        return;
    }
    if(tam == 0){
        cout << "No hay registros para restaurar." << endl;
        system("pause");
        return;
    }

    file.limpiarArchivo();

    for(int i = 0; i<tam; i++){
        aux = bkpFile.leerRegistro(i);
        file.agregarRegistro(aux);
    }

    cout<< "se han restaurado los datos de deportes"<<endl;
    system("pause");
}

void datosInicio(){

    ArchivoJugadores jugadoresInicio("jugadoresInicio.dat");
    ArchivoJugadores jugadores;
    Jugador auxJugador;

    int tam = jugadoresInicio.cantidadRegistros();

    if(tam == -1){
        cout << "No existe el archivo de datos de inicio de jugadores." << endl;
        system("pause");
        return;
    }
    if(tam == 0){
        cout << "No hay registros de inicio de jugadores." << endl;
        system("pause");
        return;
    }

    jugadores.limpiarArchivo();

    for(int i = 0; i<tam; i++){
        auxJugador = jugadoresInicio.leerRegistro(i);
        jugadores.agregarRegistro(auxJugador);
    }

    ArchivoDeportes deportesInicio("deportesInicio.dat");
    ArchivoDeportes deportes;
    Deporte auxDeporte;

    tam = deportesInicio.cantidadRegistros();

    if(tam == -1){
        cout << "No existe el archivo de datos de inicio de deportes." << endl;
        system("pause");
        return;
    }
    if(tam == 0){
        cout << "No hay registros de inicio de deportes." << endl;
        system("pause");
        return;
    }

    deportes.limpiarArchivo();

    for(int i = 0; i<tam; i++){
        auxDeporte = deportesInicio.leerRegistro(i);
        deportes.agregarRegistro(auxDeporte);
    }

    cout << "Se reestablecerieron los datos de inicio." << endl;
    system("pause");
}

#endif // MENUCONFIGURACION_H_INCLUDED
