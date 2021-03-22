/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Person table function:
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

#include "table/person.h"
#include "utils/preprocess_string.h"

int import_person(struct db *db, char *csv_line) {
    struct person new_rec;          // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[CSV_BUF_LEN];    // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct person));

    // set type
    strncpy(new_rec.type, tables_metadata[PERSON].prefix, PREFIX_LEN);

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

int export_person(struct db *db) {
    struct person tuple;        // tuple read from the database file
    char new_line[CSV_BUF_LEN]; // new line to write in the csv file

    memset(&tuple, 0, sizeof(struct person));
    if (fread(&tuple, sizeof(struct person), 1, db->dat_file) == 1) {
        sprintf(new_line, "%d;%d;%d;%s;%s;%s;%s;%s;%s;%s;%s;%d\n",
            tuple.id, tuple.id_company, tuple.id_job, tuple.title, tuple.firstname,
            tuple.lastname, tuple.gender, tuple.creation_date, tuple.phone_number,
            tuple.mobile_number, tuple.email, tuple.shares);
        if (strlen(new_line) == (long unsigned)fprintf(db->csv_file, new_line)) {
            return 1;
        }
    }
    return 0;
}

unsigned read_person_company_id(struct db *db, unsigned offset) {
    struct person tuple;    // tuple read from the database file
    memset(&tuple, 0, sizeof(struct person));
    fseek(db->dat_file, offset, SEEK_SET);
    if (fread(&tuple, sizeof(struct person), 1, db->dat_file) == 1) {
        return tuple.id_company;
    }
    return UINT_MAX;
}

void read_person_lastname(struct db *db, unsigned offset, char *out_lastname) {
    struct person tuple;    // tuple read from the database file
    memset(&tuple, 0, sizeof(struct person));
    fseek(db->dat_file, offset, SEEK_SET);
    if (fread(&tuple, sizeof(struct person), 1, db->dat_file) == 1) {
        strncpy(out_lastname, tuple.lastname, PERSON_LASTNAME_LEN);
    }
}

void *read_person(struct db *db, unsigned offset) {
    struct person *tuple;   // tuple read from the database file

    tuple = malloc(sizeof (struct person));
    memset(tuple, 0, sizeof(struct person));
    fseek(db->dat_file, offset, SEEK_SET);
    fread(tuple, sizeof(struct person), 1, db->dat_file);

    return tuple;
}

void print_person_details(struct person *person) {
    printf("%-16s %u\n"
            "%-16s %u\n"
            "%-16s %u\n"
            "%-16s %s\n"
            "%-16s %s\n"
            "%-16s %s\n"
            "%-16s %s\n"
            "%-16s %s\n"
            "%-16s %s\n"
            "%-16s %s\n"
            "%-16s %s\n"
            "%-16s %u\n",
            "ID", person->id,
            "COMPANY ID", person->id_company,
            "JOB ID", person->id_job,
            "TITLE", person->title,
            "LASTNAME", person->lastname,
            "FIRSTNAME", person->firstname,
            "GENDER", person->gender,
            "CREATION DATE", person->creation_date,
            "PHONE NUMBER", person->phone_number,
            "MOBILE NUMBER", person->mobile_number,
            "EMAIL", person->email,
            "SHARES", person->shares);
}

void print_person(struct person *person) {
    printf("%" STR(ID_LEN) "u "
            "%-" STR(PERSON_TITLE_LEN) "s "
            "%-" STR(PERSON_LASTNAME_LEN) "s "
            "%-" STR(PERSON_FIRSTNAME_LEN) "s "
            "%-7s\n",
            person->id,
            person->title,
            person->lastname,
            person->firstname,
            person->gender);
}

void print_person_header(void) {
    printf("%" STR(ID_LEN) "s "
            "%-" STR(PERSON_TITLE_LEN) "s "
            "%-" STR(PERSON_LASTNAME_LEN) "s "
            "%-" STR(PERSON_FIRSTNAME_LEN) "s "
            "%-7s\n",
            "ID",
            "TITLE",
            "LASTNAME",
            "FIRSTNAME",
            "GENDER");
}

int compare_person_id(struct db *db, unsigned offset, unsigned searched) {
    struct person person;

    memset(&person, 0, sizeof(struct person));
    fseek(db->dat_file, offset, SEEK_SET);
    if (fread(&person, sizeof(struct person), 1, db->dat_file) == 1) {
        return searched - person.id;
    }

    return INT_MAX;
}

int compare_person_lastname(const void *person1, const void *person2) {
    struct person *p1 = *(struct person **)person1;
    struct person *p2 = *(struct person **)person2;

    return (strcmp(p1->lastname, p2->lastname));
}
