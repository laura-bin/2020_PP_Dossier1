/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Industry table functions:
 *  - import from csv file to dat file
 *  - export from dat file to csv file
 *  - load from dat file to buffer
 *  - print a single tuple tuple from the buffer
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "table/industry.h"
#include "utils/preprocess_string.h"
#include "utils/string_utils.h"

int import_industry(struct db *db, char *csv_line) {
    struct industry new_rec;        // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[CSV_BUF_LEN];    // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct industry));

    // set type
    strncpy(new_rec.type, tables_metadata[INDUSTRY].prefix, PREFIX_LEN);

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
    if (new_rec.name[strlen(new_rec.name)-1] == '\r') {
        new_rec.name[strlen(new_rec.name)-1] = 0;
    }

    return fwrite(&new_rec, sizeof(struct industry), 1, db->dat_file);
}

int export_industry(struct db *db) {
    struct industry tuple;      // tuple read from the database file
    char new_line[CSV_BUF_LEN]; // new line to write in the csv file

    memset(&tuple, 0, sizeof(struct industry));
    if (fread(&tuple, sizeof(struct industry), 1, db->dat_file) == 1) {
        sprintf(new_line, "%d;%s;%s\n", tuple.id, tuple.sector, tuple.name);
        if (strlen(new_line) == (long unsigned)fprintf(db->csv_file, new_line)) {
            return 1;
        }
    }
    return 0;
}

int load_industries(struct db *db, int count) {
    struct industry entity;
    int i;
    int load_count = 0;

    for (i = 0; i < count; i++) {
        memset(&entity, 0, sizeof(struct industry));

        if (fread(&entity, sizeof(struct industry), 1, db->dat_file) == 1) {
            db->industries[i] = entity;
            load_count++;
        }
    }
    return load_count;
}

void *read_industry(struct db *db, unsigned offset) {
    struct industry *tuple;    // tuple read from the database file

    tuple = malloc(sizeof (struct industry));
    memset(tuple, 0, sizeof(struct industry));
    fseek(db->dat_file, offset, SEEK_SET);
    fread(tuple, sizeof(struct industry), 1, db->dat_file);

    return tuple;
}

void print_industry(struct industry *industry) {
    printf("%" STR(ID_LEN) "u "
            "%-" STR(INDUSTRY_SECTOR_LEN) "s "
            "%-" STR(INDUSTRY_NAME_LEN) "s\n",
            industry->id,
            industry->sector,
            industry->name);
}

void print_industry_header(void) {
    printf("%" STR(ID_LEN) "s "
            "%-" STR(INDUSTRY_SECTOR_LEN) "s "
            "%-" STR(INDUSTRY_NAME_LEN) "s\n",
            "ID",
            "SECTOR",
            "NAME");
}

int compare_industry_id(struct db *db, unsigned offset, unsigned searched) {
    struct industry industry;

    memset(&industry, 0, sizeof(struct industry));
    fseek(db->dat_file, offset, SEEK_SET);
    if (fread(&industry, sizeof(struct industry), 1, db->dat_file) == 1) {
        return searched - industry.id;
    }

    return INT_MAX;
}

void *compare_industry(struct db *db, unsigned i, char *searched) {
    void *found = NULL;

    if (contain_icase(2, searched,
            db->industries[i].sector,
            db->industries[i].name)) {
        found = &db->industries[i];
    }

    return found;
}
