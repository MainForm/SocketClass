#include "pch.h"
#include "Socket.h"


namespace SocketClass {
	//private
	inline void Socket::setPort(const int& port)
	{
		addr.sin_port = htons(port);
	}


	//if error didn't occur, return 1 
	inline int Socket::setIP(const string& ip) {
		return inet_pton(addr.sin_family, ip.data(), &addr.sin_addr);
	}

	//public
	Socket::Socket(int af, int type, int protocol)
		: addr{ } // initialize data to 0 in addr struct
	{
		sock = ::socket(af, type, protocol);
		addr.sin_family = PF_INET;
		addr.sin_addr.s_addr = INADDR_ANY;
	}

	Socket::~Socket() {
		close();
	}

	int Socket::bind(const string& ip,const int& port) {

		this->setPort(port);

		if (inet_pton(AF_INET, ip.data(), &addr.sin_addr) <= 0) {
			return -1;
		}

		return ::bind(sock, (const sockaddr*)&addr, sizeof(addr));
	}

	int Socket::bind(const int& port) {
		this->setPort(port);

		return ::bind(sock, (const sockaddr*)&addr, sizeof(addr));
	}

	int Socket::listen(const int& backlog) {
		return ::listen(sock, backlog);
	}

	int Socket::accept(Socket& client) {

		int clientAddrSize = sizeof(client.addr);
		if (client.sock = ::accept(sock, (sockaddr*)&client.addr, &clientAddrSize), client.sock == SOCKET_ERROR)
			return SOCKET_ERROR;

		return 0;
	}

	int Socket::connect(const string& ip,const int& port) {

		setPort(port);

		if (inet_pton(AF_INET, ip.data(), &addr.sin_addr) <= 0) {
			return -1;
		}

		return ::connect(sock, (const sockaddr*)&addr, sizeof(addr));
	}

	void Socket::close() {
		if (sock != NULL) {
			closesocket(sock);
			sock = NULL;
		}
	}

	int Socket::shutdown(int how)
	{
		return ::shutdown(sock, how);
	}

	int Socket::send(const vector<char>& data) {
		return ::send(sock, data.data(), data.size(), 0);
	}

	int Socket::recv(vector<char>& data) {
		return ::recv(sock, data.data(), data.size(), 0);
	}
}