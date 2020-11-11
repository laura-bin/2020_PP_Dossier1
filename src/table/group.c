/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Group table functions:
*   - import
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "catalog.h"
#include "table/group.h"

/***************************************************************************************
* Imports a group from a csv file line to the dat file
* returns the number of new records imported (1 if all is ok)
****************************************************************************************/
int import_group(struct db *db, char *csv_line, unsigned line_len) {
    struct group new_rec;           // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[line_len];       // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct group));

    // set type
    strncpy(new_rec.type, tables_metadatas[COUNTRY].prefix, PREF_LEN);

    // set id
    tok = strtok(csv_line, ";");
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, line_len);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id = atoi(tmp_field);

    // set name
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.name, tok, next_tok-tok-1);

    // set country id
    memset(tmp_field, 0, line_len);
    strncpy(tmp_field, next_tok, strlen(next_tok)-1);
    new_rec.country_id = atoi(tmp_field);

    // write the new entity into the dat file
    return fwrite(&new_rec, sizeof(struct group), 1, db->dat_file);
}