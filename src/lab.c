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
#include <ctype.h>
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
    // printf("Directory coming in: %s\n", *(*&dir));
    // char const * arg1 = dir[1];
    // printf("Second Argument: %s\n", arg1);

    int retvalue;
    // char cwd[1024];

    //IF directory is null and Home is not null, change to the home directory
    if(dir[1] == NULL && getenv("HOME") != NULL){
        // printf("Inside only cd command, home directory %s\n", getenv("HOME")); //Take these out later
        retvalue = chdir(getenv("HOME"));
        // printf("retvalue %d\n", retvalue);                                     //Take these out later
        // getcwd(cwd, sizeof(cwd));                                              //Take these out later
        // printf("Current working dir cd only: %s\n", cwd);                      //Take these out later
        return retvalue;
    }

    /* If directory is null, and get home directory is null, then find the home directory of the user and change to it */
    if(dir[1] == NULL && getenv("HOME") == NULL){
        userid = getuid();
        pw = getpwuid(userid);
        if(pw == NULL){
            perror("user is not valid (pwuid is NULL)");
            return -1;
        }
        retvalue = chdir(pw->pw_dir);
        // getcwd(cwd, sizeof(cwd));                                          //Take these out later
        // printf("Current working dir: %s\n", cwd);                          //Take these out later
        if(retvalue == 0){
            return retvalue;
        }
        else {
            return retvalue;
        }
    }

    /* If directory is not null, then changes to specified directory */
    if(dir[1] != NULL && getenv("HOME") != NULL){
        // printf("Directory not null\n");                                  //Take these out later
        retvalue = chdir(dir[1]);
        // getcwd(cwd, sizeof(cwd));
        // printf("Current working dir - directory not null: %s\n", cwd);   //Take these out later
        // printf("retvalue: %d\n", retvalue);                              //Take these out later
    }
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

    while(args[argCounter] != NULL && argCounter < MAX_SIZE - 1){
        argCounter++;
        args[argCounter] = strtok(NULL, " ");
        // printf("args[%d]: %s\n", argCounter, args[argCounter]);   //Print line remove later
    }

    argCounter = 0;
    
    return args;

}

void cmd_free(char ** line){

    free(*(&line));
    line = NULL;
}

char *trim_white(char *line){

    size_t i = 0;
    size_t j = 0;

    
    // Remove leading spaces
    for (i = 0; isspace(line[i]); i++);

    // Shift all characters to the left
    for (j = 0; line[i] != '\0'; i++, j++) {
        line[j] = line[i];
    }
    line[j] = '\0';

    // Remove trailing spaces
    for (i = strlen(line) - 1; i >= 0 && isspace(line[i]); i--) {   //heap buffer overflow - handle only spaces case
        line[i] = '\0';
    }

   return line;
}

bool do_builtin(struct shell *sh, char **argv){
    
    /* If statements to take care of command line arguments */
    bool returnvalue = false;

    char const * arg0 = argv[0];
    // printf("arg0: %s\n", arg0);                        //Take these out later
    // char const * arg1 = argv[1];                       //Take these out later
    // printf("arg1: %s\n", arg1);                        //Take these out later
    // char ** argv1pointer = &argv[1];                   //Take these out later
    char cwd[1024];
    

    /* Exit and Crtl-D Scenarios */ 
    if((strcmp(arg0, "exit") == 0) || (arg0 == NULL)){
        // printf("inside exit\n");                      //Take these out later
        returnvalue = true;
        if(argv != NULL){
            // printf("free arguments\n");                  //Take these out later
            for(int i = 0; argv[i] != NULL; i++){
                free(argv[i]);
            }
        }
        cmd_free(argv);
        sh_destroy(sh);
        exit(0);
    }

    /* Change directory */
    if(strcmp(arg0, "cd") == 0){
        change_dir(argv);
        returnvalue = true;
    }
    /* Print working directory */
    if(strcmp(arg0, "pwd") == 0){
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
        // printf("Path of current Working directory: %s\n", getenv("PATH"));
        returnvalue = true;
    }
    return returnvalue;
}

void sh_init(struct shell *sh){

    /* Initialize the sh with the initial values */
    sh->shell_is_interactive = 1;
    sh->shell_pgid = 0;  //grab from the OS
    sh->shell_tmodes.c_iflag = 1; //Maybe set all flags to off
    sh->shell_terminal = 1;
    sh->prompt = NULL;
}

void sh_destroy(struct shell *sh){
    /* Destroy the shell struct */
    free(sh->prompt);
    free(sh);
}

void parse_args(int argc, char **argv);




