#include <stdio.h> // file io
#include <stdlib.h> // EXIT_FAILURE
#include <errno.h> // errno
#include <string.h> // sterror()
#include <linux/limits.h>

int read_str(char * file_name, char var[PATH_MAX]) {
	FILE * fp_in = fopen(file_name, "r");

	if (fp_in == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	if (fscanf(fp_in, "%1023[^\n]%*c", var) != 1) {
		fprintf(stderr, "ERROR: Could not read string from %s. Make sure file is formatted properly.\n", file_name);
		return EXIT_FAILURE;
	}

	fclose(fp_in);

	return EXIT_SUCCESS;
}

int write_int(char * file_name, int input) {
	FILE * fp_out = fopen(file_name, "w");

	if (fp_out == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	fprintf(fp_out, "%d", input);
	fclose(fp_out);

	return EXIT_SUCCESS;
}

int read_int(char * file_name, int * var) {
	FILE * fp_in = fopen(file_name, "r");

	if (fp_in == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	int output;
	if (fscanf(fp_in, "%d", &output) != 1) {
		fprintf(stderr, "ERROR: Could not read int from %s. Make sure file is formatted properly.", file_name);
		return EXIT_FAILURE;
	}
	fclose(fp_in);
	*var = output;

	return EXIT_SUCCESS;
}

int read_long(char * file_name, unsigned long int * var) {
	FILE * fp_in = fopen(file_name, "r");

	if (fp_in == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	unsigned long int output;
	if (fscanf(fp_in, "%li", &output) != 1) {
		fprintf(stderr, "ERROR: Could not read long from %s. Make sure file is formatted properly.", file_name);
		return EXIT_FAILURE;
	}
	fclose(fp_in);

	*var = output;

	return EXIT_SUCCESS;
}

int read_float(char * file_name, float * var) {
	FILE * fp_in = fopen(file_name, "r");

	if (fp_in == NULL) {
		fprintf(stderr, "ERROR: Could not open %s: %s\n", file_name, strerror(errno));
		return EXIT_FAILURE;
	}

	float output;
	if (fscanf(fp_in, "%f", &output) != 1) {
		fprintf(stderr, "ERROR: Could not read float from %s. Make sure file is formatted properly.", file_name);
		return EXIT_FAILURE;
	}
	fclose(fp_in);

	*var = output;

	return EXIT_SUCCESS;
}
