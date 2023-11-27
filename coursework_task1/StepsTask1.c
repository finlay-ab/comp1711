#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here


// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
int main() {

    FITNESS_DATA bean ;
    char steps[3];

    tokeniseRecord("2023-09-01,07:30,300", ",",bean.date,bean.time,steps);

    //count number of lines in file

    //read each line and store data

    //"Number of records in file: 234"

    //2023-09-01/08:15/150

    char filename [] = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("");
        return 1;
    }

    int counter = 0;
    int buffer_size = 100;
    char line_buffer[buffer_size];
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        counter ++;
    }

    fclose(file);
    printf("Number of records in file: %d\n", counter);

    FITNESS_DATA data[counter];

    char filename_ [] = "FitnessData_2023.csv";
    FILE *file_ = fopen(filename_, "r");
    if (file_ == NULL) {
        perror("");
        return 1;
    }

    int index_ = 0;
    int buffer_size_ = 100;
    char line_buffer_[buffer_size_];
    while (fgets(line_buffer_, buffer_size_, file_) != NULL) {
        index_ ++;
        char temp[5];
        tokeniseRecord(line_buffer_,",",data[index_].date,data[index_].time,temp);
        data[index_].steps = atoi(temp); 
    }

    fclose(file);

    for (int i = 1; i<4; i++)
    {
            //2023-09-01/08:15/150
        printf("%s/%s/%d\n",data[i].date,data[i].time,data[i].steps);
    }

    return 0;
}