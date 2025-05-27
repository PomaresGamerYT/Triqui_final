#include <iostream>
#include <conio.h>
#include "jvsj.h"
#include "gotoxy.h"
#include "logica.h"
#include "interfaz.h"
#include "audio.h"
#pragma comment(lib, "winmm.lib")

using namespace std;
int j1=0, j2=0; //Contadores para victorias

void jvsj() {
    int fila = 0, columna = 0;
    bool juegoTerminado = false; //En falso para indicar que no ha terminado y esta en curso
    gotoxy (1,1);cout << "1.Modo Jugador 1 vs Jugador 2."; //Se imprime mensaje del modo en el que se esta
    gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<j1<<endl; //Mensaje para contador de jugador 1
    gotoxy (92,7);cout<<"Victorias Jugador 2: "<<j2<<endl; //Mensaje para contador de jugador 2
    
    playBackgroundMusic("musicatablero.wav"); //Se reproduce la musica de la partida
 
    
    while (!juegoTerminado) { //Si el juego esta en progreso y no ha terminado
    	
        gotoxy(posiciones[fila][columna][0], posiciones[fila][columna][1]); //Posiciona al jugador en las coordenadas x/y de cada casilla

        if (kbhit()) { //Se detecta si se presiono una tecla
            int tecla = getch(); //Lee las teclas presionadas
            if (tecla == 224) { //Codigo especial de las flechas
                tecla = getch();
                switch (tecla) { //Maneja el movimiento del jugador
                    case 72: if (fila > 0) fila--; break; //Movimiento con flecha hacia arriba
                    case 80: if (fila < 2) fila++; break; //Movimiento con flecha hacia abajo 
                    case 75: if (columna > 0) columna--; break; //Movimiento con flecha hacia la izquierda
                    case 77: if (columna < 2) columna++; break; //Movimiento con flecha hacia la derecha
                }
            } else if (tecla == 13) { //Si la tecla es enter para colocar "X" u "O"
                if (matrizJuego[fila][columna] == ' ') { //Si la celda esta vacia
                	playEffect("sonidoboton.wav"); //Reproduce el sonido al colocar
                    char simbolo = turnoJugador1 ? 'X' : 'O'; //Se marca con "X" u "O" dependiendo de la intercalacion del turno
                    matrizJuego[fila][columna] = simbolo;  //Se guarda el simbolo para ser utilizado en la funcion y dibujar posteriormente
                    dibujarSimbolo(fila, columna, simbolo); //Se dibuja el simbolo

                    if (hayGanador()) { //Si gana el jugador 1 o 2
                        gotoxy(35, 28); //Coordenada donde se imprime el mensaje
                        poner_color(9);
                        cout << (turnoJugador1 ? "Jugador 1 (X) gana!" : "Jugador 2 (O) gana!"); //A partir del ganador dado por la ultima intercalacion se imprime el mensaje
                        pauseBackgroundMusic(); //Se pausa la musica para poner el sonido de victoria
                        playEffect("victoria.wav"); //Se reproduce el mensaje
                        if (turnoJugador1){ //Si se gano al momento de que fue turno del jugador 1
                            j1++; //Se le suma una victoria al jugador 1
                        }else{
                            j2++; //Se le suma una victoria al jugador 2 
                        }
                        gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<j1<<endl; //Se actualiza el mensaje de las victorias del jugador 1
                        gotoxy (92,7);cout<<"Victorias Jugador 2: "<<j2<<endl; //Se actualiza el mensaje de las victorias del jugador 2
                        getch();
                        juegoTerminado = true; //Se acaba el juego
                    } else if (hayEmpate()) { //Si hay empate
                        gotoxy(41, 28); //Coordenada donde se imprime el mensaje
                        cout << "Empate!"; //Se imprime el mensaje
                        getch();
                        juegoTerminado = true; //Se finaliza el juego
                    }
                    turnoJugador1 = !turnoJugador1; //Alterna el turno entre jugador 1 (X) y jugador 2 (O)
                }
            }
        }
        Sleep(50); //Para que no sean tan inmediatas las acciones
    }
    
    mciSendString("close all", NULL, 0, NULL); //Se detiene todo audio

    char respuesta; //Se crea variable para la respuesta
    gotoxy(26, 28); cout << "Desea iniciar una nueva partida? (S/N): "; //Se le pregunta al jugador si desea continuar
    cin >> respuesta;
    if (respuesta == 'S' || respuesta == 's') { //Si su respuesta es si
    	playEffect("sonidoboton.wav"); //Se reproduce sonido al haber seleccionado
        gotoxy(26, 28); cout << "                                         "; //Se borra el mensaje anterior
        reiniciarTablero(); //Se reinicia el tablero
        tablero(); //Se llama de nuevo a la funcion para iniciar un nuevo juego
        jvsj(); //Se llama a logica del modo de juego
    } else {
    	playEffect("sonidoboton.wav"); //Se reproduce sonido al haber seleccionado
        system("cls"); //Se borra todo y se muestran los creditos
        gotoxy (12,4); cout<<"Grupo Conformado por:"<<endl;
        gotoxy (12,6); cout<<"1. Fabian Coronel Morato"<<endl;
        gotoxy (12,8); cout<<"2. Andres Pomares Navarro"<<endl;
        gotoxy (12,10); cout<<"3. Cesar Beltran Alvarado"<<endl;
        gotoxy (12,12); cout<<"Clase: Programacion II"<<endl;
        gotoxy (10,14); cout<<"Profesor: Tomas Campo Cadernas"<<endl;
        gotoxy (6,16); cout<<"Institucion: Universidad del Magdalena"<<endl;
        gotoxy(15,18); cout << "Gracias por jugar!";
    }
}