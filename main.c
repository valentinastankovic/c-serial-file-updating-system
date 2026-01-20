#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "adts.h"
#include "util.h"
#include "misc.h"


int main(int argc, char* argv[]) {
    // 1. Inicijalizacija sistemskih parametara (datum)
    inicijalizuj_datum();

    // 2. Prikaz zaglavlja (onaj uokvireni tekst sa zvezdicama)
    prikazi_zaglavlje();

    // 3. Obrada argumenata komandne linije (ako se pokrene npr: asd.exe -d1)
    if (argc > 1) {
        if (strncmp(argv[1], "-d", 2) == 0) {
            // Uzimamo broj nakon "-d" (npr. iz "-d1" uzimamo '1')
            char opcija = argv[1][2];

            printf("\n[SISTEM] Pokretanje demo scenarija %c direktno...\n", opcija);

            switch (opcija) {
            case '1':
                create_maticna();
                create_transakciona();
                sumiraj_i_sortiraj_transakcije();
                printf("Scenario 1 (Osnovni) je pripremljen.\n");
                break;
            case '2':
                create_maticna();
                kreiraj_transakcije_scenario2();
                printf("Scenario 2 (Greska kolicine) je pripremljen.\n");
                break;
            case '3':
                create_maticna();
                kreiraj_transakcije_scenario3();
                printf("Scenario 3 (Novi proizvod) je pripremljen.\n");
                break;
            case '4':
                //kreiraj_demo_podatke_slucaj1();
                kreiraj_transakcije_scenario4();
                printf("Scenario 4 (Nepostojeci proizvod) je pripremljen.\n");
                break;
            case '5':
                popuni_maticnu_demo_osnovni(); // Prvo napuni bazu proizvodima (ID 20, 30, 40...)
                pripremi_demo_podatke_slucaj_5(); // Ova funkcija koju smo sredili stavlja fajl u DATA
                printf("Scenario 5 (Sveobuhvatno) je pripremljen u radnom folderu.\n");
                break;
            default:
                printf("[Greska] Nepoznat demo scenario: %s\n", argv[1]);
                break;
            }
        }
    }

    // 4. Pokretanje interaktivnog menija
    glavni_meni();

    return 0;
}