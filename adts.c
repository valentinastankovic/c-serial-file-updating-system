#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
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



void kreiraj_maticnu_datoteku() {
    char putanja[] = ".\\DATA\\maticna.dat";

    // 1. Provera postojanja
    FILE* provera = fopen(putanja, "rb");
    if (provera != NULL) {
        fclose(provera);

        // TAÈNA PORUKA IZ SPECIFIKACIJE
        printf("\nU folderu sa podacima vec postoji maticna datoteka.");
        printf("\nDa li zelite da je obrisete i kreirate novu maticnu datoteku? (D/N): ");

        char odg;
        scanf(" %c", &odg);

        if (odg != 'D' && odg != 'd') {
            printf("INFO: Operacija otkazana. Postojeca maticna datoteka je sacuvana.\n");
            return;
        }
    }

    // 2. Kreiranje POTPUNO PRAZNE datoteke
    FILE* f = fopen(putanja, "wb");
    if (f == NULL) {
        printf("[Greska] Neuspelo kreiranje datoteke na putanji %s\n", putanja);
        return;
    }

    fclose(f);
    printf("INFO: Nova prazna maticna datoteka je kreirana.\n");
}

void obrisi_maticnu_datoteku(char* putanja) {
    // 1. Provera da li datoteka uopste postoji
    FILE* f = fopen(putanja, "rb");
    if (f == NULL) {
        printf("ERROR: Maticna datoteka ne postoji, pa se ne moze obrisati.\n");
        return;
    }
    fclose(f);

    // 2. Potvrda brisanja
    printf("Da li ste sigurni da zelite da unistite maticnu datoteku? (D/N): ");
    char odg;
    scanf(" %c", &odg);

    if (odg == 'D' || odg == 'd') {
        // remove() vraca 0 ako je fajl uspesno obrisan sa diska
        if (remove(putanja) == 0) {
            printf("INFO: Maticna datoteka je obrisana.\n");
        }
        else {
            printf("ERROR: Maticna datoteka nije obrisana.\n");
        }
    }
    else {
        printf("INFO: Brisanje otkazano.\n");
    }
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

    int sume[1000] = { 0 };
    int korisceni[1000] = { 0 }; // Pratimo koji su ID-jevi postojali
    TRANSAKCIJA t;

    while (fread(&t, sizeof(TRANSAKCIJA), 1, fs)) {
        if (t.Id < 1000) {
            sume[t.Id] += (t.Promena == ULAZ ? (int)t.Kolicina : -(int)t.Kolicina);
            korisceni[t.Id] = 1;
        }
    }
    fclose(fs);

    char p[100];
    sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    FILE* fn = fopen(p, "wb");
    if (!fn) return;

    for (int i = 0; i < 1000; i++) {
        if (korisceni[i]) {
            TRANSAKCIJA s;
            s.Id = i;
            if (sume[i] >= 0) {
                s.Promena = ULAZ;
                s.Kolicina = sume[i];
            }
            else {
                s.Promena = IZLAZ;
                s.Kolicina = -sume[i];
            }
            fwrite(&s, sizeof(TRANSAKCIJA), 1, fn);
        }
    }
    fclose(fn);
    printf("INFO: Sumarna transakciona kreirana u folderu OLD.\n");
}

void prikazi_maticnu(char* putanja) {
    FILE* f = fopen(putanja, "rb");
    if (!f) {
        printf("\nERROR: Maticna datoteka ne postoji ili se ne moze otvoriti.\n");
        printf("Putanja: %s\n", putanja);
        return;
    }

    PROIZVOD p;
    int brojac = 0;
    int redova_po_strani = 10; // Koliko proizvoda prikazujemo pre pauze

    printf("\n%-10s %-20s %-10s\n", "ID", "NAZIV", "KOLICINA");
    printf("------------------------------------------\n");

    while (fread(&p, sizeof(PROIZVOD), 1, f) == 1) {
        // Koristimo fiksne sirine (%-10u, %-20s) da tabela bude ravna
        printf("%-10u %-20s %-10u\n", p.Id, p.Naziv, p.Kolicina);
        brojac++;

        // Logika "stranu po stranu"
        if (brojac % redova_po_strani == 0) {
            printf("\n--- Pritisnite taster za nastavak prikaza ---\n");
            system("pause");
            // Ponovo ispisemo zaglavlje na novoj strani
            printf("\n%-10s %-20s %-10s\n", "ID", "NAZIV", "KOLICINA");
            printf("------------------------------------------\n");
        }
    }

    if (brojac == 0) {
        printf("INFO: Maticna datoteka je prazna.\n");
    }
    else {
        printf("------------------------------------------\n");
        printf("INFO: Ukupno procitano %d proizvoda.\n", brojac);
    }

    fclose(f);
}

void prikazi_maticnu_id(char* putanja, unsigned trazeni_id) {
    FILE* f = fopen(putanja, "rb");
    if (!f) {
        printf("\nERROR: Maticna datoteka ne postoji.\n");
        return;
    }

    PROIZVOD p;
    int pronadjen = 0;

    // Prolazimo kroz celu datoteku
    while (fread(&p, sizeof(PROIZVOD), 1, f) == 1) {
        if (p.Id == trazeni_id) {
            pronadjen = 1;
            // Lepo formatiran prikaz jednog proizvoda
            printf("\n--- PODACI O PROIZVODU ---");
            printf("\nID:       %u", p.Id);
            printf("\nNaziv:    %s", p.Naziv);
            printf("\nKolicina: %u", p.Kolicina);
            printf("\n--------------------------\n");
            break; // Nasli smo ga, nema potrebe da citamo dalje
        }
    }

    if (!pronadjen) {
        printf("\nINFO: Proizvod sa ID %u ne postoji u maticnoj datoteci.\n", trazeni_id);
    }

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
void insert_maticna() {
    // ISPRAVLJENO: Koristimo dupli backslash
    char putanja[] = ".\\DATA\\maticna.dat";
    char putanja_nova[] = ".\\DATA\\maticna_nova.dat";

    // Prvo samo proveravamo da li stara maticna uopste postoji
    FILE* fs = fopen(putanja, "rb");

    // AKO MATICNA NE POSTOJI
    if (fs == NULL) {
        FILE* f_novi = fopen(putanja, "wb");
        if (f_novi == NULL) {
            printf("ERROR: Ne mogu da kreiram fajl. Proverite da li folder DATA postoji!\n");
            return;
        }
        PROIZVOD p;
        printf("Unos prvog proizvoda u praznu datoteku:\n");
        printf("ID: "); scanf("%u", &p.Id);
        printf("Naziv: "); scanf("%s", p.Naziv);
        printf("Kolicina: "); scanf("%u", &p.Kolicina);

        fwrite(&p, sizeof(PROIZVOD), 1, f_novi);
        fclose(f_novi);
        printf("INFO: Prvi proizvod dodat.\n");
        return;
    }

    // AKO MATICNA POSTOJI, otvaramo pomocni fajl za prepisivanje
    FILE* fn = fopen(putanja_nova, "wb");
    if (fn == NULL) {
        printf("ERROR: Ne mogu da kreiram pomocni fajl!\n");
        fclose(fs);
        return;
    }

    PROIZVOD novi, tekuci;
    int ubacen = 0;

    printf("\n--- DODAVANJE NOVOG PROIZVODA ---\n");
    printf("ID novog proizvoda: "); scanf("%u", &novi.Id);
    printf("Naziv: "); scanf("%s", novi.Naziv);
    printf("Kolicina: "); scanf("%u", &novi.Kolicina);

    // Citamo staru i prepisujemo u novu, ubacujuci novi proizvod na pravo mesto
    while (fread(&tekuci, sizeof(PROIZVOD), 1, fs)) {
        // 1. Provera sortiranja: ako je novi ID manji od tekuceg, ubaci ga ispred
        if (!ubacen && novi.Id < tekuci.Id) {
            fwrite(&novi, sizeof(PROIZVOD), 1, fn);
            ubacen = 1;
        }

        // 2. Provera duplikata: ID ne sme biti isti
        if (tekuci.Id == novi.Id) {
            printf("ERROR: Proizvod sa ID %u vec postoji!\n", novi.Id);
            fclose(fs);
            fclose(fn);
            remove(putanja_nova); // Brise privremeni fajl
            return;
        }

        // 3. Prepisivanje starog sloga
        fwrite(&tekuci, sizeof(PROIZVOD), 1, fn);
    }

    // Ako je novi ID bio najveci, dodajemo ga na sam kraj
    if (!ubacen) {
        fwrite(&novi, sizeof(PROIZVOD), 1, fn);
    }

    fclose(fs);
    fclose(fn);

    // Zamena fajlova na disku
    remove(putanja);
    if (rename(putanja_nova, putanja) == 0) {
        printf("INFO: Proizvod dodat i datoteka je sortirana.\n");
    }
    else {
        printf("ERROR: Neuspesna zamena datoteka!\n");
    }
}

// Opcija 4: Delete
void delete_proizvod_maticna() {
    unsigned trazeni_id;
    PROIZVOD p;
    int pronadjen = 0;
    char putanja[] = ".\\DATA\\maticna.dat";
    char putanja_nova[] = ".\\DATA\\maticna_nova.dat";

    // 1. CISCENJE BAFERA - Ovo sprecava da program "preskoci" unos ili pogresi broj
    while (getchar() != '\n');

    printf("\nUnesite tacnu cifru ID-a za brisanje: ");
    if (scanf("%u", &trazeni_id) != 1) {
        printf("ERROR: Nevazeci unos!\n");
        return;
    }

    FILE* fs = fopen(putanja, "rb");
    if (!fs) {
        printf("ERROR: Maticna datoteka ne postoji.\n");
        return;
    }

    // 2. PRVI PROLAZ - Samo proveravamo da li ID postoji (identicno kao Select All)
    while (fread(&p, sizeof(PROIZVOD), 1, fs) == 1) {
        if (p.Id == trazeni_id) {
            printf("\n--- PRONADJEN ---");
            printf("\nID: %u | Naziv: %-15s | Stanje: %u", p.Id, p.Naziv, p.Kolicina);
            pronadjen = 1;
            break;
        }
    }

    if (!pronadjen) {
        printf("\nINFO: Proizvod sa ID %u nije pronadjen u bazi.\n", trazeni_id);
        fclose(fs);
        return;
    }

    // 3. POTVRDA
    printf("\n\nDa li ste sigurni da zelite brisanje? D/N: ");
    char odg;
    scanf(" %c", &odg);

    if (odg != 'D' && odg != 'd') {
        printf("INFO: Brisanje otkazano.\n");
        fclose(fs);
        return;
    }

    // 4. DRUGI PROLAZ - Prepisivanje svega OSIM tog ID-a
    rewind(fs); // Vracamo se na pocetak fajla
    FILE* fn = fopen(putanja_nova, "wb");
    if (!fn) {
        printf("ERROR: Ne mogu da napravim pomocni fajl.\n");
        fclose(fs);
        return;
    }

    while (fread(&p, sizeof(PROIZVOD), 1, fs) == 1) {
        if (p.Id != trazeni_id) {
            fwrite(&p, sizeof(PROIZVOD), 1, fn);
        }
    }

    fclose(fs);
    fclose(fn);

    // 5. ZAMENA FAJLOVA
    remove(putanja);
    if (rename(putanja_nova, putanja) == 0) {
        printf("INFO: Proizvod %u je uspesno obrisan.\n", trazeni_id);
    }
    else {
        printf("ERROR: Fajl je zakljucan. Restartujte aplikaciju.\n");
    }
}

// Opcija 6: Update Id
void azuriraj_jedan_proizvod() {
    unsigned trazeni_id;
    char putanja[] = ".\\DATA\\maticna.dat";
    char putanja_nova[] = ".\\DATA\\maticna_nova.dat";
    PROIZVOD p;
    int pronadjen = 0;

    printf("\nID proizvoda za azuriranje: ");
    if (scanf("%u", &trazeni_id) != 1) {
        while (getchar() != '\n'); // Ciscenje buffera
        return;
    }

    FILE* fs = fopen(putanja, "rb");
    if (!fs) {
        printf("ERROR: Maticna datoteka ne postoji.\n");
        return;
    }

    FILE* fn = fopen(putanja_nova, "wb");
    if (!fn) {
        printf("ERROR: Neuspešno kreiranje pomoæne datoteke.\n");
        fclose(fs);
        return;
    }

    // Prolazimo kroz fajl da naðemo proizvod
    while (fread(&p, sizeof(PROIZVOD), 1, fs) == 1) {
        if (p.Id == trazeni_id) {
            pronadjen = 1;
            // 1. PRIKAZI PROIZVOD (Obavezno po SRS-u)
            printf("\n--- PRONADJEN PROIZVOD ---");
            printf("\nTrenutni naziv: %s", p.Naziv);
            printf("\nTrenutna kolicina: %u", p.Kolicina);
            printf("\n--------------------------");

            // 2. PITAJ ZA NOVI NAZIV I NOVU KOLICINU
            printf("\nUnesite novi naziv: ");
            scanf("%s", p.Naziv); // ID se ne menja!
            printf("Unesite novu kolicinu: ");
            scanf("%u", &p.Kolicina);
        }
        // Upisujemo u novi fajl (izmenjen ili originalan slog)
        fwrite(&p, sizeof(PROIZVOD), 1, fn);
    }

    fclose(fs);
    fclose(fn);

    if (pronadjen) {
        remove(putanja);
        rename(putanja_nova, putanja);
        printf("\nINFO: Proizvod sa ID %u je uspesno azuriran.\n", trazeni_id);
    }
    else {
        remove(putanja_nova); // Obrisi pomocni fajl jer nista nije menjano
        printf("\nINFO: Proizvod sa zadatim identifikatorom (%u) ne postoji.\n", trazeni_id);
    }
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

// Kreira fajlove u DEMO folderu prema specifikaciji
void pripremi_demo_podatke_slucaj_1() {
    // Maticna u .\DEMO
    FILE* f = fopen(".\\DEMO\\maticna.dat", "wb");
    PROIZVOD p[] = { {20,"Pro_20",100},{30,"Pro_30",150},{40,"Pro_40",200},{50,"Pro_50",250},{60,"Pro_60",300},{70,"Pro_70",350},{80,"Pro_80",400},{90,"Pro_90",450} };
    if (f) { fwrite(p, sizeof(PROIZVOD), 8, f); fclose(f); }

    // Transakcije u .\DEMO\SLUC_1
    f = fopen(".\\DEMO\\SLUC_1\\transakciona.dat", "wb");
    TRANSAKCIJA t[] = { {60,ULAZ,150},{40,ULAZ,80},{60,ULAZ,50},{60,IZLAZ,100},{40,IZLAZ,50},{60,IZLAZ,150},{60,ULAZ,200},{40,IZLAZ,80},{60,ULAZ,20},{60,IZLAZ,120},{40,ULAZ,100},{60,IZLAZ,100},{70,ULAZ,50},{70,IZLAZ,50} };
    if (f) { fwrite(t, sizeof(TRANSAKCIJA), 14, f); fclose(f); }
}

void kopiraj_fajl(const char* izvor, const char* odrediste) {
    FILE* src = fopen(izvor, "rb");
    if (!src) {
        printf("[GRESKA] Izvorna datoteka nije pronadjena: %s\n", izvor);
        return;
    }

    FILE* dst = fopen(odrediste, "wb");
    if (!dst) {
        printf("[GRESKA] Ne mogu da kreiram ciljnu datoteku: %s\n", odrediste);
        fclose(src);
        return;
    }

    char buffer[4096];
    size_t n;
    while ((n = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, n, dst);
    }

    fclose(src);
    fclose(dst);
}


void popuni_maticnu_demo_osnovni() {
    FILE* f = fopen(".\\DATA\\maticna.dat", "wb");
    PROIZVOD p[] = {
        {20,"Pro_20",100}, {30,"Pro_30",150}, {40,"Pro_40",200},
        {50,"Pro_50",250}, {60,"Pro_60",300}, {70,"Pro_70",350},
        {80,"Pro_80",400}, {90,"Pro_90",450}
    };
    fwrite(p, sizeof(PROIZVOD), 8, f);
    fclose(f);
}

void popuni_transakcije_demo_osnovni() {
    FILE* f = fopen(".\\DATA\\transakciona.dat", "wb");
    TRANSAKCIJA t[] = {
        {60,ULAZ,150}, {40,ULAZ,80}, {60,ULAZ,50}, {60,IZLAZ,100},
        {40,IZLAZ,50}, {60,IZLAZ,150}, {60,ULAZ,200}, {40,IZLAZ,80},
        {60,ULAZ,20}, {60,IZLAZ,120}, {40,ULAZ,100}, {60,IZLAZ,100},
        {70,ULAZ,50}, {70,IZLAZ,50}
    };
    fwrite(t, sizeof(TRANSAKCIJA), 14, f);
    fclose(f);
}

void pripremi_demo_podatke_slucaj_2() {
    // Transakcije u .\DEMO\SLUC_2
    // Tražimo 800 komada za ID 20, 50 i 60 (a oni imaju 100, 250 i 300)
    FILE* f = fopen(".\\DEMO\\SLUC_2\\transakciona.dat", "wb");
    TRANSAKCIJA t[] = { {20,IZLAZ,800}, {50,IZLAZ,800}, {60,IZLAZ,800} };
    if (f) { fwrite(t, sizeof(TRANSAKCIJA), 3, f); fclose(f); }
}

void azuriraj_maticnu_scenario2() {
    char p_e[100];
    sprintf(p_e, ".\\ERR\\err_kol_%s.rpt", globalni_datum);

    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* ft = fopen(".\\DATA\\transakciona.dat", "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
    FILE* fe = fopen(p_e, "w"); // Fajl za greske

    if (!fs || !ft || !fn || !fe) {
        printf("[Greska] Proverite foldere DATA i ERR!\n");
        if (fs) fclose(fs); if (ft) fclose(ft); if (fn) fclose(fn); if (fe) fclose(fe);
        return;
    }

    PROIZVOD p; TRANSAKCIJA t;
    while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
        rewind(ft);
        while (fread(&t, sizeof(TRANSAKCIJA), 1, ft)) {
            if (p.Id == t.Id) {
                if (t.Promena == IZLAZ && t.Kolicina > p.Kolicina) {
                    // LOGOVANJE GREŠKE
                    fprintf(fe, "GRESKA: ID %u | Na stanju: %u | Trazeno: %u\n", p.Id, p.Kolicina, t.Kolicina);
                    printf("! Detektovana greska kolicine za ID %u\n", p.Id);
                }
                else {
                    if (t.Promena == ULAZ) p.Kolicina += t.Kolicina;
                    else p.Kolicina -= t.Kolicina;
                }
            }
        }
        fwrite(&p, sizeof(PROIZVOD), 1, fn);
    }

    fclose(fs); fclose(ft); fclose(fn); fclose(fe);

    arhiviraj_maticnu();
    remove(".\\DATA\\maticna.dat");
    rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
    printf("\n[INFO] Azuriranje zavrseno. Greske zapisane u %s\n", p_e);
}

void kreiraj_transakcije_scenario2() {
    char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    FILE* f = fopen(p, "wb");
    TRANSAKCIJA t[] = { {20,IZLAZ,800}, {50,IZLAZ,800}, {60,IZLAZ,800} };
    fwrite(t, sizeof(TRANSAKCIJA), 3, f);
    fclose(f);
}



void kreiraj_transakcije_scenario3() {
    char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    FILE* f = fopen(p, "wb");
    TRANSAKCIJA t[] = { {10,ULAZ,210}, {15,ULAZ,215} };
    fwrite(t, sizeof(TRANSAKCIJA), 2, f);
    fclose(f);
}

void pripremi_demo_podatke_slucaj_3() {
    // Pravimo folder .\DEMO\SLUC_3 pre pokretanja!
    FILE* f = fopen(".\\DEMO\\SLUC_3\\transakciona.dat", "wb");
    if (!f) return;
    TRANSAKCIJA t[] = { {10, ULAZ, 210}, {15, ULAZ, 215} };
    fwrite(t, sizeof(TRANSAKCIJA), 2, f);
    fclose(f);
}

void azuriraj_maticnu_scenario3() {
    char p_t[100];
    sprintf(p_t, ".\\DATA\\transakciona.dat"); // Koristimo DP direktno za demo

    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* ft = fopen(p_t, "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");

    if (!fs || !ft || !fn) return;

    PROIZVOD p; TRANSAKCIJA t;
    int ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
    int ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);

    while (ima_s || ima_t) {
        // Ako je ID u transakcionoj manji, to je nov proizvod
        if (ima_t && (!ima_s || t.Id < p.Id)) {
            PROIZVOD nov;
            nov.Id = t.Id;
            nov.Kolicina = t.Kolicina;
            sprintf(nov.Naziv, "Pro_%u", t.Id); // Automatski naziv

            fwrite(&nov, sizeof(PROIZVOD), 1, fn);
            printf("! Dodat nov proizvod: ID %u\n", nov.Id);
            ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);
        }
        // Ako je ID u maticnoj manji, samo ga prepisujemo
        else if (ima_s && (!ima_t || p.Id < t.Id)) {
            fwrite(&p, sizeof(PROIZVOD), 1, fn);
            ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
        }
        // Ako su ID-evi isti (ovaj scenario to ne pokriva, ali nek ostane)
        else {
            if (t.Promena == ULAZ) p.Kolicina += t.Kolicina;
            else p.Kolicina -= t.Kolicina;
            fwrite(&p, sizeof(PROIZVOD), 1, fn);
            ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
            ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);
        }
    }

    fclose(fs); fclose(ft); fclose(fn);

    arhiviraj_maticnu();
    remove(".\\DATA\\maticna.dat");
    rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
}

void kreiraj_transakcije_scenario4() {
    char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
    FILE* f = fopen(p, "wb");
    TRANSAKCIJA t[] = { {92,IZLAZ,40}, {23,IZLAZ,40} };
    fwrite(t, sizeof(TRANSAKCIJA), 2, f);
    fclose(f);
}

void pripremi_demo_podatke_slucaj_4() {
    // Ruèno napravi folder .\DEMO\SLUC_4 na disku!
    FILE* f = fopen(".\\DEMO\\SLUC_4\\transakciona.dat", "wb");
    if (!f) return;
    TRANSAKCIJA t[] = { {23, IZLAZ, 40}, {92, IZLAZ, 40} };
    fwrite(t, sizeof(TRANSAKCIJA), 2, f);
    fclose(f);
}

void azuriraj_maticnu_scenario4() {
    char p_e[100];
    sprintf(p_e, ".\\ERR\\err_pro_%s.rpt", globalni_datum);

    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* ft = fopen(".\\DATA\\transakciona.dat", "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
    FILE* fe = fopen(p_e, "w"); // Izvestaj o nepostojecim proizvodima

    if (!fs || !ft || !fn || !fe) {
        printf("[Greska] Proverite foldere DATA i ERR!\n");
        return;
    }

    PROIZVOD p; TRANSAKCIJA t;

    // Za svaku transakciju proveravamo da li ID postoji u maticnoj
    while (fread(&t, sizeof(TRANSAKCIJA), 1, ft)) {
        int pronadjen = 0;
        rewind(fs); // Vrati se na pocetak maticne za svaku transakciju

        while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
            if (p.Id == t.Id) {
                pronadjen = 1;
                break;
            }
        }

        if (!pronadjen) {
            fprintf(fe, "GRESKA: Proizvod sa ID %u ne postoji u maticnoj datoteci.\n", t.Id);
            printf("! Detektovan nepostojeci proizvod ID %u\n", t.Id);
        }
    }

    // Prepisujemo maticnu (posto se nista ne menja u ovom scenariju)
    rewind(fs);
    while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
        fwrite(&p, sizeof(PROIZVOD), 1, fn);
    }

    fclose(fs); fclose(ft); fclose(fn); fclose(fe);

    arhiviraj_maticnu();
    remove(".\\DATA\\maticna.dat");
    rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
}

void pripremi_demo_podatke_slucaj_5() {
    // 1. Priprema maticne - koristimo "DEMO/maticna.dat" umesto ".\\DEMO\\"
    FILE* fm = fopen("DEMO/maticna.dat", "wb");
    if (!fm) {
        printf("[GRESKA] Ne mogu da otvorim DEMO/maticna.dat. Proveri da li folder DEMO postoji!\n");
    }
    else {
        PROIZVOD pm[] = {
            {20,"Pro_20",100}, {30,"Pro_30",150}, {40,"Pro_40",200},
            {50,"Pro_50",250}, {60,"Pro_60",300}, {70,"Pro_70",350},
            {80,"Pro_80",400}, {90,"Pro_90",450}
        };
        fwrite(pm, sizeof(PROIZVOD), 8, fm);
        fclose(fm);
    }

    // 2. Priprema transakcija u podfolderu SLUC_5
    // Izbacujemo tacku i dupla kosa crta ide u obicnu kosu crtu /
    FILE* f = fopen("DEMO/SLUC_5/transakciona.dat", "wb");
    if (!f) {
        printf("[GRESKA] Ne mogu da kreiram fajl u DEMO/SLUC_5/. Proveri da li folderi postoje!\n");
        return;
    }

    TRANSAKCIJA t[] = {
        {15, ULAZ, 150},  // Nov (ide u RPT)
        {20, ULAZ, 100},  // Update
        {22, IZLAZ, 175}, // Greska (ide u ERR_PRO)
        {35, ULAZ, 150},  // Nov (ide u RPT)
        {50, IZLAZ, 800}, // Greska (ide u ERR_KOL)
        {60, IZLAZ, 800}, // Greska (ide u ERR_KOL)
        {70, ULAZ, 100},  // Update
        {90, IZLAZ, 450}, // Update
        {92, IZLAZ, 175}  // Greska (ide u ERR_PRO)
    };

    fwrite(t, sizeof(TRANSAKCIJA), 9, f);
    fclose(f);

    printf("[OK] Demo podaci za Case 5 su uspesno pripremljeni u folderu DEMO.\n");
}

void azuriraj_maticnu_sveobuhvatno() {
    char p_ek[150], p_ep[150], p_nv[150];

    // Standardizovane Windows putanje
    sprintf(p_ek, ".\\ERR\\err_kol_%s.rpt", globalni_datum);
    sprintf(p_ep, ".\\ERR\\err_pro_%s.rpt", globalni_datum);
    sprintf(p_nv, ".\\RPT\\nov_pro_%s.rpt", globalni_datum);

    // Inicijalizacija fajlova sa zaglavljem
    FILE* f_init;
    f_init = fopen(p_nv, "w");
    if (f_init) { fprintf(f_init, "--- IZVESTAJ O NOVIM PROIZVODIMA (%s) ---\n", globalni_datum); fclose(f_init); }
    f_init = fopen(p_ek, "w");
    if (f_init) { fprintf(f_init, "--- GRESKE KOLICINE (%s) ---\n", globalni_datum); fclose(f_init); }
    f_init = fopen(p_ep, "w");
    if (f_init) { fprintf(f_init, "--- NEPOSTOJECI PROIZVODI (%s) ---\n", globalni_datum); fclose(f_init); }

    FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
    FILE* ft = fopen(".\\DATA\\transakciona.dat", "rb");
    FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");

    if (!fs || !ft || !fn) {
        printf("\n[GRESKA] Ne mogu da otvorim binarne datoteke u DATA folderu!\n");
        if (fs) fclose(fs); if (ft) fclose(ft); if (fn) fclose(fn);
        return;
    }

    PROIZVOD p;
    TRANSAKCIJA t;
    int ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
    int ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);

    while (ima_s || ima_t) {
        // SCENARIO: Novi proizvod (Transakcija ima manji ID)
        if (ima_t && (!ima_s || t.Id < p.Id)) {
            if (t.Promena == ULAZ) {
                PROIZVOD novi;
                novi.Id = t.Id;
                novi.Kolicina = t.Kolicina;
                sprintf(novi.Naziv, "Pro_%u", t.Id);
                fwrite(&novi, sizeof(PROIZVOD), 1, fn);

                // UPIS U RPT - Otvaramo i odmah zatvaramo da osiguramo upis na disk
                FILE* frpt = fopen(p_nv, "a");
                if (frpt) {
                    fprintf(frpt, "ID: %-4u | Naziv: %-15s | Primljeno: %u\n", novi.Id, novi.Naziv, novi.Kolicina);
                    fclose(frpt);
                    printf(" -> [RPT] Zapisan nov proizvod: ID %u\n", t.Id);
                }
                else {
                    printf(" -> [GRESKA] Neuspelo otvaranje RPT fajla za ID %u\n", t.Id);
                }
            }
            else {
                FILE* ferr = fopen(p_ep, "a");
                if (ferr) {
                    fprintf(ferr, "GRESKA: Pokusaj izdavanja nepostojeceg ID %u\n", t.Id);
                    fclose(ferr);
                    printf(" -> [ERR] Nepostojeci ID %u\n", t.Id);
                }
            }
            ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);
        }
        // SCENARIO: Prepisivanje (Samo u maticnoj)
        else if (ima_s && (!ima_t || p.Id < t.Id)) {
            fwrite(&p, sizeof(PROIZVOD), 1, fn);
            ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
        }
        // SCENARIO: Podudaranje (Azuriranje postojeceg)
        else if (ima_s && ima_t && p.Id == t.Id) {
            while (ima_t && t.Id == p.Id) {
                if (t.Promena == IZLAZ && t.Kolicina > p.Kolicina) {
                    FILE* fkol = fopen(p_ek, "a");
                    if (fkol) {
                        fprintf(fkol, "ID %u | Stanje: %u | Trazeno: %u\n", p.Id, p.Kolicina, t.Kolicina);
                        fclose(fkol);
                        printf(" -> [ERR] Nedovoljno stanja za ID %u\n", p.Id);
                    }
                }
                else {
                    if (t.Promena == ULAZ) p.Kolicina += t.Kolicina;
                    else p.Kolicina -= t.Kolicina;
                }
                ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);
            }
            fwrite(&p, sizeof(PROIZVOD), 1, fn);
            ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
        }
    }

    fclose(fs); fclose(ft); fclose(fn);
    remove(".\\DATA\\maticna.dat");
    rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
    printf("\n--- AZURIRANJE ZAVRSENO ---\n");
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

void prikazi_tekstualni_izvestaj(char* putanja) {
    FILE* f = fopen(putanja, "r");
    if (!f) {
        // Ako fajl ne postoji, znaci da u tom scenariju nije bilo te vrste gresaka
        return;
    }

    char linija[256];
    int brojac = 0;
    printf("\n--- SADRZAJ IZVESTAJA: %s ---\n", putanja);
    printf("----------------------------------------------------------\n");

    while (fgets(linija, sizeof(linija), f)) {
        printf("%s", linija);
        brojac++;
        // Na svakih 15 redova pravi pauzu (stranu po stranu)
        if (brojac % 15 == 0) {
            printf("\n[Pritisnite taster za nastavak...]\n");
            system("pause");
        }
    }
    printf("----------------------------------------------------------\n");
    fclose(f);
    system("pause");
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
            prikazi_objasnjenje_osnovni(); // Tekst iz SSZ (iz misc.c)

            // 1. Priprema DEMO strukture na disku (ovo radimo jednom)
            pripremi_demo_podatke_slucaj_1();

            // 2. Kopiranje iz DEMO u radni folder DATA (prema specifikaciji)
            kopiraj_fajl(".\\DEMO\\maticna.dat", ".\\DATA\\maticna.dat");
            kopiraj_fajl(".\\DEMO\\SLUC_1\\transakciona.dat", ".\\DATA\\transakciona.dat");

            printf("\n--- 1. STARA MATICNA DATOTEKA (Ucitana iz .\\DEMO) ---");
            prikazi_maticnu(".\\DATA\\maticna.dat");
            system("pause");

            printf("\n--- 2. TRANSAKCIONA DATOTEKA (Ucitana iz .\\DEMO\\SLUC_1) ---");
            prikazi_transakcije(".\\DATA\\transakciona.dat");
            system("pause");

            // 3. Sumiranje (rezultat ide u .\DATA\OLD prema tvojoj funkciji)
            sumiraj_i_sortiraj_transakcije();
            char p_prom[100];
            sprintf(p_prom, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
            printf("\n--- 3. DATOTEKA PROMENA (Sumirano u .\\DATA\\OLD) ---");
            prikazi_transakcije(p_prom);
            system("pause");

            // 4. Azuriranje
            azuriraj_maticnu_osnovni();
            printf("\n--- 4. NOVA MATICNA DATOTEKA (Rezultat azuriranja) ---");
            prikazi_maticnu(".\\DATA\\maticna.dat");

            printf("\n[OK] Demo osnovnog slucaja je zavrsen.\n");
            system("pause");
            break;
        case 2:
            prikazi_objasnjenje_scenario2();

            // 1. Priprema i kopiranje demo podataka
            pripremi_demo_podatke_slucaj_2();
            kopiraj_fajl(".\\DEMO\\maticna.dat", ".\\DATA\\maticna.dat");
            kopiraj_fajl(".\\DEMO\\SLUC_2\\transakciona.dat", ".\\DATA\\transakciona.dat");

            printf("\n--- 1. STARA MATICNA DATOTEKA ---");
            prikazi_maticnu(".\\DATA\\maticna.dat");
            system("pause");

            printf("\n--- 2. TRANSAKCIONA DATOTEKA (Zahtevi za izlaz: 800 komada) ---");
            prikazi_transakcije(".\\DATA\\transakciona.dat");
            system("pause");

            // 3. Ažuriranje sa proverom kolièine
            azuriraj_maticnu_scenario2();

            printf("\n--- 3. NOVA MATICNA DATOTEKA (Vrednosti moraju ostati iste) ---");
            prikazi_maticnu(".\\DATA\\maticna.dat");

            printf("\n--- 4. IZVESTAJ O GRESKAMA (Proverite folder ERR) ---");
            // Ovde bi programer mogao dodati funkciju za ispis .rpt fajla na ekran
            printf("\n[OK] Scenario 2 zavrsen.\n");
            system("pause");
            break;
        case 3:
            prikazi_objasnjenje_scenario3();

            // 1. Priprema podataka u DEMO i kopiranje u DATA
            pripremi_demo_podatke_slucaj_3();
            kopiraj_fajl(".\\DEMO\\maticna.dat", ".\\DATA\\maticna.dat");
            kopiraj_fajl(".\\DEMO\\SLUC_3\\transakciona.dat", ".\\DATA\\transakciona.dat");

            printf("\n--- 1. STARA MATICNA DATOTEKA (Pocinje od ID 20) ---");
            prikazi_maticnu(".\\DATA\\maticna.dat");
            system("pause");

            printf("\n--- 2. TRANSAKCIONA DATOTEKA (Novi proizvodi ID 10 i 15) ---");
            prikazi_transakcije(".\\DATA\\transakciona.dat");
            system("pause");

            // 3. Sumiranje (opciono, ali dobro radi preglednosti)
            //sumiraj_i_sortiraj_transakcije();

            // 4. Azuriranje (Merge logika koja dodaje nove slogove)
            azuriraj_maticnu_scenario3();

            printf("\n--- 3. NOVA MATICNA DATOTEKA (ID 10 i 15 su sada na pocetku) ---");
            prikazi_maticnu(".\\DATA\\maticna.dat");

            printf("\n[OK] Scenario 3 zavrsen. Novi proizvodi su uspesno dodati.\n");
            system("pause");
            break;
        case 4:
            prikazi_objasnjenje_scenario4();

            // 1. Priprema podataka u DEMO i kopiranje u DATA
            pripremi_demo_podatke_slucaj_4();
            kopiraj_fajl(".\\DEMO\\maticna.dat", ".\\DATA\\maticna.dat");
            kopiraj_fajl(".\\DEMO\\SLUC_4\\transakciona.dat", ".\\DATA\\transakciona.dat");

            printf("\n--- 1. STARA MATICNA DATOTEKA ---");
            prikazi_maticnu(".\\DATA\\maticna.dat");
            system("pause");

            printf("\n--- 2. TRANSAKCIONA DATOTEKA (ID 23 i 92 ne postoje u bazi) ---");
            prikazi_transakcije(".\\DATA\\transakciona.dat");
            system("pause");

            // 3. Azuriranje sa logikom za nepostojece proizvode
            azuriraj_maticnu_scenario4();

            printf("\n--- 3. NOVA MATICNA DATOTEKA (Vrednosti ostaju iste) ---");
            prikazi_maticnu(".\\DATA\\maticna.dat");

            printf("\n--- 4. IZVESTAJ O GRESKAMA (Folder ERR) ---");
            printf("\nProverite fajl err_pro_*.rpt za detalje o ID 23 i 92.");
            printf("\n[OK] Scenario 4 zavrsen.\n");
            system("pause");
            break;
        case 5:
            prikazi_objasnjenje_scenario5();

            // 1. Priprema svezih demo podataka
            pripremi_demo_podatke_slucaj_5();

            // 2. Kopiranje u radni folder (Koristimo / putanje)
            kopiraj_fajl("DEMO/maticna.dat", "DATA/maticna.dat");
            kopiraj_fajl("DEMO/SLUC_5/transakciona.dat", "DATA/transakciona.dat");

            printf("\n--- 1. STARA MATICNA DATOTEKA ---");
            prikazi_maticnu("DATA/maticna.dat");
            system("pause");

            printf("\n--- 2. TRANSAKCIONA DATOTEKA (Kombinovano) ---");
            prikazi_transakcije("DATA/transakciona.dat");
            system("pause");

            // 3. Izvrsavanje azuriranja
            azuriraj_maticnu_sveobuhvatno();

            printf("\n--- 3. NOVA MATICNA DATOTEKA ---");
            prikazi_maticnu("DATA/maticna.dat");

            // 4. AUTOMATSKI PRIKAZ IZVESTAJA
            printf("\n\n--- 4. PROVERA GENERISANOG IZVESTAJA (RPT) ---");
            char putanja_za_prikaz[150]; // Jedna promenljiva za sve
            sprintf(putanja_za_prikaz, "RPT/nov_pro_%s.rpt", globalni_datum);
            prikazi_tekstualni_izvestaj(putanja_za_prikaz);

            system("pause");
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
            kreiraj_maticnu_datoteku();
            break;
        case 2:
            obrisi_maticnu_datoteku(putanja);
            break;
        case 3:
            insert_maticna();
            break;
        case 4:
            delete_proizvod_maticna();
            break;
        case 5: {
            int sc;
            printf("\nIzaberite scenario azuriranja:");
            printf("\n1.Osnovni 2.Greska_kol 3.Novi_pro 4.Nepostojeci 5.Sveobuhvatno");
            printf("\nIzbor: ");
            if (scanf("%d", &sc) != 1) {
                while (getchar() != '\n');
                break;
            }

            if (sc == 5) {
                // --- LOGIKA SA STRANE 15 SPECIFIKACIJE ---
                FILE* provera_m = fopen("DATA/maticna.dat", "rb");
                if (provera_m == NULL) {
                    printf("INFO: Maticna datoteka ne postoji. Kopiram iz DEMO (SRS str. 15)...\n");
                    kopiraj_fajl("DEMO/maticna.dat", "DATA/maticna.dat");
                }
                else {
                    fclose(provera_m);
                }

                FILE* provera_t = fopen("DATA/transakciona.dat", "rb");
                if (provera_t == NULL) {
                    printf("INFO: Transakciona datoteka ne postoji. Kopiram iz DEMO/SLUC_5 (SRS str. 15)...\n");
                    kopiraj_fajl("DEMO/SLUC_5/transakciona.dat", "DATA/transakciona.dat");
                }
                else {
                    fclose(provera_t);
                }
                // ------------------------------------------

                azuriraj_maticnu_sveobuhvatno();

                printf("\n--- PRIKAZ GENERISANIH IZVESTAJA ---");
                char p_rpt[150];

                printf("\n--- GRESKE KOLICINE ---");
                sprintf(p_rpt, "ERR/err_kol_%s.rpt", globalni_datum);
                prikazi_tekstualni_izvestaj(p_rpt);

                printf("\n--- NEPOSTOJECI PROIZVODI ---");
                sprintf(p_rpt, "ERR/err_pro_%s.rpt", globalni_datum);
                prikazi_tekstualni_izvestaj(p_rpt);

                printf("\n--- NOVI PROIZVODI (RPT) ---");
                sprintf(p_rpt, "RPT/nov_pro_%s.rpt", globalni_datum);
                prikazi_tekstualni_izvestaj(p_rpt);
            }
            // ... ostatak koda
            break;
        }
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