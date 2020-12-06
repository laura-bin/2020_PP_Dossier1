/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database file views:
 *  - print code tables from their buffers (county, job, industry, group)
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

// TODO pagination
// TODO print table header
// TODO check if table is empty
// TODO fix carriage return problem

int print_countries(struct db *db) {
    tables_metadata[COUNTRY].print_buf(db, db->header.n_recorded[COUNTRY]);
    return 0;
}

int print_jobs(struct db *db) {
    tables_metadata[JOB].print_buf(db, db->header.n_recorded[JOB]);
    return 0;
}

int print_industries(struct db *db) {
    tables_metadata[INDUSTRY].print_buf(db, db->header.n_recorded[INDUSTRY]);
    return 0;
}

int print_groups(struct db *db) {
    tables_metadata[GROUP].print_buf(db, db->header.n_recorded[GROUP]);
    return 0;
}
