#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "adts.h"
#include "util.h"
#include "misc.h"

// NOVO: Arhivira maticnu pre nego sto je nova zameni
void arhiviraj_maticnu() {
    char putanja_old[100];
    sprintf(putanja_old, ".\\DATA\\OLD\\mat_%s.dat", globalni_datum);
    FILE* src = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* dest = fopen(putanja_old, "wb");
    if (src && dest) {
        PROIZVOD p;
        while (fread(&p, sizeof(PROIZVOD), 1, src)) fwrite(&p, sizeof(PROIZVOD), 1, dest);
    }
    if (src) fclose(src); if (dest) fclose(dest);
    printf("INFO: Stara maticna arhivirana u folder OLD.\n");
}



void kreiraj_demo_podatke_slucaj1() {
    FILE* f = fopen(".\\DATA\\maticna.dat", "wb");
    PROIZVOD p[] = { {20,"Pro_20",100},{30,"Pro_30",150},{40,"Pro_40",200},{50,"Pro_50",250},{60,"Pro_60",300},{70,"Pro_70",350},{80,"Pro_80",400},{90,"Pro_90",450} };
    fwrite(p, sizeof(PROIZVOD), 8, f);
    fclose(f);
}

void kreiraj_transakcionu_datoteku() {
    char putanja[] = ".\\DATA\\transakciona.dat";

    // Provera da li datoteka vec postoji
    FILE* provera = fopen(putanja, "rb");
    if (provera != NULL) {
        fclose(provera); // Zatvaramo je jer smo samo proveravali postojanje

        printf("\nU folderu sa podacima vec postoji transakciona datoteka.");
        printf("\nDa li zelite da je obrisete i kreirate novu transakcionu datoteku? (D/N): ");

        char odg;
        scanf(" %c", &odg);

        if (odg != 'D' && odg != 'd') {
            printf("INFO: Operacija otkazana. Postojeca datoteka je sacuvana.\n");
            return; // Prekidamo funkciju, ne pravimo novu
        }
    }

    // Kreiranje nove POTPUNO PRAZNE datoteke
    FILE* f = fopen(putanja, "wb");
    if (f == NULL) {
        printf("[Greska] Neuspelo kreiranje datoteke na putanji %s\n", putanja);
        return;
    }

    fclose(f); // Odmah zatvaramo - ostaje prazna
    printf("INFO: Nova prazna transakciona datoteka je kreirana.\n");
}

void sumiraj_i_sortiraj_transakcije() {
    FILE* fs = fopen(".\\DATA\\transakciona.dat", "rb");
    if (!fs) return;
    int sume[1000] = { 0 }; TRANSAKCIJA t;
    while (fread(&t, sizeof(TRANSAKCIJA), 1, fs)) sume[t.Id] += (t.Promena * (int)t.Kolicina);
    fclose(fs);
    char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum); // Sumarna ide u OLD
    FILE* fn = fopen(p, "wb");
    int ids[] = { 40, 60, 70 };
    for (int i = 0; i < 3; i++) {
        TRANSAKCIJA s; s.Id = ids[i];
        if (sume[ids[i]] >= 0) { s.Promena = ULAZ; s.Kolicina = sume[ids[i]]; }
        else { s.Promena = IZLAZ; s.Kolicina = -sume[ids[i]]; }
        fwrite(&s, sizeof(TRANSAKCIJA), 1, fn);
    }
    fclose(fn);
    printf("INFO: Sumarna transakciona kreirana u folderu OLD.\n");
}

void prikazi_maticnu(char* putanja) {
    FILE* f = fopen(putanja, "rb");
    if (!f) return;
    PROIZVOD p; printf("\nID\tNAZIV\t\tKOLICINA\n----------------------------------\n");
    while (fread(&p, sizeof(PROIZVOD), 1, f)) printf("%u\t%s\t\t%u\n", p.Id, p.Naziv, p.Kolicina);
    fclose(f);
}

void prikazi_maticnu_id(char* putanja, unsigned id) {
    FILE* f = fopen(putanja, "rb");
    if (!f) return;
    PROIZVOD p; int n = 0;
    while (fread(&p, sizeof(PROIZVOD), 1, f)) if (p.Id == id) { printf("\nID: %u | Naziv: %s | Stanje: %u\n", p.Id, p.Naziv, p.Kolicina); n = 1; break; }
    if (!n) printf("Nema ga.\n");
    fclose(f);
}

void prikazi_transakcije(char* putanja) {
    // Otvaramo u "rb" modu (read binary)
    FILE* f = fopen(putanja, "rb");

    if (!f) {
        printf("ERROR: Transakciona datoteka ne postoji ili se ne moze otvoriti.\n");
        return;
    }

    TRANSAKCIJA t;
    int brojac = 0;

    printf("\n--- PRIKAZ SVIH TRANSAKCIJA ---\n");
    // Formatiranje zaglavlja: %-10s znaci levo poravnanje, 10 mesta sirine
    printf("%-10s %-10s %-10s\n", "ID", "PROMENA", "KOLICINA");
    printf("----------------------------------\n");

    // fread vraca broj uspesno procitanih blokova (ovde 1)
    while (fread(&t, sizeof(TRANSAKCIJA), 1, f) == 1) {
        // Koristimo %-10u za ID i %-10s za tekst promene
        printf("%-10u %-10s %-10u\n",
            t.Id,
            (t.Promena == ULAZ ? "ULAZ" : "IZLAZ"),
            t.Kolicina);
        brojac++;
    }

    printf("----------------------------------\n");
    if (brojac == 0) {
        printf("INFO: Datoteka je prazna.\n");
    }
    else {
        printf("INFO: Ukupno procitano %d transakcija.\n", brojac);
    }

    fclose(f);
}

void prikazi_transakcije_id(char* putanja, unsigned trazeni_id) {
    FILE* f = fopen(putanja, "rb");
    if (!f) {
        printf("ERROR: Transakciona datoteka ne postoji.\n");
        return;
    }

    TRANSAKCIJA t;
    int pronadjeno = 0;

    while (fread(&t, sizeof(TRANSAKCIJA), 1, f) == 1) {
        if (t.Id == trazeni_id) {
            // Ako je ovo prva koju smo nasli, odstampaj zaglavlje tabele
            if (pronadjeno == 0) {
                printf("\n%-10s %-10s %-10s\n", "ID", "PROMENA", "KOLICINA");
                printf("----------------------------------\n");
            }
            printf("%-10u %-10s %-10u\n",
                t.Id,
                (t.Promena == ULAZ ? "ULAZ" : "IZLAZ"),
                t.Kolicina);
            pronadjeno++;
        }
    }

    fclose(f);

    // Ovaj deo je obavezan po specifikaciji!
    if (pronadjeno == 0) {
        printf("INFO: Ne postoje transakcije za proizvod sa ID %u.\n", trazeni_id);
    }
    else {
        printf("----------------------------------\n");
    }
}

void obrisi_transakcionu_datoteku(char* putanja) {
    // Prvo proverimo da li fajl uopste postoji da ne bismo brisali nesto cega nema
    FILE* f = fopen(putanja, "rb");
    if (f == NULL) {
        printf("ERROR: Transakciona datoteka ne postoji.\n");
        return;
    }
    fclose(f);

    printf("Da li ste sigurni da zelite da obrisete transakcionu datoteku? (D/N): ");
    char odg;
    scanf(" %c", &odg);

    if (odg == 'D' || odg == 'd') {
        // remove() vraca 0 ako je brisanje uspelo
        if (remove(putanja) == 0) {
            printf("INFO: Transakciona datoteka je obrisana.\n");
        }
        else {
            printf("ERROR: Transakciona datoteka nije obrisana.\n");
        }
    }
    else {
        printf("INFO: Brisanje otkazano.\n");
    }
}
// Opcija 3: Insert
void dodaj_proizvod_rucno() {
    FILE* f = fopen(".\\DATA\\maticna.dat", "ab");
    if (!f) { printf("[Greska] Datoteka ne postoji.\n"); return; }
    PROIZVOD p;
    printf("ID novog proizvoda: "); scanf("%u", &p.Id);
    printf("Naziv: "); scanf("%s", p.Naziv);
    printf("Kolicina: "); scanf("%u", &p.Kolicina);
    fwrite(&p, sizeof(PROIZVOD), 1, f);
    fclose(f);
    printf("INFO: Proizvod dodat.\n");
}

// Opcija 4: Delete
void obrisi_proizvod_rucno() {
    unsigned trazeni_id;
    printf("Unesite ID proizvoda za brisanje: "); scanf("%u", &trazeni_id);
    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
    if (!fs || !fn) return;
    PROIZVOD p; int obrisano = 0;
    while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
        if (p.Id != trazeni_id) fwrite(&p, sizeof(PROIZVOD), 1, fn);
        else obrisano = 1;
    }
    fclose(fs); fclose(fn);
    remove(".\\DATA\\maticna.dat"); rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
    if (obrisano) printf("INFO: Proizvod ID %u je obrisan.\n", trazeni_id);
    else printf("INFO: Proizvod sa tim ID-jem nije pronadjen.\n");
}

// Opcija 6: Update Id
void azuriraj_jedan_proizvod() {
    unsigned id, kol; int tip;
    printf("ID proizvoda za azuriranje: "); scanf("%u", &id);
    printf("Tip promene (1 za ULAZ, -1 za IZLAZ): "); scanf("%d", &tip);
    printf("Kolicina: "); scanf("%u", &kol);

    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
    if (!fs || !fn) return;
    PROIZVOD p;
    while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
        if (p.Id == id) {
            if (tip == 1) p.Kolicina += kol;
            else {
                if (kol > p.Kolicina) printf("Greska: Nedovoljno na stanju!\n");
                else p.Kolicina -= kol;
            }
        }
        fwrite(&p, sizeof(PROIZVOD), 1, fn);
    }
    fclose(fs); fclose(fn);
    remove(".\\DATA\\maticna.dat"); rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
    printf("INFO: Azuriranje zavrseno.\n");
}

void azuriraj_maticnu_osnovni() {
    char p_t[100]; sprintf(p_t, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    char p_r[100]; generisi_putanju(p_r, "RPT", "prom", "rpt");
    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* ft = fopen(p_t, "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
    FILE* fr = fopen(p_r, "w");
    if (!fs || !ft || !fn || !fr) return;
    PROIZVOD p; TRANSAKCIJA t;
    while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
        rewind(ft);
        while (fread(&t, sizeof(TRANSAKCIJA), 1, ft)) {
            if (p.Id == t.Id) {
                if (t.Promena == ULAZ) p.Kolicina += t.Kolicina; else p.Kolicina -= t.Kolicina;
                break;
            }
        }
        fwrite(&p, sizeof(PROIZVOD), 1, fn);
    }
    fclose(fs); fclose(ft); fclose(fn); fclose(fr);
    arhiviraj_maticnu();
    remove(".\\DATA\\maticna.dat"); rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
    printf("\n[OK] Azuriranje zavrseno.\n");
}

void kreiraj_transakcije_scenario2() {
    char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    FILE* f = fopen(p, "wb");
    TRANSAKCIJA t[] = { {20,IZLAZ,800}, {50,IZLAZ,800}, {60,IZLAZ,800} };
    fwrite(t, sizeof(TRANSAKCIJA), 3, f);
    fclose(f);
}

void azuriraj_maticnu_scenario2() {
    char p_t[100]; sprintf(p_t, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    char p_e[100]; generisi_putanju(p_e, "ERR", "err_kol", "rpt");
    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* ft = fopen(p_t, "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
    FILE* fe = fopen(p_e, "w");
    if (!fs || !ft || !fn || !fe) return;
    PROIZVOD p; TRANSAKCIJA t;
    while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
        rewind(ft);
        while (fread(&t, sizeof(TRANSAKCIJA), 1, ft)) {
            if (p.Id == t.Id) {
                if (t.Promena == IZLAZ && t.Kolicina > p.Kolicina) fprintf(fe, "ID %u: Nedovoljno\n", p.Id);
                else { if (t.Promena == ULAZ) p.Kolicina += t.Kolicina; else p.Kolicina -= t.Kolicina; }
            }
        }
        fwrite(&p, sizeof(PROIZVOD), 1, fn);
    }
    fclose(fs); fclose(ft); fclose(fn); fclose(fe);
    arhiviraj_maticnu();
    remove(".\\DATA\\maticna.dat"); rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
    printf("\n[OK] Scenario 2 zavrsen.\n");
}

void kreiraj_transakcije_scenario3() {
    char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    FILE* f = fopen(p, "wb");
    TRANSAKCIJA t[] = { {10,ULAZ,210}, {15,ULAZ,215} };
    fwrite(t, sizeof(TRANSAKCIJA), 2, f);
    fclose(f);
}

void azuriraj_maticnu_scenario3() {
    char p_t[100]; sprintf(p_t, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* ft = fopen(p_t, "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
    if (!fs || !ft || !fn) return;
    PROIZVOD p; TRANSAKCIJA t;
    int k_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 0);
    int k_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 0);
    while (!k_s || !k_t) {
        if (!k_s && (k_t || p.Id < t.Id)) { fwrite(&p, sizeof(PROIZVOD), 1, fn); k_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 0); }
        else if (!k_t && (k_s || t.Id < p.Id)) {
            PROIZVOD n; n.Id = t.Id; n.Kolicina = t.Kolicina; sprintf(n.Naziv, "Pro_%u", t.Id);
            fwrite(&n, sizeof(PROIZVOD), 1, fn); k_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 0);
        }
        else {
            if (t.Promena == ULAZ) p.Kolicina += t.Kolicina; else p.Kolicina -= t.Kolicina;
            fwrite(&p, sizeof(PROIZVOD), 1, fn); k_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 0); k_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 0);
        }
    }
    fclose(fs); fclose(ft); fclose(fn);
    arhiviraj_maticnu();
    remove(".\\DATA\\maticna.dat"); rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
    printf("\n[OK] Scenario 3 zavrsen.\n");
}

void kreiraj_transakcije_scenario4() {
    char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    FILE* f = fopen(p, "wb");
    TRANSAKCIJA t[] = { {92,IZLAZ,40}, {23,IZLAZ,40} };
    fwrite(t, sizeof(TRANSAKCIJA), 2, f);
    fclose(f);
}

void azuriraj_maticnu_scenario4() {
    char p_t[100]; sprintf(p_t, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    char p_e[100]; generisi_putanju(p_e, "ERR", "err_pro", "rpt");
    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* ft = fopen(p_t, "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
    FILE* fe = fopen(p_e, "w");
    if (!fs || !ft || !fn || !fe) return;
    TRANSAKCIJA t; PROIZVOD p;
    while (fread(&t, sizeof(TRANSAKCIJA), 1, ft)) {
        rewind(fs); int n = 0;
        while (fread(&p, sizeof(PROIZVOD), 1, fs)) if (p.Id == t.Id) { n = 1; break; }
        if (!n && t.Promena == IZLAZ) fprintf(fe, "ID %u: Nepostojeci.\n", t.Id);
    }
    rewind(fs); while (fread(&p, sizeof(PROIZVOD), 1, fs)) fwrite(&p, sizeof(PROIZVOD), 1, fn);
    fclose(fs); fclose(ft); fclose(fn); fclose(fe);
    arhiviraj_maticnu();
    remove(".\\DATA\\maticna.dat"); rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
    printf("\n[OK] Scenario 4 zavrsen.\n");
}

void kreiraj_transakcije_scenario5() {
    char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    FILE* f = fopen(p, "wb");
    TRANSAKCIJA t[] = { {15,ULAZ,150}, {20,ULAZ,100}, {22,IZLAZ,175}, {35,ULAZ,150}, {50,IZLAZ,800}, {60,IZLAZ,800}, {70,ULAZ,100}, {90,IZLAZ,450}, {92,IZLAZ,175} };
    fwrite(t, sizeof(TRANSAKCIJA), 9, f);
    fclose(f);
}
void dodaj_transakciju() {
    // Koristimo "ab" jer se transakcije samo dopisuju na kraj, nikad se ne menjaju postojeæe
    FILE* f = fopen(".\\DATA\\transakciona.dat", "ab");
    if (!f) {
        printf("ERROR: Transakciona datoteka ne postoji. Prvo uradite Create.\n");
        return;
    }

    TRANSAKCIJA t;
    int pro;

    printf("\n--- UNOS NOVE TRANSAKCIJE (Storno = ista kol, suprotna promena) ---\n");
    printf("ID proizvoda: ");
    scanf("%u", &t.Id);

    printf("Promena (1 za ULAZ, -1 za IZLAZ): ");
    scanf("%d", &pro);

    // Osiguravamo da unos bude ispravan prema tvom enum-u
    if (pro == 1) t.Promena = ULAZ;
    else if (pro == -1) t.Promena = IZLAZ;
    else {
        printf("ERROR: Nevazeca promena! Transakcija nije sacuvana.\n");
        fclose(f);
        return;
    }

    printf("Kolicina: ");
    scanf("%u", &t.Kolicina);

    fwrite(&t, sizeof(TRANSAKCIJA), 1, f);
    fclose(f);

    printf("INFO: Transakcija uspesno dodata u datoteku.\n");
}

void azuriraj_maticnu_sveobuhvatno() {
    char p_t[100]; sprintf(p_t, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    char p_ek[100]; generisi_putanju(p_ek, "ERR", "err_kol", "rpt");
    char p_ep[100]; generisi_putanju(p_ep, "ERR", "err_pro", "rpt");
    char p_nv[100]; generisi_putanju(p_nv, "RPT", "nov_pro", "rpt");
    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* ft = fopen(p_t, "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
    FILE* fek = fopen(p_ek, "w"); FILE* fep = fopen(p_ep, "w"); FILE* fnv = fopen(p_nv, "w");
    if (!fs || !ft || !fn) return;
    PROIZVOD p; TRANSAKCIJA t;
    int k_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 0);
    int k_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 0);
    while (!k_s || !k_t) {
        if (!k_s && (k_t || p.Id < t.Id)) { fwrite(&p, sizeof(PROIZVOD), 1, fn); k_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 0); }
        else if (!k_t && (k_s || t.Id < p.Id)) {
            if (t.Promena == ULAZ) { PROIZVOD n; n.Id = t.Id; n.Kolicina = t.Kolicina; sprintf(n.Naziv, "Pro_%u", t.Id); fwrite(&n, sizeof(PROIZVOD), 1, fn); fprintf(fnv, "Nov ID %u\n", n.Id); }
            else fprintf(fep, "ID %u ne postoji.\n", t.Id);
            k_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 0);
        }
        else {
            if (t.Promena == IZLAZ && t.Kolicina > p.Kolicina) fprintf(fek, "ID %u: Nedovoljno\n", p.Id);
            else { if (t.Promena == ULAZ) p.Kolicina += t.Kolicina; else p.Kolicina -= t.Kolicina; }
            fwrite(&p, sizeof(PROIZVOD), 1, fn); k_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 0); k_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 0);
        }
    }
    fclose(fs); fclose(ft); fclose(fn); fclose(fek); fclose(fep); fclose(fnv);
    arhiviraj_maticnu();
    remove(".\\DATA\\maticna.dat"); rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
    printf("\n[OK] Finalno azuriranje zavrseno.\n");
}

void meni_demo() {
    int izbor;
    do {
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

        if (scanf("%d", &izbor) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (izbor) {
        case 1:
            kreiraj_demo_podatke_slucaj1();
            kreiraj_transakcionu_datoteku();
            sumiraj_i_sortiraj_transakcije();
            printf("\n[OK] Pripremljen osnovni slucaj.\n");
            break;
        case 2:
            kreiraj_demo_podatke_slucaj1();
            kreiraj_transakcije_scenario2();
            printf("\n[OK] Pripremljena greska kolicine.\n");
            break;
        case 3:
            kreiraj_demo_podatke_slucaj1();
            kreiraj_transakcije_scenario3();
            printf("\n[OK] Pripremljen novi proizvod.\n");
            break;
        case 4:
            kreiraj_demo_podatke_slucaj1();
            kreiraj_transakcije_scenario4();
            printf("\n[OK] Pripremljen nepostojeci proizvod.\n");
            break;
        case 5:
            kreiraj_demo_podatke_slucaj1();
            kreiraj_transakcije_scenario5();
            printf("\n[OK] Pripremljen sveobuhvatni slucaj.\n");
            break;
        case 0:
            return;
        default:
            printf("\n[Greska] Nepostojeca opcija!\n");
        }
    } while (izbor != 0);
}

void meni_pomoc() {
    int izbor;
    do {
        printf("\nMENI Pomoc");
        printf("\n====================================");
        printf("\n0. Povratak\n");
        printf("\n1. O azuriranju serijske datoteke");
        printf("\n2. Demo");
        printf("\n3. O nama");
        printf("\n\nVas izbor: ");

        // Provera unosa da program ne bi poludeo ako neko unese slovo
        if (scanf("%d", &izbor) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (izbor) {
        case 1:
            printf("\n"); // Malo razmaka pre teksta
            prikazi_tekst_o_azuriranju();
            printf("\n");
            break;
        case 2:
            meni_demo();
            break;
        case 3:
            printf("\n");
            prikazi_o_nama();
            printf("\n");
            break;
        case 0:
            return;
        default:
            printf("\n[Greska] Nepostojeca opcija!\n");
        }
    } while (izbor != 0);
}

void meni_transakciona() {
    int izbor;
    unsigned id;
    // Koristimo glavnu transakcionu datoteku za rad
    char putanja[] = ".\\DATA\\transakciona.dat";

    do {
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

        if (scanf("%d", &izbor) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (izbor) {
        case 1:
            kreiraj_transakcionu_datoteku();
            break;
        case 2:
            obrisi_transakcionu_datoteku(putanja);
            break;
        case 3:
            dodaj_transakciju();
            break;
        case 4:
            prikazi_transakcije(putanja);
            break;
        case 5:
            printf("Unesite ID koji trazite: ");
            scanf("%u", &id);
            prikazi_transakcije_id(putanja, id);
            break;
        case 0:
            return;
        default:
            printf("[Greska] Nepostojeca opcija!\n");
        }
    } while (izbor != 0);
}

void meni_maticna() {
    int izbor;
    unsigned id;
    char putanja[] = ".\\DATA\\maticna.dat";

    do {
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

        if (scanf("%d", &izbor) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (izbor) {
        case 1:
            kreiraj_demo_podatke_slucaj1();
            printf("INFO: Maticna datoteka kreirana sa demo podacima.\n");
            break;
        case 2:
            //obrisi_datoteku(putanja);
            break;
        case 3:
            dodaj_proizvod_rucno();
            break;
        case 4:
            obrisi_proizvod_rucno();
            break;
        case 5:
            printf("\nIzaberite scenario azuriranja:");
            printf("\n1.Osnovni 2.Greska_kol 3.Novi_pro 4.Nepostojeci 5.Sveobuhvatno\nIzbor: ");
            int sc; scanf("%d", &sc);
            if (sc == 1) azuriraj_maticnu_osnovni();
            else if (sc == 2) azuriraj_maticnu_scenario2();
            else if (sc == 3) azuriraj_maticnu_scenario3();
            else if (sc == 4) azuriraj_maticnu_scenario4();
            else if (sc == 5) azuriraj_maticnu_sveobuhvatno();
            break;
        case 6:
            azuriraj_jedan_proizvod();
            break;
        case 7:
            prikazi_maticnu(putanja);
            break;
        case 8:
            printf("Unesite ID koji trazite: ");
            scanf("%u", &id);
            prikazi_maticnu_id(putanja, id);
            break;
        case 0:
            return;
        default:
            printf("[Greska] Nepostojeca opcija!\n");
        }
    } while (izbor != 0);
}

void glavni_meni() {
    int izbor;
    do {
        printf("\n==================================");
        printf("\n           GLAVNI MENI            ");
        printf("\n==================================");
        printf("\n0. Kraj rada");
        printf("\n1. Rad sa transakcionom datotekom");
        printf("\n2. Rad sa maticnom datotekom");
        printf("\n3. Pomoc");
        printf("\n----------------------------------");
        printf("\nVas izbor: ");

        if (scanf("%d", &izbor) != 1) {
            while (getchar() != '\n'); // ciscenje buffer-a u slucaju pogresnog unosa
            continue;
        }

        switch (izbor) {
        case 1:
            meni_transakciona();
            break;
        case 2:
            meni_maticna();
            break;
        case 3:
            meni_pomoc();
            break;
        case 0:
            printf("\nKraj rada aplikacije ASD. Pozdrav!\n");
            break;
        default:
            printf("\n[Greska] Nepostojeca opcija!\n");
        }
    } while (izbor != 0);
}