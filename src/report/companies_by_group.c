/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 * 
 * Report group companies grouped by country (main/detail report)
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include <stdlib.h>
#include <string.h>

#include "report/companies_by_group.h"
#include "report/report_file.h"
#include "report/utils.h"
#include "search/num_index_search.h"
#include "search/search_result.h"
#include "table/company.h"
#include "utils/logger.h"
#include "utils/preprocess_string.h"


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
