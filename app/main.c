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

int main(int argc, char **argv)
{

  int opt;

  /* Use getopt() to process command line arguments */
  while ((opt = getopt(argc, argv, "pvczh")) != -1)
  {
    switch (opt)
    {
    case 'p':
      printf("Get prompt variable: %s\n", get_prompt("MY_PROMPT"));
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
  return 0;
}



// #include <stdio.h>

// int main(void)
// {
//   printf("hello world\n");
//   return 0;
// }