/** \file
    A library for interacting with the mashape.com numbers api
  */
#include "get_number-lib.h"

/** param: number to get info on (a string)
    param: key_filename string of filename with mashape API key.
    param: print_fh a filehandle to print result of API request to
    returns: 0 on success, or 1,2,3 on an error.
**/

int run_get_number(char * number, char * key_filename, FILE * print_fh){
    int return_val = 0;
    char * url = NULL;
    char * key = NULL;
    if (!(url= get_url(number) ) ) {
        fprintf(stderr, "could not get url from %s\n", number);
        return_val = 1;
    }
    else if (!(key=get_key_from_file(key_filename) ) ) {
        fprintf(stderr, "could not get api key from filename %s\n", key_filename);
        return_val = 2;
    }
    else if (!(run_curl(key, url, print_fh) ) ) {
        fprintf(stderr, "problem with curl downloading from API\n");
        return_val =  3;
    }
    cleanup(&url, &key);
    return return_val;
}

/** param number (a string)
  takes a number in a string, returns a dynamically allocated url containing
  that number, if the string is a number
 **/
char * get_url(char * number){
    if (string_is_not_digits(number) ) {
        return NULL;
    }
    char * url_front = "https://numbersapi.p.mashape.com/";
    char * url_end = "/math";
    char * string = calloc(strlen(number) + strlen(url_front) + strlen(url_end) + 1, sizeof (char));
    strcpy(string, url_front);
    strcat(string, number);
    strcat(string, url_end);
    return string;
}

/** param number (a string)
  returns 1 if string is all digits, 0 if not
 **/
int string_is_not_digits(char * number){
    if (!number || !(*number)) 
        return 1;
    char * walker = number;
    while (*walker) {
        if (!(isdigit(*walker)) )  
            return 1;
        walker++; 
    }
    return 0;
}
/** param: filename of the keyfile
    returns a dynamically generated string of the api key
**/

char * get_key_from_file(char * filename){
    FILE * fh;
    if (!filename || !(*filename) || !(fh = fopen(filename, "r")) ) {
        return NULL;
    }
    char * return_val = NULL; 
    char buffer[512];
    int length;
    if (!(length = strlen(fgets(buffer, 511, fh) ) ) ) {
        fclose(fh);
        return NULL;
    }
    fclose(fh);
    if (buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
        length--;
    }
    return_val = calloc(length + 1, sizeof (char) );
    strcpy(return_val, buffer);
    return return_val;
}

/** param: a string of the api key
    param: a url with the number to retrieve info on
    param: a filehandle to print the retrieved info to
    returns 1 on success, 0 on failure
**/
    
int run_curl(char * key, char * url, FILE * fh){
    CURL * curl = NULL;
    CURLcode res;
    struct curl_slist *slist=NULL;
    curl = curl_easy_init();
    int return_val = 0;
    if(url) {
        return_val = 1;
        /** Options: pass the url, don't print
            header, add the key to a header in the request, write data to the 
            passed in file handle
          **/
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HEADER, 0);

        slist = curl_slist_append(slist, key);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fh);

        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
        /* Check for errors */ 
        if(res != CURLE_OK ) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", 
                    curl_easy_strerror(res));
            return_val = 0;
        }
        else {
            fprintf(fh, "\n");
        }

        /* always cleanup */ 
        curl_easy_cleanup(curl);
        curl_slist_free_all(slist); /* free the list again */
    }
    else {
        return return_val;
    }
    return return_val; // 1 success
}

//frees passed strings if not NULL, and sets the pointers to NULL

void cleanup (char ** url, char ** key){
    if(*url) {
        free(*url);
        *url = NULL;
    }
    if(*key) {
        free(*key);
        *key = NULL;
    }
    return;
}


