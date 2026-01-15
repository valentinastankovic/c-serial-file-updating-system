#ifndef ADTS_H
#define ADTS_H

#include "defs.h"



// Arhiviranje (Novo!)
void arhiviraj_maticnu();

// Maticna datoteka
void create_maticna();
void drop_maticna(char* putanja);
void select_all_maticna(char* putanja);
void select_id_maticna(char* putanja, unsigned trazeni_id);
void delete_proizvod_maticna();
void insert_maticna();
void update_id_maticna();



// Transakciona datoteka
void create_transakciona();
void drop_transakciona(char* putanja);
void insert_transakciona();
void select_all_transakciona(char* putanja);
void select_id_transakciona(char* putanja, unsigned trazeni_id);
void sumiraj_i_sortiraj_transakcije();



// Proizvodi




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