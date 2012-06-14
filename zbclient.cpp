#include <iostream>
#include <zmq.hpp>

using namespace std;
using namespace zmq;

int main() {
	context_t ctxt(1);
	socket_t client(ctxt,ZMQ_PUSH);
	socket_t pub(ctxt,ZMQ_SUB);
	int linger = 0;
	client.connect("tcp://127.0.0.1:5655");
	pub.bind("epgm://;224.0.0.1:5656");
	client.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
	pub.setsockopt(ZMQ_LINGER, &linger, sizeof(linger));
	pub.setsockopt(ZMQ_SUBSCRIBE, "", 0);

	while(true) {
		message_t recv;
		message_t send(5);
		memcpy(send.data(), "12345", 5);	
		client.send(send);
		pub.recv(&recv);
		cout << '.';
	}

	return 0;
}
