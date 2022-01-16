//
// Created by mateo on 16/01/2022.
//

#include <SDL.h>

#define MUSIC_THEME_PATH "../sounds/zen_japan.wav"

/**
 * This function allow to play music theme in loop
 * @return @void
 */
void* loopMusicTheme();

/**
 * This function allows to play a music once
 * @param musicPath path of the music file to play
 * @return exit status
 */
int playMusic(char* musicPath);

/**
 * This function allows to stream defined length of music buffer to audio device
 * @param stream stream output
 * @param len length of the music to copy
 */
void audioCallback(void *userdata, Uint8 *stream, int len);

// global pointer to the audio buffer to be played
Uint8 *audio_pos;
// remaining length of the sample we have to play
Uint32 audio_len;
