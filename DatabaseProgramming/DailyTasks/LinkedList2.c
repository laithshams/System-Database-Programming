#include<stdio.h>

struct node {
    int value;
    struct node *next;
    struct node *pre;
};

int main() {

    struct node n1;
    printf("value: ");
    scanf("%i", &n1.value);

    struct node n2;
    printf("value: ");
    scanf("%i", &n2.value);

    struct node n3;
    printf("value: ");
    scanf("%i", &n3.value);

    struct node n4;
    printf("value: ");
    scanf("%i", &n4.value);

    struct node n5;
    printf("value: ");
    scanf("%i", &n5.value);

    n1.next = &n2;

    n2.next = &n3;
    n2.pre = &n1;

    n3.next = &n4;
    n3.pre = &n2;

    n4.next = &n5;
    n4.pre = &n3;

    n5.pre = &n4;

    struct node search = n1;

    int value;
    printf("search value: ");
    scanf("%i", &value);

    for(int i = 0; i < 5; i++) {
        if(search.value == value){
            printf("index: %i", i + 1);
            break;
        } else if(i == 4) {
           printf("not found"); 
           break;
        }
        search = *search.next;
    }
    return 0;
}