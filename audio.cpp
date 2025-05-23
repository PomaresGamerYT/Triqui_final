#include "audio.h"
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <digitalv.h>
#pragma comment(lib, "winmm.lib")

// Variable para controlar el estado de la música
static bool musicPaused = false;

void playEffect(const char* soundFile) {
    char command[128];
    sprintf(command, "play \"%s\" from 0", soundFile);
    mciSendString(command, NULL, 0, NULL);
}

void playBackgroundMusic(const char* musicFile) {
    char command[128];
    sprintf(command, "open \"%s\" type mpegvideo alias bgmusic", musicFile);
    mciSendString("close bgmusic", NULL, 0, NULL); // Cerrar cualquier instancia previa
    mciSendString(command, NULL, 0, NULL);
    mciSendString("play bgmusic repeat", NULL, 0, NULL);
    musicPaused = false;
}

void pauseBackgroundMusic() {
    mciSendString("pause bgmusic", NULL, 0, NULL);
    musicPaused = true;
}

void resumeBackgroundMusic() {
    mciSendString("resume bgmusic", NULL, 0, NULL);
    musicPaused = false;
}

void stopBackgroundMusic() {
    mciSendString("stop bgmusic", NULL, 0, NULL);
    mciSendString("close bgmusic", NULL, 0, NULL);
    musicPaused = false;
}

bool isBackgroundMusicPaused() {
    return musicPaused;
}