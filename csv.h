#include <stdio.h> // you

//CSV Record structure
typedef struct record_t {
	int num_fields;
	int *field_lengths;
	char **fields;
} record_t;

// Function for reading a single CSV record
record_t read_csv_record(FILE **csvfile);

// Function for writing a single CSV record
void write_csv_record(FILE **csvfile, record_t record);

// Function for reading a CSV file
record_t *read_csv_file(FILE **csvfile, int *n);

// Function for writing a CSV file
void write_csv_file(FILE **csvfile, record_t *contents, int n);

// Function for freeing memory in a record
void free_record(record_t record);

// Function for freeing an array of records
void free_record_array(record_t *record, int n_records);