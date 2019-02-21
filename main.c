#include <stdio.h>
#include <curses.h>
#include "spielfeld.h"
#include "sitzung.h"

void begin_game( void ) {
    // Curses initialisieren und einrichten
    initscr();
    cbreak();
    noecho();
}

void end_game( void ) {
    // Curses beenden.
    endwin();
}

int main(int argc, char const *argv[]) {
    begin_game();

    struct Sitzung *sitzung = neue_sitzung("ein_spielfeld.txt");
    // struct SpielFeld *sfeld = lade_spielfeld("test.txt");

    getch();
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Runter);

    getch();
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Runter);

    getch();
    sitzung_drucken(sitzung);
    bewege_schritt(sitzung, Rechts);

    getch();
    beende_sitzung(sitzung);
    end_game();
    return 0;
}
