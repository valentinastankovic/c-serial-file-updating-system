#ifndef ADTS_H
#define ADTS_H

#include "defs.h"



// Arhiviranje (Novo!)
void arhiviraj_maticnu();

// Maticna datoteka
void kreiraj_maticnu_datoteku();
void obrisi_maticnu_datoteku(char* putanja);
void prikazi_maticnu(char* putanja);
void prikazi_maticnu_id(char* putanja, unsigned trazeni_id);
void prikazi_tekstualni_izvestaj(char* putanja);


// Transakciona datoteka
void kreiraj_transakcionu_datoteku();
void prikazi_transakcije(char* putanja);
void prikazi_transakcije_id(char* putanja, unsigned trazeni_id);
void sumiraj_i_sortiraj_transakcije();
void dodaj_transakciju();
void obrisi_transakcionu_datoteku(char* putanja);

// Proizvodi
void insert_maticna();
void delete_proizvod_maticna();
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
void pripremi_demo_podatke_slucaj_1();


void kopiraj_fajl(const char* izvor, const char* odrediste);

// Demo
void pripremi_demo_podatke_slucaj_2();
void azuriraj_maticnu_scenario2();

// Meni
void meni_transakciona();
void meni_maticna();
void meni_demo();
void meni_pomoc();
void glavni_meni();

#endif