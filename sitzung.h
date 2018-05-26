#ifndef SITZUNG_Header
#define SITZUNG_Header

struct Sitzung {
    struct SpielFeld *sfeld;
    unsigned int pos_x, pos_y; // Position des Spielers
};

enum Richtung {
    Rauf,
    Rechts,
    Runter,
    Links
};

struct Sitzung *neue_sitzung(char *spielfeld_name);
void beende_sitzung(struct Sitzung *sitzung);


void sitzung_drucken (struct Sitzung *sitzung);
void bewege_schritt (struct Sitzung *s, enum Richtung r);


#endif
