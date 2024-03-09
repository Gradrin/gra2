#pragma once
#include <SFML/Network.hpp>
#include<string>
#include<thread>
#include <mutex>
#include <any>
#include"Gui.h"
#include<atomic>
#include<vector>


enum socketType :bool { HOST, CLIENT };
enum sizeOfSocket :short { SOCKET_SIZE = 2 };

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

class Online
{
private:

	Gui& gui;


	sf::Socket::Status status;

	std::mutex mutex2;
	std::vector<sf::TcpSocket*>* socket2;
	sf::TcpSocket socket[SOCKET_SIZE];

	sf::IpAddress address = "localHost";


	sf::TcpListener listener;

	//Indicating flags (you are host or client)
	bool hosting;
	bool connection;

	//Flags to connect or hosting server
	bool connected;
	bool host;

	bool clientStatus;
	bool logOut;

	bool packetFlag;

	//Flags for Start class
	std::atomic<bool> gameOnline;
	bool turn;

	int port;

	int numberTable;
	short sign;
	sf::TcpSocket* socketX = new sf::TcpSocket();
	bool x;
public:
	sf::Packet packet;
	sf::Packet packet2;
	sf::Packet packet3;
	sf::TcpSocket hostSocket;

	Online(Gui& gui)
		:gui(gui)
	{
		port = 30000;
		hosting = false;
		connected = false;

		connection = false;
		host = false;

		clientStatus = false;

		packetFlag = false;

		gameOnline = false;
		numberTable = 0;
		turn = HOST;
		sign = 0;
		logOut = false;
	}

	~Online()
	{

	}



	//Functions that return connection or hosting flag

	const bool& Hosting() const
	{
		return this->hosting;
	}

	const bool& IsConnected() const
	{
		return this->connection;
	}

	//Functions that return host or client flag

	const bool& getHost() const
	{
		return this->host;
	}

	const bool& getClient() const
	{
		return this->connected;
	}

	//Functions that return packet

	const sf::Packet& getPacket()const
	{
		return this->packet;
	}

	//Functions that return sockets

	const sf::TcpSocket& getSocket(bool& variable)const
	{
		return this->socket[variable];
	}

	sf::TcpSocket& getSo()
	{
		return this->socket[CLIENT];
	}

	//Functions that return turn flags

	const bool& getTurn()const
	{
		return this->turn;
	}

	const bool& Connection() const
	{
		return this->connection;
	}

	const bool& GameOnline()const
	{
		return this->gameOnline;
	}

	//Functions that return address and port

	sf::IpAddress getAdress() const
	{
		return this->address;
	}

	std::string getPort()
	{
		return std::to_string(port);
	}

	//Functions that return variable

	const int& getSign()const
	{
		return this->sign;
	}

	const int& getNumberTable()const
	{
		return this->numberTable;
	}

	bool& getClientStatus()
	{
		return this->clientStatus;
	}

	bool& getLogOut()
	{
		return this->logOut;
	}

	//void functions

	void ConnectClients()
	{
		while (true)
		{
			if ((hosting == true) && (connected == false))
			{
				hosting = false;
				if (listener.listen(port) == sf::Socket::Done)
				{
					logl(" Server is Started");
					if (listener.accept(socket[HOST]) == sf::Socket::Done)
					{
						socket[HOST].setBlocking(false);
						logl("Added client " << socket[HOST].getRemoteAddress() << ":" << socket[HOST].getRemotePort() << " on slot ");
						host = true;
					}
				}
				else
					logl("Can not create the server");
			}

			if ((connection == true) && (host == false))
			{
				connection = false;
				if (socket[CLIENT].connect(address, port) != sf::Socket::Done)
				{
					logl("Could not connect to the server\n");
				}
				else
				{
					logl("Connected to the server\n");
					connected = true;
				}
			}

			if ((connected == true) && (logOut == true))
			{
				socket[CLIENT].disconnect();
				logl("disconnection server");
				logOut = false;


			}
			if ((host == true) && (connected == false))
			{
				auto flag = listener.accept(socket[CLIENT]);
				switch (flag)
				{
				case sf::Socket::Done:
					logl("The socket has sent / received the data" << socket[CLIENT].getRemoteAddress() << ":" << socket[CLIENT].getRemotePort());
				case sf::Socket::NotReady:
					logl("The socket is not ready to send / receive data yet ");
				case::sf::Socket::Partial:
					logl("The socket sent a part of the data. ");
				case::sf::Socket::Disconnected:
					logl("The TCP socket has been disconnected. ");
				case::sf::Socket::Error:
					logl("Error An unexpected error happened ");
				default:
					logl("something else \n");
				}
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
			std::cout << clientStatus << std::endl;
	}

	void packetSystem()
	{
		while (true)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
				std::cout << clientStatus << std::endl;
			if (socket[CLIENT].receive(packet) == sf::Socket::Done)
			{
				std::size_t receiving;
				std::string information;
				packet >> information >> receiving;

				if (information == "VARIABLE")
					gui.getVariable() = receiving;
				else if (information.find("GAME_TYPE") != std::string::npos)
					gui.getTypeGame() = information.erase(0, 9);
				else if (information == "BASIC_VARIABLE")
					gui.getBasicVariable() = receiving;
				else if (information == "GET_SEND_PLAYER")
					gui.getPlayer() = receiving;

				else if (information == "GET_PLAYER")
					sign = receiving;
				else if (information == "CLIENT")
					turn = receiving;
				else if (information == "NR_TABLE")
					numberTable = receiving;

				logl("receiving data!");
				gameOnline = true;
				packet.clear();

			}
			if (socket[HOST].receive(packet) == sf::Socket::Done)
			{
				std::size_t receiving;
				std::string information;
				packet >> information >> receiving;

				if (information == "START_STATUS")
					gui.startStatus() = receiving;

				else if (information == "GET_PLAYER")
					sign = receiving;
				else if (information == "HOST")
					turn = receiving;
				else if (information == "NR_TABLE")
					numberTable = receiving;
				else if (information == "CONNECT")
					clientStatus = true;

				logl("receiving data!");
				gameOnline = true;
				packet.clear();
			}
			if (clientStatus == true)
			{
				logl("Added client " << socket[HOST].getRemoteAddress() << ":" << socket[HOST].getRemotePort() << " on slot ");
				logl("Added client C " << socket[CLIENT].getRemoteAddress() << ":" << socket[HOST].getRemotePort() << " on slot ");
				socket[CLIENT].disconnect();
				logl("Added client " << socket[HOST].getRemoteAddress() << ":" << socket[HOST].getRemotePort() << " on slot ");
				logl("Added client C " << socket[CLIENT].getRemoteAddress() << ":" << socket[HOST].getRemotePort() << " on slot ");
				clientStatus = false;
			}
		}
	}

	void IsConnectionVariable(bool variable)
	{
		connection = true;
	}

	void HostingVariable(bool variable)
	{
		hosting = variable;
	}

	//Functions to send information to sockets

	void HostSendPacket(std::string information, std::size_t variable)
	{

		packet2 << information << variable;
		socket[HOST].send(packet2);
		packet2.clear();
	}

	void ClientSendPacket(std::string information, std::size_t variable)
	{
		packet2 << information << variable;
		socket[CLIENT].send(packet2);
		packet2.clear();
	}

	void changePlayer(bool player)
	{
		turn = player;
	}
	void gameOnlineStatus(bool status)
	{
		gameOnline = status;

	}


	void hostDisconnet()
	{
		listener.close();
		socket[HOST].disconnect();
	}

};
