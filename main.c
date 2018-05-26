#include <stdio.h>
#include "spielfeld.h"
#include "sitzung.h"

int main(int argc, char const *argv[]) {
    struct Sitzung *sitzung = neue_sitzung("ein_spielfeld.txt");
    // struct SpielFeld *sfeld = lade_spielfeld("test.txt");

    printf("\n");
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Rauf);

    printf("\n");
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Runter);

    printf("\n");
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Runter);

    printf("\n");
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Runter);

    printf("\n");
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Runter);

    printf("\n");
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Rechts);

    printf("\n");
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Rechts);

    beende_sitzung(sitzung);
    return 0;
}
