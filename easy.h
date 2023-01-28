#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPENAI_API_URL "https://api.openai.com/v1/completions"
#define OPENAI_DEFAULT_MODEL "text-davinci-003"
#define OPENAI_DEFAULT_MAX_TOKENS 2048
#define OPENAI_DEFAULT_TEMPERATURE 0.7


typedef struct Openai_easy Openai;

Openai *openai_easy_init(char *api_key);
void openai_easy_perform(Openai *openai, char *request);
void openai_easy_cleanup(Openai *openai);
