#include "laptop.h"
#include "sensor.h"
#include "screen.h"
#include <stdio.h>

int test_objects(int n_pass, int n_fail) {
	test_laptop(&n_pass, &n_fail);
	test_sensor(&n_pass, &n_fail);
	test_screen(&n_pass, &n_fail);

	return 0;
}
