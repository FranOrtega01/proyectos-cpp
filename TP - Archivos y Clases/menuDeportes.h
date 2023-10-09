#ifndef MENUDEPORTES_H_INCLUDED
#define MENUDEPORTES_H_INCLUDED

#include "DeporteClases.h"

void agregarDeporte();
void mostrarDeportes();
void listarDeporteID();
void modificarFechaDeporte();
void bajaLogicaDeporte();

void menuDeportes(){
    int opc;

    while(true){
        system("cls");
        cout << "MENU DEPORTES" << endl;
        cout << "----------------------------------" << endl;
        cout << "1) AGREGAR DEPORTE" << endl;
        cout << "2) LISTA DEPORTE POR ID" << endl;
        cout << "3) LISTAR TODO" << endl;
        cout << "4) MODIFICAR ANIO DE ORIGEN" << endl;
        cout << "5) ELIMINAR REGISTRO DE DEPORTE" << endl;
        cout << "----------------------------------" << endl;
        cout << "0) VOLVER AL MENU" << endl;
        cout << "Seleccione una de las opciones: ";
        cin >> opc;
        switch(opc){
            case 1:
                agregarDeporte();
                break;
            case 2:
                listarDeporteID();
                break;
            case 3:
                mostrarDeportes();
                break;
            case 4:
                modificarFechaDeporte();
                break;
            case 5:
                bajaLogicaDeporte();
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

void agregarDeporte(){
    ArchivoDeportes file;
    Deporte aux;

    int tam = file.cantidadRegistros();
    int id;
    if(tam == -1 || tam == 0){
        id = 1;
    }else{
        id = file.leerRegistro(tam - 1).getID() + 1;
    }
    aux.cargar(id);
    file.agregarRegistro(aux);
}

void listarDeporteID(){
    system("cls");
    Deporte aux;
    ArchivoDeportes file;

    int id;
    cout << "Ingrese ID: ";
    cin >> id;

    int pos = file.buscarRegistro(id);

    if(pos == -2){
        cout << "Hubo un error al abrir el archivo.";
        system("pause");
        return ;
    }
    if(pos == -1){
        cout << "Deporte no encontrado";
        system("pause");
        return ;
    }

    aux = file.leerRegistro(pos);
    aux.mostrar();
    system("pause");
}

void mostrarDeportes(){
    system("cls");
    Deporte aux;
    ArchivoDeportes file;

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

void modificarFechaDeporte(){
    system("cls");
    int nuevaFecha;
    ArchivoDeportes file;
    Deporte aux;

    int id;
    cout << "Ingrese ID: " ;
    cin >> id;

    int pos = file.buscarRegistro(id);

    if(pos == -2){
        cout << "Hubo un error al abrir el archivo.";
        system("pause");
        return ;
    }
    if(pos == -1){
        cout << "Deporte no encontrado";
        system("pause");
        return ;
    }
    cout << "Deporte a cambiar: " << endl;
    aux = file.leerRegistro(pos);
    aux.mostrar();
    cout << endl;
    cout << "Nueva fecha: "<< endl;
    cin >> nuevaFecha;
    aux.setFechaOrigen(nuevaFecha);

    file.sobreescribirRegistro(aux, pos);
}

void bajaLogicaDeporte(){
    system("cls");
    ArchivoDeportes file;
    Deporte aux;
    cout << "Ingrese ID: ";
    int id;
    cin >> id;

    int pos = file.buscarRegistro(id);

    if(pos == -2){
        cout << "Hubo un error al abrir el archivo.";
        system("pause");
        return ;
    }
    if(pos == -1){
        cout << "Deporte no encontrado";
        system("pause");
        return ;
    }

    aux = file.leerRegistro(pos);
    aux.setEstado(false);

    file.sobreescribirRegistro(aux, pos);
}

#endif // MENUDEPORTES_H_INCLUDED
