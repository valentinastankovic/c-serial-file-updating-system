#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "obrada.h" 
#include "util.h"     
#include "defs.h"    
#include "datoteka.h"  

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