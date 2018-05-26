#include "spielfeld.h"
#include <stdlib.h>
#include <stdio.h>

//
struct SpielFeld *lade_spielfeld (char *dateiname) {
    // Wir öffnen die Datei, die das Spielfeld beinhalten soll
    FILE *felddatei;
    felddatei = fopen(dateiname, "r");

    if (felddatei == NULL) {
        printf("Moment! Die Datei %s kann nicht geöffnet werden.", dateiname);
        exit(EXIT_FAILURE);
    }

    // Nun können wir den Inhalt der Datei lesen.
    size_t line_length = 0;
    ssize_t read_length = 0;
    char *line_string = NULL;

    // Die ersten beiden Zeilen werden gelesen.
    getline(&line_string, &line_length, felddatei);
    uint w=0;
    uint h=0;
    sscanf(line_string, "SpielFeld %d %d", &w, &h );

    getline(&line_string, &line_length, felddatei);
    uint p_x=0;
    uint p_y=0;
    sscanf(line_string, "Spieler %d %d", &p_x, &p_y );

    // Inhalt des Spielfelds wird geladen
    unsigned int *buffer = malloc(w*h*sizeof(uint));
    unsigned int *bcursor = buffer;

    while ((read_length = getline(&line_string, &line_length, felddatei)) != -1) {
        for (int i=0; i<read_length-1; i+=1) {
            *bcursor = line_string[i];
            bcursor ++;
        }
    }

    // Diese Beiden brauchen wir nicht mehr.
    bcursor = NULL;
    free(line_string);

    // Das Spielfeld kann zusammengesetzt werden.
    struct SpielFeld *newmap = malloc(sizeof(struct SpielFeld));
    newmap->w = w;
    newmap->h = h;
    newmap->einstieg_x = p_x;
    newmap->einstieg_y = p_y;
    newmap->buffer = buffer;
    return newmap;
}



void loesche_spielfeld (struct SpielFeld *sfeld) {
    free(sfeld->buffer);
    free(sfeld);
}
