/** *************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * Database indexes creation
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 ****************************************************************************************/

#include "db_file/catalog.h"
#include "db_file/index.h"

int create_person_by_company_id(struct db *db) {
    return 0;
}


int create_person_by_lastname(struct db *db) {
    return 0;
}


// int create_index(struct db *db) {
//     int i;
//     unsigned offset;
//     struct person person;
//     struct person_by_lastname index;

//     // charger les données à trier : id company + offset de la personne
//     for (i = 0; i < db->header.n_table_rec[PERSON]; i++) {
//         memset(&person, 0, sizeof(struct person));
//         offset = db->header.table_off[PERSON] + i * sizeof(struct person);
//         fseek(db->dat_file, offset, SEEK_SET);
//         fread(&person, sizeof(struct person), 1, db->dat_file);

//         // remplir une structure de tri temporaire
//         strcpy(db->sort[i].nm_sort, person.lastname);
//         db->sort[i].nr_offset = offset;
//     }

//     // tri avec quick sort
//     quick_sort(db, 0, db->header.n_table_rec[PERSON]-1, NM_SRT);

//     // ecrire dans la db
//     fseek(db->dat_file, db->header.index_off[PERS_BY_COMP_ID], SEEK_SET);

//     for (i = 0; i < db->header.n_table_rec[PERSON]; i++) {
//         memset(&index, 0, sizeof(struct person_by_company));
//         strcpy(index.type, "IPN");
//         strcpy(index.lastname, db->sort[i].nm_srt);
//         index.offset = db->sort[i].offset;

//         fwrite(&index, 1, sizeof(struct person_by_lastname), db->dat_file);
//     }

//     // creation de l'arbre
//     // remplir les noeuds a-gauche et droits (pour les noms seulement)
//     int lev = 0;
//     db->header.index_off[PERSON] // head de l'arbre
//         = tree_ipn(db, (db->header.n_table_rec[PERSON]-1) / 2, db->header.n_table_rec[PERSON], 'R');

        

//     return 0;
// }
