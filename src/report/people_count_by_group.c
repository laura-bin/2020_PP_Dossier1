/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Report group employees count grouped by companies:
 *  group employees and employees known in the database (aggregation report)
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <string.h>

#include "report/people_count_by_group.h"
#include "report/report_file.h"
#include "search/num_index_search.h"
#include "search/search_result.h"
#include "ui/ui-utils.h"
#include "utils/logger.h"

int report_people_count_by_group(struct db *db) {
    struct group *group;                // group found
    unsigned group_id;                  // group id searched
    struct search_result companies;     // group companies found
    struct node *company_node;          // current node of the companies found
    struct company *company;            // company buffer
    unsigned company_index;             // company's index used for iteration
    unsigned total_employees = 0;       // company's employee count
    unsigned total_records = 0;         // company's recorded employee count
    struct search_result employees;     // company's employee found
    double percentage;

    FILE *report;
    char filename[255];
    char log_msg[255];

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
    sprintf(filename, "%s_employees_count", group->name);
    sprintf(log_msg, "Creating group employees count report (%s)", group->name);
    if ((report = create_report_file(filename)) == NULL) {
        log_error(db, log_msg);
        perror("Creating the report file");
        return 1;
    }

    // print the report title
    fprintf(report, "%s (%s) employees count\n", group->name, db->countries[group->country_id-1].name);

    // get companies by group id searched
    companies = search_by_num_index(db, COMP_BY_GROUP_ID, group_id);
    if (companies.result_count > 0) {
        company_node = companies.head;
        company_index = 1;

        // list companies employees count
        while (company_node) {
            company = company_node->data;
            total_employees += company->n_employees;
            employees = search_by_num_index(db, PERS_BY_COMP_ID, company->id);
            total_records += employees.result_count;
            if (company->n_employees) {
                percentage = (double)employees.result_count * 100.0 / (double)company->n_employees;
            } else {
                percentage = 0.0;
            }

            fprintf(report, "\n[%u/%u] %s (%s)\n",
                company_index, companies.result_count, company->name,
                db->countries[company->id_country-1].name);
            fprintf(report, "\tNumber of employees: %12u\n", company->n_employees);
            fprintf(report, "\tRecorded employees:  %12u  %5.2lf%%\n", employees.result_count, percentage);

            free_list(employees.head, 1);
            company_index++;
            company_node = company_node->next;
        }
        free_list(companies.head, 1);
    } else {
        fprintf(report, "\nNo company registered in the database\n");
    }

    // compute total percentage of employees recorded
    percentage = total_employees ? (double)total_records * 100.0 / (double)total_employees : 0.0;

    fprintf(report, "\nTOTAL number of employees: %10u\n", total_employees);
    fprintf(report, "TOTAL recorded employees:  %10u  %5.2lf%%\n", total_records, percentage);
    fclose(report);

    log_info(db, log_msg, "Success");
    printf("Report successfully generated - %5.2lf%% employees recorded\n", percentage);

    return 0;
}
