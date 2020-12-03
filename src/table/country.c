/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Country table functions:
*   - import from csv file to dat file
*   - export from dat file to csv file
*   - load from dat file to buffer
*   - print a single tuple tuple from the buffer
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "catalog.h"
#include "table/country.h"

/***************************************************************************************
* Imports a country from a csv file line to the dat file
* returns the number of new records imported (1 if all is ok)
****************************************************************************************/
int import_country(struct db *db, char *csv_line) {
    struct country new_rec;         // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[CSV_BUF_LEN];    // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct country));

    // set type
    strncpy(new_rec.type, tables_metadata[COUNTRY].prefix, PREF_LEN);

    // set id
    tok = strtok(csv_line, ";");
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, CSV_BUF_LEN);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id = atoi(tmp_field);

    // set name
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.name, tok, next_tok-tok-1);

    // set zone
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.zone, tok, next_tok-tok-1);

    // set ISO code
    tok = next_tok;
    strncpy(new_rec.iso, tok, strlen(tok)-1);

    // write the new entity into the dat file
    return fwrite(&new_rec, sizeof(struct country), 1, db->dat_file);
}

int *read_country(struct db *db, struct country *out_country) {
    memset(out_country, 0, sizeof(struct country));
    if (fread(out_country, sizeof(struct country), 1, db->dat_file) == 1) {

    }


    return 0;
}

/***************************************************************************************
* Exports a country from the dat file to the csv file
* returns the number of tuples successfully exported (1 or 0)
****************************************************************************************/
int export_country(struct db *db) {
    struct country tuple;       // tuple read from the database file
    char new_line[CSV_BUF_LEN]; // new line to write in the csv file

    memset(&tuple, 0, sizeof(struct country));
    if (fread(&tuple, sizeof(struct country), 1, db->dat_file) == 1) {
        sprintf(new_line, "%d;%s;%s;%s\n", tuple.id, tuple.name, tuple.zone, tuple.iso);
        if (strlen(new_line) == (long unsigned)fprintf(db->csv_file, new_line)) return 1;
    }
    return 0;
}

int load_countries(struct db *db, int count) {
    struct country country;
    int i;
    int load_count = 0;

    for (i = 0; i < count; i++) {
        memset(&country, 0, sizeof(struct country));

        if (fread(&country, sizeof(struct country), 1, db->dat_file) == 1) {
            db->countries[i] = country;
            load_count++;
        }
    }
    return load_count;
}

int print_country(struct db *db) {
    return 0;
}