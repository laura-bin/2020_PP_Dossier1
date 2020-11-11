/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
* ======================================
*
* Company table functions:
*   - import
*
* PP 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "catalog.h"
#include "table/company.h"

/***************************************************************************************
* Imports a company from a csv file line to the dat file
* returns the number of new records imported (1 if all is ok)
****************************************************************************************/
int import_company(struct db *db, char *csv_line, unsigned line_len) {
    struct company new_rec;         // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[line_len];       // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct company));

    // set type
    strncpy(new_rec.type, tables_metadatas[COMPANY].prefix, PREF_LEN);

    // set id
    tok = strtok(csv_line, ";");
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, line_len);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id = atoi(tmp_field);

    // set group id
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, line_len);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id_group = atoi(tmp_field);

    // set country id
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, line_len);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id_country = atoi(tmp_field);

    // set industry id
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, line_len);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.id_industry = atoi(tmp_field);

    // set name
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.name, tok, next_tok-tok-1);

    // set address
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.address, tok, next_tok-tok-1);

    // set zip code
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.zip_code, tok, next_tok-tok-1);

    // set city
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.city, tok, next_tok-tok-1);

    // set phone number
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.phone_number, tok, next_tok-tok-1);

    // set website
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.website, tok, next_tok-tok-1);

    // set creation date
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    strncpy(new_rec.creation_date, tok, next_tok-tok-1);

    // set number of employees
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, line_len);
    strncpy(tmp_field, tok, next_tok-tok-1);
    new_rec.n_employees = atoi(tmp_field);


    // set share value
    tok = next_tok;
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, line_len);
    strncpy(tmp_field, tok, strlen(tok)-1);
    new_rec.share_value = atof(tmp_field);

    // write the new entity into the dat file
    return fwrite(&new_rec, sizeof(struct company), 1, db->dat_file);
}