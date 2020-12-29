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
int contain_icase(int n_str, char* substr, ...);

/**
 * Tests if a string starts with a substring
 * (case insensitive)
 *
 * @param string: string to compare
 * @param searched: searched substring
 *
 * @return either:
 *          < 0 if the string is shorter than the substring
 *              or if the substring is before the string in alphabetical order
 *          0 if the string starts with the substring
 *          > 0 if the substring is after the string in alphabetical order
 */
int start_with_icase(char *string, char *searched);
