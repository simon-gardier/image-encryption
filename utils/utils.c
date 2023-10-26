/**
 * \file utils.c
 * \brief This file contains type definitions and functions for manipulating matrices and file names
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "utils.h"

/**
 * \def BASE64_CHAR_BINARY_SIZE
 * The size of the binary representation of a character.
 */
#define BASE64_CHAR_BINARY_SIZE 6

const char *forbidenCharactersInFiles = "/\\:*?\"<>|";
const char *BASE64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

unsigned int **create_matrix(unsigned int matrix_len, unsigned int row_len)
{
    assert(matrix_len > 0 && row_len > 0);
    unsigned int **matrix;

    if (!(matrix = malloc(sizeof(int *) * matrix_len)))
    {
        return NULL;
    }

    for (unsigned i = 0; i < matrix_len; i++)
    {
        matrix[i] = malloc(row_len * sizeof(unsigned int));
        if (!matrix[i])
        {
            for (unsigned j = 0; j < i; j++)
            {
                free(matrix[j]);
            }
            free(matrix[i]);
            return NULL;
        }
    }

    return matrix;
} // end create_matrix()

void free_matrix(unsigned int **m, unsigned int lines)
{
    assert(m);
    for (unsigned i = 0; i < lines; i++)
    {
        free(m[i]);
        m[i] = NULL;
    }
    free(m);
    m = NULL;
} // end free_matrix()

char *base64_string_to_binary_string(char *string)
{
    assert(string);

    char *toBinaryString = malloc(sizeof(char) * ((BASE64_CHAR_BINARY_SIZE + 1) * strlen(string) + 1));
    if (!toBinaryString)
    {
        return NULL;
    }
    toBinaryString[(BASE64_CHAR_BINARY_SIZE + 1) * strlen(string)] = '\0';

    for (unsigned int i = 0; i < strlen(string); i++)
    {
        char *indexInBase64 = strchr(BASE64, string[i]);
        if (!indexInBase64)
        {
            printf("> 🔴 The character [%c] isn't allowed. Please use only these : [%s].\n", string[i], BASE64);
            return NULL;
        }

        unsigned int decimalCharacterRepresentation = (unsigned int)(indexInBase64 - BASE64);

        char *binaryCharacterRepresentation = malloc((BASE64_CHAR_BINARY_SIZE + 1) * sizeof(char));
        if (!binaryCharacterRepresentation)
        {
            free(toBinaryString);
            return NULL;
        }
        binaryCharacterRepresentation[BASE64_CHAR_BINARY_SIZE] = '\0';

        for (int j = BASE64_CHAR_BINARY_SIZE; j > 0; j--)
        {
            if (decimalCharacterRepresentation % 2 == 0)
            {
                binaryCharacterRepresentation[j - 1] = '0';
            }
            else
            {
                binaryCharacterRepresentation[j - 1] = '1';
            }
            decimalCharacterRepresentation /= 2;
        } // end for j
        strcat(toBinaryString, binaryCharacterRepresentation);
        free(binaryCharacterRepresentation);
    } // end for i

    return toBinaryString;
} // end base64_string_to_binary_string()

char *get_file_extension(char *fileName)
{
    assert(fileName != NULL);
    char *extension;
    if (!(extension = strrchr(fileName, '.')))
    {
        printf("> 🔴 The file name [%s] does not contain an extension.\n", fileName);
        return NULL;
    }
    extension++;
    return extension;
} // end get_file_extension()

int check_file_name(char *fileName)
{
    assert(fileName != NULL);
    unsigned int size = strlen(fileName);
    unsigned int forbidenCharactersLen = strlen(forbidenCharactersInFiles);
    unsigned int extensionFounded = 0;
    // iteration in the  fileName
    for (unsigned int i = 0; i < size; i++)
    {
        if (fileName[i] == '.')
        {
            if (!extensionFounded)
            {
                extensionFounded = 1;
            }
            else
            {
                printf("> 🔴 The file name [%s] contain more than one [.] character (wich shouldn't happen).\n", fileName);
                return 0;
            }
        }
        // check the current character in fileName
        for (unsigned int j = 0; j < forbidenCharactersLen; j++)
        {
            if (fileName[i] == forbidenCharactersInFiles[j])
            {
                printf("> 🔴 The file name [%s] contain at least a forbiden character : [%c].\n", fileName, forbidenCharactersInFiles[j]);
                return 0;
            }
        }
    }
    return 1;
} // end check_file_name()
