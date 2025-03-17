#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "../source/csv.h"

//Name: Jean Michel Mugabe.

// Function handles reading record from a csv file
record_t read_csv_record(FILE **csvfile) {
    // initialize variables and elements of the struct record_t.
    record_t r1;
    char ch;
    r1.num_fields = 0;
    r1.field_lengths = NULL;
    r1.fields = NULL;
    int field_length = 0;
    int temp_size = 64;
    char *temporary_field = (char *)malloc(temp_size * sizeof(char));
    // check if the file pointer or pointer to the file pointer is valid
    if (*csvfile == NULL) {
        fprintf(stderr, "File pointer is not valid.\n");
        exit(EXIT_FAILURE);
    }
    // loops through the record and get each character in the field
    while ((ch = fgetc(*csvfile)) != EOF && ch != '\n') {
	    // check for the comma to verify one field
        if (ch == ',') {
            // Increase the number of fields
            r1.num_fields++;

            // Reallocate memory for field_lengths and fields
            r1.field_lengths = (int *)realloc(r1.field_lengths, r1.num_fields * sizeof(int));
            r1.fields = (char **)realloc(r1.fields, r1.num_fields * sizeof(char *));

            if (r1.field_lengths == NULL || r1.fields == NULL) {
                fprintf(stderr, "Reallocation failed.\n");
                exit(EXIT_FAILURE);
            }

            // Store the length of the previous field
            r1.field_lengths[r1.num_fields - 1] = field_length;

            // Allocate memory for the new field
            r1.fields[r1.num_fields - 1] = (char *)malloc((field_length + 1) * sizeof(char));
            if (r1.fields[r1.num_fields - 1] == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }

            // Copy the temporary field to the new field
            strcpy(r1.fields[r1.num_fields - 1], temporary_field);

            // Reset temporary_field and field_length for the next field
            free(temporary_field);
            temp_size = 64;
            temporary_field = (char *)malloc(temp_size * sizeof(char));
            if (temporary_field == NULL) {
                fprintf(stderr, "Memory allocation failed.\n");
                exit(EXIT_FAILURE);
            }
            field_length = 0;
        } else {

            // Increase the size of temporary_field if necessary
            if (field_length >= temp_size - 1) {
                temp_size *= 2;
                temporary_field = (char *)realloc(temporary_field, temp_size * sizeof(char));
                if (temporary_field == NULL) {
                    fprintf(stderr, "Memory allocation failed.\n");
                    exit(EXIT_FAILURE);
                }
            }

            // Add character to the temporary field
            temporary_field[field_length] = ch;
            field_length++;
        }
    }

    // Handle the last field
    if (field_length > 0) {
        r1.num_fields++;
        r1.field_lengths = (int *)realloc(r1.field_lengths, r1.num_fields * sizeof(int));
        r1.fields = (char **)realloc(r1.fields, r1.num_fields * sizeof(char *));

        if (r1.field_lengths == NULL || r1.fields == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        r1.field_lengths[r1.num_fields - 1] = field_length;

        r1.fields[r1.num_fields - 1] = (char *)malloc((field_length + 1) * sizeof(char));
        if (r1.fields[r1.num_fields - 1] == NULL) {
            fprintf(stderr, "Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        strcpy(r1.fields[r1.num_fields - 1], temporary_field);
    }

    free(temporary_field);
    return r1;
}

//handles writing the record to an output file 
void write_csv_record(FILE **csvfile, record_t record) {
	// loops through the record , output field to th stream.
	for (int i = 0; i < record.num_fields; i++) {
        fprintf(*csvfile, "%s", record.fields[i]);

        // Add comma if it's not the last field
        if (i < record.num_fields - 1) {
            fprintf(*csvfile, ",");
        }
    }
    fprintf(*csvfile, "\n");
}

record_t *read_csv_file(FILE **csvfile, int *n) {
	int n_read = 0;
	record_t *records = NULL; // We start out with an empty array
	
	// Read records until the end of the file is reached
	while(!feof(*csvfile)) {
		n_read++;
		records = (record_t *) realloc(records, n_read * sizeof(record_t)); // realloc works with NULL too
		records[n_read - 1] = read_csv_record(csvfile);
	}
	
	// Return values
	*n = n_read;
	return records;
}

void write_csv_file(FILE **csvfile, record_t *contents, int n) {
	int i;
	
	// Write each record to the specified file
	for(i = 0; i < n; i++) {
		write_csv_record(csvfile, contents[i]);
	}
}
// free the memory allocated for the record.
void free_record(record_t record) {
	for(int i=0; i < record.num_fields;i++){
		free(record.fields[i]);
	}
	free(record.field_lengths);
	free(record.fields);
}

void free_record_array(record_t *records, int n_records) {
	int i;

	// Free each record in the array
	for(i = 0; i < n_records; i++) {
		free_record(records[i]);
	}
	// Free array
	free(records);
}

