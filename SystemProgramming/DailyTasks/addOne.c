#include<stdio.h>
int main() {

    int nums [10];

    for(int i = 0; i < 10; i++) {
        scanf("%i", &nums[i]);
    }

    addOne(&nums);

    for(int i = 0; i < 10; i++) {
        printf("%i ", nums[i]);
    }

    return 0;
}

addOne(int* num) {
    for (int i = 0; i < 10; i++) {
        *(num+i)+=1;
    }
}