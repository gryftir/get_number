#include <glib.h>
#include <glib.h>
#include "../get_number-lib.h"

typedef struct {
  void * value;
} get_num_struct;

typedef struct {
  char filename[L_tmpnam];
}tmpfile_struct;



//setup
void setup_num(get_num_struct * loc, gconstpointer test_data) {
  return;
}

//teardown
void teardown_num(get_num_struct * loc, gconstpointer test_data) {
  return;
}


//setup tmpfile
void setup_tmpfile(tmpfile_struct * temp, gconstpointer test_data) {
  strcpy(temp->filename, ".test_file");
  return;
}

//teardown tmpfile
void teardown_tmpfile(tmpfile_struct * temp, gconstpointer test_data) {
  return;
}


//tests

void test_string_is_not_digits (get_num_struct * loc, gconstpointer ignored) {
  g_assert_cmpint(string_is_not_digits(NULL), ==, 1);
  g_assert_cmpint(string_is_not_digits(""), ==, 1);
  g_assert_cmpint(string_is_not_digits("1"), ==, 0);
  g_assert_cmpint(string_is_not_digits("a"), ==, 1);
  g_assert_cmpint(string_is_not_digits("1234"), ==, 0);
  g_assert_cmpint(string_is_not_digits("a1234"), ==, 1);
  g_assert_cmpint(string_is_not_digits("12a34"), ==, 1);
  g_assert_cmpint(string_is_not_digits("1234a"), ==, 1);
  return;
}

void test_get_url (get_num_struct * loc, gconstpointer ignored) {
  char * string = get_url("12");
  g_assert_cmpstr("https://numbersapi.p.mashape.com/12/math", ==, string);
  free (string);
  return;
}

void test_get_key_from_file (tmpfile_struct * temp, gconstpointer ignored) {
  FILE * fh = fopen(temp->filename, "w");
  fprintf(fh, "test");
  fclose(fh);
  char * result = NULL;
  result = get_key_from_file(temp->filename);
  g_assert_cmpstr("test", ==, result );
  if (result) {
    free(result);
  }
  fh = fopen(temp->filename, "w");
  fprintf(fh, "test\n");
  fclose(fh);
  result = get_key_from_file(temp->filename);
  g_assert_cmpstr("test", ==, result);
  if (result) {
    free(result);
  }
  tmpfile_struct wrong_filename;
  strcpy(wrong_filename.filename, ".wrong_filename");
  result = get_key_from_file(wrong_filename.filename);
  g_assert_null(result);
  if (result) {
    free(result);
  }
  result = get_key_from_file("");
  g_assert_null(result);
  if (result) {
    free(result);
  }
  remove(temp->filename);
  return;
}


void test_cleanup (get_num_struct * temp, gconstpointer ignored) {
  char * key = calloc(4, 1);  
  char * url = calloc(4, 1);
  g_assert(key);
  g_assert(url);
  strcpy(key, "key");
  strcpy(url, "url");
  cleanup(&url, &key);
  g_assert_null(url);
  g_assert_null(key);
  cleanup(&url, &key);
  g_assert_null(url);
  g_assert_null(key);
}

void test_run_curl (void) {
  if (g_test_subprocess ())
  {
    char * url = get_url("24");
    char * key = get_key_from_file("key.txt");
    g_assert_cmpstr(key, ==, "X-Mashape-Key: lFsTPRQ91CmshmUMEy6CzwxBVwD9p1VA63JjsnEGlSXQjQTlqC");
    g_assert_cmpint (run_curl(key, url, stdout), ==, 1);
    cleanup(&key, &url);
    return;
  }

  // Reruns this same test in a subprocess
  g_test_trap_subprocess (NULL, 0, 0);
  g_test_trap_assert_stdout ("24*");
  return;
}


void test_run_get_number (void) {
  if (g_test_subprocess ())
  {
    g_assert_cmpint(run_get_number("24", "key.txt", stdout), ==, 0);
    g_assert_cmpint(run_get_number("blah", "key.txt", stdout), ==, 1);
    g_assert_cmpint(run_get_number("24", "no.such.file", stdout), ==, 2);
    g_assert_cmpint(run_get_number("24", "test/wrongkey.txt", stdout), ==, 3);
    return; 
  }
  g_test_trap_subprocess (NULL, 0, 0);
  return;
}


int main(int argc, char *argv[])
{
  g_test_init(&argc, &argv, NULL);
  g_test_add("/set1/string_is_not_digits", get_num_struct, NULL, setup_num, test_string_is_not_digits, teardown_num);
  g_test_add("/set1/get_url", get_num_struct, NULL, setup_num, test_get_url, teardown_num);
  g_test_add("/set1/get_key_from_file", tmpfile_struct, NULL, setup_tmpfile, test_get_key_from_file, teardown_tmpfile);
  g_test_add("/set1/cleanup", get_num_struct, NULL, setup_num, test_cleanup, teardown_num);
  g_test_add_func ("/set1/run_curl", test_run_curl);
  g_test_add_func ("/set1/run_get_number", test_run_get_number);
  return g_test_run();
}
