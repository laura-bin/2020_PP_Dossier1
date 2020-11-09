// /****************************************************************************************
// * Dossier 1 : Analyse de donnees clients
// *
// * Definition des structures
// *
// * Programmation procedurale 2020 - Laura Binacchi
// ****************************************************************************************/
// #include <stdio.h>
// #include <ctype.h>
// #include <stdlib.h>
// #include <string.h>


// #ifdef _WIN32
// #define DIR_SEPARATOR "\\"
// #else
// #define DIR_SEPARATOR "/"
// #endif
// #define BUF_LEN 200

// typedef unsigned int uint;






// /****************************************************************************************
// * Prototypes
// ****************************************************************************************/
// void create_db(dbc *db);                // Create an empty database file

// // Country table
// void import_countries(dbc *db);         // imports the country csv file to dat file
// void export_countries(dbc *db);         // exports the country table from dat file to csv file
// void load_countries(dbc *db);           // loads the country table from the dat file to the buffer
// void print_countries(dbc *db);          // prints the country table
// void print_country(dbc *db, uint id);   // prints a single country from the database buffer

// // Job table
// void import_jobs(dbc *db);          // imports the job csv file to dat file
// void export_jobs(dbc *db);          // exports the job table from dat file to csv file
// void load_jobs(dbc *db);            // loads the job table from the dat file to the buffer
// void print_jobs(dbc *db);           // prints the job table
// void print_job(dbc *db, uint id);   // prints a single job from the database buffer

// // Industry table
// void import_industries(dbc *db);         // imports the industry csv file to dat file
// void export_industries(dbc *db);         // exports the industry table from dat file to csv file
// void load_industries(dbc *db);           // loads the industry table from the dat file to the buffer
// void print_industries(dbc *db);          // prints the industry table
// void print_industry(dbc *db, uint id);   // prints a single industry from the database buffer

// // Group table
// void import_groups(dbc *db);        // imports the group csv file to dat file
// void export_groups(dbc *db);        // exports the group table from dat file to csv file
// void print_groups(dbc *db);         // prints the group table from the database file