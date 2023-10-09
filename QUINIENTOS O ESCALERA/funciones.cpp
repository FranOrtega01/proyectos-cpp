#include <iostream>
using namespace std;
#include "rlutil.h"
#include "funciones.h"


// Menu
void mostrarOpciones(const char *texto, int posx, int posy, bool seleccionado){
    if (seleccionado)
    {
        rlutil::setBackgroundColor(rlutil::COLOR::YELLOW);
        rlutil::setColor(rlutil::COLOR::BLACK);
        rlutil::locate(posx - 2, posy);
        cout << (char)175 << " " << texto << " " << (char)174 << endl;
    }
    else
    {
        rlutil::setBackgroundColor(rlutil::COLOR::MAGENTA);
        rlutil::setColor(rlutil::COLOR::WHITE);
        rlutil::locate(posx - 2, posy);
        cout << "  " << texto << "  " << endl;
    }
}

void titulo(){
    rlutil::locate(45, 8);
    rlutil::setBackgroundColor(rlutil::COLOR::MAGENTA);
    rlutil::setColor(rlutil::COLOR::WHITE);
    cout << "QUINIENTOS O ESCALERA" << endl;
}

void linea(int xPos, int yPos){
    rlutil::locate(xPos, yPos);
    cout << "------------------------------------------------------------------" << endl;
}

void lineaCorta(int xPos, int yPos){
    rlutil::locate(xPos, yPos);
    cout<<"------------------------------------"<<endl;
}

void lineaVer(int yPosInicio, int yPosFin, int xPos){
    int i;
    for(i=yPosInicio;i<=yPosFin;i++){
    rlutil::locate(xPos, i);
    cout << (char)186 << endl;
    }
}

// Dados
void dados(){
    rlutil::setBackgroundColor(rlutil::COLOR::MAGENTA);
    rlutil::cls();
    dibujarDado(1, 5, 5);
    dibujarDado(2, 15, 5);
    dibujarDado(3, 25, 5);
    dibujarDado(4, 35, 5);
    dibujarDado(5, 45, 5);
    dibujarDado(6, 55, 5);

    rlutil::locate(1, 24);
    rlutil::anykey();
    rlutil::setBackgroundColor(rlutil::COLOR::MAGENTA);
    rlutil::cls();
}

void dibujarDado(int numero, int posx, int posy){
    dibujarCuadrado(posx, posy);
    dibujarPuntos(numero, posx, posy);
}

void dibujarCuadrado(int posx, int posy){
    int x, y;
    for (x = 0; x < 7; x++)
    {
        for (y = 0; y < 3; y++)
        {
            rlutil::setColor(rlutil::COLOR::WHITE);
            rlutil::locate(x + posx, y + posy);
            cout << (char)219 << endl;
        }
    }
}

void dibujarPuntos(int numero, int posx, int posy){
    switch (numero)
    {
    case 1:
        rlutil::setColor(rlutil::COLOR::BLACK);
        rlutil::setBackgroundColor(rlutil::COLOR::WHITE);
        rlutil::locate(posx + 3, posy + 1);
        cout << (char)254 << endl;
        break;
    case 2:
        rlutil::setColor(rlutil::COLOR::BLACK);
        rlutil::setBackgroundColor(rlutil::COLOR::WHITE);
        rlutil::locate(posx + 1, posy);
        cout << (char)254 << endl;
        rlutil::locate(posx + 5, posy + 2);
        cout << (char)254 << endl;
        break;
    case 3:
        rlutil::setColor(rlutil::COLOR::BLACK);
        rlutil::setBackgroundColor(rlutil::COLOR::WHITE);
        rlutil::locate(posx + 1, posy);
        cout << (char)254 << endl;
        rlutil::locate(posx + 3, posy + 1);
        cout << (char)254 << endl;
        rlutil::locate(posx + 5, posy + 2);
        cout << (char)254 << endl;
        break;
    case 4:
        rlutil::setColor(rlutil::COLOR::BLACK);
        rlutil::setBackgroundColor(rlutil::COLOR::WHITE);
        rlutil::locate(posx + 1, posy);
        cout << (char)254 << endl;
        rlutil::locate(posx + 5, posy);
        cout << (char)254 << endl;
        rlutil::locate(posx + 1, posy + 2);
        cout << (char)254 << endl;
        rlutil::locate(posx + 5, posy + 2);
        cout << (char)254 << endl;
        break;
    case 5:
        rlutil::setColor(rlutil::COLOR::BLACK);
        rlutil::setBackgroundColor(rlutil::COLOR::WHITE);
        rlutil::locate(posx + 1, posy);
        cout << (char)254 << endl;
        rlutil::locate(posx + 5, posy);
        cout << (char)254 << endl;
        rlutil::locate(posx + 1, posy + 2);
        cout << (char)254 << endl;
        rlutil::locate(posx + 5, posy + 2);
        cout << (char)254 << endl;
        rlutil::locate(posx + 3, posy + 1);
        cout << (char)254 << endl;
        break;
    case 6:
        rlutil::setColor(rlutil::COLOR::BLACK);
        rlutil::setBackgroundColor(rlutil::COLOR::WHITE);
        rlutil::locate(posx + 1, posy);
        cout << (char)254 << endl;
        rlutil::locate(posx + 5, posy);
        cout << (char)254 << endl;
        rlutil::locate(posx + 1, posy + 1);
        cout << (char)254 << endl;
        rlutil::locate(posx + 5, posy + 1);
        cout << (char)254 << endl;
        rlutil::locate(posx + 1, posy + 2);
        cout << (char)254 << endl;
        rlutil::locate(posx + 5, posy + 2);
        cout << (char)254 << endl;
        break;
    }
}

void generarDados(int dados[], int size){
    for (int j = 0; j < size; j++){
        // NORMAL MODE
        dados[j] = rand() % 6 + 1;


        //CHEAT MODE
        // if(t == 1) {
        //     for(int k = 0 ; k < 6; k++){
        //         dados[k] = 2;
        //     }
        // }
        // if(t == 2){
        //     for(int k = 0 ; k < 6; k++){
        //         dados[k] = 6;
        //     }
        // }
        // if(t== 3){
        //     for(int k = 0 ; k < 6; k++){
        //         dados[k] = k + 1;
        //     }
        // }


        dibujarDado(dados[j], 5 + 10 * j, 7);
        rlutil::setBackgroundColor(rlutil::COLOR::MAGENTA);
        rlutil::setColor(rlutil::COLOR::WHITE);
    }
}

// Interfaces
void interfazRonda(int r, char nombre[], int puntajeTotal){
    int i;
    rlutil::cls();
    lineaCorta(30, 4);
    rlutil::locate(40, 6);
    cout<<"RONDA N"<< (char)167 <<r<<endl;
    lineaCorta(30, 7);
    rlutil::locate(37, 9);
    cout<<"NOMBRE DEL JUGADOR: "<<nombre<<endl;
    rlutil::locate(37, 11);
    cout<<"PUNTAJE: "<<puntajeTotal;
    lineaCorta(30, 13);
    lineaVer(4, 13, 66);
    lineaVer(4, 13, 29);
    rlutil::anykey();
}

void interfazRonda2(int r, char nombre1[], char nombre2[], int puntajeTotal1, int puntajeTotal2){
    rlutil::cls();
    lineaCorta(30, 2);
    rlutil::locate(40, 4);
    cout<<"RONDA N"<< (char)167 <<r<<endl;
    lineaCorta(30, 5);
    rlutil::locate(35, 7);
    cout<<"NOMBRE DEL JUGADOR 1: "<<nombre1<<endl;
    rlutil::locate(35, 8);
    cout<<"PUNTAJE: "<<puntajeTotal1;
    rlutil::locate(35, 10);
    cout<<"NOMBRE DEL JUGADOR 2: "<<nombre2<<endl;
    rlutil::locate(35, 11);
    cout<<"PUNTAJE: "<<puntajeTotal2;
    lineaCorta(30, 13);
    lineaVer(2, 13, 66);
    lineaVer(2, 13, 29);
    rlutil::anykey();
}

void interfazTirada(int r, int t, char nombre[], int puntajeTotal , int puntajeRonda){
    rlutil::cls();
    rlutil::setBackgroundColor(rlutil::COLOR::MAGENTA);
    cout << "TURNO DE " << nombre << "  ||  RONDA N" << (char)167 << r << "  ||  PUNTAJE TOTAL: " << puntajeTotal << endl;
    linea(0, 1);
    cout << "MAXIMO PUNTAJE DE LA RONDA: " << puntajeRonda << " PUNTOS" << endl;
    cout << "LANZAMIENTO N" << (char)167 << t << endl;
    linea(0, 4);
    rlutil::locate(1, 7);
    cout << "Toca cualquier tecla para tirar los dados" << endl;
    lineaVer(1, 13, 67);
    linea(0, 13);
    rlutil::anykey();
    rlutil::locate(1, 7);
    cout << "                                              " << endl;

}

void interfazFin(int puntajeTotal, int victoria, char nombre[], int r){
    linea(22, 1);
    if (puntajeTotal >= victoria){
        rlutil::locate(42, 1);
        cout<<"| GANASTE LA PARTIDA!! |"<<endl;
    }else{
        rlutil::locate(42, 1);
        cout<<"| PERDISTE LA PARTIDA... |"<<endl;
    }
    rlutil::locate(50, 3);
    cout<<"EN RONDA: "<<r-1<<endl;
    linea(22, 4);
    rlutil::locate(30, 5);
    cout<<"JUGADOR: "<<nombre<<endl;
    rlutil::locate(60, 5);
    cout<<"PUNTAJE: "<<puntajeTotal<<endl;
    linea(22, 6);
    lineaVer(1, 6, 21);
    lineaVer(1, 6, 88);
    rlutil::anykey();
    rlutil::cls();
}

//interfaces para dos jugadores
void interfazTurnos(int r, int i, int puntajeTotal1, int puntajeTotal2, char nombre1[], char nombre2[]){
    rlutil::cls();
    char nombre[30];
    i == 1 ? strcpy(nombre, nombre1) : strcpy(nombre, nombre2);
    lineaCorta(30, 2);
    rlutil::locate(42, 4);
    cout<< "RONDA N" << (char)167 << r << endl;
    rlutil::locate(37, 6);
    cout<< "PROXIMO TURNO: " << nombre << endl;
    lineaCorta(30, 8);
    rlutil::locate(37, 10);
    cout<< "PUNTAJE " << nombre1 << ": " << puntajeTotal1 << " PUNTOS" << endl;
    rlutil::locate(37, 12);
    cout<< "PUNTAJE " << nombre2 << ": " << puntajeTotal2  <<" PUNTOS" << endl;
    lineaCorta(30, 14);
    lineaVer(2, 14, 29);
    lineaVer(2, 14, 66);
    rlutil::anykey();

}

void interfazFin2(int r, char nombre1[], char nombre2[], int puntajeTotal1, int puntajeTotal2){

    linea(22, 1);
    if(puntajeTotal1>=500&&puntajeTotal2>=500){
        rlutil::locate(40, 1);
        cout << "|LA PARTIDA FUE UN EMPATE|" << endl;
    }else if (puntajeTotal1>puntajeTotal2){
        rlutil::locate(45, 1);
        cout<<"| GANADOR: " << nombre1 << "!! |" << endl;
    } else {
        rlutil::locate(45, 1);
        cout<<"| GANADOR: " << nombre2 << "!! |" << endl;
    }
    rlutil::locate(47, 3);
        cout<<"EN RONDA: "<<r-1<<endl;
    linea(22, 4);
    rlutil::locate(36, 6);
        cout<<"JUGADOR: "<<nombre1<<endl;
    rlutil::locate(62, 6);
        cout<<"PUNTAJE: "<<puntajeTotal1<<endl;
    rlutil::locate(36, 8);
        cout<<"JUGADOR: "<<nombre2<<endl;
    rlutil::locate(62, 8);
        cout<<"PUNTAJE: "<<puntajeTotal2<<endl;
        linea(22, 10);
        lineaVer(1, 10, 21);
        lineaVer(1, 10, 88);

    rlutil::anykey();
    rlutil::cls();

}


// Combinaciones
int seis6(int dados[]){
    int cantSeis = 0;
    for(int i = 0; i < 6; i++){
        if(dados[i] == 6){
            cantSeis++;
        }
    }
    // Retorna true si los seis dados son 6, si no retorna false
    return cantSeis == 6;
}

int seisIguales(int dados[]){
    int valor = dados[0];
    int cantValor = 0;
    for(int i = 0; i < 6; i++){
        if(dados[i] == valor){
            cantValor++;
        }
    }
    // Retorna true si los seis dados son iguales y distintos de 6, si no retorna false
    return (cantValor == 6 && valor != 6);
}

int escalera(int dados[]){
    int i;
    bool escalera = true;
    for(i=0;i<=5;i++){
        if(dados[i] != i+1 && escalera){
            escalera = false;
        }
    }
    rlutil::locate(10,13);
    return escalera;
}

int ContadorDeDadosIguales(int dados[], int contador[]){
    int numeroMultMayor = 0;
    int j, k, numeroMult;

    for (j = 0; j < 6; j++){
        int indice = dados[j] - 1;
        contador[indice]++;
        for (k = 0; k < 6; k++){
            if ((contador[k] >= 3) && (contador[k] <= 5)){
                numeroMult = k+1;
                if ((numeroMult > numeroMultMayor) || (numeroMultMayor == 0)){
                    numeroMultMayor = k+1;
                }
            }
        }
    }
    return numeroMultMayor;
}


// Vectores
void cargarVector(int vec[], int size){
    for(int i = 0; i < size ; i++){
        vec[i] = 0;
    }
}

void mostrarVector(int vec[], int size){
    cout << "Vector: [";
    for(int i = 0; i < size; i++){
        cout << vec[i] << ",";
    }
    cout << "]";
}

int sumarVector(int vec[], int size){
    int suma = 0;
    for(int i = 0; i < size; i++){
        suma += vec[i];
    }
    return suma;
}







