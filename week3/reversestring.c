#include <stdio.h>

int main(){
    char word[] = "Hello";

    for(int i = 4; i >= 0; i--)
    {
        printf("%c", word[i]);
    }
}