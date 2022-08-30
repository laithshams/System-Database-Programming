#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct element {
    int value;
    struct element *leftelement;
    struct element *rightelement;
}*root;
void search(int value) {
    // you should implement the search function
    struct element *currPos = root;
    struct element *parent = root;
    char path[100] = "";
    printf("the search has started... searching value: %i\n", value);
    while(currPos){
        printf("current position: %i ... ", currPos->value);
        if(currPos->value == value){
            printf("found it");
            return;
        } else if(currPos->value > value) {
            currPos = currPos->leftelement;
            printf("going left\n");
        } else {
            currPos = currPos->rightelement;
            printf("going right\n");
        }
    }
    printf("invalid value...\n");
}
void insert(int value) {
    struct element *tempelement = (struct element*) malloc(sizeof(struct element));
    struct element *currPos;
    struct element *parent;
    // you should implement the rest of the insert function
    if(!root) {
        root = tempelement;
        root->value = value;
        return;
    }
    currPos = root;
    while(1){
        if(currPos->value > value) {
            if(!(currPos->leftelement)){
                currPos->leftelement = (struct element*) malloc(sizeof(struct element));
                currPos = currPos->leftelement;
                break;
            }
            currPos = currPos->leftelement;
        } else {
            parent = currPos;
            if(!(currPos->rightelement)){
                parent->rightelement = (struct element*) malloc(sizeof(struct element));
                currPos = currPos->rightelement;
                break;
            }
            currPos = currPos->rightelement;
        }
    }
    currPos->value = value;
}
int main() {
    insert(50);
    insert(30);
    insert(20);
    insert(40);
    insert(70);
    insert(60);
    insert(80);
    search(80);
    return 0;
}