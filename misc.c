
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "adts.h"
#include "util.h"



void prikazi_tekst_o_azuriranju() {
    printf("*******************************************************************");
    printf("\n--- O AZURIRANJU SERIJSKE DATOTEKE ---\n");
    printf("Azuriranje podrazumeva spajanje Stare maticne i Datoteke promena.\n");
    printf("Nova maticna postaje trenutna, a stara ide u folder OLD.\n");
    printf("*******************************************************************");
}

void prikazi_o_nama() {
    printf("*******************************************************************");
    printf("\n--- INFORMACIJE O AUTORU ---\n");
    printf("Softverski inženjeri: Valentina Stankoviæ i Nikola Todoroviæ\n");
    printf("Email: vs20220306@student.fon.bg.ac.rs i nt20220044@student.fon.bg.ac.rs\n");
    printf("Mentor: Saša D. Lazareviæ\n");
    printf("Godina: 2026\n");
    printf("*******************************************************************");

}

void prikazi_zaglavlje() {
    printf("************************************************************************\n");
    printf("* Aplikacija: ASD                                                      *\n");
    printf("* Opis      : Azuriranje serijske (sortirane redne) datoteke           *\n");
    printf("* Verzija   : 1.0                                                      *\n");
    printf("* Upotreba  : asd.exe [-d[1|2|3|4|5]]                                  *\n");
    printf("*             1 - Osnovni slucaj                                       \n");
    printf("             2 - Nepostojeæa kolicina (greska kolicine)              \n");
    printf("             3 - Novi proizvod (prijem nepostojeceg)                  \n");
    printf("             4 - Nepostojeci proizvod (izdavanje nepostojeceg)        \n");
    printf("             5 - Sveobuhvatni slucaj                                   *\n");
    printf("* Datum     : %s                                                   *\n", globalni_datum);
    printf("* Autor     : Valentina Stankovic | Nikola Todorovic\n  vs20220306@student.fon.bg.ac.rs | nt20220044@student.fon.bg.ac.rs *\n");
    printf("* Mentor    : Sasa D. Lazarevic, slazar@fon.rs                         *\n");
    printf("************************************************************************\n");
}