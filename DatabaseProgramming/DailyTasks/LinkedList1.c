#include<stdio.h>

struct node {
    int value;
    struct node *next;
    struct node *pre;
};

int main() {

    struct node n1;
    scanf("%i", &n1.value);

    struct node n2;
    scanf("%i", &n2.value);

    struct node n3;
    scanf("%i", &n3.value);

    struct node n4;
    scanf("%i", &n4.value);

    struct node n5;
    scanf("%i", &n5.value);

    n1.next = &n2;

    n2.next = &n3;
    n2.pre = &n1;

    n3.next = &n4;
    n3.pre = &n2;

    n4.next = &n5;
    n4.pre = &n3;

    n5.pre = &n4;

    int val3 = n3.value;
    int val4 = n3.next->value;
    int val2 = n3.pre->value;

    printf("%i ", val3);
    printf("%i ", val4);
    printf("%i ", val2);
    return 0;
}