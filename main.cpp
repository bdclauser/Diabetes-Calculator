//
// Created by Brian Clauser on 2018-12-06.
//

#include "diabetes.h"
#include <iostream>
#include "ncurses.h"
#include <SDL.h>
#include <SDL_audio.h>
#include <string>
#include "SDL_mixer.h"
#include "rlutil.h"

using namespace std;

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

    if (!init()) {
        printf("Failed to initialize!\n");
    } else {
        bool quit = false;
        SDL_Event e;

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_Quit) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
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

void close() {
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
        loadAudio();
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

void diabetes::getvalue() {
    clear();
    setColor(rlutil::WHITE);
    gotoxy(20, 8);
    puts("P E R S O N A L  I N F O R M A T I O N");
    gotoxy(25, 10);
    puts("N A M E: ");
    gotoxy(25, 12);
    puts("A G E: ");
    gotoxy(25, 14);
    puts("W E I G H T:");
    gotoxy(25, 16);
    puts("H E I G H T:");
    gotoxy(25, 18);
    puts("S E X (M/F) : ");
    setColor(rlutil::WHITE);
    gotoxy(42, 10);
    gets(name);
    gotoxy(42, 12);
    cin >> age;
    gotoxy(42, 14);
    cin >> wt;
    gotoxy(42, 16);
    cin >> ht;
    gotoxy(42, 18);
    cin >> sex;
    getch();
    return;
}

void diagnosis(void) {
    clear();
    setColor(rlutil::WHITE);
    gotoxy(20, 5);
    puts(" **  D I A G N O S I S  W I N D O W **  ");
    cout << "\n\n\n";
    puts(" Let's have a look at symptoms...........");
    cout << "\n\n\n";
    puts(" Please enter the form in the next page .");
    cout << "\n\n\n\n\n\n\t\t\t ";
    setColor(rlutil::YELLOW);
    puts("***** PRESS ANY KEY ***** ");
    getch();
}

void diabetes::getlevel1_symptoms(void) {
    clear();
    int i = 0;
    gotoxy(23, 3);
    setColor(rlutil::WHITE);
    puts(" *** MEDICAL DIAGNOSIS FORM ***");
    gotoxy(3, 6);
    puts("APPETITE (H(HIGH),/L(LOW),/N(NORMAL):");
    gotoxy(64, 6);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
    gotoxy(3, 8);
    puts("FREQUENCY OF THIRST(H(HIGH),/L(LOW),/N(NORMAL):");
    gotoxy(64, 8);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
    gotoxy(3, 10);
    puts("FREQUENCY OF URINATION(H(HIGH),/L(LOW),/N(NORMAL):");
    gotoxy(64, 10);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
    gotoxy(3, 12);
    puts("VISION (I(IMPAIRMENT),/N(NORMAL)");
    gotoxy(64, 12);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
    gotoxy(3, 14);
    puts("URINE SUGAR (P(PASSIVE),/A(ACTIVE);");
    gotoxy(64, 14);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
    gotoxy(3, 16);
    puts("KETONUREA(P(PASSIVE),/A(ACTIVE)");
    gotoxy(64, 16);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
    gotoxy(3, 18);
    puts("FASTING BLOOD SUGAR(H(HIGH)/L(LOW)/N(NOMAL)");
    gotoxy(64, 18);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
    gotoxy(3, 20);
    puts("R B S (H(HIGH)/L(LOW)/N(NORMAL)");
    gotoxy(64, 20);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
    gotoxy(3, 22);
    puts("FAMILY HISTORY OF DIABETES(P(PASSIVE)/A(ACTIVE)");
    gotoxy(64, 22);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
    gotoxy(3, 24);
    puts("OGTT(D/N)");
    gotoxy(64, 24);
    cin >> s[i];
    s[i] = toupper(s[i]);
    ++i;
}

int diabetes::analyse_symptoms(int n) {
    int i = 0;
    int count = 0;
    int result = 0;

    switch (n) {
        case 1:
            if (s[9] == 'D')
                result = -1;
            else if (s[5] == 'P' && s[6] == 'P' && s[7] == 'H')
                result = -1;
            else {
                for (i = 0; i < 10; i++) {
                    if (s[i] == 'H' || s[i] == 'P' || s[i] == 'D' || s[i] == 'I')
                        count++;
                }
                if (count > 5)
                    result = -1;
            }
            break;

        case 2:
            if ((s[0] == 'P') || (s[1] == 'P') || (s[2] == 'P') || (s[3] == 'H') || (s[4] == 'P') || (s[5] == 'P') ||
                (s[6] == 'P'))
                result = -1;
            else
                result = 0;
            break;
        case 3:
            if ((s[0] == 'Y') && (s[1] == 'N') && (s[2] == 'W') && (s[3] == 'P') && (s[4] == 'P') ||

                (s[0] == 'Y') && (s[1] == 'B') && (s[2] == 'W') && (s[3] == 'P') && (s[4] == 'P') ||

                (s[0] == 'Y') && (s[1] == 'N') && (s[2] == 'M') && (s[3] == 'P') && (s[4] == 'P') ||

                (s[0] == 'Y') && (s[1] == 'N') && (s[2] == 'Y') && (s[3] == 'P') && (s[4] == 'P'))
                result = 0;
            else
                result = -1;
            break;
        default:
            break;
    }
    return (result);
}

