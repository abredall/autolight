#include <stdio.h>

int write_to(char * file_name, int input) {
	FILE * fp_out = fopen(file_name, "w");
	if (fp_out == NULL) return 1;
	fprintf(fp_out, "%d", input);
	fclose(fp_out);
	return 0;
}

int read_from(char * file_name) {
	FILE * fp_in = fopen(file_name, "r");
	if (fp_in == NULL) return 1;
	int output;
	fscanf(fp_in, "%d", &output);
	fclose(fp_in);
	return output;
}
