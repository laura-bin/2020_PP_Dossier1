#pragma once
/** *******************************************************************************************************************
 * Dossier 1 : Analyse de donnees clients
 * ======================================
 *
 * String utils functions:
 *  - lower a string
 *  - string contains a substring (case insensitive)
 *  - string starts with a substring (case insensitive)
 *  - replacement of a character by another one
 *
 * PP 2020-2021 - Laura Binacchi - Fedora 32
 *********************************************************************************************************************/

/**
 * Creates a new lowercase string from a given string
 * /!\ free after use
 *
 * @param str: string to lower
 *
 * @return the lowercase string
 */
char* lower_str(char *str);

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
 *          < 0 if the substring is before the string in alphabetical order
 *          0 if the string starts with the substring
 *          > 0 if the substring is after the string in alphabetical order
 */
int start_with_icase(char *string, char *searched);

/**
 * Replaces a character of a string with another one
 * 
 * @param string: string in which replace character(s)
 * @param search: character to replace
 * @param replace: replacement character
 */
void string_replace(char *string, char search, char replace);
