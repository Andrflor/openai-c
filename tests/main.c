#include "util.h"
#include <assert.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  int TOTAL_TESTS = 0;
  int FAILED_TESTS = 0;

  printf("\n[TEST] Started...\n\n");

  test_util();

  printf("[TEST] RAN: %d, PASSED: %d, FAILED: %d, PERCENT: %.2f%%\n",
         TOTAL_TESTS, TOTAL_TESTS - FAILED_TESTS, FAILED_TESTS,
         TOTAL_TESTS == 0 ? 0
                          : 100 * (((float)TOTAL_TESTS - (float)FAILED_TESTS)) /
                                (float)TOTAL_TESTS);
  return 0;
}
