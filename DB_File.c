/****************************************************************************************
* Dossier 1 : Analyse de donnees clients
*
* Creation du fichier de base de données
*
* Programmation procedurale 2020 - Laura Binacchi - Fedora 32
****************************************************************************************/
#include "DB_Main.h"

/****************************************************************************************
* Create an empty DB file (.dat)
****************************************************************************************/
void create_db(dbc *db) {
    int i;
    country_entity country;
    job_entity job;
    industry_entity industry;
    group_entity group;
    FILE *dat_file, *log_file;    // dat & log files

    /* Open files */
    dat_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.dat", "wb");
    log_file = fopen("Data_DB_Comp"DIR_SEPARATOR"DB_Comp.log", "a");

    /* Create header */
    memset(&db->header, 0, sizeof(db_header));

    strcpy(db->header.db_name, "DB_Comp");

    db->header.n_res_ctr = N_RES_CTR;
    db->header.n_res_job = N_RES_JOB;
    db->header.n_res_ind = N_RES_IND;
    db->header.n_res_grp = N_RES_GRP;

    db->header.off_ctr = sizeof(db_header);
    db->header.off_job = db->header.off_ctr + N_RES_CTR*sizeof(country_entity);
    db->header.off_ind = db->header.off_job + N_RES_JOB*sizeof(job_entity);
    db->header.off_grp = db->header.off_ind + N_RES_IND*sizeof(industry_entity);

    db->header.db_size = db->header.off_grp + N_RES_GRP*sizeof(group_entity);

    db->header.n_ctr = 0;
    db->header.n_job = 0;
    db->header.n_ind = 0;
    db->header.n_grp = 0;

    fwrite(&db->header, 1, sizeof(db->header), dat_file);

    /* Create empty country table */
    memset(&country, 0, sizeof(country_entity));
    strcpy(country.type, "CTR");
    for (i = 0; i < N_RES_CTR; i++) {
        fwrite(&country, 1, sizeof(country_entity), dat_file);
    }

    /* Create empty job table */
    memset(&job, 0, sizeof(job_entity));
    strcpy(job.type, "JOB");
    for (i = 0; i < N_RES_JOB; i++) {
        fwrite(&job, 1, sizeof(job_entity), dat_file);
    }

    /* Create empty industry table */
    memset(&industry, 0, sizeof(industry_entity));
    strcpy(industry.type, "IND");
    for (i = 0; i < N_RES_IND; i++) {
        fwrite(&industry, 1, sizeof(industry_entity), dat_file);
    }

    /* Create empty group table */
    memset(&group, 0, sizeof(group_entity));
    strcpy(group.type, "GRP");
    for (i = 0; i < N_RES_GRP; i++) {
        fwrite(&group, 1, sizeof(group_entity), dat_file);
    }

    fprintf(log_file, "Database %s created\n", db->header.db_name);

    fclose(dat_file);
    fclose(log_file);

    printf("Database %s created \n", db->header.db_name);
}
