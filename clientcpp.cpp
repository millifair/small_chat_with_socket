#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <thread>
#pragma warning(disable: 4996)
SOCKET Connection;
void mesget() {
	char msg[256];
	while (true) {
		recv(Connection, msg, sizeof(msg), 0);
		std::cout << msg << std::endl;
	}
}
int main(int argc, char* argv[]) {
	//WSAStartup
	WSAData wsaData;
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsaData) != 0) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeofaddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1211);
	addr.sin_family = AF_INET;

	 Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		std::cout << "Error: failed connect to server.\n";
		return 1;
	}
	std::cout << "client connected" << std::endl;
	char msg[256];
	
	recv(Connection, msg, sizeof(msg), 0);
		std::cout << msg << std::endl;
		char mes[256];
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)mesget, NULL, NULL, NULL);

		while (true) {
			std::cin.getline(mes,sizeof(mes));
			send(Connection, mes, sizeof(mes), 0);
			Sleep(10);
		}
		
	system("pause");
	return 0;
}