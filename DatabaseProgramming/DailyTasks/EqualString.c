#include<stdio.h>

int main() {

    char str1 [10];
    char str2 [10];

    printf("1st string: ");
    scanf("%s", &str1);

    printf("2nd string: ");
    scanf("%s", &str2);

    printf("they're %i", equalStrings(str1, str2));

    return 0;
}

int equalStrings(char str1[], char str2[]) {

    int bool = 1;
    if(strlen(str1) != strlen(str2)) {
        bool = 0;
        return bool;
    }
    for (int i = 0; i < strlen(str1); i++) {
        if(str1[i] == str2[i]) {
            printf("2 %c and %c ", str1[i], str2[i]);
            continue;
        } else {
            bool = 0;
            break;
        }
    }

    return bool;
}