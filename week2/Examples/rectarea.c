#include <stdio.h>

int main(){
    float length;
    float width;

    printf("Input rect length: ");
    scanf("%f", &length);

    printf("Input rect width: ");
    scanf("%f", &width);

    printf("Your rectangles area is: %f \n", width * length);

    return 0;
}
