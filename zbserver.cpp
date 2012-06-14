#include <iostream>
#include <zmq.hpp>

using namespace std;
using namespace zmq;

int main() {
	context_t ctxt(1);
	socket_t client(ctxt,ZMQ_PULL);
	socket_t pub(ctxt,ZMQ_PUB);
	int linger = 0;
	client.bind("tcp://127.0.0.1:5655");
	pub.connect("epgm://;224.0.0.1:5656");
	client.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
	pub.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));

	while(true) {
		message_t recv;
		message_t send;
		client.recv(&recv);
		send.copy(&recv);
		pub.send(send);
		cout << '.';
	}

	return 0;
}
