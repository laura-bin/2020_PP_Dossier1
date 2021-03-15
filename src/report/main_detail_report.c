/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * TODO
 * Main/detail reports:
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "db_file/catalog.h"
#include "report/main_detail_report.h"
#include "search/binary_search.h"
#include "search/num_index_search.h"
#include "ui/ui-utils.h"
#include "utils/logger.h"
#include "report/report_file.h"
#include "table/company.h"
#include "utils/preprocess_string.h"

int report_people_by_group_order_by_company(struct db *db) {
    struct group *group;            // group found
    struct node *company_node;      // current node of the companies found
    struct company *company;        // company buffer
    struct node *person_node;       // current node of the people found
    struct person *person;          // person found
    struct job *job;                // job buffer
    struct search_result companies; // companies found
    struct search_result people;    // people found
    unsigned offset;                // tuple offset found
    unsigned company_index;         // company's index used for iteration
    unsigned person_index;          // person's index used for iteration
    unsigned people_found = 0;      // 0 if no employee is registered in the database file for the searched group
    unsigned people_count = 0;      // employees count

    const struct table_metadata *group_table_info = &tables_metadata[GROUP];
    const struct table_metadata *job_table_info = &tables_metadata[JOB];

    FILE *report;
    char filename[255];
    
    // get the user input
    printf("Enter the group id searched: ");
    unsigned searched = get_uns_input();

    // get the group offset (or the offset of the nearest result)
    offset = binary_search(db, searched, 0, db->header.n_rec_table[GROUP]-1, GROUP);
    if (offset == UINT_MAX) {
        log_info(db, "Searching group by id", strerror(errno));
        printf("\nAn error occured: %s\n", strerror(errno));
        return 1;
    }

    // get the group from the database file
    group = (*group_table_info->read)(db, offset);
    if (group == NULL) {
        log_info(db, "Reading group in the database file", strerror(errno));
        printf("\nAn error occured: %s\n", strerror(errno));
        return 1;
    }

    // compare if the group found is the group searched by the user
    if (group->id != searched) {
        // if not: print the nearest result group id
        printf("\nNo group found\nNearest group id: [%u]\n", group->id);
        free(group);
        return 1;
    }

    strcpy(filename, group->name);
    strcat(filename, "_employees_report");
    report = open_report_file(filename);

    // open the file
    if (report == NULL) {
        log_error(db, "Creating people by group report file");
        perror("Creating people by group report file");
        return 1;
    }

    fprintf(report, "%s list of employees\n", group->name);

    // get companies by group id
    companies = search_by_num_index(db, COMP_BY_GROUP_ID, searched);
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
                    offset = binary_search(db, person->id_job, 0, db->header.n_rec_table[JOB]-1, JOB);
                    if (offset != UINT_MAX) {
                        job = (*job_table_info->read)(db, offset);
                    } else {
                        job = malloc(sizeof(struct job));
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

    fprintf(report, "\nTOTAL group employees: %24u\n", people_count);
    fprintf(report, "TOTAL employees registered: %19u\n", people_found);
    fclose(report);

    log_info(db, "group employees report creation", "success");
    printf("Report successfully generated (%u employees found in the database)\n", people_found);

    return 0;
}

int report_companies_by_group_order_by_country(struct db *db) {






    return 0;
}
