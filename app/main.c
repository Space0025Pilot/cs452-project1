/**File: main.c
 * Author: Caitlyn Nelson
 * Date: 9/16/2024
 * Description: Main Code for Simple Shell
 **/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../src/lab.h"

int main(int argc, char **argv)
{

  int opt;
  char *line;
  char **linepointer;
  char *linereturnpointer;
  int err;
  struct shell *sh;
  bool handledOrNot;

  /* Catch the aspect of printing the version */
  /* Use getopt() to process command line arguments */
  while ((opt = getopt(argc, argv, "v")) != -1)
  {
    switch (opt)
    {
    case 'v':
      printf("Version -> %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
      break;
    case '?':
      if (optopt == 'opt')
        fprintf(stderr, "Option -%c requires an argument.\n", optopt);
      else if (isprint(optopt))
        fprintf(stderr, "Unknown option `-%c'.\n", optopt);
      else
        fprintf(stderr,
                "Unknown option character `\\x%x'.\n",
                optopt);
      return 1;
    default:
      abort();
    } 
  }
  
  /* Initialize the shell */
  sh_init(sh);

  /* Get prompt from the environment variable*/
  sh->prompt = get_prompt("MY_PROMPT");
  // printf("Get prompt variable: %s\n", prompt);

  /* Start of readline and use of history */
  using_history();
  while ((line=readline("$"))){
    // printf("%s\n",line);
    add_history(line);
    
    /* Trim whitespace from line*/
    line = trim_white(line);

    /* Parse the command line */
    linereturnpointer = cmd_parse(line); //may have pointer issues here just BEWARE!
    linepointer = &linereturnpointer;

    /* Handle the arguments */
    handledOrNot = do_builtin(sh, linepointer);
    if(handledOrNot == false){
      //error
      cmd_free(linepointer);
      free(line);
      sh_destroy(sh);
      exit(-1);
    }

  }
  /* Free the command line */
  cmd_free(linepointer);

  /* Free the allocated memory for the shell */
  sh_destroy(sh);
  return 0;
}
    




  //Extra code that may help later:
  //Read the entire line and delimit by whitespace
    // if((strncmp(line, "cd", 2) == 0)){
    //   printf("success\n");
    //   //nothing entered -- users home directory
    //   if(strcmp(line, "cd") == 0){
    //     home = getenv("HOME");
    //     printf("Getenv HOME: %s\n", home);
    //     homepointer = &home;
    //     if(home != NULL){
    //       err = change_dir(homepointer);
    //       printf("err: %d\n", err);
    //       printf("Getenv HOME Second Call: %s\n", getenv("HOME"));
    //       if(err == -1){
    //         // free(err);
    //         // free(homepointer);
    //         // free(home);
    //         exit(1);
    //       }
    //     }
    //     // free(err);
    //     // free(homepointer);
    //     // free(home);