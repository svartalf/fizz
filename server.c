/**
 * libev TCP server for clients serving
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <ev.h>

/**
 * Accept all the client connections
 */
static void accept_callback(EV_P, ev_io *w, int revents) {
	// TODO: accept client connections and them to them IDs
	// TODO: check for EV_ERROR & revents
}

/**
 * Start serving
 */
int server_serve(int port) {

	// Create TCP socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	// TODO: check for sock value here

	// Create address for socket binding
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	// Bind socket to address
	bind(sock, (struct sockaddr*) &address, sizeof(address));

	// Start listening on socket
	listen(sock, 5);  // TODO: What backlog size should be used?

	struct ev_loop *loop = EV_DEFAULT;
	ev_io watcher;
	printf("Init\n");

	// Initialize and start IO watcher
	// `accept_callback` will be called when sock will become writeable
	ev_io_init(&watcher, accept_callback, sock, EV_WRITE);
	ev_io_start(loop, &watcher);
	printf("Start\n");
	// Run loop
	ev_run(loop, 0);

	// Break was called
	return 0;
}
