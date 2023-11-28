
#ifndef FITNESS_DATA_STRUCT_H
#define FITNESS_DATA_STRUCT_H

#include <stdio.h>

// Define an appropriate struct
typedef struct
{
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Defineing variables
int buffer_size = 100;

// Helper function prototypes
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps);

#endif // FITNESS_DATA_STRUCT_H

/**
 * @brief Opens the file in the correct mode
 *
 * @param filename the name of the file to open
 * @param mode the mode (r/w/a/r+/w+/a+)
 * @return FILE* The file object to store the opened file in.
 */
FILE *open_file(char *filename, char *mode)
{
	char line[buffer_size];

	FILE *input = fopen(filename, mode);
	if (!input)
	{
		if (filename == NULL)
		{
			printf("Incorrectly named data file\n");
		}
		else
		{
			printf("Error: Could not find or open the file.\n");
		}

		exit(1);
	}

	printf("File successfully loaded.\n");
	return input;
}

// returns the amount of data the file is giving
int count_data(FILE *inputFile)
{
	int counter = 0;
	int buffer_size = 100;
	char line_buffer[buffer_size];
	while (fgets(line_buffer, buffer_size, inputFile) != NULL)
	{
		counter++;
	}

	fseek(inputFile, 0, SEEK_SET);
	return counter;
}

/**
 * @brief Checks that there was data for each part of each reading in the file
 *
 * @param dataArray The array of data from the file
 * @param numReadings The number of readings in the array
 * @return int Return 0 if there are no errors, 1 if you find an error.
 */
int data_checker(FITNESS_DATA *dataArray, int numReadings)
{
	for (int index = 0; index <= numReadings; index++)
	{
		if (dataArray[index].date == NULL || dataArray[index].steps < 0 || dataArray[index].steps > 1000 || dataArray[index].time == NULL)
		{
			return 1;
		}
	}
	return 0;
}

// inputs data into data array
void input_data(FILE *file, int amount_of_data, FITNESS_DATA *data)
{
	int index = 0;
    int buffer_size = 100;
    char line_buffer[buffer_size];
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        index ++;
        char temp[6];
        tokeniseRecord(line_buffer,",",data[index].date,data[index].time,temp);
        data[index].steps = atoi(temp); 
    }
	fseek(file, 0, SEEK_SET);
}