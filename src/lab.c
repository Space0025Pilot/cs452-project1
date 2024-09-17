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

char *get_prompt(const char *env){
    if(getenv(env) != NULL){
        printf("Inside not null");
        setenv(env, "foo>", 1);
        free(getenv(env));
        return getenv(env);   //Note here that we need to free the resulting string from getenv as it calls malloc internally.
    }
    if (getenv(env) == NULL){
        printf("Inside else");
        setenv(env, "shell>", 1);
        return getenv(env);
    }
    
    
}

void sh_init(struct shell *sh){

    /* Allocate space for shell struct in heap and validate */
    sh = (struct shell *)malloc(sizeof(struct shell));
    // if(sh == NULL){
    //     return NULL;
    // }

    /* Initialize the sh with the initial values */
    sh->shell_is_interactive = 1;
    sh->shell_pgid = 0;
    // struct termios *tm = malloc(sizeof(struct termios));   //Not sure this is a struct so do I allocate the memory for this.
    // sh->shell_tmodes = expression;
    sh->shell_terminal = 1;
    sh->prompt = "";
}

void sh_destroy(struct shell *sh){

    /* Validate Parameter */
    if(sh == NULL){
        return;
    }

    // free(sh->shell_tmodes); //Again not sure how to do this

    free(sh);
}




