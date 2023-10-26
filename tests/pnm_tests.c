/**
 * \file pnm_tests.c
 * \brief This file contains tests for the PNM library.
 * \author Gardier Simon
 * \date 26.10.2023
 * \version: V2
 */

#include "../seatest/seatest.h"
#include "../pnm/pnm.h"
#include "../lfsr/lfsr.h"

/**
 * \fn static void test_load_pnm()
 * @brief Test test_load_pnm() for :
 *      - File wich do not exist
 *      - File with an extension wich does not match the magic number
 *      - File with a magic number different from P1, P2 and P3
 *      - File with missing pixels
 *      - File with a correct structure
 *      - File with a correct structure and comment bt two lines of the pixels matrix
 */
static void test_load_pnm(void);

/**
 * \fn static void test_write_pnm()
 * @brief Test test_write_pnm() for :
 *      - File from another directory
 *      - File from the current (wich is the good) directory
 */
static void test_write_pnm(void);

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

static void test_load_pnm(void)
{
  PNM *imageStruct;

  assert_int_equal(-1, load_pnm(&imageStruct, "img/pnm_tests/thisFileDoNotExist.ppm"));
  assert_int_equal(-2, load_pnm(&imageStruct, "img/pnm_tests/incorrectExtension.pgm"));
  assert_int_equal(-3, load_pnm(&imageStruct, "img/pnm_tests/nonExistingMagicNumb.ppm"));
  assert_int_equal(-3, load_pnm(&imageStruct, "img/pnm_tests/commentFrstLine.ppm"));
  assert_int_equal(-3, load_pnm(&imageStruct, "img/pnm_tests/missPixels.ppm"));
  assert_int_equal(0, load_pnm(&imageStruct, "img/pnm_tests/correct.ppm"));
  free_pnm(&imageStruct);

  assert_int_equal(0, load_pnm(&imageStruct, "img/pnm_tests/commentBtMatrixLines.ppm"));
  free_pnm(&imageStruct);
} // test_load_pnm()

static void test_write_pnm(void)
{
  PNM *imageStruct;
  load_pnm(&imageStruct, "img/pnm_tests/correct.ppm");

  assert_int_equal(-1, write_pnm(imageStruct, "../badPath.ppm"));
  assert_int_equal(0, write_pnm(imageStruct, "goodPath.ppm"));

  free_pnm(&imageStruct);
} // end test_write_pnm()

static void test_free_pnm(void)
{
  PNM *imageStruct;
  load_pnm(&imageStruct, "img/pnm_tests/correct.ppm");
  free_pnm(&imageStruct);
  assert_true(imageStruct == NULL);
}

static void test_fixture(void)
{
  test_fixture_start();
  run_test(test_load_pnm);
  run_test(test_write_pnm);
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
