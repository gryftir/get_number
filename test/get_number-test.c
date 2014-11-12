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

//test_init

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

int main(int argc, char *argv[])
{
  g_test_init(&argc, &argv, NULL);
  g_test_add("/set1/num test", get_num_struct, NULL, setup_num, test_string_is_not_digits, teardown_num);
  return g_test_run();
}
