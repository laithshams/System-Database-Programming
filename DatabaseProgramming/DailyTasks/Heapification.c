#include<stdio.h>


int main(){
    int size = 6;
    int arr[size];
    arr[0] = 5;
    arr[1] = 6;
    arr[2] = 3;
    arr[3] = 12;
    arr[4] = 9;
    arr[5] = 15;

    showArray(arr, size);
    callHeap(arr, size);
    showArray(arr, size);
}

void showArray(int arr[], int size){
    for(int i = 0; i < size; i++){
        printf("%i ", arr[i]);
    }
}

void callHeap(int arr[], int size){
    for(int i = size/2-1; i>=0; i--){
        heapfunc(arr, size, i);
    }
    for(int i = size-1; i<=0; i--){
        switchVals(&arr[0], &arr[i]);
        heapfunc(arr, size, 0);
    }
}
void switchVals(int *i1, int *i2){
        int temp = *i1;
        *i1 = *i2;
        *i2 = temp;
}

void heapfunc(int arr[], int size, int currPos){
    int currTesting = currPos;
    int LC = currPos * 2 + 1;
    int RC = currPos * 2 + 2;

    if(arr[currTesting] < arr[LC]){
        currTesting = LC;
    }
    if(arr[currTesting] < arr[RC]){
        currTesting = RC;
    }
    if(currPos != currTesting){
        switchVals(&arr[currPos], &arr[currTesting]);
        heapfunc(arr, size, currTesting);
    }
}