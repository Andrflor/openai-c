/* Utiliies for the program */

/* Duplicates a string */
char *strdup(const char *s);

/* Duplicates an array of strings */
char **arr_strdup(char **original);

/* Pretty print string array to json formatted string */
char *arr_strpretty(char **arr);

/* Extract a substring between the thow specified delimiters */
char *strextract(const char *str, const char *start, const char *end);

/* Utility log macro */
#ifdef DEBUG
#define log(fmt, ...) printf("[DEBUG] " fmt, ##__VA_ARGS__)
#else
#define log(fmt, ...)
#endif
