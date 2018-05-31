#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "sitzung.h"
#include "spielfeld.h"

void richtungsvektor(enum Richtung r, int *dx, int *dy) {
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

bool begehbar(unsigned int z) {
    switch (z) {
        case '.':
            return true;
        default:
            return false;
    }
}

bool feld_begehbar(struct Sitzung *s, unsigned int px, unsigned int py) {
    unsigned int *b = s->sfeld->terrain_buffer;
    unsigned int p = s->sfeld->w * py + px;
    return begehbar(*(b + p));
}

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

//
void feldcode_drucken(unsigned int z) {
    putchar(z);
}

void sitzung_drucken (struct Sitzung *sitzung) {
    struct SpielFeld *sfeld = sitzung->sfeld;
    unsigned int *feldeintrag = sfeld->terrain_buffer;

    //
    for(int y=0; y<sfeld->h; y++) {
        for(int x=0; x<sfeld->w; x++) {
            if (x == sitzung->pos_x && y == sitzung->pos_y){
                putchar('O');
            } else {
                feldcode_drucken(*feldeintrag);
            }
            feldeintrag ++;
        }
        printf("\n");
    }
}

struct Sitzung *neue_sitzung(char *spielfeld_name) {
    struct Sitzung *sitzung = malloc(sizeof(struct Sitzung));
    sitzung->sfeld = lade_spielfeld(spielfeld_name);
    sitzung->pos_x = sitzung->sfeld->einstieg_x;
    sitzung->pos_y = sitzung->sfeld->einstieg_y;
    return sitzung;
}

void beende_sitzung(struct Sitzung *sitzung) {
    loesche_spielfeld(sitzung->sfeld);
    free(sitzung);
}
