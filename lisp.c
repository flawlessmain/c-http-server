#include <stdio.h>
#define TRUE 1

static char input[2048];

int main(int argc, char** argv){
    puts("My own Lisp version 0.0.1");
    puts("Press ctrl+c to exit.");

    while (TRUE) {
        fputs("lisp> ", stdout);
        fgets(input, 2048, stdin);
        printf("No, you are a %s", input);
    }
    return 0;
}