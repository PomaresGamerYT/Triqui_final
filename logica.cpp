#include "logica.h"
#include "gotoxy.h"
#include <iostream>

using namespace std;

char matrizJuego[3][3] = {
    {' ', ' ', ' '}, 
    {' ', ' ', ' '}, 
    {' ', ' ', ' '}
};

bool turnoJugador1 = true;

int posiciones[3][3][2] = {
    {{30,10}, {44,10}, {58,10}},
    {{30,16}, {44,16}, {58,16}},
    {{30,22}, {44,22}, {58,22}}
};

void dibujarX(int x, int y) {
    for(int i = 0; i < 5; i++) {
        gotoxy(x + i, y + i); cout << char(219);
        gotoxy(x + 4 - i, y + i); cout << char(219);
    }
}

void dibujarO(int x, int y) {
    for(int i = 0; i < 5; i++) {
        gotoxy(x, y + i); cout << char(219);
        gotoxy(x + 4, y + i); cout << char(219);
    }
    for(int i = 1; i < 4; i++) {
        gotoxy(x + i, y); cout << char(219);
        gotoxy(x + i, y + 4); cout << char(219);
    }
}

void dibujarLineaGanadora(int tipo, int posicion) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 13);
    switch(tipo) {
        case 1: // Horizontal
            for(int x = 24; x <= 63; x += 1) {
                gotoxy(x, posiciones[posicion][0][1] + 0); cout << char(219);
                Sleep(30);
            }
            break;
        case 2: // Vertical
            for(int y = 7; y <= 25; y += 1) {
                gotoxy(posiciones[0][posicion][0] + 0, y); cout << char(219);
                Sleep(30);
            }
            break;
        case 3: // Diagonal principal
            for (int i = 0; i < 19; i++) {
                gotoxy(26 + i * 2, 7 + i);
                cout << char(219) << char(219);
                Sleep(30);
            }
            break;
        case 4: // Diagonal secundaria
            for (int i = 0; i < 19; i++) {
                gotoxy(63 - i * 2, 7 + i);
                cout << char(219) << char(219);
                Sleep(30);
            }
            break;
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void dibujarSimbolo(int fila, int columna, char simbolo) {
    if (fila >= 0 && fila < 3 && columna >= 0 && columna < 3) {
        int x = posiciones[fila][columna][0] - 2;
        int y = posiciones[fila][columna][1] - 2;
    
        for(int i = 0; i < 5; i++) {
            for(int j = 0; j < 5; j++) {
                gotoxy(x + i, y + j);
                cout << ' ';
            }
        }
        
        if (simbolo == 'X') {
            dibujarX(x, y);
        } else if (simbolo == 'O') {
            dibujarO(x, y);
        }
    }
}

bool hayGanador() {
    for (int i = 0; i < 3; i++) {
        if (matrizJuego[i][0] != ' ' && 
            matrizJuego[i][0] == matrizJuego[i][1] && 
            matrizJuego[i][1] == matrizJuego[i][2]) {
            dibujarLineaGanadora(1, i);
            return true;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        if (matrizJuego[0][i] != ' ' && 
            matrizJuego[0][i] == matrizJuego[1][i] && 
            matrizJuego[1][i] == matrizJuego[2][i]) {
            dibujarLineaGanadora(2, i);
            return true;
        }
    }
    
    if (matrizJuego[0][0] != ' ' && 
        matrizJuego[0][0] == matrizJuego[1][1] && 
        matrizJuego[1][1] == matrizJuego[2][2]) {
        dibujarLineaGanadora(3, 0);
        return true;
    }
    
    if (matrizJuego[0][2] != ' ' && 
        matrizJuego[0][2] == matrizJuego[1][1] && 
        matrizJuego[1][1] == matrizJuego[2][0]) {
        dibujarLineaGanadora(4, 0);
        return true;
    }
    
    return false;
}

bool hayEmpate() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (matrizJuego[i][j] == ' ') return false;
    return true;
}

void reiniciarTablero() {
    system("cls");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            matrizJuego[i][j] = ' ';
        }
    }
    turnoJugador1 = true;
}