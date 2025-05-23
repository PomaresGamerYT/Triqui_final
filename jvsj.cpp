#include <iostream>
#include <conio.h>
#include "jvsj.h"
#include "gotoxy.h"
#include "logica.h"
#include "interfaz.h"
#include "audio.h"
#pragma comment(lib, "winmm.lib")

using namespace std;
int j1=0, j2=0;

void jvsj() {
    int fila = 0, columna = 0;
    bool juegoTerminado = false;
    gotoxy (1,1);cout << "1.Modo Jugador 1 vs Jugador 2.";
    gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<j1<<endl;
    gotoxy (92,7);cout<<"Victorias Jugador 2: "<<j2<<endl;
    
    playBackgroundMusic("musicatablero.wav");
 
    
    while (!juegoTerminado) {
    	
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
                    char simbolo = turnoJugador1 ? 'X' : 'O';
                    matrizJuego[fila][columna] = simbolo;
                    dibujarSimbolo(fila, columna, simbolo);

                    if (hayGanador()) {
                        gotoxy(35, 28);
                        poner_color(9);
                        cout << (turnoJugador1 ? "Jugador 1 (X) gana!" : "Jugador 2 (O) gana!");
                        pauseBackgroundMusic();
                        playEffect("victoria.wav");
                        if (turnoJugador1){
                            j1++;
                        }else{
                            j2++;
                        }
                        gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<j1<<endl;
                        gotoxy (92,7);cout<<"Victorias Jugador 2: "<<j2<<endl;
                        getch();
                        juegoTerminado = true;
                    } else if (hayEmpate()) {
                        gotoxy(41, 28);
                        cout << "Empate!";
                        getch();
                        juegoTerminado = true;
                    }
                    turnoJugador1 = !turnoJugador1;
                }
            }
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
        jvsj();
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