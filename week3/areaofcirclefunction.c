#include <stdio.h>

float areaOfCircle(float radius)
{
    return radius*radius*3.14159;
}

int main(){
    float radius = 10.0;

    printf("Enter the radius of your circle");
    scanf("%f", &radius);

    printf("The area of your circle is: %f", areaOfCircle(radius));
}