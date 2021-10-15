#include <stdio.h>
#include "objects/test.h"
#include "cfg.h"

int main(int argc, char **argv) {
	config_initialize(argv[0]);
	int n_pass = 0, n_fail = 0;
	test_objects(&n_pass, &n_fail);
	printf("Passed: %d\tFailed: %d\n", n_pass, n_fail);

	return 0;
}
