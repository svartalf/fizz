/**
 * ID generation algorithm
 */

#include <stdio.h>
#include <stdlib.h>

#include <ev.h>

#include "generator.h"

/**
 * Long long time ago this function generates current time in milliseconds.
 *
 * And still doing it!
 */
long long time(EV_P) {
	return (long long)(ev_now(loop)*1000);
}

/**
 * Skipping some time
 */
long long til_next_millis(long long last_timestamp, EV_P) {
	long long timestamp = time(loop);

	while (timestamp <= last_timestamp) {
		timestamp = time(loop);
	}

	return timestamp;
}

/**
 * Initialize generator
 */
Context generator_init(int worker_id, int datacenter_id) {
	Context ctx;

	ctx.worker_id = worker_id;
	ctx.datacenter_id = datacenter_id;

	ctx.sequence = 0;
	ctx.last_timestamp = -1;

	ctx.twepoch = 1288834974657ll;
	ctx.worker_id_bits = 5;
	ctx.datacenter_id_bits = 5;
	ctx.sequence_bits = 12;

	ctx.worker_id_shift = ctx.sequence_bits;
	ctx.datacenter_id_shift = ctx.sequence_bits + ctx.worker_id_bits;
	ctx.timestamp_left_shift = ctx.sequence_bits + ctx.worker_id_bits + ctx.datacenter_id_bits;
	ctx.sequence_mask = -1 ^ (-1 << ctx.sequence_bits);

	return ctx;
}

/**
 * Generate next ID based on the worker id, datacenter id and current time
 */
long long generator_next_id(Context *ctx, EV_P) {
	// Converting `ev_time` double into long long milliseconds

	long long timestamp = time(loop);

	if (ctx->last_timestamp == timestamp) {
		ctx->sequence = (ctx->sequence + 1) & ctx->sequence_mask;
		if (ctx->sequence == 0) {
			timestamp = til_next_millis(ctx->last_timestamp, loop);
		}
	} else {
		ctx->sequence = 0;
	}

	ctx->last_timestamp = timestamp;

	return ((timestamp - ctx->twepoch) << ctx->timestamp_left_shift) |
	      (ctx->datacenter_id << ctx->datacenter_id_shift) |
	      (ctx->worker_id << ctx->worker_id_shift) |
	      ctx->sequence;

}
