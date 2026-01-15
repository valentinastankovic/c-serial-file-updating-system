
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
    printf("\nOSNOVNI SLUCAJ AZURIRANJA");
    printf("\n----------------------------------------------------------------");
    printf("\nOvo je najjednostavniji proces azuriranja u kojem se obradjuju");
    printf("\nproizvodi koji vec postoje u bazi. Kod prijema robe (ULAZ),");
    printf("\nstanje se uvecava, dok se kod izdavanja (IZLAZ) stanje umanjuje");
    printf("\njer na zalihama uvek postoji dovoljna kolicina. Sve nastale");
    printf("\npromene se uspesno beleze u izvestaj o radu.");
    printf("\n================================================================\n");
    system("pause");
}

void prikazi_objasnjenje_scenario2() {
    printf("\n================================================================");
    printf("\nNEPOSTOJECA KOLICINA");
    printf("\n----------------------------------------------------------------");
    printf("\nOvaj scenario obuhvata azuriranje postojeceg proizvoda uz strogu");
    printf("\nkontrolu raspolozivih zaliha. Pored redovnog prijema i ispravnog");
    printf("\nizdavanja robe, sistem testira i kriticnu situaciju u kojoj je");
    printf("\ntrazena kolicina za izlaz veca od one koja se trenutno nalazi");
    printf("\nu bazi. U takvim okolnostima, operacija se automatski odbija");
    printf("\nkako bi se sacuvao integritet podataka, slog u maticnoj ostaje");
    printf("\nnepromenjen, a razlog greske se belezi u folderu ERR.");
    printf("\n================================================================\n");
    system("pause");
}

void prikazi_objasnjenje_scenario3() {
    printf("\n================================================================");
    printf("\nNOV PROIZVOD");
    printf("\n----------------------------------------------------------------");
    printf("\nPored azuriranja postojecih artikala, ovaj proces omogucava");
    printf("\nuvodjenje novih u bazu. Ukoliko se evidentira prijem robe za");
    printf("\nID koji ne postoji u sistemu, program automatski kreira novi");
    printf("\nslog, uz obavezno ocuvanje sortiranog redosleda datoteke.");
    printf("\n================================================================\n");
    system("pause");
}

void prikazi_objasnjenje_scenario4() {
    printf("\n================================================================");
    printf("\nNEPOSTOJECI PROIZVOD");
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
    printf("\nSVEOBUHVATNI PROCES");
    printf("\n----------------------------------------------------------------");
    printf("\nOvaj slucaj simulira realne uslove rada objedinjavanjem svih");
    printf("\nprethodnih situacija. Testira se standardna promena stanja,");
    printf("\nuvodjenje novih artikala u sistem, kao i pravilno upravljanje");
    printf("\ngreskama pri pokusaju izdavanja nedovoljne kolicine robe ili");
    printf("\nartikala koji se uopste ne nalaze u evidenciji.");
    printf("\n================================================================\n");
    system("pause");
}
void prikazi_tekstualni_izvestaj(char* putanja) {
    FILE* f = fopen(putanja, "r");
    if (!f) {
        return;
    }

    char linija[256];
    int brojac = 0;
    printf("\n--- SADRZAJ IZVESTAJA: %s ---\n", putanja);
    printf("----------------------------------------------------------\n");

    while (fgets(linija, sizeof(linija), f)) {
        printf("%s", linija);
        brojac++;
        if (brojac % 15 == 0) {
            printf("\n[Pritisnite taster za nastavak...]\n");
            system("pause");
        }
    }
    printf("----------------------------------------------------------\n");
    fclose(f);
    system("pause");
}

void prikaz_meni_demo() {
    printf("\n====================================");
    printf("\n MENI Demo");
    printf("\n====================================");
    printf("\n 0. Povratak\n");
    printf("\n 1. Osnovni slucaj");
    printf("\n 2. Nepostojeca kolicina");
    printf("\n 3. Nov proizvod");
    printf("\n 4. Nepostojeci proizvod");
    printf("\n 5. Sveobuhvatni slucaj");
    printf("\n\n Vas izbor: ");
}

void prikaz_meni_pomoc() {
    printf("\nMENI Pomoc");
    printf("\n====================================");
    printf("\n0. Povratak\n");
    printf("\n1. O azuriranju serijske datoteke");
    printf("\n2. Demo");
    printf("\n3. O nama");
    printf("\n\nVas izbor: ");
}

void prikaz_meni_transakciona() {
    printf("\n====================================================================");
    printf("\n MENI Transakciona datoteka");
    printf("\n====================================================================");
    printf("\n 0. Povratak");
    printf("\n\n 1. Create      ::= Kreiranje nove transakcione datoteke");
    printf("\n 2. Drop        ::= Unistavanje postojece transakcione datoteke");
    printf("\n 3. Insert      ::= Dodavanje nove transakcije");
    printf("\n 4. Select All  ::= Prikazivanje svih transakcija");
    printf("\n 5. Select Id   ::= Prikazivanje svih transakcija jednog proizvoda");
    printf("\n\n Vas izbor: ");
}

void prikaz_meni_maticna() {
    printf("\n====================================================================");
    printf("\n MENI Maticna datoteka");
    printf("\n====================================================================");
    printf("\n 0. Povratak");
    printf("\n\n 1. Create      ::= Kreiranje nove maticne datoteke");
    printf("\n 2. Drop        ::= Unistavanje postojece maticne datoteke");
    printf("\n 3. Insert      ::= Dodavanje novog proizvoda");
    printf("\n 4. Delete      ::= Brisanje postojeceg proizvoda");
    printf("\n 5. Update All  ::= Azuriranje maticne datoteke upotrebom transakcione datoteke");
    printf("\n 6. Update Id   ::= Azuriranje jednog proizvoda");
    printf("\n 7. Select All  ::= Prikazivanje svih proizvoda");
    printf("\n 8. Select Id   ::= Prikazivanje jednog proizvoda");
    printf("\n\n Vas izbor: ");
}

void prikaz_meni_glavni() {
    printf("\n==================================");
    printf("\n           GLAVNI MENI            ");
    printf("\n==================================");
    printf("\n0. Kraj rada");
    printf("\n1. Rad sa transakcionom datotekom");
    printf("\n2. Rad sa maticnom datotekom");
    printf("\n3. Pomoc");
    printf("\n----------------------------------");
    printf("\nVas izbor: ");
}