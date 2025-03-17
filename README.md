# CSV Library in C

## Overview
This project is a simple **CSV (Comma-Separated Values) library in C** for reading and writing CSV files. The library handles CSV records dynamically using memory allocation, allowing efficient storage and processing of fields.

## Features
- Read and write CSV files one record at a time.
- Dynamically allocate memory for fields and records.
- Handle variable-length fields and records.
- Prevent buffer overruns by allocating space as needed.
- Ensure proper memory management to avoid leaks.

## Data Structure
```c
typedef struct record {
    int num_fields;       // Number of fields in the record
    int *field_lengths;   // Array storing lengths of each field
    char **fields;        // Array of dynamically allocated field strings
} record_t;
```

## Functionality
### Reading a CSV File
- Reads one record at a time from a file.
- Dynamically resizes memory to accommodate varying field sizes.
- Uses `getc()` to process characters efficiently.
- Handles empty lines as single-field records with an empty string.

### Writing a CSV File
- Writes records to a file using `fprintf()`.
- Ensures proper formatting with commas and newline characters.
- Maintains the original record order.

### Memory Management
- Allocates memory dynamically for records and fields.
- Uses `realloc()` for efficient space management.
- Frees memory properly to prevent leaks.

## Usage
### Compilation
Compile the project using a standard C compiler:
```sh
gcc -o csv_program main.c csv.c -Wall -Wextra -pedantic
```

### Example Usage
#### Reading a CSV file
```c
FILE *fp = fopen("data.csv", "r");
record_t record;
while (read_record(fp, &record)) {
    // Process record
    free_record(&record); // Free memory after use
}
fclose(fp);
```

#### Writing a CSV file
```c
FILE *fp = fopen("output.csv", "w");
record_t record = {/* Populate record */};
write_record(fp, &record);
fclose(fp);
free_record(&record); // Free memory after use
```

## Error Handling
- The program prints error messages if memory allocation fails.
- Handles file I/O errors gracefully.

## Future Improvements
- Add support for quoted fields.
- Implement escaping for special characters.
- Optimize memory reallocation strategies.

## Author
Jean Michel Mugabe

## Acknowledgement 
Dr. Michael Cormier (micormier@mta.ca)

