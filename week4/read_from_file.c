#include <stdio.h>

int main()
{
    char filename[] = "data.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("");
        return 1;
    }
    int buffer_size = 100;
    char line_buffer[buffer_size];
    
    fclose(file);
    return 0;
}