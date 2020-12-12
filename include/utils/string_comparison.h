#pragma once
/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * String comparison function
 *
 * PP 2020 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

/**
 * Tests if a substring is contained in at least one of the given strings
 * (case insensitive)
 *
 * @param n_str: number of strings to compare with the substring
 * @param substr: substring searched
 * @param ...: strings compared to the substring
 *
 * @return either:
 *          1 if at least one of the strings contains the substring
 *          0 if no string contains the substring
 */
int contains_icase(int n_str, char* substr, ...);
