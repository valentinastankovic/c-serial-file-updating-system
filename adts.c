#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <time.h>
#include "adts.h"
#include "util.h"
#include "misc.h"


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
		printf("Putanja: %s\n", putanja);
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

void sumiraj_i_sortiraj_transakcije() {
	FILE* fs = fopen(".\\DATA\\transakciona.dat", "rb");
	if (!fs) return;

	int sume[1000] = { 0 };
	int korisceni[1000] = { 0 }; 
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

void pripremi_demo_podatke_slucaj_1() {
	FILE* f = fopen(".\\DEMO\\maticna.dat", "wb");
	PROIZVOD p[] = { {20,"Pro_20",100},{30,"Pro_30",150},{40,"Pro_40",200},{50,"Pro_50",250},{60,"Pro_60",300},{70,"Pro_70",350},{80,"Pro_80",400},{90,"Pro_90",450} };
	if (f) {
		fwrite(p, sizeof(PROIZVOD), 8, f); fclose(f);
	}
	f = fopen(".\\DEMO\\SLUC_1\\transakciona.dat", "wb");
	TRANSAKCIJA t[] = { {60,ULAZ,150},{40,ULAZ,80},{60,ULAZ,50},{60,IZLAZ,100},{40,IZLAZ,50},{60,IZLAZ,150},{60,ULAZ,200},{40,IZLAZ,80},{60,ULAZ,20},{60,IZLAZ,120},{40,ULAZ,100},{60,IZLAZ,100},{70,ULAZ,50},{70,IZLAZ,50} };
	if (f) { fwrite(t, sizeof(TRANSAKCIJA), 14, f); fclose(f); }
}

void pripremi_demo_podatke_slucaj_2() {
	FILE* f = fopen(".\\DEMO\\SLUC_2\\transakciona.dat", "wb");
	TRANSAKCIJA t[] = { {20,IZLAZ,800}, {50,IZLAZ,800}, {60,IZLAZ,800} };
	if (f) { fwrite(t, sizeof(TRANSAKCIJA), 3, f); fclose(f); }
}

void pripremi_demo_podatke_slucaj_3() {
	// Pravimo folder .\DEMO\SLUC_3 pre pokretanja!
	FILE* f = fopen(".\\DEMO\\SLUC_3\\transakciona.dat", "wb");
	if (!f) return;
	TRANSAKCIJA t[] = { {10, ULAZ, 210}, {15, ULAZ, 215} };
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

void pripremi_demo_podatke_slucaj_5() {
	FILE* fm = fopen("DEMO/maticna.dat", "wb");
	if (!fm) {
		printf("ERROR: Greska pri otvaranju fajla.\n");
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
	FILE* f = fopen("DEMO/SLUC_5/transakciona.dat", "wb");
	if (!f) {
		printf("ERROR: Greska pri kreiranju fajla!\n");
		return;
	}

	TRANSAKCIJA t[] = {
		{15, ULAZ, 150},  
		{20, ULAZ, 100},  
		{22, IZLAZ, 175}, 
		{35, ULAZ, 150},  
		{50, IZLAZ, 800}, 
		{60, IZLAZ, 800}, 
		{70, ULAZ, 100},  
		{90, IZLAZ, 450}, 
		{92, IZLAZ, 175}  
	};

	fwrite(t, sizeof(TRANSAKCIJA), 9, f);
	fclose(f);

	printf("INFO: Demo podaci za Case 5 su uspesno pripremljeni u folderu DEMO.\n");
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

void kreiraj_transakcije_scenario4() {
	char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
	FILE* f = fopen(p, "wb");
	TRANSAKCIJA t[] = { {92,IZLAZ,40}, {23,IZLAZ,40} };
	fwrite(t, sizeof(TRANSAKCIJA), 2, f);
	fclose(f);
}

void kreiraj_transakcije_scenario5() {
	char p[100]; sprintf(p, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
	FILE* f = fopen(p, "wb");
	TRANSAKCIJA t[] = { {15,ULAZ,150}, {20,ULAZ,100}, {22,IZLAZ,175}, {35,ULAZ,150}, {50,IZLAZ,800}, {60,IZLAZ,800}, {70,ULAZ,100}, {90,IZLAZ,450}, {92,IZLAZ,175} };
	fwrite(t, sizeof(TRANSAKCIJA), 9, f);
	fclose(f);
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
	remove(".\\DATA\\maticna.dat"); 
	rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
	printf("\nINFO: Azuriranje zavrseno.\n");
}

void azuriraj_maticnu_scenario2() {
	char p_e[100];
	sprintf(p_e, ".\\ERR\\err_kol_%s.rpt", globalni_datum);

	FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
	FILE* ft = fopen(".\\DATA\\transakciona.dat", "rb");
	FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
	FILE* fe = fopen(p_e, "w"); 

	if (!fs || !ft || !fn || !fe) {
		printf("ERROR: Proverite foldere DATA i ERR!\n");
		if (fs) fclose(fs);
		if (ft) fclose(ft);
		if (fn) fclose(fn); 
		if (fe) fclose(fe);
		return;
	}

	PROIZVOD p; TRANSAKCIJA t;
	while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
		rewind(ft);
		while (fread(&t, sizeof(TRANSAKCIJA), 1, ft)) {
			if (p.Id == t.Id) {
				if (t.Promena == IZLAZ && t.Kolicina > p.Kolicina) {
					// LOGOVANJE GREŠKE
					fprintf(fe, "ERROR: ID %u | Na stanju: %u | Trazeno: %u\n", p.Id, p.Kolicina, t.Kolicina);
					printf("! Greska kolicine za ID %u\n", p.Id);
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
	printf("\nINFO: Azuriranje zavrseno. Greske zapisane u %s\n", p_e);
}

void azuriraj_maticnu_scenario3() {
	char p_t[100];
	sprintf(p_t, ".\\DATA\\transakciona.dat"); 

	FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
	FILE* ft = fopen(p_t, "rb");
	FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");

	if (!fs || !ft || !fn) return;

	PROIZVOD p; TRANSAKCIJA t;
	int ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
	int ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);

	while (ima_s || ima_t) {
		if (ima_t && (!ima_s || t.Id < p.Id)) {
			PROIZVOD nov;
			nov.Id = t.Id;
			nov.Kolicina = t.Kolicina;
			sprintf(nov.Naziv, "Pro_%u", t.Id); 

			fwrite(&nov, sizeof(PROIZVOD), 1, fn);
			printf("! Dodat nov proizvod: ID %u\n", nov.Id);
			ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);
		}
		else if (ima_s && (!ima_t || p.Id < t.Id)) {
			fwrite(&p, sizeof(PROIZVOD), 1, fn);
			ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
		}
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

void azuriraj_maticnu_scenario4() {
	char p_e[100];
	sprintf(p_e, ".\\ERR\\err_pro_%s.rpt", globalni_datum);

	FILE* fs = fopen(".\\DATA\\maticna.dat", "rb");
	FILE* ft = fopen(".\\DATA\\transakciona.dat", "rb");
	FILE* fn = fopen(".\\DATA\\maticna_nova.dat", "wb");
	FILE* fe = fopen(p_e, "w"); 

	if (!fs || !ft || !fn || !fe) {
		printf("ERROR: Proverite foldere DATA i ERR!\n");
		return;
	}

	PROIZVOD p; 
	TRANSAKCIJA t;
	while (fread(&t, sizeof(TRANSAKCIJA), 1, ft)) {
		int pronadjen = 0;
		rewind(fs); 

		while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
			if (p.Id == t.Id) {
				pronadjen = 1;
				break;
			}
		}

		if (!pronadjen) {
			fprintf(fe, "ERROR: Proizvod sa ID %u ne postoji u maticnoj datoteci.\n", t.Id);
			printf("! Proizvod ne postoji ID %u\n", t.Id);
		}
	}
	rewind(fs);
	while (fread(&p, sizeof(PROIZVOD), 1, fs)) {
		fwrite(&p, sizeof(PROIZVOD), 1, fn);
	}

	fclose(fs); fclose(ft); fclose(fn); fclose(fe);

	arhiviraj_maticnu();
	remove(".\\DATA\\maticna.dat");
	rename(".\\DATA\\maticna_nova.dat", ".\\DATA\\maticna.dat");
}



void azuriraj_maticnu_sveobuhvatno() {
	char p_ek[150], p_ep[150], p_nv[150];

	sprintf(p_ek, ".\\ERR\\err_kol_%s.rpt", globalni_datum);
	sprintf(p_ep, ".\\ERR\\err_pro_%s.rpt", globalni_datum);
	sprintf(p_nv, ".\\RPT\\nov_pro_%s.rpt", globalni_datum);

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
		printf("\nERROR: Greska pri otvaranju datoteka!\n");
		if (fs) fclose(fs);
		if (ft) fclose(ft);
		if (fn) fclose(fn);
		return;
	}

	PROIZVOD p;
	TRANSAKCIJA t;
	int ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
	int ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);

	while (ima_s || ima_t) {
		if (ima_t && (!ima_s || t.Id < p.Id)) {
			if (t.Promena == ULAZ) {
				PROIZVOD novi;
				novi.Id = t.Id;
				novi.Kolicina = t.Kolicina;
				sprintf(novi.Naziv, "Pro_%u", t.Id);
				fwrite(&novi, sizeof(PROIZVOD), 1, fn);

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
					fprintf(ferr, "ERROR: Pokusaj izdavanja nepostojeceg ID %u\n", t.Id);
					fclose(ferr);
					printf(" -> [ERR] Nepostojeci ID %u\n", t.Id);
				}
			}
			ima_t = (fread(&t, sizeof(TRANSAKCIJA), 1, ft) == 1);
		}
		else if (ima_s && (!ima_t || p.Id < t.Id)) {
			fwrite(&p, sizeof(PROIZVOD), 1, fn);
			ima_s = (fread(&p, sizeof(PROIZVOD), 1, fs) == 1);
		}
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

void meni_demo() {
	int izbor;
	do {
		prikaz_meni_demo();
		if (scanf("%d", &izbor) != 1) {
			while (getchar() != '\n');
			continue;
		}

		switch (izbor) {
		case 1:
			prikazi_objasnjenje_osnovni(); 

			pripremi_demo_podatke_slucaj_1();

			kopiraj_fajl(".\\DEMO\\maticna.dat", ".\\DATA\\maticna.dat");
			kopiraj_fajl(".\\DEMO\\SLUC_1\\transakciona.dat", ".\\DATA\\transakciona.dat");

			printf("\n--- 1. STARA MATICNA DATOTEKA ---");
			select_all_maticna(".\\DATA\\maticna.dat");
			system("pause");

			printf("\n--- 2. TRANSAKCIONA DATOTEKA ---");
			select_all_transakciona(".\\DATA\\transakciona.dat");
			system("pause");

			sumiraj_i_sortiraj_transakcije();
			char p_prom[100];
			sprintf(p_prom, ".\\DATA\\OLD\\tran_%s.dat", globalni_datum);
			printf("\n--- 3. DATOTEKA PROMENA ---");
			select_all_transakciona(p_prom);
			system("pause");

			azuriraj_maticnu_osnovni();
			printf("\n--- 4. NOVA MATICNA DATOTEKA ---");
			select_all_maticna(".\\DATA\\maticna.dat");

			printf("\nINFO: Demo osnovnog slucaja je zavrsen.\n");
			system("pause");
			break;
		case 2:
			prikazi_objasnjenje_scenario2();

			pripremi_demo_podatke_slucaj_2();
			kopiraj_fajl(".\\DEMO\\maticna.dat", ".\\DATA\\maticna.dat");
			kopiraj_fajl(".\\DEMO\\SLUC_2\\transakciona.dat", ".\\DATA\\transakciona.dat");

			printf("\n--- 1. STARA MATICNA DATOTEKA ---");
			select_all_maticna(".\\DATA\\maticna.dat");
			system("pause");

			printf("\n--- 2. TRANSAKCIONA DATOTEKA ---");
			select_all_transakciona(".\\DATA\\transakciona.dat");
			system("pause");

			azuriraj_maticnu_scenario2();

			printf("\n--- 3. NOVA MATICNA DATOTEKA ---");
			select_all_maticna(".\\DATA\\maticna.dat");

			printf("\n--- 4. IZVESTAJ O GRESKAMA  ---");
			printf("\nINFO: Scenario 2 zavrsen.\n");
			system("pause");
			break;
		case 3:
			prikazi_objasnjenje_scenario3();

			pripremi_demo_podatke_slucaj_3();
			kopiraj_fajl(".\\DEMO\\maticna.dat", ".\\DATA\\maticna.dat");
			kopiraj_fajl(".\\DEMO\\SLUC_3\\transakciona.dat", ".\\DATA\\transakciona.dat");

			printf("\n--- 1. STARA MATICNA DATOTEKA ---");
			select_all_maticna(".\\DATA\\maticna.dat");
			system("pause");

			printf("\n--- 2. TRANSAKCIONA DATOTEKA ---");
			select_all_transakciona(".\\DATA\\transakciona.dat");
			system("pause");

			azuriraj_maticnu_scenario3();

			printf("\n--- 3. NOVA MATICNA DATOTEKA ---");
			select_all_maticna(".\\DATA\\maticna.dat");

			printf("\nINFO: Scenario 3 zavrsen. Novi proizvodi su uspesno dodati.\n");
			system("pause");
			break;
		case 4:
			prikazi_objasnjenje_scenario4();

			pripremi_demo_podatke_slucaj_4();
			kopiraj_fajl(".\\DEMO\\maticna.dat", ".\\DATA\\maticna.dat");
			kopiraj_fajl(".\\DEMO\\SLUC_4\\transakciona.dat", ".\\DATA\\transakciona.dat");

			printf("\n--- 1. STARA MATICNA DATOTEKA ---");
			select_all_maticna(".\\DATA\\maticna.dat");
			system("pause");

			printf("\n--- 2. TRANSAKCIONA DATOTEKA ---");
			select_all_transakciona(".\\DATA\\transakciona.dat");
			system("pause");

			azuriraj_maticnu_scenario4();
			printf("\n--- 3. NOVA MATICNA DATOTEKA ---");
			select_all_maticna(".\\DATA\\maticna.dat");

			printf("\n--- 4. IZVESTAJ O GRESKAMA ---");
			printf("\nProverite fajl err_pro_*.rpt za detalje.");
			printf("\nINFO: Scenario 4 zavrsen.\n");
			system("pause");
			break;
		case 5:
			prikazi_objasnjenje_scenario5();

			pripremi_demo_podatke_slucaj_5();

			kopiraj_fajl("DEMO/maticna.dat", "DATA/maticna.dat");
			kopiraj_fajl("DEMO/SLUC_5/transakciona.dat", "DATA/transakciona.dat");

			printf("\n--- 1. STARA MATICNA DATOTEKA ---");
			select_all_maticna("DATA/maticna.dat");
			system("pause");

			printf("\n--- 2. TRANSAKCIONA DATOTEKA ---");
			select_all_transakciona("DATA/transakciona.dat");
			system("pause");

			azuriraj_maticnu_sveobuhvatno();

			printf("\n--- 3. NOVA MATICNA DATOTEKA ---");
			select_all_maticna("DATA/maticna.dat");

			printf("\n\n--- 4. PROVERA GENERISANOG IZVESTAJA (RPT) ---");
			char putanja_za_prikaz[150]; 
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
		prikaz_meni_pomoc();
		if (scanf("%d", &izbor) != 1) {
			while (getchar() != '\n');
			continue;
		}

		switch (izbor) {
		case 1:
			printf("\n"); 
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
			printf("\nERROR: Nepostojeca opcija!\n");
		}
	} while (izbor != 0);
}

void meni_transakciona() {
	int izbor;
	unsigned id;
	char putanja[] = ".\\DATA\\transakciona.dat";

	do {
		prikaz_meni_transakciona();
		if (scanf("%d", &izbor) != 1) {
			while (getchar() != '\n');
			continue;
		}

		switch (izbor) {
		case 1:
			create_transakciona();
			break;
		case 2:
			drop_transakciona(putanja);
			break;
		case 3:
			insert_transakciona();
			break;
		case 4:
			select_all_transakciona(putanja);
			break;
		case 5:
			printf("Unesite ID koji trazite: ");
			scanf("%u", &id);
			select_id_transakciona(putanja, id);
			break;
		case 0:
			return;
		default:
			printf("ERROR: Nepostojeca opcija!\n");
		}
	} while (izbor != 0);
}

void meni_maticna() {
	int izbor;
	unsigned id;
	char putanja[] = ".\\DATA\\maticna.dat";

	do {
		prikaz_meni_maticna();
		if (scanf("%d", &izbor) != 1) {
			while (getchar() != '\n');
			continue;
		}

		switch (izbor) {
		case 1:
			create_maticna();
			break;
		case 2:
			drop_maticna(putanja);
			break;
		case 3:
			insert_maticna();
			break;
		case 4:
			delete_proizvod_maticna();
			break;
		case 5: {
			FILE* provera_m = fopen(".\\DATA\\maticna.dat", "rb");
			if (provera_m == NULL) {
				printf("INFO: Maticna datoteka ne postoji. Datoteka se kopira iz foldera DEMO.\n");
				kopiraj_fajl(".\\DEMO\\maticna.dat", ".\\DATA\\maticna.dat");
			}
			else {
				fclose(provera_m);
			}

			FILE* provera_t = fopen(".\\DATA\\transakciona.dat", "rb");
			if (provera_t == NULL) {
				printf("INFO: Transakciona datoteka ne postoji. Datoteka se kopira iz foldera DEMO.\n");
				kopiraj_fajl(".\\DEMO\\SLUC_5\\transakciona.dat", ".\\DATA\\transakciona.dat");
			}
			else {
				fclose(provera_t);
			}

			printf("\nPokrecem sveobuhvatno azuriranje maticne datoteke...\n");
			azuriraj_maticnu_sveobuhvatno();
			printf("\n--- PRIKAZ GENERISANIH IZVESTAJA ---");
			char p_rpt[150];

			printf("\n--- 1. GRESKE KOLICINE ---");
			sprintf(p_rpt, ".\\ERR\\err_kol_%s.rpt", globalni_datum);
			prikazi_tekstualni_izvestaj(p_rpt);

			printf("\n--- 2. NEPOSTOJECI PROIZVODI ---");
			sprintf(p_rpt, ".\\ERR\\err_pro_%s.rpt", globalni_datum);
			prikazi_tekstualni_izvestaj(p_rpt);

			printf("\n--- 3. NOVI PROIZVODI (RPT) ---");
			sprintf(p_rpt, ".\\RPT\\nov_pro_%s.rpt", globalni_datum);
			prikazi_tekstualni_izvestaj(p_rpt);

			printf("\nINFO: Glavna operacija azuriranja je uspesno zavrsena.\n");
			break;
		}
		case 6:
			update_id_maticna();
			break;
		case 7:
			select_all_maticna(putanja);
			break;
		case 8:
			printf("Unesite ID koji trazite: ");
			scanf("%u", &id);
			select_id_maticna(putanja, id);
			break;
		case 0:
			return;
		default:
			printf("ERROR: Nepostojeca opcija!\n");
		}
	} while (izbor != 0);
}

void glavni_meni() {
	int izbor;
	do {
		prikaz_meni_glavni();
		if (scanf("%d", &izbor) != 1) {
			while (getchar() != '\n'); 
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
			printf("\nKraj rada aplikacije.\n");
			break;
		default:
			printf("\nERROR: Nepostojeca opcija!\n");
		}
	} while (izbor != 0);
}