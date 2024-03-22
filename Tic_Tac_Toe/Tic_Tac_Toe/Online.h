#pragma once
#include <SFML/Network.hpp>
#include<string>
#include<thread>
#include <mutex>
#include <any>
#include"Gui.h"
#include<vector>
#include<chrono>


enum socketType { HOST, CLIENT };

enum class packetType : uint8_t
{
	BASIC,
	BEST_OF_THREE,
	BEST_OF_FIVE,
	BEST_OF_SEVEN,
	MAIN_MENU,
	TYPE_GAME,
	MULTIPLAYER,
	VARIABLE,
	BASIC_VARIABLE,
	GET_SEND_PLAYER,
	GET_PLAYER,
	CLIENT,
	HOST,
	NR_TABLE,
	START_STATUS,
	DISCONNECT,
	CLOSE_SERVER,
	LEAVE
};

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

class Online
{
private:

	Gui& gui;


	sf::TcpSocket socket;

	sf::IpAddress address = "localHost";


	sf::TcpListener listener;

	//Indicating flags (you are host or client)
	bool hosting;
	bool connection;

	//Flags to connect or hosting server
	bool connected;
	bool host;

	//Flags to inform program when host or client is disconnect
	bool disconnectHostStatus;
	bool disconnectClientStatus;

	bool logOut;

	bool packetFlag;

	//Flags for Start class
	bool gameOnline;
	bool turn;

	int port;

	int numberTable;
	short sign;

	bool leaveFromGame;

public:
	sf::Packet packet;
	sf::Packet packet2;
	sf::TcpSocket hostSocket;
	bool clientInformationClose;

	Online(Gui& gui)
		:gui(gui)
	{
		port = 30000;
		hosting = false;
		connected = false;

		connection = false;
		host = false;

		disconnectClientStatus = false;
		disconnectHostStatus = false;

		packetFlag = false;

		gameOnline = false;
		numberTable = 0;
		turn = HOST;
		sign = 0;
		logOut = false;
		clientInformationClose = false;
		leaveFromGame = false;
	}

	~Online()
	{

	}

	//Functions that return connection or hosting flag

	bool& Hosting() 
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

	short& getSign()
	{
		return this->sign;
	}

	const int& getNumberTable()const
	{
		return this->numberTable;
	}

	bool& getClientStatus()
	{
		return this->disconnectClientStatus;
	}
	bool& getHostStatus()
	{
		return this->disconnectHostStatus;
	}

	bool& getClientInformationClose()
	{
		return this->clientInformationClose;
	}

	bool& getLogOut()
	{
		return this->logOut;
	}

	bool& getLeaveFromGame()
	{
		return this->leaveFromGame;
	}

	//void functions

	void ConnectClients()
	{
		while (true)
		{
			if ((hosting == true) && (connected == false))
			{
				if (listener.listen(port) == sf::Socket::Done)
				{
					logl("Server is open");
					hosting = false; 
					host = true;
				}
				else
					logl("Can not create the server");

				if (host == true)
				{
					if (listener.accept(socket) == sf::Socket::Done)
					{
						gameOnline = true;
						socket.setBlocking(false);
						logl("Added clientH " << socket.getRemoteAddress() << ":" << socket.getRemotePort() << " on slot ");
					}
				}

			}
			if ((connection == true) && (host == false))
			{
				connection = false;
				if (socket.connect(address, port) != sf::Socket::Done)
				{
					logl("Could not connect to the server\n");
				}
				else
				{
					logl("Connected to the server\n");
					connected = true;
					gameOnline = true;
				}
			}

			if ((connected == true) && (logOut == true))
			{
				socket.disconnect();
				logl("disconnection server");
				logOut = false;
				connected = false;
			}
		}
	}

	void packetSystem()
	{
		while (true)
		{
			if (socket.receive(packet) == sf::Socket::Done)
			{
				uint8_t variable;
				size_t receiving;
				packet >> variable >> receiving;
				packetType information = static_cast<packetType>(variable);

				switch(information)
				{
				case packetType::MAIN_MENU: {gui.getGameState() = MAIN_MENU; break; }
				case packetType::TYPE_GAME: {gui.getGameState() = TYPE_GAME; break; }
				case packetType::MULTIPLAYER: {gui.getGameState() = MULTIPLAYER; break; }
				case packetType::BASIC: {gui.getTypeGame() = "BASIC"; break; }
				case packetType::BEST_OF_THREE: {gui.getTypeGame() = "BEST_OF_THREE"; break; }
				case packetType::BEST_OF_FIVE: {gui.getTypeGame() = "BEST_OF_FIVE"; break; }
				case packetType::BEST_OF_SEVEN: {gui.getTypeGame() = "BEST_OF_SEVEN"; break; }
				case packetType::VARIABLE: {gui.getVariable() = receiving; break; }
				case packetType::BASIC_VARIABLE: {gui.getBasicVariable() = receiving; break; }
				case packetType::GET_SEND_PLAYER: {gui.getPlayer() = receiving; break; }
				case packetType::GET_PLAYER: {sign = receiving; break; }
				case packetType::CLIENT: {turn = receiving; break; }
				case packetType::HOST: {turn = receiving; break; }
				case packetType::NR_TABLE: {numberTable = receiving; break; }
				case packetType::START_STATUS: {gui.startStatus() = receiving; break; }
				case packetType::DISCONNECT: {disconnectClientStatus = true; break; }
				case packetType::CLOSE_SERVER: {clientInformationClose = true; break; }
				case packetType::LEAVE: {leaveFromGame = receiving; break; }
				}
				packet.clear();
			}
			if (clientInformationClose == true)
			{
				logl("Host closed server");
				clientInformationClose = false;
				socket.disconnect();
				connected = false;
				
				connection = false;
			}
			
			if (disconnectClientStatus == true)
			{
				logl("Disconnect Client");
				socket.disconnect();
				disconnectClientStatus = false;
			}
			if (disconnectHostStatus == true)
			{
				logl("Close Server");
				listener.close();
				socket.disconnect();
				disconnectHostStatus = false;
				host = false;
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

	void SendPacket(packetType information, size_t variable)
	{
		packet2 << static_cast<uint8_t>(information) << variable;
		socket.send(packet2);
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
		socket.disconnect();
	}

};
