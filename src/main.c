/**
 * Fizz
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include <ev.h>

#include "generator.h"
#include "server.h"

static const struct option options[] = {
	{"worker", 2, NULL, 'w'},
	{"datacenter", 2, NULL, 'd'},
	{"port", 2, NULL, 'p'},
	{"help", 0, NULL, 'h'},
};

static const char* help = "Fizz is a network service for generating unique ID numbers at high scale with some simple guarantees.\n\n"
	"Usage: fizz [options]\n\n"
	"Options:\n"
	"	-w, --worker\t\tworker ID\n"
	"	-d, --datacenter\tdatacenter ID\n"
	"	-p, --port\t\tport number\n";

int main(int argc, char* argv[]) {

	int option, option_idx;
	int worker_id = 0;
	int datacenter_id = 0;
	int port = 7954;

	while ((option = getopt_long(argc, argv, "w:d:p:", options, &option_idx)) != -1) {
		switch (option) {
			case 'w':
				worker_id = atoi(optarg);
				break;
			case 'd':
				datacenter_id = atoi(optarg);
				break;
			case 'p':
				port = atoi(optarg);
				break;
			case 'h':
			case '?':
				printf(help);
				exit(EXIT_FAILURE);
				break;
		}
	}

	Context ctx = generator_init(worker_id, datacenter_id);

	server_serve(ctx, port);

	return 0;
}
