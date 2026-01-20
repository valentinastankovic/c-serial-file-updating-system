#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datoteka.h" 
#include "util.h"     
#include "defs.h"     

void create_maticna() {
	char putanja[] = ".\\DATA\\maticna.dat";
	FILE* provera = fopen(putanja, "rb");
	if (provera != NULL) {
		fclose(provera);
		printf("\nU folderu sa podacima vec postoji maticna datoteka.");
		printf("\nDa li zelite da je obrisete i kreirate novu maticnu datoteku? (D/N): ");
		char odg;
		scanf(" %c", &odg);

		if (odg != 'D' && odg != 'd') {
			printf("INFO: Operacija otkazana. Postojeca maticna datoteka je sacuvana.\n");
			return;
		}
	}
	FILE* f = fopen(putanja, "wb");
	if (f == NULL) {
		printf("ERROR: Neuspelo kreiranje datoteke na putanji %s\n", putanja);
		return;
	}
	fclose(f);
	printf("INFO: Nova prazna maticna datoteka je kreirana.\n");
}

void drop_maticna(char* putanja) {
	FILE* f = fopen(putanja, "rb");
	if (f == NULL) {
		printf("ERROR: Maticna datoteka ne postoji, pa se ne moze obrisati.\n");
		return;
	}
	fclose(f);

	printf("Da li ste sigurni da zelite da obrisete maticnu datoteku? (D/N): ");
	char odg;
	scanf(" %c", &odg);

	if (odg == 'D' || odg == 'd') {
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

void select_all_maticna(char* putanja) {
	FILE* f = fopen(putanja, "rb");
	if (!f) {
		printf("\nERROR: Maticna datoteka ne postoji ili se ne moze otvoriti.\n");
		/*printf("Putanja: %s\n", putanja);*/
		return;
	}

	PROIZVOD p;
	int brojac = 0;
	int redova_po_strani = 10;

	printf("\n%-10s %-20s %-10s\n", "ID", "NAZIV", "KOLICINA");
	printf("------------------------------------------\n");

	while (fread(&p, sizeof(PROIZVOD), 1, f) == 1) {
		printf("%-10u %-20s %-10u\n", p.Id, p.Naziv, p.Kolicina);
		brojac++;

		if (brojac % redova_po_strani == 0) {
			printf("\n--- Pritisnite taster za nastavak prikaza ---\n");
			system("pause");
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

void select_id_maticna(char* putanja, unsigned trazeni_id) {
	FILE* f = fopen(putanja, "rb");
	if (!f) {
		printf("\nERROR: Maticna datoteka ne postoji.\n");
		return;
	}

	PROIZVOD p;
	int pronadjen = 0;
	while (fread(&p, sizeof(PROIZVOD), 1, f) == 1) {
		if (p.Id == trazeni_id) {
			pronadjen = 1;

			printf("\n--- PODACI O PROIZVODU ---");
			printf("\nID:       %u", p.Id);
			printf("\nNaziv:    %s", p.Naziv);
			printf("\nKolicina: %u", p.Kolicina);
			printf("\n--------------------------\n");
			break;
		}
	}
	if (!pronadjen) {
		printf("\nINFO: Proizvod sa ID %u ne postoji u maticnoj datoteci.\n", trazeni_id);
	}

	fclose(f);
}

void insert_maticna() {
	char putanja[] = ".\\DATA\\maticna.dat";
	char putanja_nova[] = ".\\DATA\\maticna_nova.dat";

	FILE* fs = fopen(putanja, "rb");
	if (fs == NULL) {
		FILE* f_novi = fopen(putanja, "wb");
		if (f_novi == NULL) {
			printf("ERROR: Fajl ne moze da se otvori.\n");
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

	FILE* fn = fopen(putanja_nova, "wb");
	if (fn == NULL) {
		printf("Doslo je do greske pri kreiranju fajla!\n");
		fclose(fs);
		return;
	}

	PROIZVOD novi, tekuci;
	int ubacen = 0;

	printf("\n--- DODAVANJE NOVOG PROIZVODA ---\n");
	printf("ID novog proizvoda: "); scanf("%u", &novi.Id);
	printf("Naziv: "); scanf("%s", novi.Naziv);
	printf("Kolicina: "); scanf("%u", &novi.Kolicina);

	while (fread(&tekuci, sizeof(PROIZVOD), 1, fs)) {
		if (!ubacen && novi.Id < tekuci.Id) {
			fwrite(&novi, sizeof(PROIZVOD), 1, fn);
			ubacen = 1;
		}

		if (tekuci.Id == novi.Id) {
			printf("ERROR: Proizvod sa ID %u vec postoji!\n", novi.Id);
			fclose(fs);
			fclose(fn);
			remove(putanja_nova);
			return;
		}

		fwrite(&tekuci, sizeof(PROIZVOD), 1, fn);
	}

	if (!ubacen) {
		fwrite(&novi, sizeof(PROIZVOD), 1, fn);
	}

	fclose(fs);
	fclose(fn);

	remove(putanja);
	if (rename(putanja_nova, putanja) == 0) {
		printf("INFO: Proizvod dodat i datoteka je sortirana.\n");
	}
	else {
		printf("ERROR: Neuspesna zamena datoteka!\n");
	}
}

void delete_proizvod_maticna() {
	unsigned trazeni_id;
	PROIZVOD p;
	int pronadjen = 0;
	char putanja[] = ".\\DATA\\maticna.dat";
	char putanja_nova[] = ".\\DATA\\maticna_nova.dat";

	while (getchar() != '\n');

	printf("\nUnesite tacnu cifru ID-a za brisanje: ");
	if (scanf("%u", &trazeni_id) != 1) {
		printf("ERROR: Pogresan unos!\n");
		return;
	}
	FILE* fs = fopen(putanja, "rb");
	if (!fs) {
		printf("ERROR: Maticna datoteka ne postoji.\n");
		return;
	}

	while (fread(&p, sizeof(PROIZVOD), 1, fs) == 1) {
		if (p.Id == trazeni_id) {
			printf("\n--- PRONADJEN ---");
			printf("\nID: %u | Naziv: %-15s | Stanje: %u", p.Id, p.Naziv, p.Kolicina);
			pronadjen = 1;
			break;
		}
	}

	if (!pronadjen) {
		printf("\nINFO: Proizvod sa ID %u nije pronadjen.\n", trazeni_id);
		fclose(fs);
		return;
	}

	printf("\n\nDa li ste sigurni da zelite brisanje? D/N: ");
	char odg;
	scanf(" %c", &odg);

	if (odg != 'D' && odg != 'd') {
		printf("INFO: Brisanje otkazano.\n");
		fclose(fs);
		return;
	}

	rewind(fs);
	FILE* fn = fopen(putanja_nova, "wb");
	if (!fn) {
		printf("ERROR: Greska pri kreiranju fajla.\n");
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

	remove(putanja);
	if (rename(putanja_nova, putanja) == 0) {
		printf("INFO: Proizvod %u je uspesno obrisan.\n", trazeni_id);
	}
	else {
		printf("ERROR: Nije moguce otvoriti fajl.\n");
	}
}

void update_id_maticna() {
	unsigned trazeni_id;
	char putanja[] = ".\\DATA\\maticna.dat";
	char putanja_nova[] = ".\\DATA\\maticna_nova.dat";
	PROIZVOD p;
	int pronadjen = 0;

	printf("\nID proizvoda za azuriranje: ");
	if (scanf("%u", &trazeni_id) != 1) {
		while (getchar() != '\n');
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

	while (fread(&p, sizeof(PROIZVOD), 1, fs) == 1) {
		if (p.Id == trazeni_id) {
			pronadjen = 1;

			printf("\n--- PRONADJEN PROIZVOD ---");
			printf("\nTrenutni naziv: %s", p.Naziv);
			printf("\nTrenutna kolicina: %u", p.Kolicina);
			printf("\n--------------------------");
			printf("\nUnesite novi naziv: ");
			scanf("%s", p.Naziv);
			printf("Unesite novu kolicinu: ");
			scanf("%u", &p.Kolicina);
		}

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
		remove(putanja_nova);
		printf("\nINFO: Proizvod sa zadatim identifikatorom (%u) ne postoji.\n", trazeni_id);
	}
}

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

void create_transakciona() {
	char putanja[] = ".\\DATA\\transakciona.dat";
	FILE* provera = fopen(putanja, "rb");
	if (provera != NULL) {
		fclose(provera);
		printf("\nU folderu sa podacima vec postoji transakciona datoteka.");
		printf("\nDa li zelite da je obrisete i kreirate novu transakcionu datoteku? (D/N): ");

		char odg;
		scanf(" %c", &odg);

		if (odg != 'D' && odg != 'd') {
			printf("INFO: Operacija otkazana. Postojeca datoteka je sacuvana.\n");
			return;
		}
	}

	FILE* f = fopen(putanja, "wb");
	if (f == NULL) {
		printf("ERROR: Neuspelo kreiranje datoteke na putanji %s\n", putanja);
		return;
	}
	fclose(f);
	printf("INFO: Nova prazna transakciona datoteka je kreirana.\n");
}

void drop_transakciona(char* putanja) {
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

void insert_transakciona() {
	FILE* f = fopen(".\\DATA\\transakciona.dat", "ab");
	if (!f) {
		printf("ERROR: Transakciona datoteka ne postoji.\n");
		return;
	}

	TRANSAKCIJA t;
	int pro;

	printf("\n--- UNOS NOVE TRANSAKCIJE (Storno = ista kol, suprotna promena) ---\n");
	printf("ID proizvoda: ");
	scanf("%u", &t.Id);

	printf("Promena (1 za ULAZ, -1 za IZLAZ): ");
	scanf("%d", &pro);

	if (pro == 1) t.Promena = ULAZ;
	else if (pro == -1) t.Promena = IZLAZ;
	else {
		printf("ERROR: Pogresan unos! Transakcija nije sacuvana.\n");
		fclose(f);
		return;
	}

	printf("Kolicina: ");
	scanf("%u", &t.Kolicina);

	fwrite(&t, sizeof(TRANSAKCIJA), 1, f);
	fclose(f);

	printf("INFO: Transakcija uspesno dodata u datoteku.\n");
}

void select_all_transakciona(char* putanja) {
	FILE* f = fopen(putanja, "rb");

	if (!f) {
		printf("ERROR: Transakciona datoteka ne postoji ili se ne moze otvoriti.\n");
		return;
	}

	TRANSAKCIJA t;
	int brojac = 0;

	printf("\n--- PRIKAZ SVIH TRANSAKCIJA ---\n");
	printf("%-10s %-10s %-10s\n", "ID", "PROMENA", "KOLICINA");
	printf("----------------------------------\n");

	while (fread(&t, sizeof(TRANSAKCIJA), 1, f) == 1) {
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

void select_id_transakciona(char* putanja, unsigned trazeni_id) {
	FILE* f = fopen(putanja, "rb");
	if (!f) {
		printf("ERROR: Transakciona datoteka ne postoji.\n");
		return;
	}

	TRANSAKCIJA t;
	int brojac = 0;

	while (fread(&t, sizeof(TRANSAKCIJA), 1, f) == 1) {
		if (t.Id == trazeni_id) {
			if (brojac == 0) {
				printf("\n%-10s %-10s %-10s\n", "ID", "PROMENA", "KOLICINA");
				printf("----------------------------------\n");
			}
			printf("%-10u %-10s %-10u\n",
				t.Id,
				(t.Promena == ULAZ ? "ULAZ" : "IZLAZ"),
				t.Kolicina);
			brojac++;
		}
	}

	fclose(f);

	// Ovaj deo je obavezan po specifikaciji!
	if (brojac == 0) {
		printf("INFO: Ne postoje transakcije za proizvod sa ID %u.\n", trazeni_id);
	}
	else {
		printf("----------------------------------\n");
	}
}

void kopiraj_fajl(const char* izvor, const char* odrediste) {
	FILE* src = fopen(izvor, "rb");
	if (!src) {
		printf("ERROR: Izvorna datoteka nije pronadjena: %s\n", izvor);
		return;
	}

	FILE* dst = fopen(odrediste, "wb");
	if (!dst) {
		printf("ERROR: Ne mogu da kreiram ciljnu datoteku: %s\n", odrediste);
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