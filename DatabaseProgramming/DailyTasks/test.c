#include<stdio.h>

struct node {
    int value;
    struct node *next;
};

int main() {

    struct node linkedlist, test;
    linkedlist.value = 1;
    test.value = 2;

    *linkedlist.next = struct node;
    *linkedlist.next = 3;

    printf("%i", *(linkedlist.next));
    return 0;
}