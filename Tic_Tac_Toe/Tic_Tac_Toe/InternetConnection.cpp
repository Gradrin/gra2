#include "InternetConnection.h"

InternetConnection::~InternetConnection()
{
	_SOCKET.disconnect();
	_LISTENER.close();
}

bool InternetConnection::establishConnection(bool is_host, std::string host_url, unsigned int host_port) {
	if (!is_host) {
		std::cout << "Connecting";
		if (_SOCKET.connect(host_url, host_port) != sf::Socket::Done)
			return false;
		_ADDRESS = new sf::IpAddress(host_url);
		_PORT = host_port;
	}
	else {
		std::cout << "Listening";
		_LISTENER.listen(host_port);
		if (_LISTENER.accept(_SOCKET) != sf::Socket::Done)
			return false;
		_PORT = host_port;
	}
	return true;
}
void InternetConnection::sendMove(unsigned short move) {
	_buffer = (char)move;
	if (_SOCKET.send(&_buffer, sizeof(_buffer)) != sf::Socket::Done) {
		std::cout << "Cannot send data...Connection corrupted" << std::endl;
		exit(0);
	}
}
unsigned short InternetConnection::waitForResponse() {
	std::cout << "Waiting for response" << std::endl;
	if (_SOCKET.receive(&_buffer, sizeof(_buffer), _received) != sf::Socket::Done) {
		std::cout << "Connection corrupted" << std::endl;
		is_connected = false;
	}
	return (int)_buffer;
}
void InternetConnection::resetConnection() {
	_SOCKET.disconnect();
	_LISTENER.close();
}