/**File: lab.c
 * Author: Caitlyn Nelson
 * Date: 9/16/2024
 * Description: Definition of support functions used in main.c
 **/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include "lab.h"
#include "../tests/harness/unity.h"

#define MAX_CHARACTER_LENGTH 10

char *get_prompt(const char *env){
    if(getenv(env) != NULL){
        // printf("Inside not null\n");
        char * environmentvariable = (char *)malloc(sizeof(char) * MAX_CHARACTER_LENGTH);
        environmentvariable = strcpy(environmentvariable, getenv(env));
        return environmentvariable;
        free(environmentvariable);
    }
    else{
    // if (getenv(env) == NULL){
        // printf("Inside else\n");
        char * promptarray = (char *)malloc(sizeof(char) * MAX_CHARACTER_LENGTH);
        promptarray[0] = 's';
        promptarray[1] = 'h';
        promptarray[2] = 'e';
        promptarray[3] = 'l';
        promptarray[4] = 'l';
        promptarray[5] = '>';
        promptarray[6] = '\0';
        return promptarray;
        free(promptarray);
    }
}

int change_dir(char **dir){
    int retvalue;
    retvalue = chdir(*(dir));
    return retvalue;
}

// char **cmd_parse(char const *line);

// void cmd_free(char ** line);

// char *trim_white(char *line);

// bool do_builtin(struct shell *sh, char **argv);

void sh_init(struct shell *sh){

    /* Initialize the sh with the initial values */
    sh->shell_is_interactive = 1;
    sh->shell_pgid = 0;  //grab from the OS
    // struct termios *tm = malloc(sizeof(struct termios));   //Not sure this is a struct so do I allocate the memory for this.
    sh->shell_tmodes.c_iflag = 1;
    sh->shell_terminal = 1;
    sh->prompt = "";
}

void sh_destroy(struct shell *sh){

    /* Validate Parameter */
    // if(sh == NULL){
    //     return;
    // }

    // free(sh->shell_tmodes); //Again not sure how to do this

    free(sh);
}

void parse_args(int argc, char **argv);




