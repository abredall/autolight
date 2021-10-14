#include <stdio.h>
#include "objects/test.h"
#include "cfg.h"

int main() {
	config_initialize();
	int n_pass = 0, n_fail = 0;
	test_objects(&n_pass, &n_fail);
	printf("Passed: %d\tFailed: %d\n", n_pass, n_fail);

	return 0;
}
