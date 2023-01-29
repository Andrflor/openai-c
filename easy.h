#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define OPENAI_API_URL "https://api.openai.com/v1/completions"
#define OPENAI_DEFAULT_MODEL "text-davinci-003"
#define OPENAI_DEFAULT_MAX_TOKENS 2048
#define OPENAI_DEFAULT_TEMPERATURE 0.7

typedef enum {
    OpenAI_Stop,
    OpenAI_Model,
    OpenAI_MaxTokens,
    OpenAI_Temperature,
}  OpenAIOption;

typedef struct Openai_easy OpenAI;

OpenAI *openai_easy_init(char *api_key);
void openai_easy_cleanup(OpenAI *openai);


void openai_easy_perform(OpenAI *openai, char *request);
CURLcode openai_easy_setopt(OpenAI *openai, OpenAIOption option, ...);
