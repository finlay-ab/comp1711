#include <stdio.h>

int main()
{
    // setting up 15 slots of memory for a string
    char name[15];

    // promts the user
    printf("Hello, please enter your name: ");

    // takes the users input and stores it into name
    scanf("%s", name);

    // prints out the users name
    printf("Your name is %s \n", name);

    return 0;
}