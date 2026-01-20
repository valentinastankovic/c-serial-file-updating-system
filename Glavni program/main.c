#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "util.h"
#include "kki.h"
#include "datoteka.h"
#include "obrada.h"
#include "misc.h"

int main(int argc, char* argv[]) {

    inicijalizuj_datum();

    prikazi_zaglavlje();

    if (argc > 1) {
        if (strncmp(argv[1], "-d", 2) == 0) {
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
                kreiraj_transakcije_scenario4();
                printf("Scenario 4 (Nepostojeci proizvod) je pripremljen.\n");
                break;
            case '5':
                popuni_maticnu_demo_osnovni();
                pripremi_demo_podatke_slucaj_5();
                printf("Scenario 5 (Sveobuhvatno) je pripremljen u radnom folderu.\n");
                break;
            default:
                printf("[Greska] Nepoznat demo scenario: %s\n", argv[1]);
                break;
            }
        }
    }

    glavni_meni();

    return 0;
}