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


int main() {

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

    return 0;
}

void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

bool init() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
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
    }

}