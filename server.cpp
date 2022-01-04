
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <thread>
#pragma warning(disable: 4996)
SOCKET connections[100];
int counter = 0;
void clientmess(int index) {
	char msg[256];
	while (true) {
		recv(connections[index], msg, sizeof(msg), 0);
		for (int i = 0;i < counter;++i) {
			if (i == index) {
				continue;
			}
			send(connections[i], msg, sizeof(msg), 0);
		}
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
	addr.sin_family = AF_INET;//интернет протокол

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));//привязка адреса и порта к сокету
	listen(sListen, SOMAXCONN);//

	SOCKET newConnection;
	for (int i = 0;i < 100;++i) {
		newConnection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
		if (newConnection == 0) {
			std::cout << "Error #2\n";
		}
		else {
			std::cout << "Client Connected!\n";
			char msg[256] = "write something in this chat";
			send(newConnection, msg, sizeof(msg), NULL);
			connections[i] = newConnection;
			counter++;
			HANDLE hThread;
			hThread= CreateThread(
				NULL,         // атрибуты безопасности по умолчанию
				0,            // размер стека используется по умолчанию
				(LPTHREAD_START_ROUTINE)clientmess,   // функция потока
				(LPVOID)i, // аргумент функции потока
				0,            // флажки создания используются по умолчанию
				0); // возвращает идентификатор потока
				// При успешном завершении проверяет возвращаемое значение.
			if (hThread == NULL)
			{
				std::cout << "Error, not correct thread" << std::endl;
			}
			else
			{
				CloseHandle(hThread);
			}
			
		}
		}
	
	
	system("pause");
	return 0;
}