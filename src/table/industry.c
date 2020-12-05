//TODO
/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Industry table functions:
*   - import from csv file to dat file
*   - export from dat file to csv file
*   - load from dat file to buffer
*   - print a single tuple tuple from the buffer
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "table/industry.h"

/***************************************************************************************
* Imports an industry from a csv file line to the dat file
* returns the number of new records imported (1 if all is ok)
****************************************************************************************/
int import_industry(struct db *db, char *csv_line) {
    struct industry new_rec;        // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[CSV_BUF_LEN];    // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct industry));

    // set type
    strncpy(new_rec.type, tables_metadata[INDUSTRY].prefix, PREF_LEN);

    // set id
    tok = strtok(csv_line, ";");
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, CSV_BUF_LEN);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id = atoi(tmp_field);

    // set sector
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.sector, tok, next_tok-tok-1);

    // set name
    tok = next_tok;
    strncpy(new_rec.name, tok, strlen(tok)-1);

    return fwrite(&new_rec, sizeof(struct industry), 1, db->dat_file);
}

/***************************************************************************************
* Exports an industry from the dat file to the csv file
* returns the number of tuples successfully exported (1 or 0)
****************************************************************************************/
int export_industry(struct db *db) {
    struct industry tuple;       // tuple read from the database file
    char new_line[CSV_BUF_LEN]; // new line to write in the csv file

    memset(&tuple, 0, sizeof(struct industry));
    if (fread(&tuple, sizeof(struct industry), 1, db->dat_file) == 1) {
        sprintf(new_line, "%d;%s;%s\n", tuple.id, tuple.sector, tuple.name);
        if (strlen(new_line) == (long unsigned)fprintf(db->csv_file, new_line)) return 1;
    }
    return 0;
}

int load_industries(struct db *db, int count) {
    return 0;
}

int print_industry(struct db *db) {
    return 0;
}