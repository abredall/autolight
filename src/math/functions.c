#include <math.h>

float scale_log(long int value, long int min, long int max) {
	return (log(value)-log(min))/(log(max)-log(min));
}

float scale_lin(int value, int min, int max) {
	return ((float)(value-min))/((float)(max-min));
}
