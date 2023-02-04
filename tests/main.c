#include "../src/util.h"
#include <assert.h>
#include <stdio.h>

#define TEST(name, func) ;

#define expect(actual, expected, evaluator)                                    \
  TOTAL_TESTS++;                                                               \
  if (!(evaluator(actual, expected))) {                                        \
    FAILED_TESTS++;                                                            \
    printf("Assertion failed\n, expected: , got: ");                           \
  }

#define equals(a, b) a == b

int TOTAL_TESTS = 0;
int FAILED_TESTS = 0;

struct Test {
  char *name;
  int (*func)(void);
};

int trol(void) { return 0; }

int firstTest() {
  expect(1, 1, equals);
  return 0;
}

int main(int argc, char *argv[]) {

  printf("\n[TESTS] started...\n");

  struct Test test = {
      .name = "SuperTest",
      .func = trol,
  };

  log("Super login\n");
  printf("[TESTS] RAN: %d, PASSED: %d, FAILED: %d, PERCENT: %.2f%%\n",
         TOTAL_TESTS, TOTAL_TESTS - FAILED_TESTS, FAILED_TESTS,
         TOTAL_TESTS == 0 ? 0
                          : 100 * (((float)TOTAL_TESTS - (float)FAILED_TESTS)) /
                                (float)TOTAL_TESTS);
  return 0;
}
