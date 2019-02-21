#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <curses.h>

#include "sitzung.h"
#include "spielfeld.h"

/*
    Die Sitzung besteht aus einem Link zu einer SpielFeld-Struktur, und der aktuellen Position des Spielers.

    Ähnlich wie eine SpielFeld-Struktur wird eine Sitzung alloziert. Dafür ist die Prozedur neue_sitzung vorgesehen. Nach Benutzung der Sitzung sollte ihr Speicher mit beende_sitzung befreit werden.
*/

struct Sitzung *neue_sitzung(char *spielfeld_name) {
    struct Sitzung *sitzung = malloc(sizeof(struct Sitzung));
    sitzung->sfeld = lade_spielfeld(spielfeld_name);
    sitzung->pos_x = sitzung->sfeld->einstieg_x;
    sitzung->pos_y = sitzung->sfeld->einstieg_y;

    // Curses einrichten.
    clear();
    return sitzung;
}

void beende_sitzung(struct Sitzung *sitzung) {
    loesche_spielfeld(sitzung->sfeld);
    free(sitzung);
}

/*
    Innerhalb einer Situng können wir einen Spieler entlang einer Richtung bewegen. Die Richtung wird  definiert über
        enum Richtung {
            Rauf,
            Rechts,
            Runter,
            Links
        };
*/

void richtungsvektor(enum Richtung r, int *dx, int *dy) {
    /*
        Umwandlung einer Richtungsbeschreibung (enum Richtung r) in einen zweidimensionalen Vektor.
    */
    switch (r) {
        case Rauf:
            *dx=0;
            *dy=-1;
            break;
        case Rechts:
            *dx=1;
            *dy=0;
            break;
        case Runter:
            *dx=0;
            *dy=1;
            break;
        case Links:
            *dx=-1;
            *dy=0;
            break;
    }
}

/*
    Verschiedene Felder, auf denen sich der Spieler hinzubewegt, sind verschieden begehbar. Es gibt also begehbares und unwegsames Gelände.
*/

bool begehbar(unsigned int z) {
    /*
        Ist das Terrain begehbar, dessen Terrain-Code in der Variablen 'z' gespeichert ist?
    */
    switch (z) {
        case '.':
            return true;
        default:
            return false;
    }
}

bool feld_begehbar(struct Sitzung *s, unsigned int px, unsigned int py) {
    /*
        Die Begehbarkeit eines spezifischen Feldes in einem SpielFeld prüfen.
    */
    unsigned int *b = s->sfeld->terrain_buffer;
    unsigned int p = s->sfeld->breite * py + px;
    return begehbar(*(b + p));
}


/*
    Mit Hilfe von feld_begehbar können wir eine Funktion bewege_schritt definieren. Der Aufruf von bewege_schritt soll den Spieler einer Sitzung nach einer Richtungsbeschreibung (enum Richtung) bewegen.
    Ist das Terrain des Feldes in der gewünschten Richtung begehbar, wird die Position des Spielers innerhalb der Sitzung angepasst. Ist jenes Terrain unbegehbar, wird eine entsprechende Meldung angezeigt.
*/

void bewege_schritt (struct Sitzung *s, enum Richtung r) {
    int dx, dy;
    richtungsvektor(r, &dx, &dy);

    unsigned int p_x = s->pos_x + dx;
    unsigned int p_y = s->pos_y + dy;

    if (feld_begehbar(s, p_x, p_y)) {
        s->pos_x = p_x;
        s->pos_y = p_y;
    } else {
        printf( "Hoppla!\nDu bist vor die Wand gerannt. Passiert jedem mal.\n");
    }
}

/*
    Wir kommen zur Visualisation einer Session.
*/


void feldcode_drucken(unsigned int z, int y, int x) {
    /*
        Das Terrain von jenem Feldcode auf dem Bildschirm anzeigen. In diesem Fall ist es einfach die Variable 'z' als Charakter, wie er im Commandline-Interface der Console zu sehen ist.
    */
    mvaddch(y,x,z);
}


void sitzung_drucken (struct Sitzung *sitzung) {
    /*
        Die Sitzung visualisieren.
    */
    struct SpielFeld *sfeld = sitzung->sfeld;
    unsigned int *feldeintrag = sfeld->terrain_buffer;

    //
    for(int y=0; y<sfeld->hoehe; y++) {
        for(int x=0; x<sfeld->breite; x++) {
            if (x == sitzung->pos_x && y == sitzung->pos_y){
                mvaddch(y,x,'O');
            } else {
                feldcode_drucken(*feldeintrag, y, x);
            }
            feldeintrag ++;
        }
        printf("\n");
    }

    // NCurses bescheid geben, daß eine Änderung gerendert werden soll.
    refresh();
}
