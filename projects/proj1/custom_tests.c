#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "asserts.h"
// Necessary due to static functions in state.c
#include "state.c"

char* COLOR_GREEN = "";
char* COLOR_RESET = "";

/* Look at asserts.c for some helpful assert functions */

int greater_than_forty_two(int x) {
  return x > 42;
}

bool is_vowel(char c) {
  char* vowels = "aeiouAEIOU";
  for (int i = 0; i < strlen(vowels); i++) {
    if (c == vowels[i]) {
      return true;
    }
  }
  return false;
}

/*
  Example 1: Returns true if all test cases pass. False otherwise.
    The function greater_than_forty_two(int x) will return true if x > 42. False otherwise.
    Note: This test is NOT comprehensive
*/
bool test_greater_than_forty_two() {
  int testcase_1 = 42;
  bool output_1 = greater_than_forty_two(testcase_1);
  if (!assert_false("output_1", output_1)) {
    return false;
  }

  int testcase_2 = -42;
  bool output_2 = greater_than_forty_two(testcase_2);
  if (!assert_false("output_2", output_2)) {
    return false;
  }

  int testcase_3 = 4242;
  bool output_3 = greater_than_forty_two(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

/*
  Example 2: Returns true if all test cases pass. False otherwise.
    The function is_vowel(char c) will return true if c is a vowel (i.e. c is a,e,i,o,u)
    and returns false otherwise
    Note: This test is NOT comprehensive
*/
bool test_is_vowel() {
  char testcase_1 = 'a';
  bool output_1 = is_vowel(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'e';
  bool output_2 = is_vowel(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'i';
  bool output_3 = is_vowel(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'o';
  bool output_4 = is_vowel(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'u';
  bool output_5 = is_vowel(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'k';
  bool output_6 = is_vowel(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

/* Task 4.1 */

bool test_is_tail() {
  // TODO: Implement this function.
  char testcase_1 = 'w';
  bool output_1 = is_tail(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 's';
  bool output_2 = is_tail(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'a';
  bool output_3 = is_tail(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'd';
  bool output_4 = is_tail(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'q';
  bool output_5 = is_tail(testcase_5);
  if (!assert_false("output_5", output_5)) {
    return false;
  }

  char testcase_6 = '!';
  bool output_6 = is_tail(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

bool test_is_head() {
  // TODO: Implement this function.
  char testcase_1 = 'W';
  bool output_1 = is_head(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'S';
  bool output_2 = is_head(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'A';
  bool output_3 = is_head(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'D';
  bool output_4 = is_head(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = 'x';
  bool output_5 = is_head(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'w';
  bool output_6 = is_head(testcase_6);
  if (!assert_false("output_6", output_6)) {
    return false;
  }

  return true;
}

bool test_is_snake() {
  // TODO: Implement this function.
  char testcase_1 = 'W';
  bool output_1 = is_snake(testcase_1);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 's';
  bool output_2 = is_snake(testcase_2);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = '<';
  bool output_3 = is_snake(testcase_3);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = '>';
  bool output_4 = is_snake(testcase_4);
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = '^';
  bool output_5 = is_snake(testcase_5);
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = 'v';
  bool output_6 = is_snake(testcase_6);
  if (!assert_true("output_6", output_6)) {
    return false;
  }

  char testcase_7 = '9';
  bool output_7 = is_snake(testcase_7);
  if (!assert_false("output_7", output_7)) {
    return false;
  }

  return true;
}

bool test_body_to_tail() {
  // TODO: Implement this function.
  char testcase_1 = '^';
  bool output_1 = (body_to_tail(testcase_1) == 'w');
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = '>';
  bool output_2 = (body_to_tail(testcase_2) == 'd');
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = '<';
  bool output_3 = (body_to_tail(testcase_3) == 'a');
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'v';
  bool output_4 = (body_to_tail(testcase_4) == 's');
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = '4';
  bool output_5 = (body_to_tail(testcase_5) == '?');
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = '9';
  bool output_6 = (body_to_tail(testcase_6) == '?');
  if (!assert_true("output_6", output_6)) {
    return false;
  }
  return true;
}

bool test_head_to_body() {
  // TODO: Implement this function.
  char testcase_1 = 'W';
  bool output_1 = (head_to_body(testcase_1) == '^');
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'S';
  bool output_2 = (head_to_body(testcase_2) == 'v');
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = 'A';
  bool output_3 = (head_to_body(testcase_3) == '<');
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  char testcase_4 = 'D';
  bool output_4 = (head_to_body(testcase_4) == '>');
  if (!assert_true("output_4", output_4)) {
    return false;
  }

  char testcase_5 = '4';
  bool output_5 = (head_to_body(testcase_5) == '?');
  if (!assert_true("output_5", output_5)) {
    return false;
  }

  char testcase_6 = '9';
  bool output_6 = (head_to_body(testcase_6) == '?');
  if (!assert_true("output_6", output_6)) {
    return false;
  }
  return true;
}

bool test_get_next_x() {
  // TODO: Implement this function.
  char testcase_1 = '>';
  bool output_1 = (get_next_x(10, testcase_1) == 11);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 'a';
  bool output_2 = (get_next_x(20, testcase_2) == 19);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = '0';
  bool output_3 = (get_next_x(30, testcase_3) == 30);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

bool test_get_next_y() {
  // TODO: Implement this function.
  char testcase_1 = '^';
  bool output_1 = (get_next_y(10, testcase_1) == 9);
  if (!assert_true("output_1", output_1)) {
    return false;
  }

  char testcase_2 = 's';
  bool output_2 = (get_next_y(20, testcase_2) == 21);
  if (!assert_true("output_2", output_2)) {
    return false;
  }

  char testcase_3 = '0';
  bool output_3 = (get_next_y(30, testcase_3) == 30);
  if (!assert_true("output_3", output_3)) {
    return false;
  }

  return true;
}

bool test_customs() {
  if (!test_greater_than_forty_two()) {
    printf("%s\n", "test_greater_than_forty_two failed.");
    return false;
  }
  if (!test_is_vowel()) {
    printf("%s\n", "test_is_vowel failed.");
    return false;
  }
  if (!test_is_tail()) {
    printf("%s\n", "test_is_tail failed");
    return false;
  }
  if (!test_is_head()) {
    printf("%s\n", "test_is_head failed");
    return false;
  }
  if (!test_is_snake()) {
    printf("%s\n", "test_is_snake failed");
    return false;
  }
  if (!test_body_to_tail()) {
    printf("%s\n", "test_body_to_tail failed");
    return false;
  }
  if (!test_head_to_body()) {
    printf("%s\n", "test_head_to_body failed");
    return false;
  }
  if (!test_get_next_x()) {
    printf("%s\n", "test_get_next_x failed");
    return false;
  }
  if (!test_get_next_y()) {
    printf("%s\n", "test_get_next_y failed");
    return false;
  }
  return true;
}

void init_colors() {
  if (!isatty(STDOUT_FILENO)) {
    return;
  }

  if (getenv("NO_COLOR") != NULL) {
    return;
  }

  char* term = getenv("TERM");
  if (term == NULL || strstr(term, "xterm") == NULL) {
    return;
  }

  COLOR_GREEN = "\033[0;32m";
  COLOR_RESET = "\033[0m";
}

bool test_and_print(char* label, bool (*run_test)()) {
  printf("\nTesting %s...\n", label);
  bool result = run_test();
  if (result) {
    printf("%sAll %s tests passed!%s\n", COLOR_GREEN, label, COLOR_RESET);
  } else {
    printf("Not all %s tests passed.\n", label);
  }
  return result;
}

int main(int argc, char* argv[]) {
  init_colors();

  if (!test_and_print("custom", test_customs)) {
    return 0;
  }

  return 0;
}
