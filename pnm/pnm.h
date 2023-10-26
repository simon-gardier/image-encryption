/**
 * \file pnm.h
 * \brief This file contains type declarations and prototypes of functions for the manipulation of PNM images.
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#ifndef __PNM__
#define __PNM__

#include "../lfsr/lfsr.h"

/**
 * \typedef PNM
 * \brief  Data structure representing a pnm image
 */
typedef struct PNM_t PNM;

/**
 * Enumeration of all possible magic numbers
 */
typedef enum MAGIC_NUMBERS_t { 
    P1,
    P2,
    P3
} MAGIC_NUMBERS;

/**
 * \brief Loads a PNM image from a file.
 *
 * \param image The address of a PNM pointer to which to write the content of the file filename.
 * \param filename The path to the file containing the image.
 *
 * \pre image is instanced, filename is instanced
 * \post image points to the image loaded from the file.
 *
 * \return int 0 Success
 *             -1 Error in memory allocation
 *             -2 Name of file is malformed
 *             -3 Content of file is malformed
 */
int load_pnm(PNM** image, char* filename);

/**
 * \brief Saves a PNM image to a file.
 *
 * \param image Pointer on PNM.
 * \param filename File path of the destination.
 *
 * \pre image is instanced, filename is instanced.
 * \post The file filename contain the informations of PNM image.
 *
 * \return  int 0 Success
 *             -1 Name of file is malformed
 *             -2 Error of file manipulation
 */
int write_pnm(PNM* image, char* filename);

/**
 * \brief Encrypt a pnm file with using the lfsr cipher
 *
 * \param image The image to encrypt.
 * \param lfsr The lfsr instance use to encrypt the file
 *
 * \pre image is instanced, lfsr is instanced.
 * \post The image pixels matrix is encrypted
 */
void pnm_file_encryption(PNM* image, LFSR* lfsr);

/**
 * \brief Free a pointer on PNM
 *
 * \param image The adress of the PNM instance.
 *
 * \pre image is instanced.
 * \post The structure is frees.
 */
void free_pnm(PNM** image);

#endif // __PNM__
