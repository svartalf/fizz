#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "ev.h"

/**
 * Context for ID generator
 */
typedef struct context {
	int worker_id;
	int datacenter_id;

	long sequence;
	long long last_timestamp;

	// Various once initialized variables
	long long twepoch;
	char worker_id_bits;
	char datacenter_id_bits;
	char sequence_bits;
	int worker_id_shift;
	int datacenter_id_shift;
	int timestamp_left_shift;
	int sequence_mask;

} Context;

Context generator_init(int worker_id, int datacenter_id);

long long generator_next_id(Context *ctx, EV_P);

#endif // GENERATOR_H_
