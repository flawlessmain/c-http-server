#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

#define TRUE 1

int main(int argc, char** argv){
    puts("My own Lisp version 0.0.1");
    puts("Press ctrl+c to exit.");

    while (TRUE) {
        char *input = readline("lisp> ");
        add_history(input);
        printf("%s\n", input);
        free(input);
    }
    return 0;
}