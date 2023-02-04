#include "../src/util.h"
#include <assert.h>
#include <stdio.h>

#define TO_STRING(x) #x
#define TEST(func)                                                             \
  printf("[TEST] Runing: %s\n", TO_STRING(func));                              \
  func()

#define expect(actual, expected, evaluator)                                    \
  TOTAL_TESTS++;                                                               \
  if (!(evaluator(actual, expected))) {                                        \
    FAILED_TESTS++;                                                            \
    printf("[TEST] Failed, expected: %s, got: %s\n", #expected, #actual);      \
  }

#define equals(a, b) a == b

int TOTAL_TESTS = 0;
int FAILED_TESTS = 0;

void trol(void) { expect(1, 2, equals); }

int firstTest() {
  expect(1, 1, equals);
  return 0;
}

int main(int argc, char *argv[]) {

  printf("\n[TEST] Started...\n");

  TEST(trol);

  printf("[TEST] RAN: %d, PASSED: %d, FAILED: %d, PERCENT: %.2f%%\n",
         TOTAL_TESTS, TOTAL_TESTS - FAILED_TESTS, FAILED_TESTS,
         TOTAL_TESTS == 0 ? 0
                          : 100 * (((float)TOTAL_TESTS - (float)FAILED_TESTS)) /
                                (float)TOTAL_TESTS);
  return 0;
}
