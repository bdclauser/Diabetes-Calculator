//
// Created by Brian Clauser on 2018-12-06.
//

#ifndef DIABETES_DETECTION_GOTOXY_H
#define DIABETES_DETECTION_GOTOXY_H

#include <stdio.h>
#include <string.h>

using namespace std;


void gotoxy(int x, int y) {

    char essq[100];  /* String variable to hold the escape sequence */

    char xstr[100];  /* Strings to hold the x and y coordinates */

    char ystr[100];  /* Escape sequences must be built with characters */
    sprintf(xstr, "%d", x);

    sprintf(ystr, "%d", y);
    essq[0] = '\0';

    strcat(essq, "\033[");

    strcat(essq, ystr);
    strcat(essq, "d");
    strcat(essq, "\033[");

    strcat(essq, xstr);

    strcat(essq, "G");

    printf("%s", essq);

}

#endif //DIABETES_DETECTION_GOTOXY_H
