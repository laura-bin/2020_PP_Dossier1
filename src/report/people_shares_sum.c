/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Report employees share value sum grouped by gender and by job (aggregation report)
 * valeur totale des actions détenues par les employés pour un groupe donné, éclaté par par genre et niveau
de fonction
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "report/people_shares_sum.h"
#include "report/report_file.h"
#include "search/num_index_search.h"
#include "ui/ui-utils.h"
#include "utils/logger.h"
#include "utils/preprocess_string.h"
#include "utils/string_replace.h"

#define FORMAT          "\n%-"STR(JOB_LEVEL_LEN)"s %20.2lf\n"
#define FORMAT_PERCENT  "%-"STR(JOB_LEVEL_LEN)"s %20.2lf    %5.2lf%%\n"

int report_people_shares_sum_group_by_job_level_group_by_gender(struct db *db) {
    unsigned group_id;                  // group id searched
    struct group *group;                // group found
    struct search_result companies;     // group companies found
    struct node *company_node;          // current node of the companies found
    struct company *company;            // company buffer
    struct search_result employees;     // company's employee
    struct node *person_node;           // current node of the employee found
    struct person *person;              // person buffer

    struct node *report_head = NULL;            // first element of the report list of data
    struct node *report_tail = NULL;            // last element of the report list of data
    struct node *report_node = NULL;            // current element of the report list of data
    struct people_shares_data *data;            // current data buffer
    struct people_shares_data *report_data;     // report data

    double total = 0;       // total sum of shares for all the group
    double total_f = 0;     // total sum of shares for all the female employees of the group
    double total_m = 0;     // total sum of shares for all the male employees of the group
    double total_x = 0;     // total sum of shares for all the non binary employees of the group
    double total_job;       // total sum of shares for a job level
    double value;           // double value result


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
    char *group_name = strdup(group->name);
    string_replace(group_name, ' ', '_');
    sprintf(filename, "%s_employees_shares_sum", group_name);
    free(group_name);

    sprintf(log_msg, "Creating employees sum of shares values report (%s)", group->name);
    if ((report = create_report_file(filename)) == NULL) {
        log_error(db, log_msg);
        perror("Creating the report file");
        return 1;
    }

    // print the report title
    fprintf(report, "%s employees sum of shares\n", group->name);

    // get companies by group id searched
    companies = search_by_num_index(db, COMP_BY_GROUP_ID, group_id);
    if (companies.result_count > 0) {
        company_node = companies.head;

        // for each company
        while (company_node) {
            company = company_node->data;
            employees = search_by_num_index(db, PERS_BY_COMP_ID, company->id);
            if (employees.result_count > 0) {
                person_node = employees.head;

                // and for each employee of the company
                while (person_node) {
                    person = person_node->data;
                    report_node = report_head;
                    report_data = NULL;

                    // check if the job level of the employee is already in the report
                    while (report_node && report_data == NULL) {
                        data = report_node->data;
                        if (!strcmp(db->jobs[person->id_job-1].level, data->job_level)) {
                            report_data = data;
                        }
                        report_node = report_node->next;
                    }

                    // else create a new report data structure and add it to the report list
                    if (report_data == NULL) {
                        report_data = malloc(sizeof(struct people_shares_data));
                        strcpy(report_data->job_level, db->jobs[person->id_job-1].level);
                        report_data->shares_sum_f = 0;
                        report_data->shares_sum_m = 0;
                        report_data->shares_sum_x = 0;
                        report_tail = append_item(report_tail, report_data);

                        if (report_head == NULL) {
                            report_head = report_tail;
                        }
                    }

                    // then compute the sum of shares
                    value = company->share_value * (double)person->shares;
                    total += value;
                    if (person->gender[0] == 'F') {
                        total_f += value;
                        report_data->shares_sum_f += value;
                    } else if (person->gender[0] == 'M') {
                        total_m += value;
                        report_data->shares_sum_m += value;
                    } else {
                        total_x += value;
                        report_data->shares_sum_x += value;
                    }

                    person_node = person_node->next;
                }

                free_list(employees.head, 1);
            }

            company_node = company_node->next;
        }
        free_list(companies.head, 1);

        // print the result list
        report_node = report_head;
        while (report_node) {
            data = report_node->data;
            total_job = data->shares_sum_f + data->shares_sum_m + data->shares_sum_x;

            // job level name
            fprintf(report, "\n%s\n", data->job_level);

            // female employees shares
            value = total_job ? data->shares_sum_f * 100.0 / total_job : 0.0;
            fprintf(report, FORMAT_PERCENT, "    female", data->shares_sum_f, value);

            // male employees shares
            value = total_job ? data->shares_sum_m * 100.0 / total_job : 0.0;
            fprintf(report, FORMAT_PERCENT, "    male", data->shares_sum_m, value);

            // non binary employees shares
            value = total_job ? data->shares_sum_x * 100.0 / total_job : 0.0;
            fprintf(report, FORMAT_PERCENT, "    non binary", data->shares_sum_x, value);

            // total and percentage job / total
            value = total ? total_job * 100.0 / total : 0.0;
            fprintf(report, FORMAT_PERCENT, "    TOTAL", total_job, value);
            
            report_node = report_node->next;
        }
    } else {
        fprintf(report, "\nNo company registered in the database\n");
    }

    fprintf(report, "\n\n");


    value = total ? total_f * 100.0 / total : 0.0;
    fprintf(report, FORMAT_PERCENT, "TOTAL female", total_f, value);

    value = total ? total_m * 100.0 / total : 0.0;
    fprintf(report, FORMAT_PERCENT, "TOTAL male", total_m, value);

    value = total ? total_x * 100.0 / total : 0.0;
    fprintf(report, FORMAT_PERCENT, "TOTAL non binary", total_x, value);

    fprintf(report, FORMAT, "TOTAL", total);


    fclose(report);

    log_info(db, log_msg, "Success");
    printf("Report successfully generated\n");

    return 0;
}
