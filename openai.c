#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>


#define API_URL "https://api.openai.com/v1/engines/text-davinci-002/completions"


char* openai_generate_post_data(char *data) {
    char *post_data;
    sprintf(post_data, "{\"prompt\":\"What is the weather like today?\",\"max_tokens\":2048,\"stop\":\"\",\"temperature\":0.5}");
    return post_data;
}


bool openai_curl_setup(CURL **curl) {
    char *api_key = getenv("OPENAI_API_KEY");
    if (!api_key || strlen(api_key) < 20) {
        printf("OPENAI_API_KEY environment variable not set.\n");
        return false;
    }

    *curl = curl_easy_init();

    if(*curl) {
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

void openai_curl_perform(CURL *curl) {
    CURLcode res;

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, openai_generate_post_data("dwdw"));
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
          fprintf(stderr, "Calling openai failed: %s\n",
                  curl_easy_strerror(res));
    }
}

int main(int argc, char *argv[])
{
    CURL *curl;
    if (!openai_curl_setup(&curl))
        return 1;

    openai_curl_perform(curl);
    curl_easy_cleanup(curl);
    return 0;
}
