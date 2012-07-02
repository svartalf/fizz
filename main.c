/**
 * Fizz
 */

#include <stdio.h>
#include <stdlib.h>

#include <ev.h>


long long twepoch = 1288834974657ll;

const long worker_id_bits = 5;
const long datacenter_id_bits = 5;
const long sequence_bits = 12;

long sequence = 0;
long long last_timestamp = -1;

long long time() {
	return (long long)(ev_time()*1000);
}

long long til_next_millis(long long last_timestamp) {
	long long timestamp = time();

	while (timestamp <= last_timestamp) {
    	timestamp = time();
    }

    return timestamp;
}

/**
 * Generate next ID based on the worker id, datacenter id and current time
 */
long long generate_id(int worker_id, int datacenter_id) {
	// Converting `ev_time` double into long long milliseconds
	// TODO: replace with a `ev_now` function

	int worker_id_shift = sequence_bits;
	int datacenter_id_shift = sequence_bits + worker_id_bits;
	int timestamp_left_shift = sequence_bits + worker_id_bits + datacenter_id_bits;
	int sequence_mask = -1 ^ (-1 << sequence_bits);

	long long timestamp = time();

	if (last_timestamp == timestamp) {
		sequence = (sequence + 1) & sequence_mask;
		if (sequence == 0) {
			timestamp = til_next_millis(last_timestamp);
		}
	} else {
		sequence = 0;
	}

	last_timestamp = timestamp;

	return ((timestamp - twepoch) << timestamp_left_shift) |
	      (datacenter_id << datacenter_id_shift) |
	      (worker_id << worker_id_shift) |
	      sequence;

}


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

	printf("%lld\n", generate_id(atoi(argv[1]), atoi(argv[2])));

	return 0;
}
