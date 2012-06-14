#include <iostream>
#include <zmq.hpp>
#include "options.h"

using namespace std;
using namespace zmq;

int main(int argc, char ** argv) {
	options opts;
	opts.configure(argc, argv);
	context_t ctxt(1);
	socket_t client(ctxt,ZMQ_PULL);
	socket_t pub(ctxt,ZMQ_PUB);
	int linger = 0;
	client.bind(opts.clientURL.c_str());
	pub.connect(opts.pubURL.c_str());
	client.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
	pub.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));

	while(true) {
		message_t recv;
		message_t send;
		client.recv(&recv);
		send.copy(&recv);
		pub.send(send);
		if (opts.flood)
			cout << '.';
	}

	return 0;
}
