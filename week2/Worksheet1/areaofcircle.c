#include <stdio.h>

int main(){
    float radius;

    printf("Input a radius of a circle: ");
    scanf("%f", &radius);

    printf("the area of your circle is: %f \n", 3.14159*radius*radius );

    return 0;
}