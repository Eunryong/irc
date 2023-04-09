/*
<message>  ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
<prefix>   ::= <servername> | <nick> [ '!' <user> ] [ '@' <host> ]
<command>  ::= <letter> { <letter> } | <number> <number> <number>
<SPACE>    ::= ' ' { ' ' }
<params>   ::= <SPACE> [ ':' <trailing> | <middle> <params> ]

<middle>   ::= <Any *non-empty* sequence of octets not including SPACE
               or NUL or CR or LF, the first of which may not be ':'>
<trailing> ::= <Any, possibly *empty*, sequence of octets not including
               NUL or CR or LF>

<crlf>     ::= CR LF

<target>     ::= <to> [ "," <target> ]
<to>         ::= <channel> | <user> '@' <servername> | <nick> | <mask>
<channel>    ::= ('#' | '&') <chstring>
<servername> ::= <host>
<host>       ::= see RFC 952 [DNS:4] for details on allowed hostnames
<nick>       ::= <letter> { <letter> | <number> | <special> }
<mask>       ::= ('#' | '$') <chstring>
<chstring>   ::= <any 8bit code except SPACE, BELL, NUL, CR, LF and
                     comma (',')>

<user>       ::= <nonwhite> { <nonwhite> }
<letter>     ::= 'a' ... 'z' | 'A' ... 'Z'
<number>     ::= '0' ... '9'
<special>    ::= '-' | '[' | ']' | '\' | '`' | '^' | '{' | '}'
<nonwhite>   ::= <any 8bit code except SPACE (0x20), NUL (0x0), CR
                     (0xd), and LF (0xa)>
*/

#ifndef __MESSAGEHANDLER_HPP__
#define __MESSAGEHANDLER_HPP__

#include <string>
#include <vector>
#include <map>
#include <set>
#include <cctype>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>

#include "recvData.hpp"
#include "FileDescriptor.hpp"
#include "Channel.hpp"
#include "CommandResponses.hpp"
#include "Bot.hpp"

#define MESSAGE 91
#define PREFIX 92
#define COMMAND 93
#define SPACE 94
#define PARAMS 95
#define MIDDLE 96
#define TRAILING 97
#define CRLF 98

#define COLON 922

#define BROADCAST -1

enum cmd {PASS_, NICK_, USER_, QUIT_, JOIN_, KICK_, PART_, NAMES_, PRIVMSG_};

class EventHandler {
	public:
		EventHandler(recvData rec, std::map<int, FileDescriptor>& fdList,
						std::map<std::string, Channel>& channelList,
						std::string& pass, std::string& port);
	private:
		EventHandler(const EventHandler& other);
		EventHandler& operator=(const EventHandler& other);

	public:
		std::set<int> getFdTo() const;
		std::string getSendMsg() const;
		bool isInFd(int fd);

	private:
		std::size_t findPos(std::string str, std::string del);

		void tokenize();

		// process message
		// ::= [':' <prefix> <SPACE> ] <command> <params> <crlf>
		void messageF();

		// ::= <SPACE> [ ':' <trailing> | <middle> <params> ]
		void paramsF();

		void cmdPass();
		void cmdNick();
		void cmdUser();
		void cmdQuit();
		void cmdJoin();
		void cmdKick();
		void cmdPart();
		void cmdNames();
		void cmdPrivmsg();

		void pushChannel(std::string channel);
		int  getFd(std::string nick);
		void cmdHandler();
		bool checkNick(std::string nick);

		std::set<int> joinChannel(std::string channelName, int fd);

		void sendMessage(std::string msg);
		void connectServer();

	public:
		// void printParse();

	private:
		std::string _msg;
		int _fdFrom;
		std::set<int> _fdTo;
		std::vector<std::pair<int, std::string> > _parse;
		std::string _sendMsg;

		// from server
		std::map<int, FileDescriptor>& _fdList;
		std::map<std::string, Channel>& _channelList;
		std::string& _pass;
		std::string& _port;
};

#endif
