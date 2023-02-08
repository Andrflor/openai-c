#include <stdio.h>

#define TEST(func)                                                             \
  printf("[TEST] Runing: %s\n", #func);                                        \
  CURRENT = #func;                                                             \
  func()

#define expect(actual, expected, evaluator)                                    \
  TOTAL_TESTS++;                                                               \
  if (!(evaluator(actual, expected))) {                                        \
    FAILED_TESTS++;                                                            \
    printf("[TEST] Failed %s\n[TEST] Expected: %s, got: %s\n\n", CURRENT,      \
           #expected, #actual);                                                \
  }

void test_util(void);
