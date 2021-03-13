/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Main/detail reports:
 *  - Liste de toutes les personnes travaillant pour chaque compagnie d’un groupe
 *  - Liste de toutes les compagnies appartenant à un groupe, par pays
 *  - people by company name prefix
 *      result x    company.id    company.name    group.name    country.name    industry.name
 *      company.address
 *      company.zip_code    company.city
 *      company.phone_number
 *      company.website
 *      company.n_employees (share value ?)
 *      --------
 *          result x    person.id    person.lastname    person.firstname    job.name
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/database.h"

int report_people_by_company_name(struct db *db);
int report_people_by_group_order_by_company(struct db *db);
int report_companies_by_group_order_by_country(struct db *db);
