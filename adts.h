#ifndef ADTS_H
#define ADTS_H

#include "defs.h"



// Arhiviranje (Novo!)
void arhiviraj_maticnu();

// Maticna datoteka
void kreiraj_demo_podatke_slucaj1();
void prikazi_maticnu(char* putanja);
void prikazi_maticnu_id(char* putanja, unsigned trazeni_id);
void obrisi_transakcionu_datoteku(char* putanja);

// Transakciona datoteka
void kreiraj_transakcionu_datoteku();
void prikazi_transakcije(char* putanja);
void prikazi_transakcije_id(char* putanja, unsigned trazeni_id);
void sumiraj_i_sortiraj_transakcije();
void dodaj_transakciju();

// Proizvodi
void dodaj_proizvod_rucno();
void obrisi_proizvod_rucno();
void azuriraj_jedan_proizvod();

// Scenariji azuriranja
void azuriraj_maticnu_osnovni();
void kreiraj_transakcije_scenario2();
void azuriraj_maticnu_scenario2();
void kreiraj_transakcije_scenario3();
void azuriraj_maticnu_scenario3();
void kreiraj_transakcije_scenario4();
void azuriraj_maticnu_scenario4();
void kreiraj_transakcije_scenario5();
void azuriraj_maticnu_sveobuhvatno();

// Pomocni tekstovi
void prikazi_tekst_o_azuriranju();

// Meni
void meni_transakciona();
void meni_maticna();
void meni_demo();
void meni_pomoc();
void glavni_meni();

#endif