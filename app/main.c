/**File: main.c
 * Author: Caitlyn Nelson
 * Date: 9/16/2024
 * Description: Main Code for Simple Shell
 **/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../src/lab.h"

static int exitcmd(int flag){
  if(flag == 1){
    exit(0);
  }
  exit(1);
}

int main(int argc, char **argv)
{

  int opt;
  char * prompt;
  int exitflag = 0;
  // struct shell *sh = (struct shell *)malloc(sizeof(struct shell));
  // sh_init(sh);

  /* Use getopt() to process command line arguments */
  while ((opt = getopt(argc, argv, "pvczhe")) != -1)
  {
    switch (opt)
    {
    case 'p':
      prompt = get_prompt("MY_PROMPT");
      printf("Get prompt variable: %s\n", prompt);
      free(prompt);
      prompt = NULL; 
      break;
    case 'v':
      printf("Version -> %d.%d\n", lab_VERSION_MAJOR, lab_VERSION_MINOR);
      break;
    case 'c':
      printf("Hi c\n");
      break;
    case 'z':
      printf("Hi z\n");
      break;
    case 'h':
      // fprintf(stdout, "Usage: %s [-a] [-v] [-c] [-z] [-h]\n", argv[0]);
      fprintf(stdout, "        -p        Prints shell prompt\n");
      fprintf(stdout, "        -v        Display the shell version\n");
      fprintf(stdout, "        -c        Display proc entries sorted by command lexicographically\n");
      fprintf(stdout, "        -z        Display ONLY proc entries in the zombie state\n");
      fprintf(stdout, "        -h        Display this help message\n");
      exit(0);
    case 'e':
      printf("Exiting...\n");
      exitflag = 1;
      exitcmd(exitflag);
      break;
    // default:
    //     fprintf(stderr, "Error: Invalid Option Specified\n");
    //     // fprintf(stderr, "Usage: %s [-d <path>] \n", argv[0]);
    //     break;
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
  // sh_destroy(sh);

  // char *line;
  // using_history();
  // while ((line=readline("$")) || exitflag != 1){
  //   printf("%s\n",line);
  //   add_history(line);
  //   free(line);
  // }
  // exitcmd(exitflag);

  return 0;
}



// #include <stdio.h>

// int main(void)
// {
//   printf("hello world\n");
//   return 0;
// }