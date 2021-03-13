/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Aggregation reports:
 *  - Nombre de personnes par groupe (somme des nr_emp) et nombre de personnes connues dans la DB
(comptage des records personnes liés au groupe)
 *    number of employees by group and number of people records by group
 *      group.id    group.name    country.name
 *      --------
 *          n_employees    count(employees)
 *     (éclaté par company ??)
 *  - valeur totale des actions détenues par les employés pour un groupe donné, éclaté par par genre et niveau
de fonction
 *      group.id    group.name    country.name
 *      
 * 
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

int report_count_people_by_group(struct db *db);
int report_sum_shares_by_employee_group_by_gender_group_by_job(struct db *db);
