#include "easy.h"

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

  OpenAI *openai;
  openai = openai_easy_init(openai_api_key);
  openai_easy_setopt(openai, OPENAI_MAX_TOKENS, 12);

  while (1) {
    char *request = openai_main_getinput();
    openai_easy_perform(openai, request);
    free(request);
  }

  openai_easy_cleanup(openai);
  return 0;
}
