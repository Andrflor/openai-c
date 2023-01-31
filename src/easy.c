#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "easy.h"
#include "util.h"

const char *format = "{\"prompt\":\"%s\",\"max_tokens\": %d,\"stop\": %s,"
                     "\"model\": \"%s\",\"temperature\": %f, \"top_p\": %f, "
                     "\"frequency_penalty\": %f, \"presence_penalty\": %f}";

typedef struct OpenAIStruct {
  CURL *curl;
  char *model;
  char **stop;
  uint max_tokens;
  float presence_penalty;
  float frequency_penalty;
  float top_p;
  float temperature;
} OpenAIStruct;

OpenAI openai_easy_init(char *api_key) {
  CURL *curl = curl_easy_init();

  if (curl && strlen(api_key) == 51) {
    struct curl_slist *headers = NULL;
    char auth_header[74];
    sprintf(auth_header, "Authorization: Bearer %s", api_key);
    headers = curl_slist_append(headers, auth_header);
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, OPENAI_API_URL);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
  }

  OpenAIStruct *openai = (OpenAIStruct *)malloc(sizeof(OpenAIStruct));
  openai->curl = curl;
  openai->model = OPENAI_DEFAULT_MODEL;
  openai->max_tokens = OPENAI_DEFAULT_MAX_TOKENS;
  openai->temperature = OPENAI_DEFAULT_TEMPERATURE;
  openai->stop = OPENAI_DEFAULT_STOP;
  openai->top_p = OPENAI_DEFAULT_TOP_P;
  openai->frequency_penalty = OPENAI_DEFAULT_FREQUENCY_PENALTY;
  openai->presence_penalty = OPENAI_DEFAULT_PRESENCE_PENALTY;

  return openai;
}

OpenAI openai_easy_duphandle(OpenAI openai) {
  OpenAIStruct *openai_dup = (OpenAIStruct *)malloc(sizeof(OpenAIStruct));
  openai_dup->curl = curl_easy_duphandle(openai->curl);
  openai_dup->model = strdup(openai->model);
  openai_dup->stop = arr_strdup(openai->stop);
  openai_dup->max_tokens = openai->max_tokens;
  openai_dup->temperature = openai->temperature;
  openai_dup->top_p = openai->top_p;
  openai_dup->frequency_penalty = openai->frequency_penalty;
  openai_dup->presence_penalty = openai->presence_penalty;

  return openai_dup;
}

CURLcode openai_easy_setopt(OpenAI openai, OpenAIOption option, ...) {
  va_list args;
  va_start(args, option);
  switch (option) {
  case OPENAIOPT_MODEL:
    openai->model = va_arg(args, char *);
    break;
  case OPENAIOPT_MAX_TOKENS:
    openai->max_tokens = va_arg(args, uint);
    break;
  case OPENAIOPT_TEMPERATURE:
    openai->temperature = (float)va_arg(args, double);
    break;
  case OPENAIOPT_STOP:
    openai->stop = va_arg(args, char **);
    break;
  case OPENAIOPT_TOP_P:
    openai->top_p = (float)va_arg(args, double);
    break;
  case OPENAIOPT_PRESENCE_PENALTY:
    openai->presence_penalty = (float)va_arg(args, double);
    break;
  case OPENAIOPT_FREQUENCY_PENALTY:
    openai->frequency_penalty = (float)va_arg(args, double);
    break;
  default:
    return CURLE_UNKNOWN_OPTION;
  }

  va_end(args);
  return CURLE_OK;
}

char *openai_easy_body(OpenAI openai, char *data) {
  char *post_data = (char *)malloc(strlen(data) + 200);
  char *stop = arr_strpretty(openai->stop);
  sprintf(post_data, format, data, openai->max_tokens, stop, openai->model,
          openai->temperature, openai->top_p, openai->frequency_penalty,
          openai->presence_penalty);
  free(stop);
  printf("%s\n", post_data);
  return post_data;
}

void openai_easy_perform(OpenAI openai, char *request) {
  CURLcode res;

  if (openai) {
    char *body = openai_easy_body(openai, request);
    curl_easy_setopt(openai->curl, CURLOPT_POSTFIELDS, body);
    res = curl_easy_perform(openai->curl);
    if (res != CURLE_OK)
      fprintf(stderr, "Calling openai failed: %s\n", curl_easy_strerror(res));
    free(body);
  }
}

void openai_easy_cleanup(OpenAI openai) {
  if (openai) {
    curl_easy_cleanup(openai->curl);
    free(openai->model);

    for (uint i = 0; openai->stop[i] != NULL; i++) {
      free(openai->stop[i]);
    }

    free(openai->stop);
    free(openai);
  }
}
