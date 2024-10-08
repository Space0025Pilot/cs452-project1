#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "harness/unity.h"
#include "../src/lab.h"


// void setUp(void) {
//   // set stuff up here
// }

// void tearDown(void) {
//   // clean stuff up here
// }


void test_cmd_parse2(void)
{
     //The string we want to parse from the user.
     //foo -v
     char *stng = (char*)malloc(sizeof(char)*7); // leak here, not freed correctly
     strcpy(stng, "foo -v");
    //  printf("stng: %s\n", stng);            //Print line remove later
     char **actual = cmd_parse(stng);
    //  printf("actual[0]: %s\n", actual[0]);  //Print line remove later
    //  printf("actual[1]: %s\n", actual[1]);  //Print line remove later
     //construct our expected output
     size_t n = sizeof(char*) * 6;
     char **expected = (char**) malloc(sizeof(char*) *6);  //leak here, not freed correctly
     memset(expected,0,n);
     expected[0] = (char*)malloc(sizeof(char)*4);  //leak here, not freed correctly
     expected[1] = (char*)malloc(sizeof(char)*3);  //leak here, not freed correctly
     expected[2] = (char*)NULL;

     strcpy(expected[0], "foo");
     strcpy(expected[1], "-v");
    //  printf("expected[0]: %s\n", expected[0]);  //Print line remove later
    //  printf("expected[1]: %s\n", expected[1]);  //Print Line remove later
     TEST_ASSERT_EQUAL_STRING(expected[0],actual[0]);
     TEST_ASSERT_EQUAL_STRING(expected[1],actual[1]);
     TEST_ASSERT_FALSE(actual[2]);
     free(stng);
     free(expected[0]);
     free(expected[1]);
     free(expected[2]);
     cmd_free(expected);
     cmd_free(actual);
}

void test_cmd_parse(void)
{
     char **rval = cmd_parse("ls -a -l");
     TEST_ASSERT_TRUE(rval);
     TEST_ASSERT_EQUAL_STRING("ls", rval[0]);
     TEST_ASSERT_EQUAL_STRING("-a", rval[1]);
     TEST_ASSERT_EQUAL_STRING("-l", rval[2]);
     TEST_ASSERT_EQUAL_STRING(NULL, rval[3]);
     TEST_ASSERT_FALSE(rval[3]);
     cmd_free(rval);
}

void test_trim_white_no_whitespace(void)
{
     char *line = (char*) calloc(10, sizeof(char));
     strncpy(line, "ls -a", 10);
     char *rval = trim_white(line);
     TEST_ASSERT_EQUAL_STRING("ls -a", rval);
     free(line);
}

void test_trim_white_start_whitespace(void)
{
     char *line = (char*) calloc(10, sizeof(char));
     strncpy(line, "  ls -a", 10);
     char *rval = trim_white(line);
     TEST_ASSERT_EQUAL_STRING("ls -a", rval);
     free(line);
}

void test_trim_white_end_whitespace(void)
{
     char *line = (char*) calloc(10, sizeof(char));
     strncpy(line, "ls -a  ", 10);
     char *rval = trim_white(line);
     TEST_ASSERT_EQUAL_STRING("ls -a", rval);
     free(line);
}

void test_trim_white_both_whitespace_single(void)
{
     char *line = (char*) calloc(10, sizeof(char));
     strncpy(line, " ls -a ", 10);
     char *rval = trim_white(line);
     TEST_ASSERT_EQUAL_STRING("ls -a", rval);
     free(line);
}

void test_trim_white_both_whitespace_double(void)
{
     char *line = (char*) calloc(10, sizeof(char));
     strncpy(line, "  ls -a  ", 10);
     char *rval = trim_white(line);
     TEST_ASSERT_EQUAL_STRING("ls -a", rval);
     free(line);
}

void test_trim_white_all_whitespace(void)
{
     char *line = (char*) calloc(10, sizeof(char));
     strncpy(line, "  ", 10);
     char *rval = trim_white(line);
     TEST_ASSERT_EQUAL_STRING("", rval);
     free(line);
}

void test_trim_white_mostly_whitespace(void)
{
     char *line = (char*) calloc(10, sizeof(char));
     strncpy(line, "    a    ", 10);
     char *rval = trim_white(line);
     TEST_ASSERT_EQUAL_STRING("a", rval);
     free(line);
}

void test_get_prompt_default(void)
{
     char *prompt = get_prompt("MY_PROMPT");
     TEST_ASSERT_EQUAL_STRING(prompt, "shell>");
     free(prompt);
}

void test_get_prompt_custom(void)
{
     const char* prmpt = "MY_PROMPT";
     if(setenv(prmpt,"foo>",true)){
          TEST_FAIL();
     }

     char *prompt = get_prompt(prmpt);
     TEST_ASSERT_EQUAL_STRING(prompt, "foo>");
     free(prompt);
     unsetenv(prmpt);
}

void test_ch_dir_home(void)
{
     char *line = (char*) calloc(10, sizeof(char));
     strncpy(line, "cd", 10);
     char **cmd = cmd_parse(line);
     char *expected = getenv("HOME");
     change_dir(cmd);
     char *actual = getcwd(NULL,0);
     TEST_ASSERT_EQUAL_STRING(expected, actual);
     free(line);
     free(actual);
     cmd_free(cmd);
}

void test_ch_dir_root(void)
{
     char *line = (char*) calloc(10, sizeof(char));
     strncpy(line, "cd /", 10);
     char **cmd = cmd_parse(line);
     change_dir(cmd);
     char *actual = getcwd(NULL,0);
     TEST_ASSERT_EQUAL_STRING("/", actual);
     free(line);
     free(actual);
     cmd_free(cmd);
}

// int main(void) {
//   UNITY_BEGIN();
//   RUN_TEST(test_cmd_parse);
//   RUN_TEST(test_cmd_parse2);
//   RUN_TEST(test_trim_white_no_whitespace);
//   RUN_TEST(test_trim_white_start_whitespace);
//   RUN_TEST(test_trim_white_end_whitespace);
//   RUN_TEST(test_trim_white_both_whitespace_single);
//   RUN_TEST(test_trim_white_both_whitespace_double);
//   RUN_TEST(test_trim_white_all_whitespace);
//   RUN_TEST(test_get_prompt_default);
//   RUN_TEST(test_get_prompt_custom);
//   RUN_TEST(test_ch_dir_home);
//   RUN_TEST(test_ch_dir_root);

//   return UNITY_END();
// }
// #include "harness/unity.h"
// #include "../src/lab.h"


void setUp(void) {
  // set stuff up here
}

void tearDown(void) {
  // clean stuff up here
}

void test_stuff(void){
  // test stuff here
}

int main(void) {
  UNITY_BEGIN();
  // RUN_TEST(test_stuff);
  RUN_TEST(test_get_prompt_default);
  RUN_TEST(test_get_prompt_custom);
  RUN_TEST(test_cmd_parse);
  RUN_TEST(test_cmd_parse2);
  RUN_TEST(test_trim_white_no_whitespace);
  RUN_TEST(test_trim_white_start_whitespace);
  RUN_TEST(test_trim_white_end_whitespace);
  RUN_TEST(test_trim_white_both_whitespace_single);
  RUN_TEST(test_trim_white_both_whitespace_double);
  RUN_TEST(test_trim_white_mostly_whitespace);
  RUN_TEST(test_trim_white_all_whitespace); 
  RUN_TEST(test_ch_dir_home);
  RUN_TEST(test_ch_dir_root);
  
  return UNITY_END();
}
