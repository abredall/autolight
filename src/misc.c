#include <math.h> // log

float scale_log(long int value, long int min, long int max) {
	return (log(value)-log(min))/(log(max)-log(min));
}

