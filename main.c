#include <stdio.h>
#include <curses.h>
#include "spielfeld.h"
#include "sitzung.h"

void begin_game( void ) {
    // Curses initialisieren und einrichten
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}

void end_game( void ) {
    // Curses beenden.
    endwin();
}

void eingabe_schleife (struct Sitzung *sitzung) {
    /*
        Die Sitzung drucken wir gleich zu Beginn, damit der Benutzer die sitzung sehen kann, bevor er eine Eingabe mit dem Keyboard tätigt.
    */
    sitzung_drucken(sitzung);

    /*
        Die Eingabeschleife behandelt Benutzereingaben, und fürt gegebenfalls Aktionen aus.
    */
    bool weiter = TRUE;
    while (weiter) {
        int ch = getch();
        switch (ch) {
        case KEY_UP:
            bewege_schritt(sitzung, Rauf);
            break;
        case KEY_DOWN:
            bewege_schritt(sitzung, Runter);
            break;
        case KEY_LEFT:
            bewege_schritt(sitzung, Links);
            break;
        case KEY_RIGHT:
            bewege_schritt(sitzung, Rechts);
            break;
        case 'q':
            weiter = FALSE;
            break;
        }
        sitzung_drucken(sitzung);
    }
}

int main(int argc, char const *argv[]) {
    begin_game();

    struct Sitzung *sitzung = neue_sitzung("ein_spielfeld.txt");
    // struct SpielFeld *sfeld = lade_spielfeld("test.txt");

    eingabe_schleife(sitzung);
    beende_sitzung(sitzung);
    end_game();
    return 0;
}
