#ifndef DATOTEKA_H
#define DATOTEKA_H

#include "defs.h"


// Maticna datoteka
void create_maticna();
void drop_maticna(char* putanja);
void select_all_maticna(char* putanja);
void select_id_maticna(char* putanja, unsigned trazeni_id);
void delete_proizvod_maticna();
void insert_maticna();
void update_id_maticna();
void arhiviraj_maticnu();

// Transakciona datoteka
void create_transakciona();
void drop_transakciona(char* putanja);
void insert_transakciona();
void select_all_transakciona(char* putanja);
void select_id_transakciona(char* putanja, unsigned trazeni_id);

void kopiraj_fajl(const char* izvor, const char* odrediste);

#endif