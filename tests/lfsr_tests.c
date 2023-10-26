/**
 * \file lfsr_tests.c
 * \brief This file contains tests for the LFSR library.
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#include <string.h>
#include <stdlib.h>
#include "../seatest/seatest.h"
#include "../lfsr/lfsr.h"

char *wrong_seed = "IShouldNotBeAbleToCreateALFSR";               /*!< An incorrect seed used to create a lfsr instance.*/
char *seed = "01101000010";                                       /*!< A seed used to create a lfsr instance.*/
unsigned int expectedReg[11] = {0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0}; /*!< Expected value of lfsr->reg for a lfsr instance created with seed.*/
int tap = 8;                                                      /*!< A tap used to create a lfsr instance.*/

/**
 * \fn static void test_create_lfsr()
 * @brief Test create_lfsr() for:
 *      - Basic cas
 *      - Tap too big
 *      - Tap too small
 *      - Incorrect seed
 */
static void test_create_lfsr(void);

/**
 * \fn static void test_operation()
 * @brief Test test_operation() in a basic case
 */
static void test_operation(void);

/**
 * \fn static void test_generation()
 * @brief Test test_generation() for :
 *      - Basic case
 *      - Invalid seed
 *      - Invalid tap
 */
static void test_generation(void);

/**
 *
 * \fn static void test_get_register()
 * @brief Test test_get_register() in a basic case
 *
 */
static void test_get_register(void);

/**
 * \fn static void test_generation()
 * @brief Test test_generation() in a basic case
 */
static void test_get_tap(void);

/**
 * \fn static void test_to_string()
 * @brief Test test_to_string() in a basic case
 */
static void test_to_string(void);

/**
 * \fn static void test_free_pnm()
 * @brief Test test_free_pnm() in a basic case
 */
static void test_free_pnm(void);

/**
 * \fn static void test_fixture()
 * @brief Run the test routine
 */
static void test_fixture(void);

/**
 * \fn static void all_tests()
 * @brief Launch the test routine
 */
static void all_tests(void);

static void test_create_lfsr(void)
{
    LFSR *lfsr;
    lfsr = create_lfsr(seed, tap);

    assert_true(lfsr != NULL);
    free_lfsr(&lfsr);

    lfsr = create_lfsr(seed, tap * 1000);
    assert_true(lfsr == NULL);

    lfsr = create_lfsr(seed, -tap);
    assert_true(lfsr == NULL);

    lfsr = create_lfsr(wrong_seed, tap);
    assert_true(lfsr == NULL);
} // end test_create_lfsr()

static void test_operation(void)
{
    unsigned int expectedRegAfterOperation[11] = {1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1};
    unsigned int expectedOpeResult = 1;
    LFSR *lfsr;
    lfsr = create_lfsr(seed, tap);
    int operation_result = operation(lfsr);
    assert_n_array_equal(expectedRegAfterOperation, get_register(lfsr), 11);
    assert_int_equal(expectedOpeResult, operation_result);
    free_lfsr(&lfsr);
} // end test_operation

static void test_generation(void)
{
    unsigned int expectedRegAfterOperation[11] = {0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1};
    unsigned int expectedGenResult = 25;

    LFSR *lfsr;
    lfsr = create_lfsr(seed, tap);

    int generation_result = generation(lfsr, 5);

    assert_n_array_equal(expectedRegAfterOperation, get_register(lfsr), 11);
    assert_int_equal(expectedGenResult, generation_result);
    free_lfsr(&lfsr);
} // end test_operation()

static void test_get_register(void)
{
    LFSR *lfsr;
    lfsr = create_lfsr(seed, tap);

    assert_n_array_equal(expectedReg, get_register(lfsr), 11);

    free_lfsr(&lfsr);
} // end test_get_register()

static void test_get_tap(void)
{
    LFSR *lfsr;
    lfsr = create_lfsr(seed, tap);

    assert_int_equal(tap, get_tap(lfsr));

    free_lfsr(&lfsr);
} // end test_get_tap()

static void test_to_string(void)
{
    LFSR *lfsr;
    lfsr = create_lfsr(seed, tap);
    char *register_to_string = to_string(lfsr);

    assert_true(strcmp(seed, register_to_string) == 0);
    free(register_to_string);
    free_lfsr(&lfsr);
} // end test_to_string()

static void test_free_pnm(void)
{
    LFSR *lfsr;
    lfsr = create_lfsr(seed, tap);
    free_lfsr(&lfsr);
    assert_true(lfsr == NULL);
}

static void test_fixture(void)
{
    test_fixture_start();
    run_test(test_create_lfsr);
    run_test(test_get_register);
    run_test(test_get_tap);
    run_test(test_to_string);
    run_test(test_operation);
    run_test(test_generation);
    run_test(test_free_pnm);
    test_fixture_end();
} // end test_fixture()

static void all_tests(void)
{
    test_fixture();
} // end all_tests()

int main(void)
{
    return run_tests(all_tests);
} // end main()
