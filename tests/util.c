#include "util.h"
#include "../src/util.h"

#include <setjmp.h>
#include <signal.h>

static jmp_buf s_jumpBuffer;

void sigsegv_handler(int sig) {
  fprintf(stderr, "Caught SIGSEGV: Segmentation fault\n");
  main();
}

char *CURRENT = "";
int TOTAL_TESTS = 0;
int FAILED_TESTS = 0;

void _strdup(void) {

  printf("calling _strdup");

  struct sigaction sa;
  sa.sa_handler = sigsegv_handler;
  sa.sa_flags = 0;
  sigaction(SIGSEGV, &sa, NULL);

  // Normal code execution starts here
  char *str_empty = "";
  char *str_empty_dup = strdup(str_empty);
  expect(str_empty, str_empty_dup, equals);

  char *str_random = "random";
  char *str_random_dup = strdup(str_random);
  expect(str_empty, str_empty_dup, equals);

  char *str_void;
  char *str_void_dup = strdup(str_void);

  char *str_null = NULL;
  char *str_null_dup = strdup(str_null);

  printf("We continue");
}

void _arr_strdup(void) {}

void _arr_strpretty(void) {}

void _strextract(void) {}

void util(void) {
  TEST(_strdup);
  TEST(_arr_strdup);
  TEST(_arr_strpretty);
  TEST(_strextract);
}

void test_util(void) { TEST(util); }
