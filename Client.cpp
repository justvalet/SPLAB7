#include <winSock2.h>
#include <string>
#include <stdio.h>
#include <iostream>
using namespace std;
#pragma comment(lib, "ws2_32.lib")
#pragma warning (disable:4996)
SOCKET con;
void ChatServer()
{
	char chatik[256];
	while (true)
	{
		recv(con, chatik, sizeof(chatik), NULL);//Сокет хранит соединение с сервером
		cout << chatik << endl;
	}
}
int main(int argc, char* argv[])
{
	setlocale(0, "");
	char text[256];
	//загрузка библиотеки
	WSADATA wsa;// стуктура
	WORD DLLVersion = MAKEWORD(2, 1);
	if (WSAStartup(DLLVersion, &wsa) != 0)
	{
		cout << "Error lib" << endl;
		system("pause");
		exit(1);
	}
	SOCKADDR_IN address;
	address.sin_family = AF_INET;// семейство адресов
	address.sin_port = htons(5555);
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	con = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(con, (SOCKADDR*)& address, sizeof(address)) != 0)
	{
		cout << "Error, bad connection!" << endl;
		system("pause");
		return 2;
	}
	cout << "Вы подключились!!!" << endl << endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ChatServer, NULL, NULL,
		NULL);
	while (true)
	{
		cin.getline(text, sizeof(text));// ввод пользователя
		send(con, text, sizeof(text), NULL);// отправка пользователя
		Sleep(8);
	}
	system("pause");
	return 0;
}