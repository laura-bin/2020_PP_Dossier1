/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Report group employees grouped by company (main/detail report)
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "report/people_by_group.h"
#include "report/report_file.h"
#include "search/binary_search.h"
#include "search/num_index_search.h"
#include "ui/ui-utils.h"
#include "utils/logger.h"
#include "utils/preprocess_string.h"
#include "search/search_result.h"

int report_people_by_group_order_by_company(struct db *db) {
    struct group *group;            // group found
    struct node *company_node;      // current node of the companies found
    struct company *company;        // company buffer
    struct node *person_node;       // current node of the people found
    struct person *person;          // person found
    struct search_result companies; // companies found
    struct search_result people;    // people found
    unsigned company_index;         // company's index used for iteration
    unsigned person_index;          // person's index used for iteration
    unsigned people_found = 0;      // 0 if no employee is registered in the database file for the searched group
    unsigned people_count = 0;      // employees count
    unsigned group_id;              // group id searched

    FILE *report;
    char filename[255];

    // copy the group searched pointer from the groups buffer stored in RAM
    printf("Enter the id searched [1-%u]: ", db->header.n_rec_table[GROUP]);
    group_id = get_uns_input();
    if (group_id == 0) {
        return 0;
    }
    if (group_id > db->header.n_rec_table[GROUP]) {
        puts("\nInvalid group id");
        return 1;
    }
    group = &db->groups[group_id-1];

    // create the new report file
    strcpy(filename, group->name);
    strcat(filename, "_employees_by_company");
    if ((report = create_report_file(filename)) == NULL) {
        log_error(db, "Creating group employees by company report file");
        perror("Creating the report file");
        return 1;
    }

    // print the report title
    fprintf(report, "%s list of employees by company\n", group->name);

    // get companies by group id searched
    companies = search_by_num_index(db, COMP_BY_GROUP_ID, group_id);
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
                    fprintf(report,
                        "%4u "
                        "%-" STR(PERSON_LASTNAME_LEN) "s "
                        "%-" STR(PERSON_FIRSTNAME_LEN) "s "
                        "%-" STR(JOB_NAME_LEN) "s\n",
                        person_index, person->lastname, person->firstname,
                        db->jobs[person->id_job-1].name);

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

    fprintf(report, "\nTOTAL group employees: %20u\n", people_count);
    fprintf(report, "TOTAL employees registered: %15u\n", people_found);
    fclose(report);

    log_info(db, "group employees report creation", "success");
    printf("Report successfully generated (%u employees found in the database)\n", people_found);

    return 0;
}
