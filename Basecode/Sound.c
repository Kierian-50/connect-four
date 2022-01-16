//
// Created by mateo on 16/01/2022.
//

#include "Sound.h"

/**
 * This function allow to play music theme in loop
 * @return @void
 */
void* loopMusicTheme() {
    while (1)
        playMusic(MUSIC_THEME_PATH);
}

/**
 * Allows to play winner's music
 * @return @void
 */
void* playWinMusic() {
    playMusic(WIN_MUSIC_PATH);
    SDL_Quit();
}

/**
 * Allows to play loser's music
 * @return @void
 */
void* playLoseMusic() {
    playMusic(LOSE_MUSIC_PATH);
    SDL_Quit();
}

/**
 * This function allows to play a music once
 * @param musicPath path of the music file to play
 * @return exit status
 */
int playMusic(char* musicPath) {

    if (SDL_Init(SDL_INIT_AUDIO) < 0)
        exit(1);

    // length of sample, buffer of audio file and specs of this audio
    static Uint32 wav_length;
    static Uint8 *wav_buffer;
    static SDL_AudioSpec wav_spec;

    /* Load the WAV */
    if (SDL_LoadWAV(musicPath, &wav_spec, &wav_buffer, &wav_length) == NULL)
        exit(1);

    // set the callback function, copy buffer and copy file length
    wav_spec.callback = audioCallback;
    wav_spec.userdata = NULL;
    audio_pos = wav_buffer;
    audio_len = wav_length;

    if (SDL_OpenAudio(&wav_spec, NULL) != 0)
        printf("Erreur : %s\n", SDL_GetError());

    // play until we have finished the sound
    SDL_PauseAudio(0);
    while (audio_len > 0)
        SDL_Delay(100);

    // clear buffer when sound is finished
    SDL_CloseAudio();
    SDL_FreeWAV(wav_buffer);

    return 1;
}

/**
 * This function allows to stream defined length of music buffer to audio device
 * @param stream stream output
 * @param len length of the music to copy
 */
void audioCallback(void *userdata, Uint8 *stream, int len) {

    if (audio_len ==0)
        return;

    len = len > audio_len ? audio_len : len;
    // copy from buffer to stream
    SDL_memcpy (stream, audio_pos, len);

    audio_pos += len;
    audio_len -= len;
}
