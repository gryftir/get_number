/*GENERIC header file */
#ifndef _GENERIC_
#define _GENERIC_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <curl/curl.h>
#include <ctype.h>

/*further includes*/

/*preprocessor items*/

/*Structures*/
typedef struct string_holder {
  char * string;
  size_t length_in_bytes;
}string_holder;

/*function declarations*/
int run_get_number(char * number, char * key_filename, FILE * print_fh);
char * get_url(char * number);
int string_is_not_digits(char * number);
char * get_key_from_file(char * filename);
char * get_string_from_number_api(char * url, char * key);
int init_string_holder(string_holder * string_holder_p, size_t num);
CURL * setup_curl(char * key, char * url, string_holder * string_holder_p);
void cleanup (CURL * curl_h, char * url, char * key, char * returned_string);

/*call back used in setting up curl */
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

#endif


/* call graph

main
  run_get_number
    get_url
      string_is_not_digits
    get_key_from_file
    get_string_from_number_api
    init_string_holder
    setup_curl
    cleanup
*/
