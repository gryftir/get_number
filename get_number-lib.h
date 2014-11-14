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



/*function declarations*/
int run_get_number(char * number, char * key_filename, FILE * print_fh);
char * get_url(char * number);
int string_is_not_digits(char * number);
char * get_key_from_file(char * filename);
int run_curl(char * key, char * url, FILE * fh);
void cleanup (char ** url, char ** key);

#endif


/* call graph

main
  run_get_number
    get_url
      string_is_not_digits
    get_key_from_file
    run_curl
    cleanup
*/
