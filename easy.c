#include "easy.h"
#include <curl/curl.h>

const char *format = "{\"prompt\":\"%s\",\"max_tokens\": %d,\"stop\":\"\","
                     "\"model\": \"%s\",\"temperature\": %f}";

struct Openai_easy {
  CURL *curl;
  char *model;
  char **stop;
  int max_tokens;
  double temperature;
};

OpenAI *openai_easy_init(char *api_key) {
  CURL *curl;
  curl = curl_easy_init();

  if (curl) {
    struct curl_slist *headers = NULL;
    char auth_header[100];
    sprintf(auth_header, "Authorization: Bearer %s", api_key);
    headers = curl_slist_append(headers, auth_header);
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, OPENAI_API_URL);
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
  }

  OpenAI *openai = (OpenAI *)malloc(sizeof(OpenAI));
  openai->curl = curl;
  openai->model = OPENAI_DEFAULT_MODEL;
  openai->max_tokens = OPENAI_DEFAULT_MAX_TOKENS;
  openai->temperature = OPENAI_DEFAULT_TEMPERATURE;

  return openai;
}

CURLcode openai_easy_setopt(OpenAI *openai, OpenAIOption option, ...) {

  va_list args;
  va_start(args, option);

  switch (option) {
  case OPENAI_MODEL:
    openai->model = va_arg(args, char *);
    break;
  case OPENAI_MAX_TOKENS:
    openai->max_tokens = va_arg(args, int);
    break;
  case OPENAI_TEMPERATURE:
    openai->temperature = va_arg(args, double);
    break;
  case OPENAI_STOP:
    openai->stop = va_arg(args, char **);
    break;
  default:
    return CURLE_UNKNOWN_OPTION;
  }

  va_end(args);
  return CURLE_OK;
}

char *openai_easy_body(OpenAI *openai, char *data) {
  char *post_data = (char *)malloc(strlen(data) + 200);
  sprintf(post_data, format, data, openai->max_tokens, openai->model,
          openai->temperature);
  return post_data;
}

void openai_easy_perform(OpenAI *openai, char *request) {
  CURLcode res;

  if (openai) {
    char *body = openai_easy_body(openai, request);
    curl_easy_setopt(openai->curl, CURLOPT_POSTFIELDS, body);
    res = curl_easy_perform(openai->curl);
    if (res != CURLE_OK)
      fprintf(stderr, "Calling openai failed: %s\n", curl_easy_strerror(res));
  }
}

void openai_easy_cleanup(OpenAI *openai) {
  if (openai) {
    curl_easy_cleanup(openai->curl);
    free(openai);
  }
}
