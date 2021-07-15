#pragma once

#ifdef DLL_EXPORT_SOCKET
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#endif

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace SocketClass {
	class DLL_DECLSPEC Socket
	{
	private:
		SOCKET sock = NULL;
		SOCKADDR_IN addr;

		inline void setPort(const int& port);
		inline int setIP(const string& ip);
	public:
		Socket(int af = AF_INET, int type = SOCK_STREAM, int protocol = IPPROTO_TCP);
		virtual ~Socket();

		int bind(const string& ip,const int& port);
		int bind(const int& port);

		int listen(const int& backlog = SOMAXCONN);
		int accept(Socket& client);

		int connect(const string& ip, const int& port);

		void close();
		int shutdown(int how);

		int send(const vector<char>& data);
		int recv(vector<char>& data);
	};
}
