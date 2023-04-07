#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <fstream>

#include "Multiplex.hpp"
#include "recvData.hpp"

#include "FileDescriptor.hpp"
#include "StringHandle.hpp"
#include "CommandResponses.hpp"
#include "EventHandler.hpp"
#include "Channel.hpp"

class Server {
	public:
		Server(int ac, char**av);
		~Server();

		void start();

		void closeClient(int fd);
		void deleteBuffer();

	private:
		std::string _pass;

		Multiplex _multiplex;

		std::map<int, FileDescriptor> _fdList;
		std::map<std::string, Channel> _channelList;

		std::vector<recvData> _recvBuffer;
};

#endif
