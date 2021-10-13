#include <winSock2.h>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma warning (disable:4996)
SOCKET Connections[100];//соединения пользователей
int j = 0;
void CHandler(int id)
{
	setlocale(0, "");
	char chat[256];// текст клиента
	while (true)
	{
		recv(Connections[id], chat, sizeof(chat), NULL);// принимаем сообщение клиента
		for (int i = 0; i < j; i++)// отправляем
		{
			if (i == id)
			{
				continue;
			}
			send(Connections[i], chat, sizeof(chat), NULL);
		}
	}
}
int main(int argc, char* argv[])
{
	setlocale(0, "");
	//WSAStartup
	WSAData wsa;//cтруктура
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsa) != 0)
	{
		cout << "Error - library" << endl;
		exit(1);
	}
	SOCKADDR_IN address;// хранение адресса
	int sizeofaddr = sizeof(address);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(5555);
	address.sin_family = AF_INET;
	SOCKET sock = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sock, (SOCKADDR*)& address, sizeof(address));
	listen(sock, SOMAXCONN);// прослушка порта
	// для удерижвания соединения с клиентом
	SOCKET newCon;
	for (int i = 0; i < 100; i++)
	{
		newCon = accept(sock, (SOCKADDR*)& address, &sizeofaddr);
		if (newCon == 0)
		{
			cout << "Клиент не подключился!!! \n" << endl;
		}
		else
		{
			cout << "Соединение установлено, " << i+1 << "-ый пользователь подключен!" << endl;
			char text[256] = "Добро пожаловать в чат! ";
			send(newCon, text, sizeof(text), NULL);
			Connections[i] = newCon;
			j++;
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CHandler,
				(LPVOID)(i), NULL, NULL);// после ее выполнения работает два потока, принимаются новые cоединения и отправка сообщенй
		}
	}
	system("pause");
	return 0;
}