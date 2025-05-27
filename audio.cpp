#include "audio.h"
#include <iostream>
#include <windows.h> //Biblioteca para las funciones del sistema 
#include <mmsystem.h> //Biblioteca para funciones de multimedia (Audio)
#include <digitalv.h>
#pragma comment(lib, "winmm.lib") //Enlace con la libreria winmm.lib y trabajar con el audio

// Variable para controlar el estado de la música
static bool musicPaused = false;

//Para efectos que solo se reproduciran una vez
void playEffect(const char* soundFile) {
    char command[128];
    sprintf(command, "play \"%s\" from 0", soundFile);
    mciSendString(command, NULL, 0, NULL);
}
//Reproducir musica de fondo en bucle
void playBackgroundMusic(const char* musicFile) {
    char command[128];
    sprintf(command, "open \"%s\" type mpegvideo alias bgmusic", musicFile);
    mciSendString("close bgmusic", NULL, 0, NULL); // Cerrar cualquier instancia previa
    mciSendString(command, NULL, 0, NULL);
    mciSendString("play bgmusic repeat", NULL, 0, NULL);
    musicPaused = false;
}
//Pausar la musica de fondo
void pauseBackgroundMusic() {
    mciSendString("pause bgmusic", NULL, 0, NULL);
    musicPaused = true;
}
//Resumir musica de fondo
void resumeBackgroundMusic() {
    mciSendString("resume bgmusic", NULL, 0, NULL);
    musicPaused = false;
}
//Detener musica de fondo
void stopBackgroundMusic() {
    mciSendString("stop bgmusic", NULL, 0, NULL);
    mciSendString("close bgmusic", NULL, 0, NULL);
    musicPaused = false;
}
//Verifica que la musica este pausada
bool isBackgroundMusicPaused() {
    return musicPaused;
}