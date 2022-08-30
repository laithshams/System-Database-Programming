#include<stdio.h>
int main() {

    int five [10];

    for( int i=0; i<10; i++) {
        scanf("%i", &five[i]);
    }
    for(int i = 0; i<10; i++) {
        if (five[i] == 5) {
            printf("%i", i);
        }
    }

    return 0;
}