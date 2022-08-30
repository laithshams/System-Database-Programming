#include<stdio.h>
int main() {

    char a [20];
    scanf("%c", &a);
    printf("%i", aChar(a));

    return 0;
}

int aChar(char a []) {
    int count = 0;
    for (int i = 0; i < 20; i++) {
        if(a[i] == 'a') {
            count++;
        }
    }
    return count;
}