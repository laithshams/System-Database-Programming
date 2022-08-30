#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main() {
    char* mem;
    mem = malloc(20* sizeof(char));
    if(mem== NULL)
        printf(" Could not able to allocate memory \n");
    else {
        strcpy(mem,"Database Programming");
        printf( "dynamically memory allocated content is %s\n", mem);
    }
    mem = realloc(mem, 38* sizeof(char));
    if(mem== NULL)
        printf(" Could not able to allocate memory \n");
    else {
        strcat(mem, "Buffer Management");
        printf("%s", mem);
    }
    free(mem);
}