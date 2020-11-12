/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Person table function:
*   - import
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "catalog.h"
#include "table/person.h"

/***************************************************************************************
* Imports a person from a csv file line to the dat file
* returns the number of new records imported (1 if all is ok)
****************************************************************************************/
int import_person(struct db *db, char *csv_line) {
    struct person new_rec;          // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[CSV_BUF_LEN];    // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct person));

    // set type
    strncpy(new_rec.type, tables_metadata[PERSON].prefix, PREF_LEN);

    // set id
    tok = strtok(csv_line, ";");
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, CSV_BUF_LEN);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id = atoi(tmp_field);

    // set company id
    tok = next_tok;
    next_tok = strtok(NULL,";");
    memset(tmp_field, 0, CSV_BUF_LEN);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id_company = atoi(tmp_field);

    // set job id
    tok = next_tok;
    next_tok = strtok(NULL,";");
    memset(tmp_field, 0, CSV_BUF_LEN);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id_job = atoi(tmp_field);

    // set title
    tok = next_tok;
    next_tok = strtok(NULL,";");
    strncpy(new_rec.title, tok, next_tok-tok-1);

    // set firstname
    tok = next_tok;
    next_tok = strtok(NULL,";");
    strncpy(new_rec.firstname, tok, next_tok-tok-1);

    // set lastname
    tok = next_tok;
    next_tok = strtok(NULL,";");
    strncpy(new_rec.lastname, tok, next_tok-tok-1);

    // set gender
    tok = next_tok;
    next_tok = strtok(NULL,";");
    strncpy(new_rec.gender, tok, next_tok-tok-1);

    // set creation date
    tok = next_tok;
    next_tok = strtok(NULL,";");
    strncpy(new_rec.creation_date, tok, next_tok-tok-1);

    // set phone number
    tok = next_tok;
    next_tok = strtok(NULL,";");
    strncpy(new_rec.phone_number, tok, next_tok-tok-1);

    // set mobile number
    tok = next_tok;
    next_tok = strtok(NULL,";");
    strncpy(new_rec.mobile_number, tok, next_tok-tok-1);

    // set email address
    tok = next_tok;
    next_tok = strtok(NULL,";");
    strncpy(new_rec.email, tok, next_tok-tok-1);

    // set number of shares
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, CSV_BUF_LEN);
    strncpy(tmp_field, tok, strlen(tok)-1);
    new_rec.shares = atoi(tmp_field);

    // write the new entity into the dat file
    return fwrite(&new_rec, sizeof(struct person), 1, db->dat_file);
}

/***************************************************************************************
* Exports a person from the dat file to the csv file
* returns the number of tuples successfully exported (1 or 0)
****************************************************************************************/
int export_person(struct db *db) {
    struct person tuple;        // tuple read from the database file
    char new_line[CSV_BUF_LEN]; // new line to write in the csv file

    memset(&tuple, 0, sizeof(struct person));
    if (fread(&tuple, sizeof(struct person), 1, db->dat_file) == 1) {
        sprintf(new_line, "%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
            tuple.id, tuple.id_company, tuple.id_job, tuple.title, tuple.firstname,
            tuple.lastname, tuple.gender, tuple.creation_date, tuple.phone_number,
            tuple.mobile_number, tuple.email, tuple.shares);
        if (strlen(new_line) == (long unsigned)fprintf(db->csv_file, new_line)) return 1;
    }
    return 0;
}

int print_person(struct db *db) {
    return 0;
}