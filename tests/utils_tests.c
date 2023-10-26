/**
 * \file utils_tests.c
 * \brief This file contains tests for the utils library.
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#include <string.h>
#include <stdlib.h>
#include "../seatest/seatest.h"
#include "../utils/utils.h"

/**
 * \fn static void test_create_matrix()
 * @brief Test test_create_matrix() in a basic case
 */
static void test_create_matrix(void);

/**
 * \fn static test_base64_string_to_binary_string()
 * @brief Test test_base64_string_to_binary_string() in a basic case
 */
static void test_base64_string_to_binary_string(void);

/**
 * \fn static void test_get_file_extension()
 * @brief Test test_get_file_extension() in a basic case
 */
static void test_get_file_extension(void);

/**
 * \fn static void test_check_file_name()
 * @brief Test test_check_file_name() in a basic case
 */
static void test_check_file_name(void);

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

static void test_create_matrix(void)
{
    unsigned int **matrix = create_matrix(5, 10);
    assert_true(matrix != NULL);
} // end test_create_matrix()

static void test_base64_string_to_binary_string(void)
{
    char *correctPassword = "MaitreGims";
    char *expected = "001100011010100010101101101011011110000110100010100110101100";
    char *result = base64_string_to_binary_string(correctPassword);
    assert_true(strcmp(expected, result) == 0);
    free(result);

    char *wrongPassword = "dasjn0938*&()";
    result = base64_string_to_binary_string(wrongPassword);
    assert_true(result == NULL);
} // end test_base64_string_to_binary_string()

static void test_get_file_extension(void)
{
    char *correctFilePath = "img.pgm";
    char *expectedExtension = "pgm";
    assert_true(strcmp(expectedExtension, get_file_extension(correctFilePath)) == 0);

    char *wrongFilePath = "img";
    assert_true(get_file_extension(wrongFilePath) == NULL);
} // end test_get_file_extension()

static void test_check_file_name(void)
{
    char *correctFilePath = "img.pgm";
    assert_true(check_file_name(correctFilePath));

    char *toMuchExtensions = "img.pg.m";
    assert_true(!check_file_name(toMuchExtensions));

    char *containFordidChar = "img*.pgm";
    assert_true(!check_file_name(containFordidChar));
} // end test_check_file_name()

static void test_fixture(void)
{
    test_fixture_start();
    run_test(test_create_matrix);
    run_test(test_base64_string_to_binary_string);
    run_test(test_get_file_extension);
    run_test(test_check_file_name);
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
