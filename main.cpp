//
// Created by Brian Clauser on 2018-12-06.
//

#include "diabetes.h"
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <ncurses.h>
#include <SDL.h>
#include <SDL_audio.h>
#include <string>
#include "SDL_mixer.h"


bool init();

bool loadAudio();

void close();

int main() {

    Mix_Chunk *gScratch = NULL;
    Mix_Chunk *gHigh = NULL;
    Mix_Chunk *gMedium = NULL;
    Mix_Chunk *gLow = NULL;

    char ch, choice, cho;
    //int m,n=2;
    float m;
    int n = 1;
    void diagnosis(void);
    diabetes dts;
    dts.welcome_screen();
    dts.getvalue();
    diagnosis();
    dts.getlevel1_symptoms();
    m = dts.analyse_symptoms(n);
    choice = dts.display_message(m, n);
    choice = toupper(choice);

    if (choice == 'Y') {
        ++n;
        dts.getlevel2_symptoms();
        m = dts.analyse_symptoms(n);
        choice = dts.display_message(n, m);
        choice = toupper(choice);

        if (choice == 'Y') {
            ++n;
            dts.getlevel3_symptoms();
            m = dts.analyse_symptoms(n);
            choice = dts.display_message(n, m);
            cho = toupper(cho);
            if (cho == 'Y') {
                dts.getlevel3_symptoms();
                m = dts.analyse_symptoms(n);
                choice = dts.display_message(m, n);
            }
        }
    }

    if (!init() ){
        printf("Failed to initilize!\n");
    } else{
        bool quit = false;
        SDL_Event e;

        while (!quit) {
            while(SDL_PollEvent(&e) != 0){
                if (e.type == SDL_Quit){
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN){
                    switch(e.key.keysym.sym){
                        case SDLK_1:
                            Mix_PlayChannel(-1, gHigh, 0);
                            break;
                        case SDLK_2:
                            Mix_PlayChannel(-1, gMedium, 0);
                            break;
                        case SDLK_3:
                            Mix_PlayChannel(-1, gLow, 0);
                            break;
                        case SDLK_4:
                            Mix_PlayChannel(-1, gScratch, 0);
                            break;
                    }
                }
            }
        }
    }
    close();
    return 0;
}

void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}


bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}

bool loadAudio() {
    bool success = true;

    // Load sound effects
    gScratch = Mix_LoadWAV ("21_sound_effects_and_music/scratch.wav");
    if (gScratch == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gHigh = Mix_LoadWAV ("21_sound_effects_and_music/scratch.wav");
    if (gHigh == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gMedium = Mix_LoadWAV ("21_sound_effects_and_music/scratch.wav");
    if (gMedium == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gLow = Mix_LoadWAV ("21_sound_effects_and_music/scratch.wav");
    if (gLow == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}

void close(){
Mix_FreeChunk(gScrath);
Mix_FreeChunk(gHigh);
Mix_FreeChunk(gMedium);
Mix_FreeChunk(gLox);
gScratch = NULL;
gHigh = NULL;
gMedium = NULL;
gLow = NULL;

Mix_Quit();

SDL_Quit();
}

void diabetes::welcome_screen() {
    clear();
    gotoxy(23, 7);
    puts("********** W E L C O M E ********** ");
    gotoxy(25, 9);
    puts(" ");
    gotoxy(18, 12);
    puts(" M E D I C A L  D I A G N O S I S  S O F T W A R E  ");
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    for (int x = 50; x >= 22; x--) {
        sound(2000);
        delay(120);
        nosound();
        gotoxy(x, 14);
        puts("D O N E  B Y :");
        gotoxy(x, 16);
        puts("Brian D Clauser ");
        gotoxy(43, 18);

    }

    gotoxy(17, 25);
    puts("********** PRESS ANY KEY TO CONTINUE **********");
    getch();
    return;

}