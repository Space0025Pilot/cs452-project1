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
#include <pwd.h>
#include "lab.h"
#include "../tests/harness/unity.h"

#define MAX_CHARACTER_LENGTH 10
#define MAX_SIZE 4096

uid_t userid;
struct passwd *pw; //pointer to the struct
char * home;
char **homepointer;
int argCounter = 0;

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

    /* If directory is null, get home director and change to it */
    if(*dir == NULL){
        userid = getuid();
        pw = getpwuid(userid);
        if(pw == NULL){
            perror("user is not valid (pwuid is NULL)");
            return -1;
        }
        retvalue = chdir(pw->pw_dir);
        if(retvalue == 0){
            return retvalue;
        }
        else {
            return retvalue;
        }
    }

    /* If directory is not null, then changes to specified directory */
    retvalue = chdir(*(dir));
    return retvalue;
}

char **cmd_parse(char const *line){
    
    //Variables
    argCounter = 0;
    char * copyOfLine = "";
    char ** args = (char **)malloc(sizeof(char*) * MAX_SIZE);  //leak here, never freed

    //Check that there is enough space to allocate the memory.
    if(args == NULL){
        perror("Couldn't allocate space");
        exit(-1);
    }

    //Copy of Line
    copyOfLine = strdup(line);             //leak here, never freed
    // printf("copyOfLine: %s\n", copyOfLine);      //Print line remove later

    //Parse copyofLine for 1st command
    args[argCounter] = strtok(copyOfLine, " ");
    // printf("args[0]: %s\n", args[argCounter]);   //Print line remove later

    // if(args == NULL){
    //     cmd_free(args);
    //     free(copyOfLine);
    //     exit(0);
    // }

    while(args[argCounter] != NULL && argCounter < MAX_SIZE - 1){
        argCounter++;
        args[argCounter] = strtok(NULL, " ");
        // printf("args[%d]: %s\n", argCounter, args[argCounter]);   //Print line remove later
    }

    argCounter = 0;

    // args[argCounter] = NULL;
    // free(copyOfLine);
    
    return args;

}

void cmd_free(char ** line){

    // for(int i = 0; i < argCounter; i++){
    //     free(line[i]);
    // }
    // free(line);
    free(*(&line));
    line = NULL;
}

// char *trim_white(char *line);

bool do_builtin(struct shell *sh, char **argv){
    
    /* If statements to take care of command line arguments */
    bool returnvalue = false;

    char const * arg0 = argv[0];
    // char const * arg1 = argv[1];
    char ** argv1pointer = &argv[1];

    /* Exit and Crtl-D Scenarios */ 
    if((strcmp(arg0, "exit") == 0) || (arg0 == NULL)){
        returnvalue = true;
        if(argv != NULL){
            for(int i = 0; argv[i] != NULL; i++){
                free(argv[i]);
            }
        }
        cmd_free(argv);
        free(sh);
        exit(0);
    }

    /* Change directory */
    if(strcmp(arg0, "cd") == 0){
        change_dir(argv1pointer);
        returnvalue = true;
    }
    return returnvalue;
}

void sh_init(struct shell *sh){

    /* Allocate the space for the shell and initialize */
    sh = (struct shell *)malloc(sizeof(struct shell));

    /* Initialize the sh with the initial values */
    sh->shell_is_interactive = 1;
    sh->shell_pgid = 0;  //grab from the OS
    sh->shell_tmodes.c_iflag = 1; //Maybe set all flags to off
    sh->shell_terminal = 1;
    sh->prompt = NULL;
}

void sh_destroy(struct shell *sh){
    /* Destroy the shell struct */
    free(sh);
}

void parse_args(int argc, char **argv);




