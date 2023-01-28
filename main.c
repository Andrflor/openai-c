#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPENAI_API_URL "https://api.openai.com/v1/completions"
#define OPENAI_DEFAULT_MODEL "text-davinci-003"
#define OPENAI_DEFAULT_MAX_TOKENS 2048
#define OPENAI_DEFAULT_TEMPERATURE 0.7

const char *format = "{\"prompt\":\"%s\",\"max_tokens\": %d,\"stop\":\"\","
                     "\"model\": \"%s\",\"temperature\": %f}";

struct Openai_easy {
  CURL *curl;
  char *model;
  int max_tokens;
  double temperature;
};

typedef struct Openai_easy Openai;

Openai *openai_easy_init(char *api_key) {
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

  Openai *openai = (Openai *)malloc(sizeof(Openai));
  openai->curl = curl;
  openai->model = OPENAI_DEFAULT_MODEL;
  openai->max_tokens = OPENAI_DEFAULT_MAX_TOKENS;
  openai->temperature = OPENAI_DEFAULT_TEMPERATURE;

  return openai;
}

char *openai_easy_body(Openai *openai, char *data) {
  printf("Going there");
  char *post_data = (char *)malloc(strlen(data) + 200);
  sprintf(post_data, format, data, openai->max_tokens, openai->model,
          openai->temperature);
  printf(post_data);
  return post_data;
}

void openai_easy_perform(Openai *openai, char *request) {
  CURLcode res;

  if (openai) {
    char *body = openai_easy_body(openai, request);
    curl_easy_setopt(openai->curl, CURLOPT_POSTFIELDS, body);
    res = curl_easy_perform(openai->curl);
    if (res != CURLE_OK)
      fprintf(stderr, "Calling openai failed: %s\n", curl_easy_strerror(res));
  }
}

void openai_easy_cleanup(Openai *openai) {
  if (openai) {
    curl_easy_cleanup(openai->curl);
    free(openai);
  }
}

char *openai_main_getinput() {
  char *request;
  printf("You: ");
  size_t size = 0;
  getline(&request, &size, stdin);
  request[strcspn(request, "\n")] = '\0';
  return request;
}

int main(int argc, char *argv[]) {
  char *openai_api_key = getenv("OPENAI_API_KEY");
  if (!openai_api_key || strlen(openai_api_key) <= 50) {
    printf("OPENAI_API_KEY environment variable not set.\n");
    return 1;
  }

  Openai *openai;
  openai = openai_easy_init(openai_api_key);

  while (1) {
    char *request = openai_main_getinput();
    openai_easy_perform(openai, request);
    free(request);
  }

  openai_easy_cleanup(openai);
  return 0;
}
