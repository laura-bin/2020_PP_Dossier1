/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
*
* Manipulations de la table group
*
* Programmation procedurale 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/

#include "DB_Main.h"

/****************************************************************************************
* Imports csv file to dat file
* TODO trim
****************************************************************************************/
void import_groups(dbc *db) {
    int n = 0;                      // number of record imported
    char line[BUF_LEN];             // csv line
    char tmp_field[BUF_LEN];        // temporary field used for conversion to integer
    char *tok, *next_tok;           // line's tokens separated by strtok
	group_entity entity;            // new entity to write in the dat file
	FILE *csv_file, *dat_file, *log_file;   // file pointers

    /* Open files */
    dat_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.dat", "rb+");
    log_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.log", "a");
    csv_file = fopen("Data_Import"DIR_SEPARATOR"DB_Group.csv", "r");

    fprintf(log_file, "Group table import: starting import.\n");
    printf("\nGroup table: importing...\n");

    // TODO use error function
	if (csv_file == NULL) {
        printf("Erreur\n");
        return;
    }

    // Skip the header
    fgets(line, BUF_LEN, csv_file);

    fseek(dat_file, db->header.off_grp, SEEK_SET);
    while (fgets(line, BUF_LEN, csv_file) != NULL) {
        // Init the new entity to 0
        memset(&entity, 0, sizeof(group_entity));

        // Set type
        strcpy(entity.type, "GRP");

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

        // Set country id
        tok = next_tok;
        next_tok = strtok(NULL,";");
        memset(tmp_field, 0, BUF_LEN);
        strncpy(tmp_field, next_tok, strlen(next_tok)-1);
        entity.country_id = atoi(tmp_field);

        // Write the new entity into the dat file
        fwrite(&entity, 1, sizeof(group_entity), dat_file);

        n++;
    }

    fprintf(log_file, "Group table import: %d records imported.\n", n);
    printf("\n%d records imported.\n\n", n);

    /* Update the number of groups in the DB header */
    fseek(dat_file, 0, SEEK_SET);
    fread(&db->header, sizeof(db_header), 1, dat_file);
    db->header.n_grp = n;
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
void export_groups(dbc *db) {
    uint i;
	group_entity entity;
	FILE *csv_file, *dat_file, *log_file;

    /* Open files */
    dat_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.dat", "rb+");
    log_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.log", "a");

    fprintf(log_file, "Group table export: starting export of %d records.\n", 
                db->header.n_grp);
    printf("\nGroup table: exporting %d records...\n", db->header.n_grp);

    csv_file = fopen("Data_Export"DIR_SEPARATOR"Exp_Group.csv", "w");

    /* Write the header */
    fprintf(csv_file, "Id;Name;Country_id\n");

    fseek(dat_file, db->header.off_grp, SEEK_SET);

    for (i = 0; i < db->header.n_grp; i++) {
        memset(&entity, 0, sizeof(group_entity));
        fread(&entity, 1, sizeof(group_entity), dat_file);

        fprintf(csv_file, "%d;%s;%d\n", entity.id, entity.name, entity.country_id);
    }

    fprintf(log_file, "Group table export: %d records exported.\n", db->header.n_grp);
    printf("\n%d records exported.\n\n", db->header.n_grp);

    /* Close files */
    fclose(dat_file);
    fclose(log_file);
	fclose(csv_file);
}

/****************************************************************************************
* Prints the table
****************************************************************************************/
void print_groups(dbc *db) {
    uint i;
    FILE *dat_file;
    group_entity entity;

    dat_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.dat", "rb+");
    fseek(dat_file, db->header.off_grp, SEEK_SET);
    for (i = 0; i < db->header.n_grp; i++) {
        memset(&entity, 0, sizeof(group_entity));
        fread(&entity, 1, sizeof(group_entity), dat_file);

        printf("%4d %48s %4d\n", entity.id, entity.name, entity.country_id);
    }
    fclose(dat_file);
}