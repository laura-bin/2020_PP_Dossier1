/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Job table functions:
 *  - import from csv file to dat file
 *  - export from dat file to csv file
 *  - load from dat file to buffer
 *  - print a single tuple tuple from the buffer
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "table/job.h"

int import_job(struct db *db, char *csv_line) {
    struct job new_rec;             // new record to write in the dat file
    char *tok, *next_tok;           // line's tokens separated by strtok
    char tmp_field[CSV_BUF_LEN];    // temporary field used for conversion to integer

    // init the new record to 0
    memset(&new_rec, 0, sizeof(struct job));

    // set type
    strncpy(new_rec.type, tables_metadata[JOB].prefix, PREF_LEN);

    // set id
    tok = strtok(csv_line, ";");
    next_tok = strtok(NULL, ";");
    memset(tmp_field, 0, CSV_BUF_LEN);
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
    if (new_rec.name[strlen(new_rec.name)-1] == '\r') {
        new_rec.name[strlen(new_rec.name)-1] = 0;
    }

    // write the new entity into the dat file
    return fwrite(&new_rec, sizeof(struct job), 1, db->dat_file);
}

int export_job(struct db *db) {
    struct job tuple;           // tuple read from the database file
    char new_line[CSV_BUF_LEN]; // new line to write in the csv file

    memset(&tuple, 0, sizeof(struct job));
    if (fread(&tuple, sizeof(struct job), 1, db->dat_file) == 1) {
        sprintf(new_line, "%d;%s;%s;%s\n", tuple.id, tuple.level,
                    tuple.department, tuple.name);
        if (strlen(new_line) == (long unsigned)fprintf(db->csv_file, new_line)) return 1;
    }
    return 0;
}

int load_jobs(struct db *db, int count) {
    struct job entity;
    int i;
    int load_count = 0;

    for (i = 0; i < count; i++) {
        memset(&entity, 0, sizeof(struct job));

        if (fread(&entity, sizeof(struct job), 1, db->dat_file) == 1) {
            db->jobs[i] = entity;
            load_count++;
        }
    }
    return load_count;
}

void print_job(struct job *job) {
    printf("%4d %-22s %-24s %-38s\n",
            job->id,
            job->level,
            job->department,
            job->name);
}

void print_buf_jobs(struct db *db, unsigned n_rec) {
    unsigned i;
    for (i = 0; i < n_rec; i++) {
        print_job(&db->jobs[i]);
    }
}