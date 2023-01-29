#include <curl/curl.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define OPENAI_API_URL "https://api.openai.com/v1/completions"
#define OPENAI_DEFAULT_MODEL "text-davinci-003"
#define OPENAI_DEFAULT_FREQUENCY_PENALTY 0
#define OPENAI_DEFAULT_PRESENCE_PENALTY 0
#define OPENAI_DEFAULT_MAX_TOKENS 2048
#define OPENAI_DEFAULT_TEMPERATURE 0.7
#define OPENAI_DEFAULT_STOP NULL
#define OPENAI_DEFAULT_TOP_P 1

typedef enum {
    OPENAIOPT_STOP,
    OPENAIOPT_MODEL,
    OPENAIOPT_TOP_P,
    OPENAIOPT_MAX_TOKENS,
    OPENAIOPT_TEMPERATURE,
    OPENAIOPT_PRESENCE_PENALTY,
    OPENAIOPT_FREQUENCY_PENALTY,
}  OpenAIOption;

typedef struct OpenAIStruct* OpenAI;

OpenAI openai_easy_init(char *api_key);
void openai_easy_cleanup(OpenAI openai);


void openai_easy_perform(OpenAI openai, char *request);

/* This preprocessor magic that replaces a call with the exact same call is
   only done to make sure application authors pass exactly three arguments
   to these functions. */
#define openai_easy_setopt(handle,opt,param) openai_easy_setopt(handle,opt,param)
