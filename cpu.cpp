#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>
#include <algorithm>
#include "cpu.h"
#include "gotoxy.h"
#include "logica.h"
#include "interfaz.h"
#include "audio.h"

using namespace std;
int jug1=0, cpu_puntaje=0;

// Función para verificar movimientos ganadores
bool movimientoGanador(char jugador, int& fila, int& columna) {
    // Verificar filas
    for (int i = 0; i < 3; i++) {
        int contador = 0, columna_vacia = -1;
        for (int j = 0; j < 3; j++) {
            if (matrizJuego[i][j] == jugador) contador++;
            else if (matrizJuego[i][j] == ' ') columna_vacia = j;
        }
        if (contador == 2 && columna_vacia != -1) {
            fila = i;
            columna = columna_vacia;
            return true;
        }
    }

    // Verificar columnas
    for (int j = 0; j < 3; j++) {
        int contador = 0, fila_vacia = -1;
        for (int i = 0; i < 3; i++) {
            if (matrizJuego[i][j] == jugador) contador++;
            else if (matrizJuego[i][j] == ' ') fila_vacia = i;
        }
        if (contador == 2 && fila_vacia != -1) {
            fila = fila_vacia;
            columna = j;
            return true;
        }
    }

    // Verificar diagonal principal
    int contador = 0, posicion_vacia = -1;
    for (int i = 0; i < 3; i++) {
        if (matrizJuego[i][i] == jugador) contador++;
        else if (matrizJuego[i][i] == ' ') posicion_vacia = i;
    }
    if (contador == 2 && posicion_vacia != -1) {
        fila = posicion_vacia;
        columna = posicion_vacia;
        return true;
    }

    // Verificar diagonal secundaria
    contador = 0;
    posicion_vacia = -1;
    for (int i = 0; i < 3; i++) {
        if (matrizJuego[i][2-i] == jugador) contador++;
        else if (matrizJuego[i][2-i] == ' ') posicion_vacia = i;
    }
    if (contador == 2 && posicion_vacia != -1) {
        fila = posicion_vacia;
        columna = 2-posicion_vacia;
        return true;
    }

    return false;
}

// Función para elegir la mejor jugada
void mejorJugada(int& fila, int& columna) {
    // 1. Buscar jugada ganadora para la CPU (O)
    if (movimientoGanador('O', fila, columna)) return;
    
    // 2. Bloquear jugada ganadora del jugador (X)
    if (movimientoGanador('X', fila, columna)) return;
    
    // 3. Tomar el centro si está disponible
    if (matrizJuego[1][1] == ' ') {
        fila = 1;
        columna = 1;
        return;
    }
    
    // 4. Tomar una esquina si está disponible
    vector<pair<int, int>> esquinas = {{0,0}, {0,2}, {2,0}, {2,2}};
    random_shuffle(esquinas.begin(), esquinas.end());
    for (auto pos : esquinas) {
        if (matrizJuego[pos.first][pos.second] == ' ') {
            fila = pos.first;
            columna = pos.second;
            return;
        }
    }
    
    // 5. Tomar cualquier posición disponible
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrizJuego[i][j] == ' ') {
                fila = i;
                columna = j;
                return;
            }
        }
    }
}

void cpu() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 2);

    int fila = 0, columna = 0;
    bool juegoTerminado = false;
    playBackgroundMusic("musicatablero.wav");
    
    turnoJugador1 = true;
    gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<jug1<<endl;
    gotoxy (92, 7);cout<<"Victorias CPU: "<<cpu_puntaje<<endl;
    
    while (!juegoTerminado) {
        if (turnoJugador1) {  
            gotoxy(posiciones[fila][columna][0], posiciones[fila][columna][1]);
            
            if (kbhit()) {
                int tecla = getch();
                if (tecla == 224) {
                    tecla = getch();
                    switch (tecla) {
                        case 72: if (fila > 0) fila--; break;
                        case 80: if (fila < 2) fila++; break;
                        case 75: if (columna > 0) columna--; break;
                        case 77: if (columna < 2) columna++; break;
                    }
                } else if (tecla == 13) {
                    if (matrizJuego[fila][columna] == ' ') {
                    	playEffect("sonidoboton.wav");
                        matrizJuego[fila][columna] = 'X';
                        dibujarSimbolo(fila, columna, 'X');

                        if (hayGanador()) {
                            gotoxy(35, 28);
                            poner_color(9);
                            pauseBackgroundMusic();
                            playEffect("victoria.wav");
                            cout << "Jugador 1 (X) gana!";
                            if (turnoJugador1){
                                jug1++;
                            }
                            gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<jug1<<endl;
                            getch();
                            juegoTerminado = true;
                            break;
                        } else if (hayEmpate()) {
                            gotoxy(41, 28);
                            cout << "Empate!";
                            getch();
                            juegoTerminado = true;
                            break;
                        }
                        turnoJugador1 = false;
                    }
                }
            }
        } else {
            gotoxy(32, 28); cout << "Turno de la CPU...         ";
            Sleep(500);
            gotoxy(32, 28); cout << "                         ";
            
            // La CPU decide su movimiento usando la estrategia mejorada
            mejorJugada(fila, columna);

            matrizJuego[fila][columna] = 'O';
            dibujarSimbolo(fila, columna, 'O');
            
            if (hayGanador()) {
                gotoxy(32, 28); cout << "                         ";
                gotoxy(38, 28);
                poner_color(9);
                pauseBackgroundMusic();
                playEffect("victoriacpu.wav");
                cout << "La CPU gana!";
                if (!turnoJugador1){
                    cpu_puntaje++;
                }
                gotoxy (92, 7);cout<<"Victorias CPU: "<<cpu_puntaje<<endl;
                getch();
                juegoTerminado = true;
                break;
            } else if (hayEmpate()) {
                gotoxy(32, 28); cout << "                         ";
                gotoxy(41, 28);
                cout << "Empate!";
                getch();
                juegoTerminado = true;
                break;
            }
            turnoJugador1 = true;
        }
        Sleep(50);
    }
    mciSendString("close all", NULL, 0, NULL);

    char respuesta;
    gotoxy(26, 28); cout << "Desea iniciar una nueva partida? (S/N): ";
    cin >> respuesta;
    
    if (respuesta == 'S' || respuesta == 's') {
    	playEffect("sonidoboton.wav");
        gotoxy(26, 28); cout << "                                         ";
        reiniciarTablero();
        tablero();
        cpu();
    } else {
    	playEffect("sonidoboton.wav");
        system("cls");
        gotoxy (12,2); cout<<"Grupo Conformado por:"<<endl;
        gotoxy (12,4); cout<<"1. Fabian Coronel Morato"<<endl;
        gotoxy (12,6); cout<<"2. Andres Pomares Navarro"<<endl;
        gotoxy (12,8); cout<<"3. Cesar Beltran Alvarado"<<endl;
        gotoxy (12,10); cout<<"4.                       "<<endl;
        gotoxy (12,12); cout<<"Clase: Programacion II"<<endl;
        gotoxy (10,14); cout<<"Profesor: Tomas Campo Cadernas"<<endl;
        gotoxy (6,16); cout<<"Institucion: Universidad del Magdalena"<<endl;
        gotoxy(15,18); cout << "Gracias por jugar!";
    }
}