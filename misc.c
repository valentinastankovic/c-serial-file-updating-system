
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

void prikazi_objasnjenje_osnovni() {
    printf("\n================================================================");
    printf("\nOSNOVNI SLUCAJ AZURIRANJA (SSZ)");
    printf("\n----------------------------------------------------------------");
    printf("\nAzuriranje podrazumeva spajanje Stare maticne datoteke (SMD)");
    printf("\ni Datoteke promena (DP) radi kreiranja Nove maticne datoteke.");
    printf("\nU osnovnom slucaju, za svaki slog iz DP postoji odgovarajuci");
    printf("\nslog u SMD, i nema gresaka u kolicini.");
    printf("\n================================================================\n");
    // system("pause") je ovde koristan da korisnik stigne da procita pre nego sto krenu podaci
    system("pause");
}

void prikazi_objasnjenje_scenario2() {
    printf("\n================================================================");
    printf("\nSCENARIO 2: GRESKA KOLICINE (Nedovoljno na stanju)");
    printf("\n----------------------------------------------------------------");
    printf("\nAzuriranje nailazi na transakciju IZLAZ cija je kolicina");
    printf("\nveca od trenutnog stanja u maticnoj datoteci.");
    printf("\nSlog u maticnoj ostaje nepromenjen, a greska se belezi");
    printf("\nu izvestaj o greskama (folder ERR).");
    printf("\n================================================================\n");
    system("pause");
}

void prikazi_objasnjenje_scenario3() {
    printf("\n================================================================");
    printf("\nSCENARIO 3: NOV PROIZVOD (Prijem nepostojeceg)");
    printf("\n----------------------------------------------------------------");
    printf("\nAzuriranje nailazi na transakciju sa ID-om koji ne postoji");
    printf("\nu staroj maticnoj datoteci. Ako je promena ULAZ, sistem");
    printf("\nkreira novi slog u maticnoj datoteci. Datoteka ostaje");
    printf("\nsortirana po identifikatoru.");
    printf("\n================================================================\n");
    system("pause");
}

void prikazi_objasnjenje_scenario4() {
    printf("\n================================================================");
    printf("\nSCENARIO 4: NEPOSTOJECI PROIZVOD (Greska u identifikatoru)");
    printf("\n----------------------------------------------------------------");
    printf("\nAzuriranje nailazi na transakciju sa ID-om koji ne postoji");
    printf("\nu maticnoj datoteci. Posto je u pitanju IZLAZ, sistem ne moze");
    printf("\nda izvrsi promenu i belezi gresku u izvestaj o nepostojecim");
    printf("\nproizvodima (folder ERR).");
    printf("\n================================================================\n");
    system("pause");
}

void prikazi_objasnjenje_scenario5() {
    printf("\n================================================================");
    printf("\nSCENARIO 5: SVEOBUHVATNI SLUCAJ (Kombinovano)");
    printf("\n----------------------------------------------------------------");
    printf("\nOvaj scenario simulira realan rad i sadrzi:");
    printf("\n1. Ispravne promene stanja (ID 20, 70, 90)");
    printf("\n2. Prijem novih proizvoda (ID 15, 35)");
    printf("\n3. Greske kolicine (ID 50, 60)");
    printf("\n4. Nepostojece proizvode (ID 22, 92)");
    printf("\n================================================================\n");
    system("pause");
}