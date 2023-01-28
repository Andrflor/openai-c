#include <curl/curl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define API_URL "https://api.openai.com/v1/engines/text-davinci-003/completions"

char *openai_generate_post_data(char *data) {
  char *post_data = (char *)malloc(strlen(data) + 200);
  sprintf(post_data,
          "{\"prompt\":\"%s\",\"max_tokens\":2048,\"stop\":\"\","
          "\"temperature\":0.5}",
          data);
  return post_data;
}

bool openai_curl_setup(CURL **curl) {
  char *api_key = getenv("OPENAI_API_KEY");
  if (!api_key || strlen(api_key) <= 50) {
    printf("OPENAI_API_KEY environment variable not set.\n");
    return false;
  }

  *curl = curl_easy_init();

  if (*curl) {
    struct curl_slist *headers = NULL;
    char auth_header[100];
    sprintf(auth_header, "Authorization: Bearer %s", api_key);
    headers = curl_slist_append(headers, auth_header);
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(*curl, CURLOPT_URL, API_URL);
    curl_easy_setopt(*curl, CURLOPT_POST, 1);
    curl_easy_setopt(*curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(*curl, CURLOPT_WRITEFUNCTION, NULL);
    curl_easy_setopt(*curl, CURLOPT_WRITEDATA, stdout);
    return true;
  }
  return false;
}

void openai_curl_perform(CURL *curl, char *request) {
  CURLcode res;

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,
                     openai_generate_post_data(request));
    res = curl_easy_perform(curl);
    if (res != CURLE_OK)
      fprintf(stderr, "Calling openai failed: %s\n", curl_easy_strerror(res));
  }
}

int main(int argc, char *argv[]) {
  char *request;
  printf("You: ");
  size_t size = 0;
  getline(&request, &size, stdin);
  request[strcspn(request, "\n")] = '\0';

  CURL *curl;
  if (!openai_curl_setup(&curl))
    return 1;

  openai_curl_perform(curl, request);
  curl_easy_cleanup(curl);
  return 0;
}
