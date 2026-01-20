#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "datoteka.h" 
#include "util.h"     
#include "defs.h"  

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