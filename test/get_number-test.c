#include <glib.h>
#include "../get_number-lib.h"

typedef struct {
  void * value;
} get_num_struct;
  



//setup
void setup_num(get_num_struct * loc, gconstpointer test_data) {
  return;
}

//teardown
void teardown_num(get_num_struct * loc, gconstpointer test_data) {
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

int main(int argc, char *argv[])
{
  g_test_init(&argc, &argv, NULL);
  g_test_add("/set1/string_is_not_digits", get_num_struct, NULL, setup_num, test_string_is_not_digits, teardown_num);
  g_test_add("/set1/get_url", get_num_struct, NULL, setup_num, test_get_url, teardown_num);
  return g_test_run();
}
