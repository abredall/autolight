#include <stdio.h> // file io
#include <stdlib.h> // EXIT_FAILURE
#include <errno.h> // errno
#include <string.h> // sterror()

int write_to(char * file_name, int input) {
	FILE * fp_out = fopen(file_name, "w");

	if (fp_out == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	fprintf(fp_out, "%d", input);
	fclose(fp_out);

	return EXIT_SUCCESS;
}

int read_from(char * file_name, int * var) {
	FILE * fp_in = fopen(file_name, "r");

	if (fp_in == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	int output;
	fscanf(fp_in, "%d", &output);
	fclose(fp_in);
	*var = output;

	return EXIT_SUCCESS;
}
