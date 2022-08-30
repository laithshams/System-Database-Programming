#include<stdio.h>

struct node {
    int value;
    struct node *next;
};

int main() {

    int length;
    printf("length: ");
    scanf("%i", &length);

    struct node linkedlist [length];
    printf("first value: ");
    scanf("%i", &linkedlist[0].value);

    for(int i = 1; i < length; i++) {
        linkedlist[i].value = linkedlist[i - 1].value + 1;
        linkedlist[i - 1].next = &linkedlist[i];
    }

    struct node *po = &linkedlist[0];
    for(int i = 0; i < length; i++){
        printf("%i ", *po);
        po = (po + 1);
    }
    return 0;
}