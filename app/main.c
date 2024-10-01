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
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../src/lab.h"

int main(int argc, char **argv)
{

  int opt;
  char *line;
  char **linepointer;
  char **linereturnpointer;
  // int err;
  struct shell *sh = (struct shell *)malloc(sizeof(struct shell));
  bool handledOrNot;
  char * prompt = "";
  pid_t parentProcessID;
  pid_t childProcessID;
  int status;
  int executed = 0;
  // bool ampFlag = false;
  // int idCounter = 1;
  // char * ampYesOrN0;

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
  sh_init(*(&sh));

  /* Get prompt from the environment variable*/
  prompt = get_prompt("MY_PROMPT");
  // strcpy(sh->prompt, prompt);
  sh->prompt = prompt;
  printf("Get prompt variable: %s\n", prompt);
  printf("Get shell prompt variable: %s\n", sh->prompt);

  /* Start of readline and use of history */
  using_history();
  while ((line=readline("$"))){
    // printf("%s\n",line);
    add_history(line);
    
    /* Trim whitespace from line*/
    line = trim_white(line);

    // /* Detecting no commands */
    // if(!isspace(line[0]) || line[0] =='\0'){

    // }

    /* Parse the command line */
    linereturnpointer = cmd_parse(line); //may have pointer issues here just BEWARE!
    linepointer = *(&linereturnpointer);

    /* Handle the arguments */
    handledOrNot = do_builtin(*(&sh), linepointer);
    if(handledOrNot == false){

      childProcessID = fork();
      parentProcessID = getppid();

      if(childProcessID < 0){
        cmd_free(linepointer);
        free(line);
        sh_destroy(*(&sh));
        perror("fork failed");
        exit(-1);
      }
      else if(childProcessID == 0){
        printf("This is the child process, PID: %d\n", getpid());
        setpgid(childProcessID, childProcessID);
        tcsetpgrp(sh->shell_terminal, childProcessID);
        signal (SIGINT, SIG_DFL);
        signal (SIGQUIT, SIG_DFL);
        signal (SIGTSTP, SIG_DFL);
        signal (SIGTTIN, SIG_DFL);
        signal (SIGTTOU, SIG_DFL);
        executed = execvp(linepointer[0], linepointer);
        if(executed == -1){
          cmd_free(linepointer);
          free(line);
          sh_destroy(*(&sh));
          perror("not executing");
          exit(-1);
        }
      } 
      else {
        printf("This is the parent process, PID: %d\n", getpid());
        waitpid(-1, &status, 0);
      }
      
      //error
      // cmd_free(linepointer);
      // free(line);
      // sh_destroy(*(&sh));
      // exit(-1);
    }
    
    //WE ARE WORKING ON THIS PART
    // //walk through the array to find how many arguments
    // int i = 0;
    // while(linepointer[i] != NULL){
    //   i++;
    // }
    // i--;
    // //check the last argument for ampersand
    // ampYesOrN0 = strchr(linepointer[i], '&');
    // //flip flag depending on the output
    // if(ampYesOrN0 != NULL){
    //   ampFlag = true;
    // } else {
    //   ampFlag = false;
    // }

    // // if(ampFlag == true){
    // //   idCounter++;
    // // }

    //   childProcessID = fork();
    //   parentProcessID = getppid();

    //   if(ampFlag == true){
    //     printf("[%d] %d %s\n", idCounter, childProcessID, *linepointer);
    //   }

    //   if(childProcessID < 0){
    //     cmd_free(linepointer);
    //     free(line);
    //     sh_destroy(*(&sh));
    //     perror("fork failed");
    //     exit(-1);
    //   }
    //   else if(childProcessID == 0){
    //     // printf("This is the child process, PID: %d\n", getpid());
    //     setpgid(childProcessID, childProcessID);
    //     tcsetpgrp(sh->shell_terminal, childProcessID);
    //     signal (SIGINT, SIG_DFL);
    //     signal (SIGQUIT, SIG_DFL);
    //     signal (SIGTSTP, SIG_DFL);
    //     signal (SIGTTIN, SIG_DFL);
    //     signal (SIGTTOU, SIG_DFL);

    //     handledOrNot = do_builtin(*(&sh), linepointer);

    //     if(handledOrNot == false){
    //       executed = execvp(linepointer[0], linepointer);
    //       idCounter++;
    //     }
    //     if(executed == -1){
    //       cmd_free(linepointer);
    //       free(line);
    //       sh_destroy(*(&sh));
    //       perror("not executing");
    //       exit(-1);
    //     }
    //   } 
    //   else {
    //     // printf("This is the parent process, PID: %d\n", getpid());
    //     if(ampFlag == false){
    //       waitpid(-1, &status, WNOHANG);
    //     }
        
    //   }
      
    //   //error
    //   // cmd_free(linepointer);
    //   // free(line);
    //   // sh_destroy(*(&sh));
    //   // exit(-1);

  }


  /* Free the command line */
  cmd_free(linepointer);
  cmd_free(linereturnpointer);
  free(line);

  /* Free the allocated memory for the shell */
  sh_destroy(*(&sh));
  return 0;
}