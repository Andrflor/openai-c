#include "util.h"

char **arr_strdup(char **original) {
    int length = 0;
    char **ptr = original;

    while (*ptr++) length++;

    char **copy = (char **) malloc((length + 1) * sizeof(char *));
    for (int i = 0; i < length; ++i) {
        copy[i] = strdup(original[i]);
    }
    copy[length] = NULL;

    return copy;
}
