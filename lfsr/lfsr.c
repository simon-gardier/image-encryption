/**
 * \file lfsr.c
 * \brief This file contains the LFSR type definition and the LFSR manipulation functions.
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include "lfsr.h"

/**
 * \struct LFSR_t
 * \brief  Data structure representing a linear feedback shift register.
 */
struct LFSR_t
{
    unsigned int *reg;      /*!< The register */
    unsigned int regLength; /*!< The length of the register */
    unsigned int tap;       /*!< The tap a.k.a the index (from the right) / the number of the bit to use for the XOR operation*/
};

LFSR *create_lfsr(char *seed, int tap)
{
    assert(seed);
    if (tap < 0 || tap >= (int)strlen(seed))
    {
        printf("> 🔴 Tap out of bounds.\n");
        return NULL;
    }

    LFSR *lfsr = malloc(sizeof(LFSR));
    if (!lfsr)
    {
        return NULL;
    }

    lfsr->reg = malloc(sizeof(unsigned int) * strlen(seed));
    if (!lfsr->reg)
    {
        free(lfsr);
        return NULL;
    }
    for (unsigned int i = 0; i < strlen(seed); i++)
    {
        if (seed[i] != '1' && seed[i] != '0')
        {
            free(lfsr->reg);
            free(lfsr);
            printf("> 🔴 [%c] isn't allowed in a seed. The seed should contains only 1's and 0's.\n", seed[i]);
            return NULL;
        }
        lfsr->reg[i] = (unsigned int)(seed[i] - '0');
    }
    lfsr->tap = tap;
    lfsr->regLength = strlen(seed);

    return lfsr;
}

unsigned int operation(LFSR *lfsr)
{
    assert(lfsr);

    unsigned int xor_operation = lfsr->reg[0] ^ lfsr->reg[lfsr->regLength - lfsr->tap - 1];

    for (unsigned int i = 0; i < lfsr->regLength - 1; i++)
    {
        lfsr->reg[i] = lfsr->reg[i + 1];
    }
    lfsr->reg[lfsr->regLength - 1] = xor_operation;
    return xor_operation;
}

unsigned int generation(LFSR *lfsr, unsigned int k)
{
    assert(lfsr);
    unsigned int valueGenerated = 0;
    for (unsigned int i = 0; i < k; i++)
    {
        valueGenerated = valueGenerated * 2 + operation(lfsr);
    }
    return valueGenerated;
}

unsigned int *get_register(LFSR *lfsr)
{
    assert(lfsr);
    return lfsr->reg;
}

unsigned int get_tap(LFSR *lfsr)
{
    assert(lfsr);
    return lfsr->tap;
}

char *to_string(LFSR *lfsr)
{
    assert(lfsr);

    char *stringRepresentation = malloc(lfsr->regLength * sizeof(char));
    for (unsigned int i = 0; i < lfsr->regLength; i++)
    {
        stringRepresentation[i] = (char)lfsr->reg[i] + '0';
    }

    return stringRepresentation;
}

void free_lfsr(LFSR **lfsr)
{
    assert(*lfsr);
    if ((*lfsr)->reg)
    {
        free((*lfsr)->reg);
        (*lfsr)->reg = NULL;
    }
    free(*lfsr);
    *lfsr = NULL;
}
