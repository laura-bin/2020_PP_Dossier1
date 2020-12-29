/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Group table functions:
 *  - import from csv file to dat file
 *  - export from dat file to csv file
 *  - load from dat file to buffer
 *  - print a single tuple tuple from the buffer
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "table/group.h"
#include "utils/preprocess_string.h"
#include "utils/string_comparison.h"

int import_group(struct db *db, char *csv_line) {
    struct group new_rec;           // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[CSV_BUF_LEN];    // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct group));

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

    // set country id
    memset(tmp_field, 0, CSV_BUF_LEN);
    strncpy(tmp_field, next_tok, strlen(next_tok)-1);
    new_rec.country_id = atoi(tmp_field);

    // write the new entity into the dat file
    return fwrite(&new_rec, sizeof(struct group), 1, db->dat_file);
}

int export_group(struct db *db) {
    struct group tuple;         // tuple read from the database file
    char new_line[CSV_BUF_LEN]; // new line to write in the csv file

    memset(&tuple, 0, sizeof(struct group));
    if (fread(&tuple, sizeof(struct group), 1, db->dat_file) == 1) {
        sprintf(new_line, "%d;%s;%d\n", tuple.id, tuple.name, tuple.country_id);
        if (strlen(new_line) == (long unsigned)fprintf(db->csv_file, new_line)) {
            return 1;
        }
    }
    return 0;
}

int load_groups(struct db *db, int count) {
    struct group entity;
    int i;
    int load_count = 0;

    for (i = 0; i < count; i++) {
        memset(&entity, 0, sizeof(struct group));

        if (fread(&entity, sizeof(struct group), 1, db->dat_file) == 1) {
            db->groups[i] = entity;
            load_count++;
        }
    }
    return load_count;
}

void print_group(struct group *group) {
    printf("%" STR(ID_LEN) "d "
            "%-" STR(GROUP_NAME_LEN) "s "
            "%" STR(ID_LEN) "d\n",
            group->id,
            group->name,
            group->country_id);
}

void print_group_header(void) {
    printf("%" STR(ID_LEN) "s "
            "%-" STR(GROUP_NAME_LEN) "s "
            "%" STR(ID_LEN) "s\n",
            "ID",
            "NAME",
            "COUNTRY ID");
}

void *compare_group(struct db *db, unsigned i, char *searched) {
    void *found = NULL;

    if (contain_icase(1, searched, db->groups[i].name)) {
        found = &db->groups[i];
    }

    return found;
}
