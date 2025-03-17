#include <stdio.h>
#include "csv.h"

//Dr. Michael Cormier
int main(int argc, char *argv[]) {
	int n;
	FILE *infile;
	FILE *outfile;
	record_t *records;

	// Open input and output files
	infile = fopen(argv[1], "r");
	outfile = fopen(argv[2], "w");

	// Read in CSV file
	printf("Reading records...\n");
	records = read_csv_file(&infile, &n);
	
	// Write CSV file to output file
	printf("Writing records...\n");
	write_csv_file(&outfile, records, n);
	
	// Free records
	printf("Freeing record array...\n");
	free_record_array(records, n);

	// Close files
	fclose(infile);
	fclose(outfile);

	return 0;
}

