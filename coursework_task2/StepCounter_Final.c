#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps)
{
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);

    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL)
    {
        strcpy(date, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strcpy(time, token);
    }

    token = strtok(NULL, delimiter);
    if (token != NULL)
    {
        strcpy(steps, token);
    }

    // Free the duplicated string
    free(inputCopy);
}

// Complete the main function
int main()
{
    char choice;
    char line[buffer_size];
    char filename[buffer_size];
    FITNESS_DATA data[1024];
    int amount_of_data = 0;

    int counter;
    int lowest;
    int lowest_index;
    int largest;
    int largest_index;
    int total;
    int longest_period;
    int index_of_longest_period;
    int current_period;
    int index_of_current_period;

    while (1)
    {
        printf("Menu Options:\n");
        printf("A: Specify the filename to be imported\n");
        printf("B: Display the total number of records in the file\n");
        printf("C: Find the date and time of the timeslot with the fewest steps\n");
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");
        printf("E: Find the mean step count of all the records in the file\n");
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");
        printf("Q: Quit\n");
        printf("Enter choice: ");

        // get the next character typed in and store in the 'choice'
        choice = getchar();

        // this gets rid of the newline character which the user will enter
        // as otherwise this will stay in the stdin and be read next time
        while (getchar() != '\n')
            ;

        switch (choice)
        {
        // this allows for either capital or lower case
        // get file input
        case 'A':
        case 'a':
            // get filename from the user
            printf("Input filename: ");

            // these lines read in a line from the stdin (where the user types)
            // and then takes the actual string out of it
            // this removes any spaces or newlines.
            fgets(line, buffer_size, stdin);
            sscanf(line, " %s ", filename);

            FILE *file = open_file(filename, "r");

            if (file == NULL)
            {
                return 1;
            }

            amount_of_data = count_data(file);
            input_data(file, amount_of_data, data);
            fclose(file);

            break;
        // total records
        case 'B':
        case 'b':
            printf("Total records: %d\n", amount_of_data);
            break;
        // fewest steps
        case 'C':
        case 'c':

            lowest = 999999;
            lowest_index = 0;
            counter = 1;
            while (counter <= amount_of_data)
            {

                if (data[counter].steps < lowest)
                {
                    lowest = data[counter].steps;
                    lowest_index = counter;
                    printf("data %d: %d\n", counter, data[counter].steps);
                }
                counter++;
            }
            // Fewest steps: 2023-09-01 22:00

            printf("Fewest steps: %s %s\n", data[lowest_index].date, data[lowest_index].time);
            break;
        // largest steps
        case 'D':
        case 'd':
            largest = -1;
            largest_index = 0;
            counter = 1;
            printf("amount of data: %d\n", amount_of_data);
            while (counter <= amount_of_data)
            {

                if (data[counter].steps > largest)
                {
                    largest = data[counter].steps;
                    largest_index = counter;
                    printf("data %d: %d\n", counter, data[counter].steps);
                }
                counter++;
            }
            // Fewest steps: 2023-09-01 22:00

            printf("Largest steps: %s %s\n", data[largest_index].date, data[largest_index].time);
            break;
        // mean steps
        case 'E':
        case 'e':

            counter = 1;
            while (counter <= amount_of_data)
            {
                total += round(data[counter].steps);
                counter++;
            }
            printf("Mean step count: %d\n", total / amount_of_data);
            break;
        // longest period
        case 'F':
        case 'f':
            longest_period = -1;
            index_of_longest_period = -1;
            current_period = 0;
            index_of_current_period = -1;

            counter = 0;

            while (counter <= amount_of_data)
            {
                if (data[counter].steps > 500)
                {
                    if (current_period == 0)
                    {
                        index_of_current_period = counter;
                    }
                    current_period++;
                }
                else
                {
                    if (current_period > longest_period)
                    {
                        longest_period = current_period;
                        index_of_longest_period = index_of_current_period;
                    }
                    current_period = 0;
                }
                counter++;
            }

            printf("Longest period start: %s %s\n", data[index_of_longest_period].date, data[index_of_longest_period].time);
            printf("Longest period end: %s %s\n", data[index_of_longest_period + longest_period].date, data[index_of_longest_period + longest_period].time);

            break;
        // quit
        case 'Q':
        case 'q':
            return 0;
            break;
        // if they type anything else:
        default:
            printf("Invalid choice\n");
            break;
        }
    }
}
