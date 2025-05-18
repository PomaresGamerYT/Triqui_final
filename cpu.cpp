#include <iostream>
#include <conio.h>       // Necesario para getch()
#include <windows.h>     // Necesario para Sleep(), system("cls")
#include <random>        // Para generación aleatoria mejorada
#include "cpu.h"
#include "gotoxy.h"
#include "logica.h"
#include "interfaz.h"

using namespace std;
int jug1=0, cpu_puntaje=0;
void cpu() {
    // Inicialización del generador aleatorio
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 2);

    int fila = 0, columna = 0;
    bool juegoTerminado = false;
    int movimientosCPU = 0;
    
    // El jugador siempre inicia (jugador 1 con 'X')
    turnoJugador1 = true;
    gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<jug1<<endl;
    gotoxy (92, 7);cout<<"Victorias CPU: "<<cpu_puntaje<<endl;
    // Bucle principal de partida
    while (!juegoTerminado) {
        if (turnoJugador1) {  
            // --- Turno del Jugador 1 (con 'X') ---
            // Se muestra la celda actual
            gotoxy(posiciones[fila][columna][0], posiciones[fila][columna][1]);
            cout << (matrizJuego[fila][columna] != ' ' ? matrizJuego[fila][columna] : ' ');
            cout.flush();
            
            if (kbhit()) {
                int tecla = getch();
                // Flechas para moverse
                if (tecla == 224) {
                    tecla = getch();
                    switch (tecla) {
                        case 72: if (fila > 0) fila--; break;
                        case 80: if (fila < 2) fila++; break;
                        case 75: if (columna > 0) columna--; break;
                        case 77: if (columna < 2) columna++; break;
                    }
                } else if (tecla == 13) {  // Enter para colocar ficha
                    if (matrizJuego[fila][columna] == ' ') {
                        matrizJuego[fila][columna] = 'X';
                        dibujarSimbolo(fila, columna, 'X');

                        // Verifica si ganó el jugador o hubo empate
                        if (hayGanador()) {
                            gotoxy(35, 28);
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
                        turnoJugador1 = false; // Pasa el turno a la CPU
                    }
                }
            }
        } else {
            // --- Turno de la CPU (con 'O') ---
            gotoxy(32, 28); cout << "Turno de la CPU...         ";
            Sleep(500);  // Pausa para simular proceso
            gotoxy(32, 28); cout << "                         "; //Espaciado para borrar el mensaje en cada turno
                        
            if (movimientosCPU < 2) {
                // Para las primeras dos jugadas, movimiento aleatorio
                do {
                    fila = dist(gen);
                    columna = dist(gen);
                } while (matrizJuego[fila][columna] != ' ');
            } else {
                // A partir de la tercera jugada, intenta buscar oportunidad de ganar
                bool movimientoEncontrado = false;
                int tempFila = -1, tempCol = -1;
                for (int i = 0; i < 3 && !movimientoEncontrado; i++) {
                    for (int j = 0; j < 3 && !movimientoEncontrado; j++) {
                        if (matrizJuego[i][j] == ' ') {
                            // Simula poner 'O' en esa posición
                            matrizJuego[i][j] = 'O';
                            if (hayGanador()) {
                                tempFila = i;
                                tempCol = j;
                                movimientoEncontrado = true;
                            }
                            matrizJuego[i][j] = ' '; // Revierte la simulación
                        }
                    }
                }
                if (movimientoEncontrado) {
                    fila = tempFila;
                    columna = tempCol;
                } else {
                    // Si no encontró oportunidad ganadora, elige al azar
                    do {
                        fila = dist(gen);
                        columna = dist(gen);
                    } while (matrizJuego[fila][columna] != ' ');
                }
            }
            // Realiza el movimiento de la CPU
            matrizJuego[fila][columna] = 'O';
            dibujarSimbolo(fila, columna, 'O');
            movimientosCPU++;
            
            // Verifica victoria o empate tras la jugada de la CPU
            if (hayGanador()) {
            	gotoxy(32, 28); cout << "                         ";
                gotoxy(38, 28);
                cout << "La CPU gana!";
                if (turnoJugador1==false){
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
            turnoJugador1 = true;  // Vuelve el turno al Jugador 1
        }
        Sleep(50);
    } // Fin del bucle principal

    // --- Preguntar si se desea iniciar una nueva partida ---
    char respuesta;
    gotoxy(26, 28); cout << "Desea iniciar una nueva partida? (S/N): ";
    cin >> respuesta;
    
    if (respuesta == 'S' || respuesta == 's') {
    	gotoxy(26, 28); cout << "                                         "; // Borra cualquier texto residual
        reiniciarTablero();
        cpu();      // Reinicia el modo CPU
    } else {
        system("cls");
        gotoxy (12,2); cout<<"Grupo Conformado por:"<<endl;
    	gotoxy (12,4); cout<<"Fabian Coronel Morato"<<endl;
    	gotoxy (12,6); cout<<"Andres Pomares Navarro"<<endl;
    	gotoxy (12,8); cout<<"Cesar Beltran Alvarado"<<endl;
    	gotoxy (12,10); cout<<"Isai Cabeza De la Hoz"<<endl;
    	gotoxy (12,12); cout<<"Clase: Programacion II"<<endl;
    	gotoxy (10,14); cout<<"Profesor: Tomas Campo Cadernas"<<endl;
    	gotoxy (6,16); cout<<"Institucion: Universidad del Magdalena"<<endl;
        gotoxy(15,18); cout << "Gracias por jugar!";
    }
}
