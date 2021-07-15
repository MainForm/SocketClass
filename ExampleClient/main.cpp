#include <iostream>
#include <vector>
#include <string>

#include "Socket.h"

using namespace std;
using namespace SocketClass;

int main(void) {
	Socket client;

	cout << "connecting to server" << endl;
	if (client.connect("127.0.0.1", 7896) == SOCKET_ERROR) {
		cerr << "connect() error" << endl;
		return -1;
	}

	cout << "connected to server!" << endl;

	vector<char> data(200);

	client.recv(data);

	string str = data.data();

	cout << str << endl;
	cout << str.size() << endl;
	client.close();

	return 0;
}