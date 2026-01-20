#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"


char globalni_datum[10] = "000000";

void inicijalizuj_datum() {
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    strftime(globalni_datum, sizeof(globalni_datum), "%y%m%d", tm);
}

void generisi_putanju(char* buffer, const char* folder, const char* prefiks, const char* ekstenzija) {
    if (strcmp(folder, "RPT") == 0 || strcmp(folder, "ERR") == 0) {
        sprintf(buffer, ".\\%s\\%s_%s.%s", folder, prefiks, globalni_datum, ekstenzija);
    }
    else {
        sprintf(buffer, ".\\DATA\\%s\\%s_%s.%s", folder, prefiks, globalni_datum, ekstenzija);
    }
}
