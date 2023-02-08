#include "util.h"
#include "../src/util.h"

void _strdup(void) {}

void _arr_strdup(void) {}

void _arr_strpretty(void) {}

void _strextract(void) {}

char *CURRENT = "";

void util(void) {
  TEST(_strdup);
  TEST(_arr_strdup);
  TEST(_arr_strpretty);
  TEST(_strextract);
}

void test_util(void) { TEST(util); }
