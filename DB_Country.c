/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
*
* Manipulations de la table country
*
* Programmation procedurale 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "DB_Main.h"

/****************************************************************************************
* Imports csv file to dat file
****************************************************************************************/
void import_countries(dbc *db) {
    int n = 0;                      // number of record imported
    char line[BUF_LEN];             // csv line
    char tmp_field[BUF_LEN];        // temporary field used for conversion to integer
    char *tok, *next_tok;           // line's tokens separated by strtok
	country_entity entity;          // new entity to write in the dat file
	FILE *csv_file, *dat_file, *log_file;   // file pointers

    /* Open files */
    dat_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.dat", "rb+");
    log_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.log", "a");
    csv_file = fopen("Data_Import"DIR_SEPARATOR"DB_Country.csv", "r");

    fprintf(log_file, "Country table import: starting import.\n");
    printf("\nCountry table: importing...\n");

    // TODO use error function
	if (csv_file == NULL) {
        printf("Erreur\n");
        return;
    }

    // Skip the header
    fgets(line, BUF_LEN, csv_file);

    fseek(dat_file, db->header.off_ctr, SEEK_SET);
    while (fgets(line, BUF_LEN, csv_file) != NULL) {
        // Init the new entity to 0
        memset(&entity, 0, sizeof(country_entity));

        // Set type
        strcpy(entity.type, "CTR");

        // Set id
        tok = strtok(line,";");
        next_tok = strtok(NULL,";");
        memset(tmp_field, 0, BUF_LEN);
        strncpy(tmp_field, tok, next_tok-tok-1);
        entity.id = atoi(tmp_field);

        // Set name
        tok = next_tok;
        next_tok = strtok(NULL,";");
        strncpy(entity.name, tok, next_tok-tok-1);

        // Set zone
        tok = next_tok;
        next_tok = strtok(NULL,";");
        strncpy(entity.zone, tok, next_tok-tok-1);

        // Set ISO code
        tok = next_tok;
        strncpy(entity.iso, tok, strlen(tok)-1);

        // Write the new entity into the dat file
        fwrite(&entity, 1, sizeof(country_entity), dat_file);

        n++;
    }

    fprintf(log_file, "Country table import: %d records imported.\n", n);
    printf("\n%d records imported.\n\n", n);

    /* Update the number of countries in the DB header */
    fseek(dat_file, 0, SEEK_SET);
    fread(&db->header, sizeof(db_header), 1, dat_file);
    db->header.n_ctr = n;
    fseek(dat_file, 0, SEEK_SET);
    fwrite(&db->header, sizeof(db_header), 1, dat_file);

    /* Close files */
    fclose(dat_file);
    fclose(log_file);
	fclose(csv_file);
}

/****************************************************************************************
* Exports table from dat file to csv file (test function)
****************************************************************************************/
void export_countries(dbc *db) {
    uint i;
	country_entity entity;
	FILE *csv_file, *dat_file, *log_file;

    /* Open files */
    dat_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.dat", "rb+");
    log_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.log", "a");

    fprintf(log_file, "Country table export: starting export of %d records.\n", 
                db->header.n_ctr);
    printf("\nCountry table: exporting %d records...\n", db->header.n_ctr);

    csv_file = fopen("Data_Export"DIR_SEPARATOR"Exp_Country.csv", "w");

    /* Write the header */
    fprintf(csv_file, "Id;Name;Zone;Iso\n");

    fseek(dat_file, db->header.off_ctr, SEEK_SET);

    for (i = 0; i < db->header.n_ctr; i++) {
        memset(&entity, 0, sizeof(country_entity));
        fread(&entity, 1, sizeof(country_entity), dat_file);

        fprintf(csv_file, "%d;%s;%s;%s\n",
                entity.id, entity.name, entity.zone, entity.iso);
    }

    fprintf(log_file, "Country table export: %d records exported.\n", db->header.n_ctr);
    printf("\n%d records exported.\n\n", db->header.n_ctr);

    /* Close files */
    fclose(dat_file);
    fclose(log_file);
	fclose(csv_file);
}

/****************************************************************************************
* Loads the table into the database buffer
****************************************************************************************/
void load_countries(dbc *db) {
    uint i;
	country_entity entity;
	FILE *dat_file, *log_file;

    /* Open files */
    dat_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.dat", "rb+");
    log_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.log", "a");

    fprintf(log_file, "Country table load: starting load of %d records.\n", 
                db->header.n_ctr);
    printf("\nCountry table: loading %d records...\n", db->header.n_ctr);

    /* Load the DB file header */
    fseek(dat_file, 0, SEEK_SET);
    fread(&db->header, sizeof(db_header), 1, dat_file);

    /* Read the country table */
    fseek(dat_file, db->header.off_ctr, SEEK_SET);
    for (i = 0; i < db->header.n_ctr; i++) {
        memset(&entity, 0, sizeof(country_entity));
        fread(&entity, 1, sizeof(country_entity), dat_file);
        db->countries[i] = entity;
    }

    fprintf(log_file, "Country table load: %d records loaded.\n", db->header.n_ctr);
    printf("\n%d records loaded into the buffer.\n\n", db->header.n_ctr);

    /* Close files */
    fclose(dat_file);
    fclose(log_file);
}

/****************************************************************************************
* Prints the table
****************************************************************************************/
void print_countries(dbc *db) {
    uint i;
    for (i = 0; i < db->header.n_ctr; i++) print_country(db, i);
}

/****************************************************************************************
* Prints a record from the buffer
****************************************************************************************/
void print_country(dbc *db, uint id) {
    printf("%4d %-26s %-26s %-3s \n", db->countries[id].id, db->countries[id].name,
           db->countries[id].zone, db->countries[id].iso);
}
