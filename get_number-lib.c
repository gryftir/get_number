/*GENERIC c file library*/
#include "get_number-lib.h"


int run_get_number(char * number, char * key_filename, FILE * print_fh){
  int return_val;
  return return_val;
}
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

char * get_key_from_file(char * filename){
  char * return_val;
  return return_val;
}
char * get_string_from_number_api(char * url, char * key){
  char * return_val;
  return return_val;
}
int init_string_holder(string_holder * string_holder_p, size_t num){
  int return_val;
  return return_val;
}
CURL * setup_curl(char * key, char * url, string_holder * string_holder_p){
  CURL * return_val;
  return return_val;
}
void cleanup (CURL * curl_h, char * url, char * key, char * returned_string){
  return;
}

/*call back used in setting up curl */
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);


