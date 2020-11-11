/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Job table functions:
*   - import
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "catalog.h"
#include "table/job.h"

/***************************************************************************************
* Imports a job from a csv file line to the dat file
* returns the number of new records imported (1 if all is ok)
****************************************************************************************/
int import_job(struct db *db, char *csv_line, unsigned line_len) {
    struct job new_rec;             // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[line_len];       // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct job));

    // set type
    strncpy(new_rec.type, tables_metadatas[JOB].prefix, PREF_LEN);

    // set id
    tok = strtok(csv_line, ";");
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, line_len);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id = atoi(tmp_field);

    // set level
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.level, tok, next_tok-tok-1);

    // set department
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.department, tok, next_tok-tok-1);

    // set name
    tok = next_tok;
    strncpy(new_rec.name, tok, strlen(tok)-1);

    // write the new entity into the dat file
    return fwrite(&new_rec, sizeof(struct job), 1, db->dat_file);
}