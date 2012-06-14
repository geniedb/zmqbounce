#include <iostream>
#include <zmq.hpp>
#include "options.h"

using namespace std;
using namespace zmq;

int main(int argc, char ** argv) {
	options opts;
	opts.configure(argc, argv);
	context_t ctxt(1);
	socket_t client(ctxt,ZMQ_PUSH);
	socket_t pub(ctxt,ZMQ_SUB);
	int linger = 0;
	client.connect(opts.clientURL.c_str());
	pub.bind(opts.pubURL.c_str());
	client.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
	pub.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
	pub.setsockopt(ZMQ_SUBSCRIBE, "", 0);

	while(true) {
		message_t recv;
		message_t send(5);
		memcpy(send.data(), "12345", 5);	
		client.send(send);
		pub.recv(&recv);
		if (opts.flood)
			cout << '.';
	}

	return 0;
}
