#include<stdio.h>

struct WordDef {
    char word [15];
    char def [50];
};

struct WordDef dic[5];

fillDic() {
    for(int i = 1; i < 6; i++){
        printf("enter %i word: ", i);
        gets(dic[i - 1].word);

        printf("enter %i def: ", i);
        gets(dic[i - 1].def);
    }
}

int lookUp(char search[]) {

    for(int i = 0; i < 5; i++) {
        if(equalStrings(search, dic[i].word) == 1) {
            return i;
        }
    }

    return -1;
}

int equalStrings(char search[], char word[]) {

    int bool = 1;
    if(strlen(search) != strlen(word)) {
        bool = 0;
        return bool;
    }
    for (int i = 0; i < strlen(search); i++) {
        if(search[i] == word[i]) {
            continue;
        } else {
            bool = 0;
            break;
        }
    }

    return bool;
}

int main() {

    int word;
    char look[15];
    fillDic();

    printf("search: ");
    gets(look);
    word = lookUp(look);

    if(word != -1) {
        printf("def: %s", dic[word].def);
    } else {
        printf("word %s isn't available in the dic", look);
    }

return 0;
}