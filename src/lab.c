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

uid_t userid;
struct passwd *pw; //pointer to the struct
char * home;
char **homepointer;

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
    /*Return pointer for the return value and string */
    char ** returnPointer;
    char * stringLine = "";

    /* Allocation and Instantiation of new array of arguments or argv */
    char * stringarray = (char *)malloc(sizeof(char) * _SC_ARG_MAX);

    /* Copy the incoming line to another stringLine that is muttable */
    stringLine = strcpy(stringLine, line);

    /* Tokenizing the arguments to put into the array */
    char * partofstring = strtok(stringLine, " ");

    /* Copy each piece of the tokenized array into our newly allocated array */
    int posCounter = 0;  //also argc
    while(partofstring[posCounter] != NULL || posCounter < _SC_ARG_MAX){
        stringarray[posCounter] = partofstring[posCounter];
        posCounter++;
        // printf("Token %s\n", partofstring);
    }
    returnPointer = &stringarray;
    return returnPointer;
}

void cmd_free(char ** line){
    free(*line);
    line = NULL;
}

// char *trim_white(char *line);

bool do_builtin(struct shell *sh, char **argv){
    
    /* If statements to take care of command line arguments */
    bool returnvalue = false;
    char const * arg0 = argv[0];
    char const * arg1 = argv[1];
    /* Exit and Crtl-D Scenarios */ 
    if((strcmp(arg0, "exit") == 0) || (arg0) == NULL){
        returnvalue = true;
        free(*argv);
        free(**argv);
        free(sh);
        exit(0);
    }

    /* Change directory */
    if(strcmp(arg0, "cd") == 0){
        change_dir(argv[1]);
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
    sh->prompt = "";
}

void sh_destroy(struct shell *sh){
    /* Destroy the shell struct */
    free(sh);
}

void parse_args(int argc, char **argv);




