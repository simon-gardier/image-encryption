/**
 * \file crypt_lfsr_main.c
 * \brief This file contains the main() function of the advanced encryption program
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "../pnm/pnm.h"
#include "../utils/utils.h"
#include "../lfsr/lfsr.h"

int main(int argc, char *argv[])
{
   int val;

   char *optstring = ":i:o:p:t:";
   char *input = "";
   char *output = "";
   char *seed = "";
   char *tap = "";

   char *inputExtension = NULL;
   char *outputExtension = NULL;
   int tap_value = 0;

   while ((val = getopt(argc, argv, optstring)) != EOF)
   {
      switch (val)
      {
      case 'i':
         input = optarg;
         if (!(inputExtension = get_file_extension(input)))
         {
            printf("> 🔴 Argument -i invalid.\n");
            return 0;
         }
         break;

      case 'o':
         output = optarg;
         if (!(outputExtension = get_file_extension(output)))
         {
            printf("> 🔴 Argument -o invalid.\n");
            return 0;
         }
         if (strcmp(inputExtension, outputExtension))
         {
            printf("> 🔴 The input file [%s] and the output file [%s] do not agree on the image format.\n", inputExtension, output);
            return 0;
         }
         break;

      case 'p':
         seed = optarg;
         break;

      case 't':
         tap = optarg;
         if (sscanf(tap, "%d", &tap_value) != 1)
         {
            printf("> 🔴 No numeric value in the tap [%s].\n", optarg);
            return 0;
         }
         if (tap_value < 0)
         {
            printf("> 🔴 The numeric value in the tap [%s] is too small. It should be >= 0.\n", optarg);
            return 0;
         }
         break;

      case ':':
         printf("> 🔴 Argument missing for -%c.\n", optopt);
         return 0;

      case '?':
         printf("> 🔴 Option -%c unknow.\n", optopt);
         return 0;
      }
   } // end args loop

   // check that arguments aren't empty
   if (strlen(input) == 0 || strlen(output) == 0 || strlen(seed) == 0 || strlen(tap) == 0)
   {
      printf("> 🔴 This kind of command is not likely to work.\n");
      printf(">\tHere's how to use the program :\n");
      printf(">\t./advanced_cipher -i inputFilePath -o outputFileName -p passwordValue -t tapValue\n");
      return 0;
   }

   // Step 1 : file processing
   PNM *image;
   if (load_pnm(&image, input) != 0)
   {
      printf("> 🔴 Unable to load the file [%s].\n", input);
      return 0;
   }

   // Step 2 : encryption of the file
   char *seedConverted = base64_string_to_binary_string(seed);
   LFSR *lfsr = create_lfsr(seedConverted, tap_value);
   free(seedConverted);
   if (!lfsr)
   {
      free_pnm(&image);
      printf("> 🔴 Unable to create the cipher tool.\n");
      return 0;
   }
   pnm_file_encryption(image, lfsr);

   // Step 3 : copy the file
   if (write_pnm(image, output) != 0)
   {
      free_pnm(&image);
      free_lfsr(&lfsr);
      printf("> 🔴 Unable to copy the file [%s] in [%s].\n", input, output);
      return 0;
   }

   free_lfsr(&lfsr);
   free_pnm(&image);
   return 0;
}
