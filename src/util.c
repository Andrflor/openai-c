#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **arr_strdup(char **original) {
  if (original == NULL)
    return NULL;

  int i;
  int length = 0;
  char **ptr = original;

  while (*ptr++)
    length++;

  char **copy = (char **)malloc((length) * sizeof(char *));

  for (i = 0; i < length; ++i) {
    copy[i] = strdup(original[i]);
  }
  copy[length] = NULL;

  return copy;
}

char *arr_strpretty(char **arr) {
  if (arr == NULL || arr[0] == NULL)
    return strdup("[]");

  char **ptr = arr;
  int length = strlen(*ptr);

  while (*++ptr) {
    length += strlen(*ptr) + 3;
  }

  char *json = (char *)malloc((length) * sizeof(char *));
  strcpy(json, "[");

  int i;
  for (i = 0; arr[i] != NULL; i++) {
    strcat(json, "\"");
    strcat(json, arr[i]);
    strcat(json, "\"");
    if (arr[i + 1] != NULL)
      strcat(json, ",");
  }
  strcat(json, "]");

  return json;
}
