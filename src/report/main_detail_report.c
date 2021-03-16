/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * TODO
 * Main/detail reports:
 *  - group employees grouped by company
 *  - group companies grouped by country
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "report/main_detail_report.h"
#include "report/report_file.h"
#include "search/binary_search.h"
#include "search/num_index_search.h"
#include "table/company.h"
#include "ui/ui-utils.h"
#include "utils/logger.h"
#include "utils/preprocess_string.h"
#include "search/search_result.h"

/* PRIVATE FUNCTION */

/**
 * Gets one tuple from the id entered by the user
 * (binary search in the table buffers)
 * and searches the tuple in the database file.
 * If no tuple is found, print the nearest result found.
 * 
 * @param db: database file information stored in RAM
 * @param table: table in which search the tuple
 * @param out_searched: id searched, 0 if the id must be asked to the user
 * 
 * @return either
 *      the tuple found
 *      NULL if an error occured or if no tuple exists with the given id
 */
void *get_one_by_id(struct db *db, enum table table, unsigned *out_searched) {
    unsigned offset;    // tuple offset found
    void *tuple;        // tuple found

    const struct table_metadata *table_info = &tables_metadata[table];
    
    // get the user input
    if (!*out_searched) {
        printf("Enter the id searched: ");
        *out_searched = get_uns_input();
    }

    // get the tuple offset (or the offset of the nearest result)
    offset = binary_search(db, *out_searched, 0, db->header.n_rec_table[table]-1, table);
    if (offset == UINT_MAX) {
        log_info(db, "Searching tuple by id", strerror(errno));
        return NULL;
    }

    // get the tuple from the database file
    tuple = (*table_info->read)(db, offset);
    if (tuple == NULL) {
        log_info(db, "Reading tuple into the database file", strerror(errno));
    }

    return tuple;
}

/* HEADER IMPLEMENTATION */

int report_people_by_group_order_by_company(struct db *db) {
    struct group *group;            // group found
    struct node *company_node;      // current node of the companies found
    struct company *company;        // company buffer
    struct node *person_node;       // current node of the people found
    struct person *person;          // person found
    struct job *job;                // job buffer
    struct search_result companies; // companies found
    struct search_result people;    // people found
    unsigned company_index;         // company's index used for iteration
    unsigned person_index;          // person's index used for iteration
    unsigned people_found = 0;      // 0 if no employee is registered in the database file for the searched group
    unsigned people_count = 0;      // employees count
    unsigned id_searched;           // tuple id searched (used for binary search)

    FILE *report;
    char filename[255];

    // get the group with the id given by the user
    id_searched = 0;
    group = get_one_by_id(db, GROUP, &id_searched);
    if (group == NULL) {
        perror("An error occured while searching the group");
        return 1;
    } else if (group->id != id_searched) {
        // if the group found is not the group searched, print the nearest result
        printf("\nNo record found\nNearest record id: [%u]\n", group->id);
        free(group);
        return 1;
    }

    // create the new report file
    strcpy(filename, group->name);
    strcat(filename, "_employees_by_company");
    if ((report = create_report_file(filename)) == NULL) {
        log_error(db, "Creating group emplyees by company report file");
        perror("Creating the report file");
        return 1;
    }

    // print the report title
    fprintf(report, "%s list of employees by company\n", group->name);

    // get companies by group id searched
    companies = search_by_num_index(db, COMP_BY_GROUP_ID, id_searched);
    if (companies.result_count > 0) {
        company_node = companies.head;
        company_index = 1;

        // list companies
        while (company_node) {
            company = company_node->data;
            people_count += company->n_employees;

            fprintf(report, "\n[%u/%u] %s (%u employees)\n",
                company_index, companies.result_count, company->name, company->n_employees);

            // get employees of the company
            people = search_by_num_index(db, PERS_BY_COMP_ID, company->id);

            if (people.result_count > 0) {
                person_node = people.head;
                person_index = 1;
                people_found += people.result_count;

                fprintf(report,
                    "%4s "
                    "%-" STR(PERSON_LASTNAME_LEN) "s "
                    "%-" STR(PERSON_FIRSTNAME_LEN) "s "
                    "%-" STR(JOB_NAME_LEN) "s\n",
                    "", "LASTNAME", "FIRSTNAME", "JOB");

                // list employees
                while (person_node) {
                    person = person_node->data;

                    // get employee's job
                    job = get_one_by_id(db, JOB, &person->id_job);

                    if (job == NULL) {
                        job = malloc(sizeof(struct job));
                        strcpy(job->name, "unknown");
                    } else if (job->id != person->id_job) {
                        strcpy(job->name, "unknown");
                    }

                    fprintf(report,
                        "%4u "
                        "%-" STR(PERSON_LASTNAME_LEN) "s "
                        "%-" STR(PERSON_FIRSTNAME_LEN) "s "
                        "%-" STR(JOB_NAME_LEN) "s\n",
                        person_index, person->lastname, person->firstname, job->name);

                    free(job);
                    person_index++;
                    person_node = person_node->next;
                }

                free_list(people.head, 1);
            } else {
                fprintf(report, "\tNo employee registered for this company\n");
            }
            company_index++;
            company_node = company_node->next;
        }
        free_list(companies.head, 1);
    } else {
        fprintf(report, "\nNo company registered in the database\n");
    }

    free(group);

    fprintf(report, "\nTOTAL group employees: %20u\n", people_count);
    fprintf(report, "TOTAL employees registered: %15u\n", people_found);
    fclose(report);

    log_info(db, "group employees report creation", "success");
    printf("Report successfully generated (%u employees found in the database)\n", people_found);

    return 0;
}

int report_companies_by_group_order_by_country(struct db *db) {
    struct group *group;            // group found
    struct node *company_node;      // current node of the companies found
    struct search_result companies; // list of companies found
    struct company *company;        // company buffer
    unsigned previous_country_id;   // previous country id stored for comparison
    unsigned company_index;         // company's index used for iteration
    struct country *country;        // country buffer
    unsigned id_searched;           // tuple id searched (used for binary search)
    unsigned companies_found = 0;
    unsigned countries_found = 0;
    FILE *report;
    char filename[255];

    // get the group with the id given by the user
    id_searched = 0;
    group = get_one_by_id(db, GROUP, &id_searched);
    if (group == NULL) {
        perror("An error occured while searching the group");
    } else if (group->id != id_searched) {
        // if the group found is not the group searched, print the nearest result
        printf("\nNo record found\nNearest record id: [%u]\n", group->id);
        free(group);
        return 1;
    }

    // create the new report file
    strcpy(filename, group->name);
    strcat(filename, "_companies_by_country");
    if ((report = create_report_file(filename)) == NULL) {
        log_error(db, "Creating group companies by country report file");
        perror("Creating the report file");
        return 1;
    }

    // print the report title
    fprintf(report, "%s list of companies by country\n", group->name);

    // get companies by group id searched
    companies = search_by_num_index(db, COMP_BY_GROUP_ID, id_searched);

    if (companies.result_count > 0) {
        // sort the companies list by country id
        sort_linked_list(&companies, compare_company_country_id);
        previous_country_id = 0;
        company_node = companies.head;

        // print companies information
        while (company_node) {
            company = company_node->data;
            companies_found++;

            // print the group information
            if (previous_country_id != company->id_country) {
                previous_country_id = company->id_country;
                countries_found++;
                company_index = 1;
                country = get_one_by_id(db, COUNTRY, &company->id_country);
                fprintf(report, "\n%s (%s)\n", country->name, country->zone);
                fprintf(report,
                        "%4s "
                        "%-" STR(COMPANY_NAME_LEN) "s "
                        "%-" STR(COMPANY_ZIP_CODE_LEN) "s "
                        "%-" STR(COMPANY_CITY_LEN) "s\n",
                        "", "NAME", "ZIP CODE", "CITY");
                free(country);
            }
            fprintf(report,
                        "%4u "
                        "%-" STR(COMPANY_NAME_LEN) "s "
                        "%-" STR(COMPANY_ZIP_CODE_LEN) "s "
                        "%-" STR(COMPANY_CITY_LEN) "s\n",
                        company_index, company->name, company->zip_code, company->city);

            company_node = company_node->next;
        }
        free_list(companies.head, 1);

    } else {
        fprintf(report, "\nNo company registered in the database\n");
    }

    fprintf(report, "\nTOTAL countries: %16u\n", countries_found);
    fprintf(report, "TOTAL companies: %16u\n", companies_found);
    fclose(report);

    log_info(db, "group companies report creation", "success");
    printf("Report successfully generated (%u companies found in %u countries)\n",
                companies_found, countries_found);

    return 0;
}
