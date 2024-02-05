#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include <curl/curl.h>

#define BUFFER_SIZE 16*1024UL
#define MAX_REG_LEN 10UL
#define JSON_FORMATTER "jq . "
#define API_HEADER "SVV-Authorization: Apikey "
#define CMD_LEN 255UL

#define STR2(X) #X
#define STR(X) STR2(X)

/**
 * Allocates a new string, user's responsibility to free
*/
inline char *str_to_upper(const char *in)  {
    char *out = strdup(in);
    size_t i = 0;
    while (in[i] != '\0') {
        out[i] = toupper(in[i]);
        i++;
    }
    return out;
}

int main(int argc, char **argv) {
    char reg[MAX_REG_LEN+1] = {0};

    const char *key_name = "VEGVESEN_API_KEY";
    const char *api_key = getenv(key_name);

    if (api_key == NULL) {
        fprintf(stderr, "ERROR: Environment variable %s not set\n", key_name);
        exit(EXIT_FAILURE);
    }

    if (argc == 2) {
        strncpy(reg, argv[1], MAX_REG_LEN);
    } else {
        char format[5];
        snprintf(format, sizeof format, "%%%zus", MAX_REG_LEN);
        if (scanf(format, reg) != 1) {
            perror("scanf");
            fprintf(stderr, "ERROR: %s", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    assert(reg[0] != '\0');


    CURL *hnd = curl_easy_init();

    char url[CMD_LEN] = "https://www.vegvesen.no/ws/no/vegvesen/kjoretoy/felles/datautlevering/enkeltoppslag/kjoretoydata?kjennemerke=";

    strcat(url, reg);

    curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(hnd, CURLOPT_URL, url);

    char key_header[CMD_LEN] = API_HEADER;
    strcat(key_header, api_key);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, key_header);
    curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);


    char cmd[CMD_LEN] = JSON_FORMATTER;

    /* Un-comment below to redirect and save to a file */
    // char reg_json[32] = {0};
    // char *reg_upper = str_to_upper(reg);
    // strcpy(reg_json, reg_upper);
    // strcat(reg_json, ".json");
    // strcat(cmd, " > ");
    // strcat(cmd, reg_json);

    FILE *jq_fp = popen(cmd, "w");
    // free(reg_upper);
    if (jq_fp == NULL) {
        perror("popen");
        pclose(jq_fp);
        exit(EXIT_FAILURE);
    }

    // curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(hnd, CURLOPT_WRITEDATA, jq_fp);

    CURLcode res = curl_easy_perform(hnd);

    if (res != CURLE_OK) {
        fprintf(stderr, "ERROR: curl_easy_perform failed: %s\n", curl_easy_strerror(res));
        curl_easy_cleanup(hnd);
        exit(EXIT_FAILURE);
    }

    int jq_status = pclose(jq_fp);
    if (jq_status == -1) {
        perror("pclose");
        exit(EXIT_FAILURE);
    }

    curl_easy_cleanup(hnd);

    return 0;
}
