/**
 * \file pnm.c
 * \brief This file contains the PNM type definitions and the PNM images manipulation functions.
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "pnm.h"
#include "../utils/utils.h"

/**
 * \def MAGIC_NUMBER_LEN
 * @brief The size of a magic number.
 */
#define MAGIC_NUMBER_LEN 3

/**
 * \struct PNM_t
 * \brief  Data structure representing a pnm image
 */
struct PNM_t
{
    MAGIC_NUMBERS magicNumber;     /*!< The magic number of the file (P1, P2, P3). */
    unsigned int columns;          /*!< The quantity of columns / the length of a line. */
    unsigned int lines;            /*!< The quantity of lines / the length of the pixels matrix. */
    unsigned int maxPossibleValue; /*!< The maximum encoding value (in case of P2 / P3 file). */
    unsigned int **pixels;         /*!< The matrix of pixels */
};

/**
 * \fn static int go_to_next_data(FILE* fp, unsigned int* breakPointLine)
 * \brief Go to the first visible character (i.e. not [' ', '\n', '\r', '', '\t',...] ) wich isn't in a commented area.
 *
 * \param fp file to iterate into.
 * \param breakPointLine The current line in the file.
 *
 * \pre fp is instanced, breakPointLine is instanced.
 * \post The playhead points to the next uncommented area.
 *
 * \return int 0 error
 *             1 success
 */
static int go_to_next_data(FILE *fp, unsigned int *breakPointLine)
{
    assert(fp && breakPointLine);
    char buffer;
    int valueFound = 0;

    while (!valueFound)
    {
        if ((buffer = getc(fp)) < 0)
        {
            return 0;
        }
        if (buffer == '\n' || buffer == '\r')
        {
            (*breakPointLine)++;
        }
        if (isgraph(buffer))
        {
            valueFound = 1;
        }
    }

    if (buffer == '#')
    {
        int newLineFound = 0;
        while (!newLineFound)
        {
            if ((buffer = getc(fp)) < 0)
            {
                return 0;
            }
            if (buffer == '\n' || buffer == '\r')
            {
                (*breakPointLine)++;
                newLineFound = 1;
            }
        }
        if (!go_to_next_data(fp, breakPointLine))
        {
            return 0;
        }
    }
    else
    {
        ungetc(buffer, fp);
    }

    return 1;
} // end go_to_next_data()

/**
 * \fn static int store_pixels(FILE* imageFile, PNM** image, unsigned int* breakPointLine)
 * \brief Store the pixels matrix found in a file in a PNM structure.
 *
 * \param imageFile The file.
 * \param image The image struct.
 * \param breakPointLine The current line in the file.
 *
 * \pre fp is instanced, image is instanced.
 * \post The matrix is store.
 *
 * \return int 0 Error
 *             1 Success
 */
static int store_pixels(FILE *imageFile, PNM **image, unsigned int *breakPointLine)
{
    assert(imageFile && image);

    // Step 1 : creation of the pixels matrix
    unsigned int linesLength = (*image)->columns;
    if ((*image)->magicNumber == P3)
    {
        linesLength *= 3;
    }
    if (!((*image)->pixels = create_matrix((*image)->lines, linesLength)))
    {
        printf("> 🔴 Unable to allocate the required memory space to store the image.\n");
        return -1;
    } // end Step 1

    // Step 2 : fill in the pixels matrix
    for (unsigned int i = 0; i < (*image)->lines; i++)
    {
        for (unsigned int j = 0; j < linesLength; j++)
        {
            if (!go_to_next_data(imageFile, breakPointLine))
            {
                printf("> 🔴 No more pixels to read. Position reached in the matrix : [%d, %d].\n", i + 1, j + 1);
                return 0;
            }
            if (fscanf(imageFile, "%u", &(*image)->pixels[i][j]) != 1)
            {
                printf("> 🔴 No number to read. Position reached in the matrix : [%d, %d].\n", i + 1, j + 1);
                return 0;
            }
        }
    } // end Step 2

    return 1;
} // end store_pixels()

int load_pnm(PNM **image, char *filename)
{
    assert(image != NULL && filename != NULL);

    // step 1 - checking for the file name extension and compare it with the magic number
    char *extension;
    if (!(extension = get_file_extension(filename)))
    {
        printf("> 🔴 Unable to get the file extension: [%s]\n", filename);
        return -2;
    } // end step 1

    // step 2 - Open the file
    FILE *imageFile = NULL;
    imageFile = fopen(filename, "r");
    if (!imageFile)
    {
        printf("> 🔴 Unable to open the file [%s].\n", filename);
        return -1;
    } // end step 2

    // step 3 - create the pnm instance
    *image = malloc(sizeof(PNM));
    if (!(*image))
    {
        printf("> 🔴 Unable to allocate memory space for the image.\n");
        fclose(imageFile);
        return -1;
    }
    (*image)->pixels = NULL;
    // end step 3

    // step 4 : store magic number
    unsigned int breakPointLine = 1;
    char magicNumberString[MAGIC_NUMBER_LEN];

    if (!go_to_next_data(imageFile, &breakPointLine))
    {
        printf("> 🔴 Unable to continue file read after magic number.\n");
        fclose(imageFile);
        free_pnm(image);
        return -3;
    }
    if (breakPointLine > 1)
    {
        printf("> 🔴 The file have to begin with the magic number at line 1\n");
        fclose(imageFile);
        free_pnm(image);
        return -3;
    }
    if (fscanf(imageFile, "%2[^#]", magicNumberString) != 1)
    {
        printf("> 🔴 Unable to find a string at line 1.\n");
        fclose(imageFile);
        free_pnm(image);
        return -3;
    } // end step 4

    // step 5 - compare magic number with fil extension
    if (strcmp(magicNumberString, "P1") == 0)
    {
        if (strcmp(extension, "pbm") != 0)
        {
            printf("> 🔴 file extension [%s] does not match the magic number [P%d].\n", extension, (*image)->magicNumber + 1);
            fclose(imageFile);
            free_pnm(image);
            return -2;
        }
        (*image)->magicNumber = P1;
    }
    else if (strcmp(magicNumberString, "P2") == 0)
    {
        if (strcmp(extension, "pgm") != 0)
        {
            printf("> 🔴 file extension [%s] does not match the magic number [P%d].\n", extension, (*image)->magicNumber + 1);
            fclose(imageFile);
            free_pnm(image);
            return -2;
        }
        (*image)->magicNumber = P2;
    }
    else if (strcmp(magicNumberString, "P3") == 0)
    {
        if (strcmp(extension, "ppm") != 0)
        {
            printf("> 🔴 file extension [%s] does not match the magic number [P%d].\n", extension, (*image)->magicNumber + 1);
            fclose(imageFile);
            free_pnm(image);
            return -2;
        }
        (*image)->magicNumber = P3;
    }
    else
    {
        printf("> 🔴 The magic number is unknown. Magic number found : [%s]\n", magicNumberString);
        fclose(imageFile);
        free_pnm(image);
        return -3;
    } // end step 4

    // step 5 - Store number of columns and lines
    if (!go_to_next_data(imageFile, &breakPointLine))
    {
        printf("> 🔴 Unable to continue file read after magic number.\n");
        fclose(imageFile);
        free_pnm(image);
        return -3;
    }
    if (fscanf(imageFile, "%u %u", &(*image)->columns, &(*image)->lines) != 2)
    {
        printf("> 🔴 Unable to find the number of columns and lines.\n");
        fclose(imageFile);
        free_pnm(image);
        return -3;
    }
    // end step 5

    // step 6 - Store the max color value
    if ((*image)->magicNumber == P2 || (*image)->magicNumber == P3)
    {
        if (!go_to_next_data(imageFile, &breakPointLine))
        {
            printf("> 🔴 Unable to continue file read after max color value\n");
            fclose(imageFile);
            free_pnm(image);
            return -3;
        }
        if (fscanf(imageFile, "%u", &(*image)->maxPossibleValue) != 1)
        {
            printf("> 🔴 Unable to find the max color value.\n");
            fclose(imageFile);
            free_pnm(image);
            return -3;
        }
    } // end step 6

    // step 7 - Store the pixels matrix
    if (!store_pixels(imageFile, image, &breakPointLine))
    {
        printf("> 🔴 Error when storing the pixels around line %d in %s.\n", breakPointLine, filename);
        free_pnm(image);
        fclose(imageFile);
        return -3;
    } // end step 7

    printf("> [Good news] Image successfully loaded.\n");
    fclose(imageFile);
    return 0;
} // end load_pnm()

int write_pnm(PNM *image, char *filename)
{
    assert(image && filename);

    if (!check_file_name(filename))
    {
        printf("> 🔴 The file name [%s] isn't allowed. Tips : the file have to be in the same directory as the executable, it can't contains these characters : %s \n", filename, forbidenCharactersInFiles);
        return -1;
    }

    FILE *fp = fopen(filename, "w");
    if (!fp)
    {
        printf("> 🔴 Unable to open the file [%s]\n", filename);
        return -2;
    }

    // line 1 : magic number
    switch (image->magicNumber)
    {
    case P1:
        fprintf(fp, "P1\n");
        break;
    case P2:
        fprintf(fp, "P2\n");
        break;
    case P3:
        fprintf(fp, "P3\n");
        break;
    } // end line 1

    // line 2 : number of columns and lines
    fprintf(fp, "%u %u\n", image->columns, image->lines);

    // line 3 : max number for colors encoding
    if (image->magicNumber == P2 || image->magicNumber == P3)
    {
        fprintf(fp, "%d\n", image->maxPossibleValue);
    }

    // lines > 3 : matrix lines
    unsigned int linesLength = image->columns;
    if (image->magicNumber == P3)
    {
        linesLength *= 3;
    }
    for (unsigned int i = 0; i < image->lines; i++)
    {
        for (unsigned int j = 0; j < linesLength; j++)
        {
            fprintf(fp, "%hu ", (unsigned short)image->pixels[i][j]);
        }
        fprintf(fp, "\n");
    } // end line 3

    printf("> [Good news] Image stored in [%s].\n", filename);
    fclose(fp);
    return 0;
} // end write_pnm()

void pnm_file_encryption(PNM *image, LFSR *lfsr)
{
    assert(image && lfsr);

    unsigned int columns = image->columns;
    if (image->magicNumber == P3)
    {
        columns *= 3;
    }

    unsigned short maxValue = 0;

    for (unsigned int i = 0; i < image->lines; i++)
    {
        for (unsigned int j = 0; j < columns; j++)
        {

            unsigned int valueGenerated = generation(lfsr, 32);
            image->pixels[i][j] = image->pixels[i][j] ^ valueGenerated;

            if (image->magicNumber == P2 || image->magicNumber == P3)
            {
                if ((unsigned short)image->pixels[i][j] > maxValue)
                {
                    maxValue = (unsigned short)image->pixels[i][j];
                }
            }
        }
    }

    if (image->magicNumber == P2 || image->magicNumber == P3)
    {
        image->maxPossibleValue = (unsigned int)maxValue;
    }
} // end pnm_file_encryption()

void free_pnm(PNM **image)
{
    assert(*image);
    if ((*image)->pixels)
    {
        unsigned int linesLength = (*image)->columns;
        if ((*image)->magicNumber == P3)
            linesLength *= 3;
        free_matrix((*image)->pixels, (*image)->lines);
        (*image)->pixels = NULL;
    }
    free(*image);
    *image = NULL;
} // end free_pnm()
