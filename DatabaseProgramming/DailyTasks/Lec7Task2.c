#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main() {
    int student;
    int *marks;
    int max = 0;
    int min;
    int sum = 0;
    int avg = 0;

    printf("student number: ");
    scanf("%d", &student);

    marks = calloc(student, sizeof(int));
    if(marks== NULL)
        printf(" Could not able to allocate memory \n");
    else {
        for(int i = 0; i < student; i++){
            printf("student %d:", (i+1));
            scanf("%d", &marks[i]);
        }
        min = marks[0];
        for(int i = 0; i < student; i++){
            if(marks[i] > max) {
                max = marks[i];
            } else if(marks[i] < min){
                min = marks[i];
            }
            sum+=marks[i];
        }
        avg = sum / student;
        printf("max = %d\n", max);
        printf("min = %d\n", min);
        printf("sum = %d\n", sum);
        printf("avg = %d\n", avg);
    }

    free(marks);
}