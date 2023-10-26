/**
 * \file utils.h
 * \brief This file contains type declarations and prototypes of functions for :
 *          - allocation / release of int matrixes
 *          - checking file names
 *          - conversion of char from base64 to binary
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#ifndef __UTILS__
#define __UTILS__

/**
 * The list of forbiden characters in an output file name.
 */
extern const char *forbidenCharactersInFiles;

/**
 * The list of the base 64 characters.
 */
extern const char *BASE64;

/**
 * \brief Create an int matrix of size n.
 *
 * \param n The number of lines.
 * \param m The number of columns.
 *
 * \pre n>0, m>0
 * \post A matrix of unsigned ints is return.
 *
 * \return unsigned int** The matrix created.
 */
unsigned int **create_matrix(unsigned int n, unsigned int m);

/**
 * \brief Free an int matrix of size n.
 *
 * \param m The matrix to free.
 * \param lines The number of lines
 *
 * \pre m is instanced
 * \post Memory space occupied by the matrix is frees.
 */
void free_matrix(unsigned int **m, unsigned int lines);

/**
 * \brief Convert a string made of base 64 characters in a string containing the binary representation of each character.
 *
 * \param string The string to convert.
 *
 * \pre string is instanced.
 * \post The binary representation is returned.
 *
 * \return char* The binary representation.
 */
char *base64_string_to_binary_string(char *string);

/**
 * \brief Returns the fileName extension.
 *
 * \param fileName The file path containing the image.
 *
 * \pre filename != NULL
 * \post The file name has been checked.
 *
 * \return char* The extension if found.
 *               NULL in the other cases.
 */
char *get_file_extension(char *fileName);

/**
 * \brief Check if the file contain fordiden characters.
 *
 * \param fileName the file name (wich must be in the same directory).
 *
 * \pre filename is instanced, size > 0
 * \post File name has been check.
 *
 * \return  int 1 File name is allowed
 *              0 File name isn't allowed
 */
int check_file_name(char *fileName);

#endif //__UTILS__
