#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void allocate_two_strings(char **v, char **w){
    char x[] = "Hello world!";
    char y[] = "HELLO WORLD!";

    *v = malloc(13*sizeof(char));
    //*w = malloc(13*sizeof(char));

    *w = *v;

    strcpy(*v,x);
    strcpy(*w,y);
}


//copy second argument to first argument
//then free second argument
void move(char *d, char *s) {
    strcpy(d,s);
    free(s);
}

int main() {
    char *a, *b;
    allocate_two_strings(&a,&b);

    //copy second argument to first argument
    //then free second argument
    move(b,a);

    printf(b);

    //better remember to free b
    //now I'm done with it
    free(b);

    return 0;
}
