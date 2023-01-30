#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **arr_strdup(char **original) {
  int length = 0;
  char **ptr = original;

  while (*ptr++)
    length++;

  char **copy = (char **)malloc((length + 1) * sizeof(char *));
  for (int i = 0; i < length; ++i) {
    copy[i] = strdup(original[i]);
  }
  copy[length] = NULL;

  return copy;
}

// TODO: fix that function
char *arr_strpretty(char **arr) {
  if (arr == NULL)
    return strdup("[]");
  char *json;
  int i, j, k, len = 2;

  for (i = 0; arr[i] != NULL; i++) {
    len += strlen(arr[i]) + 2;
  }

  json = malloc(len + 1);
  strcpy(json, "[");

  for (i = 0, j = 1; arr[i] != NULL; i++, j += k) {
    k = sprintf(json + j, "\"%s\"", arr[i]);
    if (arr[i + 1] != NULL) {
      json[j + k++] = ',';
    }
  }

  strcat(json, "]");
  return json;
}
