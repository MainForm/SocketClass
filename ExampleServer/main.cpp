#include <iostream>
#include "Socket.h"

using namespace std;
using namespace SocketClass;

int main(void) {
	Socket listener;

	{
		int rs = listener.bind(7896);
		if (rs == SOCKET_ERROR || rs == -1) {
			cerr << "bind() error" << endl;
			return -1;
		}
	}

	if (listener.listen() == SOCKET_ERROR) {
		cerr << "listen() error" << endl;
		return -1;
	}

	cout << "waiting client.." << endl;
	Socket client;
	
	if (listener.accept(client) == SOCKET_ERROR) {
		cerr << "accept() error" << endl;
		return -1;
	}

	cout << "client is connected" << endl;

	string msg = "Test Message!!";

	vector<char> data{ msg.begin(),msg.end() };

	client.send(data);

	client.close();
	listener.close();

	return 0;
}