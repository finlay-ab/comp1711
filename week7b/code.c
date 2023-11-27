#include "utilities.h"

int main()
{
    //get file yes
    //count lines yes
    //create stuct
    //input data to struct
    //check data of struct is correct



    

    char line[buffer_size];
    char filename[buffer_size];

    // get filename from the user
    printf("Please enter the name of the data file: ");

    // these lines read in a line from the stdin (where the user types)
    // and then takes the actual string out of it
    // this removes any spaces or newlines.
    fgets(line, buffer_size, stdin);
    sscanf(line, " %s ", filename);

    FILE *input = open_file(filename, "r");

    int numberofreadings = count_data(input);

    // array of daily readings
    reading daily_readings[numberofreadings];

    

    char choice;
    int counter = 0;
    float mean = 0;

    while (1)
    {
        FILE *input = fopen(filename, "r");
        if (!input)
        {
            printf("Error: File could not be opened\n");
            return 1;
        }

        printf("A: View all your blood iron levels\n");                       // BRONZE
        printf("B: View your average blood iron level\n");                    // BRONZE
        printf("C: View your lowest blood iron level\n");                     // SILVER
        printf("D: View your highest blood iron level\n");                    // SILVER
        printf("E: View the blood iron levels for a specific month\n");       // SILVER/GOLD
        printf("F: See some additional statistics about your iron levels\n"); // GOLD - see readme.md
        printf("G: Generate a graph of your iron levels\n");                  // GOLD/PLATINUM - see readme.md
        printf("Q: Exit the program\n");

        // get the next character typed in and store in the 'choice'
        choice = getchar();

        // this gets rid of the newline character which the user will enter
        // as otherwise this will stay in the stdin and be read next time
        while (getchar() != '\n');


        // switch statement to control the menu.
        switch (choice)
        {
        // this allows for either capital or lower case
        case 'A':
        case 'a':
            counter = 0;
            while (fgets(line, buffer_size, input))
            {
                // split up the line and store it in the right place
                // using the & operator to pass in a pointer to the bloodIron so it stores it
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);
                counter++;
            }
            for (int i = 0; i < counter; i++)
            {
                printf("%s - Blood iron: %.1f\n", daily_readings[i].date, daily_readings[i].bloodIron);
            }
            fclose(input);
            break;

        case 'B':
        case 'b':
            counter = 0;
            while (fgets(line, buffer_size, input))
            {
                // split up the line and store it in the right place
                // using the & operator to pass in a pointer to the bloodIron so it stores it
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);
                mean += daily_readings[counter].bloodIron;
                counter++;
            }
            mean /= counter;
            printf("Your average blood iron was %.2f\n", mean);
            fclose(input);
            break;

        case 'C':
        case 'c': //return lowest value
            counter = 0;
            int lowest = 999999;
            int lowest_index = 0;

            while (fgets(line, buffer_size, input))
            {
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);               
                if (daily_readings[counter].bloodIron < lowest)
                {
                    lowest = daily_readings[counter].bloodIron;
                    lowest_index = counter;
                }
                counter++;
            }

            printf("Fewest steps: %s %f\n", daily_readings[lowest_index].date, daily_readings[lowest_index].bloodIron); 
            break;

        case 'D':
        case 'd':// return highest value
            counter = 0;
            int largest = -1;
            int largeset_index = 0;

            while (fgets(line, buffer_size, input))
            {
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);               
                if (daily_readings[counter].bloodIron > largest)
                {
                    largest = daily_readings[counter].bloodIron;
                    largeset_index = counter;
                }
                counter++;
            }

            printf("Largest steps: %s %f\n", daily_readings[largeset_index].date, daily_readings[largeset_index].bloodIron); 
            break;

        case 'E':
        case 'e': 
            return 0;
            break;

        case 'F':
        case 'f': //longest period of greater then 500
            counter = 0;
            while (fgets(line, buffer_size, input))
            {
                // split up the line and store it in the right place
                // using the & operator to pass in a pointer to the bloodIron so it stores it
                tokeniseRecord(line, ",", daily_readings[counter].date, &daily_readings[counter].bloodIron);
                counter++;
            }

            counter = 0;
            int largestRunLength = 0;
            int currentRunLength = 0;
            int largestRunStartIndex = -1;
            int currentRunStartIndex = -1;

            while( counter < 100) //create counter for size of array
                if (daily_readings[counter].bloodIron > 500)
                {
                    currentRunLength ++;
                    if (currentRunLength == 1)
                    {
                        currentRunStartIndex = counter;
                    }
                }else{
                    if (currentRunLength > largestRunLength)
                    {
                        largestRunLength = currentRunLength;
                        largestRunStartIndex = currentRunStartIndex;
                    }
                    currentRunLength = 0;
                }

            printf("Longest period start: %s", daily_readings[largestRunStartIndex].date);
            printf("Longest period end: %s", daily_readings[largestRunStartIndex + largestRunLength].date);

            if (largestRunStartIndex == -1)
            {
                printf("no values found above 500"); //might not need
            }               

            break;

        case 'G': 
        case 'g':
            return 0;
            break;

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