#include "spielfeld.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/*
    Ein Spielfeld besteht aus einem Zeiger auf ein Terrain-terrain_buffer, einem Einstiegspunkt für den Spieler, und Informationen über Breite und Höhe des Terrain-Buffers.
    Spielfelder lassen sich lesen. Die Funktion, die dies für uns erledigt, ist lade_spielfeld. Mit lade_spielfeld wird ein Speicherbereich für ein Spielfeld und ein Terrain-Buffer alloziert. Nach der Benutzung des Spielfeldes müssen wir daher den Speicher wieder freigeben, um Memory-Leaks zu vermeiden. Das erledigt die Funktion loesche_spielfeld.

    Der Endbenutzer sollte mit der SpielFeld-Struktur keinen direkten Zugriff haben. Indirekt wird diese Struktur über die Struktur 'Sitzung' verwaltet und benutzt.
*/

struct SpielFeld *lade_spielfeld (
    char *dateiname // Name der Datei, aus der das Spielfeld geladen werden soll
) {
    /*
        Eine Spielfeld-Datei ist eine Textdatei, die aus drei Abschnitten besteht.
            Spielfeld <breite> <hoehe>
            Spieler <einstieg_x> <einstieg_y>
            <das Terrain>
        Beim Lesen der Datei lesen wir alle drei Abschnitte nacheinander.

        Am Anfang versuchen wir, die Datei im lese-Modus zu öffnen. Der File-Descriptor der Datei wird in
    */
    FILE *felddatei;
    /*
        festgehalten.
    */
    felddatei = fopen(dateiname, "r");

    if (felddatei == NULL) {
        printf("Moment! Die Datei %s kann nicht geöffnet werden.", dateiname);
        exit(EXIT_FAILURE);
    }

    /*
        Das Lesen der ersten beiden Abschnitte der Spielfeld-Datei geschieht Zeilenweise. Das Ende jeder Zeile wird von einem Zeilenumbruch festgelegt.
        Die erste Zeile beinhaltet den Abschnitt:
            Spielfeld <breite> <hoehe>
    */
    uint breite=0;
    uint hoehe=0;
    fscanf(felddatei, "SpielFeld %d %d\n", &breite, &hoehe );

    /*
        Der nächste Abschnitt wäre:
            Spieler <einstieg_x> <einstieg_y>
    */
    uint p_x=0;
    uint p_y=0;
    fscanf(felddatei, "Spieler %d %d\n", &p_x, &p_y );

    /*
        Zum letzten Abschnitt. Der Inhalt des Terrain-Buffers wird geladen.

        Die Addresse des Terrain-Buffers wird durch
    */
    unsigned int *terrain_buffer = malloc(breite*hoehe*sizeof(uint));
    /*
        festgehalten. Beim Zugreifen und Verändern des Terrain-Buffers wird die Variable terrain_buffer allerdings nicht verändert. Für Veränderungen am Buffer führen wir die Variable bcursor ein.
    */
    unsigned int *bcursor = terrain_buffer;

    /*
        Wir sind soweit, daß wir den Terrain-Buffer lesen können. Die Variable ...
    */
    char terrain;
    /*
        wird benutzt, um gelesene Terraininformationen abzuspeichern.
    */
    while ((terrain = fgetc(felddatei)) != -1) {
        /*
            Das Terrain-Buffer wird Zeichen für Zeichen gelesen. Dabei werden Leerzeichen ignoriert.
        */
        if ( !isspace(terrain) ) {
            *bcursor = terrain;
            bcursor ++; // Den bcursor um ein Feld verschieben.
        }
    }

    // Diese Beiden brauchen wir nicht mehr.
    bcursor = NULL;

    /*
        Nun haben wir alles, was wir für die Zusammensetzung der Struktur SpielFeld brauchen. Wir können sie zusammengeseten.
    */
    struct SpielFeld *newmap = malloc(sizeof(struct SpielFeld));
    newmap->breite = breite;
    newmap->hoehe = hoehe;
    newmap->einstieg_x = p_x;
    newmap->einstieg_y = p_y;
    newmap->terrain_buffer = terrain_buffer;
    return newmap;
}

/*
    Befreien des Speicherbereichs, der durch lade_spielfeld alloziert wurde.
*/
void loesche_spielfeld (struct SpielFeld *sfeld) {
    free(sfeld->terrain_buffer);
    free(sfeld);
}
