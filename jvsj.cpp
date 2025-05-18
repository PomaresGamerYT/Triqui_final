#include <iostream>
#include <conio.h> // Necesario para getch()
#include <windows.h> // Necesario para Sleep(), system("cls")
#include "jvsj.h"
#include "gotoxy.h"
#include "logica.h"
#include "interfaz.h"

using namespace std;
int j1=0, j2=0; //Declaracion de variables globales para evitar reinicio
// Gameplay de jugador contra jugador
void jvsj() {
// variables para la posicion
    int fila = 0, columna = 0;
    bool juegoTerminado = false;
// Inicio de juego, que se mantenga hasta que se sepa que se termino
    gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<j1<<endl;
    gotoxy (92,7);cout<<"Victorias Jugador 2: "<<j2<<endl;
    while (!juegoTerminado) {
        gotoxy(posiciones[fila][columna][0], posiciones[fila][columna][1]);
        cout << (matrizJuego[fila][columna] != ' ' ? matrizJuego[fila][columna] : ' '); 
        cout.flush();

        if (kbhit()) {
            int tecla = getch(); //saber que tecla presiona el usuario
            if (tecla == 224) { //movimiento con las flechas
                tecla = getch();
                switch (tecla) {
                    case 72: if (fila > 0) fila--; break;
                    case 80: if (fila < 2) fila++; break;
                    case 75: if (columna > 0) columna--; break;
                    case 77: if (columna < 2) columna++; break;
                }
            } else if (tecla == 13) { // presiono enter para colocar la pieza
                if (matrizJuego[fila][columna] == ' ') {
                    char simbolo = turnoJugador1 ? 'X' : 'O';
                    matrizJuego[fila][columna] = simbolo;
                    dibujarSimbolo(fila, columna, simbolo);
// proceso donde revisa si alguien gano o ya empataron
                    if (hayGanador()) {
                        gotoxy(35, 28);
                        cout << (turnoJugador1 ? "Jugador 1 (X) gana!" : "Jugador 2 (O) gana!");
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
// preguntar para jugar denuevo
    char respuesta;
    gotoxy(26, 28); cout << "Desea iniciar una nueva partida? (S/N): ";
    cin >> respuesta;
    if (respuesta == 'S' || respuesta == 's') {
    	gotoxy(26, 28); cout << "                                         ";
    	reiniciarTablero();
    	jvsj();
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
