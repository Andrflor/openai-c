#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "easy.h"

char *openai_main_getinput(void) {
  char *request;
  printf("You: ");
  size_t size = 0;
  getline(&request, &size, stdin);
  request[strcspn(request, "\n")] = '\0';
  return request;
}

int main(int argc, char *argv[]) {
  char *openai_api_key = getenv("OPENAI_API_KEY");
  if (!openai_api_key || strlen(openai_api_key) != 51) {
    printf("OPENAI_API_KEY environment variable not properly set.\n");
    return 1;
  }

  OpenAI openai = openai_easy_init(openai_api_key);

  char *stop[4] = {"\\n", "\\t", "wwwww"};
  openai_easy_setopt(openai, OPENAIOPT_STOP, stop);
  openai_easy_setopt(openai, OPENAIOPT_MODEL, "text-davinci-002");
  openai_easy_setopt(openai, OPENAIOPT_TEMPERATURE, 0.75);
  openai_easy_setopt(openai, OPENAIOPT_FREQUENCY_PENALTY, 0.1);
  openai_easy_setopt(openai, OPENAIOPT_PRESENCE_PENALTY, 0.1);
  openai_easy_setopt(openai, OPENAIOPT_TOP_P, 0.9);

  char *request = openai_main_getinput();
  struct OpenAIResponse response = openai_easy_perform(openai, request);
  printf("Response %s\n", response.data);
  printf("Code %i\n", response.code);
  free(request);

  openai_easy_cleanup(openai);
  return 0;
}
