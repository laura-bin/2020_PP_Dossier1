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
* PP 2020-2021 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "table/country.h"
#include "utils/preprocess_string.h"
#include "utils/string_utils.h"

int import_country(struct db *db, char *csv_line) {
    struct country new_rec;         // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[CSV_BUF_LEN];    // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct country));

    // set type
    strncpy(new_rec.type, tables_metadata[COUNTRY].prefix, PREFIX_LEN);

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
    if (new_rec.iso[strlen(new_rec.iso)-1] == '\r') {
        new_rec.iso[strlen(new_rec.iso)-1] = 0;
    }

    // write the new entity into the dat file
    return fwrite(&new_rec, sizeof(struct country), 1, db->dat_file);
}

int export_country(struct db *db) {
    struct country tuple;       // tuple read from the database file
    char new_line[CSV_BUF_LEN]; // new line to write in the csv file

    memset(&tuple, 0, sizeof(struct country));
    if (fread(&tuple, sizeof(struct country), 1, db->dat_file) == 1) {
        sprintf(new_line, "%d;%s;%s;%s\n", tuple.id, tuple.name, tuple.zone, tuple.iso);
        if (strlen(new_line) == (long unsigned)fprintf(db->csv_file, new_line)) {
            return 1;
        }
    }
    return 0;
}

int load_countries(struct db *db, int count) {
    struct country entity;
    int i;
    int load_count = 0;

    for (i = 0; i < count; i++) {
        memset(&entity, 0, sizeof(struct country));

        if (fread(&entity, sizeof(struct country), 1, db->dat_file) == 1) {
            db->countries[i] = entity;
            load_count++;
        }
    }
    return load_count;
}

void *read_country(struct db *db, unsigned offset) {
    struct country *tuple;    // tuple read from the database file

    tuple = malloc(sizeof (struct country));
    memset(tuple, 0, sizeof(struct country));
    fseek(db->dat_file, offset, SEEK_SET);
    fread(tuple, sizeof(struct country), 1, db->dat_file);

    return tuple;
}

void print_country(struct country *country) {
    printf("%" STR(ID_LEN) "u "
            "%-" STR(COUNTRY_NAME_LEN) "s "
            "%-" STR(COUNTRY_ZONE_LEN) "s "
            "%-" STR(COUNTRY_ZONE_LEN) "s\n",
            country->id,
            country->name,
            country->zone,
            country->iso);
}

void print_country_header(void) {
    printf("%" STR(ID_LEN) "s "
            "%-" STR(COUNTRY_NAME_LEN) "s "
            "%-" STR(COUNTRY_ZONE_LEN) "s "
            "%-" STR(COUNTRY_ZONE_LEN) "s\n",
            "ID",
            "NAME",
            "ZONE",
            "ISO");
}

int compare_country_id(struct db *db, unsigned offset, unsigned searched) {
    struct country country;

    memset(&country, 0, sizeof(struct country));
    fseek(db->dat_file, offset, SEEK_SET);
    if (fread(&country, sizeof(struct country), 1, db->dat_file) == 1) {
        return searched - country.id;
    }

    return INT_MAX;
}

void *compare_country(struct db *db, unsigned i, char *searched) {
    void *found = NULL;

    if (contain_icase(3, searched,
            db->countries[i].name,
            db->countries[i].zone,
            db->countries[i].iso)) {
        found = &db->countries[i];
    }

    return found;
}
