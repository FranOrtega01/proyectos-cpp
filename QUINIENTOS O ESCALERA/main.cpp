#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;
#include "rlutil.h"
#include "funciones.h"

int main(){
    rlutil::setBackgroundColor(rlutil::COLOR::MAGENTA);
    rlutil::cls();
    const int victoria = 100;
    int y = 0, i, j, r = 0, k, t, dados[6], contador[6]{},rondas, numeroMult, numeroMultMayor, puntajeTotal = 0, puntajeRonda = 0, puntajeTirada = 0, highscore = 0, puntajeTotal1, puntajeTotal2;
    bool ejecucion = true;
    char nombre[30], nombreHighscore[30], nombre1[30], nombre2[30];;

    //CHEAT MODE
    // Sexteto
    // for(int k = 0 ; k < 6; k++){
    //     dados[k] = 2;
    // }
    // Sexteto de 6
    // for(int k = 0 ; k < 6; k++){
    //     dados[k] = 6;
    // }

    // Escalera
    // for(int k = 0 ; k < 6; k++){
        // dados[k] = k + 1;
    // }

    // mostrarVector(dados, 6);
    // contadores
    // mostrarVector(contador, 6);

    srand(time(0));

    rlutil::hidecursor();
    do{
        // menu
        titulo();
        mostrarOpciones(" 1 JUGADOR ", 50, 10, y == 0);
        mostrarOpciones("2 JUGADORES", 50, 11, y == 1);
        mostrarOpciones(" HIGHSCORE ", 50, 12, y == 2);
        mostrarOpciones("   SALIR   ", 50, 13, y == 3);

        rlutil::setBackgroundColor(rlutil::COLOR::MAGENTA);
        rlutil::setColor(rlutil::COLOR::WHITE);
        lineaVer(1, 29, 30);
        lineaVer(1, 29, 80);
        switch (rlutil::getkey()){
            case 14: // ARRIBA
                rlutil::locate(48, 10 + y);
                cout << " " << endl;
                y--;
                if (y < 0){
                    y = 3;
                }
                break;
            case 15: // ABAJO
                rlutil::locate(48, 10 + y);
                cout << " " << endl;
                y++;

                if (y > 3){
                    y = 0;
                }
                break;
            case 1: // ENTER
                switch (y){
                    // 1 Jugador
                    case 0:
                        // Reset
                        puntajeTotal = 0;
                        puntajeRonda = 0;
                        puntajeTirada = 0;

                        rlutil::cls();
                        linea(1, 3);
                        linea(1, 9);
                        lineaVer(3, 9, 1);
                        lineaVer(3, 9, 66);
                        rlutil::locate(10, 5);
                        cout << "ESCRIBA SU NOMBRE:" << endl;
                        rlutil::locate(30, 5);
                        cin >> nombre;
                        rlutil::locate(10, 7);
                        cout << "INGRESE LA CANTIDAD DE RONDAS:" << endl;
                        rlutil::locate(42, 7);
                        cin >> rondas;
                        r = 1;
                        // Rondas
                        while (r <= rondas && puntajeTotal < victoria){

                            interfazRonda(r, nombre, puntajeTotal);

                            // Tiradas
                            t = 1;
                            while(t <= 3){
                                puntajeTirada = 0;

                                interfazTirada(r,t,nombre, puntajeTotal, puntajeRonda);

                                generarDados(dados, 6);


                                // Verificar dados

                                // Si seis 6, puntaje de la ronda = 0
                                if (seis6(dados)){
                                    rlutil::locate(1, 11);
                                    cout<<"SEXTETO DE 6, NO! PERDISTE TODOS LOS PUNTOS DE LA RONDA"<<endl;
                                    puntajeRonda = 0;
                                }

                                // Si seis iguales, puntaje del lanzamiento = numero * 50
                                if (seisIguales(dados)){
                                    rlutil::locate(1, 11);
                                    cout<<"SEXTETO, NUMERO DEL DADO MULTIPLICADO 50!"<<endl;
                                    puntajeTirada += dados[0] * 50;
                                }

                                // Si escalera gana la partida
                                if(escalera(dados)){
                                    cout<<"ESCALERA!!! GANASTE LA PARTIDA!"<<endl;
                                    puntajeRonda+=500;
                                    rlutil::anykey();
                                    break;
                                }

                                // Devuelve el numero repetido mayor
                                numeroMultMayor = ContadorDeDadosIguales(dados, contador);

                                if ((numeroMultMayor != 0) && (!seisIguales(dados)) && (!seis6(dados)) ){
                                    rlutil::locate(1, 11);
                                    cout<<"3 O MAS DADOS IGUALES  -  NUMERO DEL DADO MULTIPLICADO 10"<<endl;
                                    puntajeTirada = numeroMultMayor * 10;
                                }

                                // menos de 2 dados iguales
                                if ( (numeroMultMayor == 0) && (!seisIguales(dados)) && (!seis6(dados))  && (!escalera(dados)) ){
                                    rlutil::locate(1, 11);
                                    cout<<"MENOS DE 2 DADOS IGUALES - SE SUMAN TODOS LOS DADOS"<<endl;
                                    puntajeTirada = sumarVector(dados, 6);
                                }

                                rlutil::locate(1, 12);
                                cout << "PUNTAJE DE LA TIRADA: " << puntajeTirada;

                                rlutil::anykey();

                                cargarVector(contador, 6);

                                t++;
                                puntajeRonda += puntajeTirada;
                            }

                            rlutil::cls();
                            puntajeTotal += puntajeRonda;
                            puntajeRonda = 0;
                            r++;
                        }
                        if(puntajeTotal>highscore || highscore==0){
                            highscore = puntajeTotal;
                            strcpy(nombreHighscore, nombre);
                        }

                        interfazFin(puntajeTotal, victoria, nombre, r);
                        break;


                    // 2 Jugadores
                    case 1:
                        puntajeTotal1 = 0;
                        puntajeTotal2 = 0;

                        rlutil::cls();
                        linea(1, 3);
                        linea(1, 11);
                        lineaVer(3, 11, 1);
                        lineaVer(3, 11, 66);
                        rlutil::locate(10, 5);
                        cout << "ESCRIBA EL NOMBRE DEL JUGADOR 1:" << endl;
                        rlutil::locate(45, 5);
                        cin >> nombre1;
                        rlutil::locate(10, 7);
                        cout << "ESCRIBA EL NOMBRE DEL JUGADOR 2:" << endl;
                        rlutil::locate(45, 7);
                        cin >> nombre2;
                        rlutil::locate(10, 9);
                        cout << "INGRESE LA CANTIDAD DE RONDAS:" << endl;
                        rlutil::locate(42, 9);
                        cin >> rondas;

                        r = 1;
                        // Rondas
                        while (r <= rondas && (puntajeTotal1 < victoria && puntajeTotal2 < victoria)){

                            interfazRonda2(r, nombre1, nombre2, puntajeTotal1, puntajeTotal2);

                            // Tiradas
                            for(i=1;i<=2;i++){

                                interfazTurnos(r,  i,  puntajeTotal1, puntajeTotal2,  nombre1,  nombre2);
                                t = 1;

                                while(t <= 3){
                                    puntajeTirada = 0;

                                    if(i==1){
                                        strcpy(nombre, nombre1);
                                        puntajeTotal = puntajeTotal1;
                                    }else{
                                        strcpy(nombre, nombre2);
                                        puntajeTotal = puntajeTotal2;
                                    }

                                    interfazTirada(r,t,nombre, puntajeTotal, puntajeRonda);

                                    generarDados(dados, 6);


                                    // Verificar dados

                                    // Si seis 6, puntaje de la ronda = 0
                                    if (seis6(dados)){
                                        rlutil::locate(1, 11);
                                        cout<<"SEXTETO DE 6, NO! PERDISTE TODOS LOS PUNTOS DE LA RONDA"<<endl;
                                        puntajeRonda = 0;
                                    }

                                    // Si seis iguales, puntaje del lanzamiento = numero * 50
                                    if (seisIguales(dados)){
                                        rlutil::locate(1, 11);
                                        cout<<"SEXTETO, NUMERO DEL DADO MULTIPLICADO 50!"<<endl;
                                        puntajeTirada += dados[0] * 50;
                                    }

                                    // Si escalera gana la partida
                                    if(escalera(dados)){
                                        cout<<"ESCALERA!!! GANASTE LA PARTIDA!"<<endl;
                                        puntajeRonda+=500;
                                        rlutil::anykey();
                                        break;
                                    }

                                    // Devuelve el numero repetido mayor
                                    numeroMultMayor = ContadorDeDadosIguales(dados, contador);

                                    if ((numeroMultMayor != 0) && (!seisIguales(dados)) && (!seis6(dados)) ){
                                        rlutil::locate(1, 11);
                                        cout<<"3 O MAS DADOS IGUALES  -  NUMERO DEL DADO MULTIPLICADO 10"<<endl;
                                        puntajeTirada = numeroMultMayor * 10;
                                    }

                                    // menos de 2 dados iguales
                                    if ( (numeroMultMayor == 0) && (!seisIguales(dados)) && (!seis6(dados))  && (!escalera(dados)) ){
                                        rlutil::locate(1, 11);
                                        cout<<"MENOS DE 2 DADOS IGUALES - SE SUMAN TODOS LOS DADOS"<<endl;
                                        puntajeTirada = sumarVector(dados, 6);
                                    }

                                    rlutil::locate(1, 12);
                                    cout << "PUNTAJE DE LA TIRADA: " << puntajeTirada;

                                    rlutil::anykey();

                                    cargarVector(contador, 6);

                                    t++;
                                    puntajeRonda += puntajeTirada;
                                }
                                rlutil::cls();

                                if(i==1){
                                    puntajeTotal1 += puntajeRonda;
                                }else{
                                    puntajeTotal2 += puntajeRonda;
                                }
                                puntajeRonda = 0;
                            }

                            r++;
                        }

                        interfazFin2(r, nombre1, nombre2, puntajeTotal1, puntajeTotal2);

                        // Busca ganador
                        char ganador[30];
                        int puntajeGanador;

                        if( puntajeTotal1 >= puntajeTotal2){
                            puntajeGanador = puntajeTotal1;
                            strcpy(ganador, nombre1);
                        }else{
                            puntajeGanador= puntajeTotal2;
                            strcpy(ganador, nombre2);
                        }

                        // Asigna nuevo highscore
                        if(puntajeGanador > highscore || highscore == 0){
                            highscore = puntajeGanador;
                            strcpy(nombreHighscore, ganador);
                        }

                        puntajeTotal1 = 0;
                        puntajeTotal2 = 0;
                        break;

                    // Highscore
                    case 2:
                        rlutil::cls();
                        linea(21, 5);
                        linea(21, 8);
                        lineaVer(5, 8, 21);
                        lineaVer(5, 8, 86);
                        rlutil::locate(30, 6);
                        cout << "PUNTUACION MAS ALTA: " << highscore << endl;
                        rlutil::locate(30, 7);
                        cout << "DE: " << nombreHighscore << endl;
                        rlutil::anykey();
                        rlutil::cls();
                        break;

                    // Salir
                    case 3:
                        ejecucion = false;
                        break;
                }
        }
    }while (ejecucion != false);
    return 0;
}

