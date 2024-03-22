#pragma once
#include"Button.h"
#include <SFML/Network.hpp>
class InternetConnection
{
private:
	sf::IpAddress* _ADDRESS;
	sf::TcpSocket _SOCKET;
	sf::TcpListener _LISTENER;

	int _PORT = 9999;
	int is_connected = false;
	char _buffer;
	std::size_t _received = 0;
public:
	~InternetConnection();
	bool establishConnection(bool host, std::string, unsigned);
	void sendMove(unsigned short);
	unsigned short waitForResponse();
	void resetConnection();

};

