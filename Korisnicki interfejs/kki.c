
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"
#include "obrada.h"
#include "datoteka.h"
#include "kki.h"

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
    printf("*            1 - Osnovni slucaj                                       \n");
    printf("             2 - Nepostojeca kolicina              \n");
    printf("             3 - Novi proizvod                \n");
    printf("             4 - Nepostojeci proizvod        \n");
    printf("             5 - Sveobuhvatni slucaj                                   *\n");
	printf("* Datum     : %c%c.%c%c.20%c%c                                               *\n",
		globalni_datum[4], globalni_datum[5],
		globalni_datum[2], globalni_datum[3],
		globalni_datum[0], globalni_datum[1]);
    printf("* Autor     : Valentina Stankovic | Nikola Todorovic\n  vs20220306@student.fon.bg.ac.rs | nt20220044@student.fon.bg.ac.rs    *\n");
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


			break;
		case 0:
			return;
		default:
			printf("\nERROR: Nepostojeca opcija!\n");
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