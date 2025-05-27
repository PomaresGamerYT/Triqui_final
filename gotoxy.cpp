#include <windows.h>

void gotoxy(int x, int y) { //Funcion utilizada para hacer todo el diseño del juego usando caracteres ASCII
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}