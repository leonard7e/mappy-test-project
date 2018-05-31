#ifndef SPIELFELD_HEADER
#define SPIELFELD_HEADER
struct SpielFeld {
    unsigned int breite, hoehe;
    unsigned int einstieg_x, einstieg_y;
    unsigned int *terrain_buffer;
};

struct SpielFeld *lade_spielfeld (char *dateiname);
void spielfeld_anzeigen (struct SpielFeld *sfeld);
void loesche_spielfeld (struct SpielFeld *sfeld);
#endif
