#ifndef __BOT_HPP__
#define __BOT_HPP__

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

#define NOTCMD 0
#define HELP 1
#define INFO 2
#define JUMMECHU 3

class Bot {
	public:
		Bot(std::string msg, std::string& port);
		// Bot(const Bot& obj);
		~Bot();
		// Bot& operator=(const Bot& obj);
		std::vector<std::string> process();

		int checkCmd();

		std::vector<std::string> help();
		std::vector<std::string> info();
		std::vector<std::string> jummechu();

	private:
		std::string _msg;
		std::string _cmd;
		std::string _arg;
		std::string& _port;
};

#endif
