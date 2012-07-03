/**
 * Fizz
 */

#include <stdio.h>
#include <stdlib.h>

#include <ev.h>

#include "generator.h"

/**
 * Usage:
 *     run program with a two arguments:
 *         - worker ID
 *         - datacenter ID
 *     Both arguments should be an integers.
 *
 */
int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Wrong arguments\n");
		return 1;
	}

	Context ctx = generator_init(atoi(argv[1]), atoi(argv[2]));

	printf("%lld\n", generator_next_id(&ctx));

	return 0;
}
