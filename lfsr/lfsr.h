/**
 * \file lfsr.h
 * \brief This file contains type declarations and prototypes of functions for the manipulation of LFSR.
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#ifndef __LFSR__
#define __LFSR__

/**
 * \typedef LFSR
 * \brief  Data structure representing a linear feedback shift register.
 */
typedef struct LFSR_t LFSR;

/**
 * \brief Create an lfsr instance.
 *
 * \param seed The seed of the lfsr.
 * \param tap The number of the bit (considering reading from right to left) for the XOR operation on the register.
 *
 * \pre seed is instanced
 * \post A lfsr instance is returned.
 *
 * \return LFSR* The pointer dynamically allocated.
 *               NULL in case of error.
 */
LFSR *create_lfsr(char *seed, int tap);

/**
 * \brief Shift a register to the left and return the XOR operation BT the tap bit and the most significant byte.
 *
 * \param lfsr The lfsr instance.
 *
 * \pre lfsr is instanced.
 * \post The new register is returned.
 *
 * \return int The result of the XOR operation.
 */
unsigned int operation(LFSR *lfsr);

/**
 * \brief Make k operations on the register of the lfsr instance.
 *
 * \param lfsr The lfsr instance.
 * \param k The number of iterations.
 *
 * \pre lfsr is instanced, k > 0
 * \post The result of the calculation is returned.
 *
 * \return unsigned int The result of the calculation for k operations.
 */
unsigned int generation(LFSR *lfsr, unsigned int k);

/**
 * \brief Get the register of the lfsr instance.
 *
 * \param lfsr The lfsr instance.
 *
 * \pre lfsr is instanced.
 * \post The register is returned.
 *
 * \return unsigned int* The register.
 */
unsigned int *get_register(LFSR *lfsr);

/**
 * \brief Get the tap of a lfsr instance.
 *
 * \param lfsr The lfsr instance.
 *
 * \pre lfsr is instanced.
 * \post The tap is returned.
 *
 * \return unsigned int The tap
 */
unsigned int get_tap(LFSR *lfsr);

/**
 * \brief Return the representation of a register in characters.
 *
 * \param lfsr The lfsr instance to represent.
 *
 * \pre lfsr is instanced, stringRepresentation is instanced.
 * \post The register string representation is returned.
 *
 * \return char* The register representation.
 */
char *to_string(LFSR *lfsr);

/**
 * \brief Free a lfsr structure.
 *
 * \param lfsr The adress of the instance to free.
 *
 * \pre lfsr is instanced
 * \post The memory space is frees.
 */
void free_lfsr(LFSR **lfsr);
#endif // __LFSR__
