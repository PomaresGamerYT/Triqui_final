#ifndef AUDIO_H
#define AUDIO_H

// Reproducir efecto de sonido (se detiene solo)
void playEffect(const char* soundFile);

// Control de música de fondo
void playBackgroundMusic(const char* musicFile);
void pauseBackgroundMusic();
void resumeBackgroundMusic();
void stopBackgroundMusic();


#endif