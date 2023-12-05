#include "EventHandler.hpp"

EventHandler::EventHandler(recvData rec,
						std::map<int, FileDescriptor>& fdList,
						std::map<std::string, Channel>& channelList,
						std::string& pass, std::string& port)
: _msg(rec.msg), _fdFrom(rec.fdFrom),
	_fdList(fdList), _channelList(channelList), _pass(pass), _port(port) {
	while (!_msg.empty()) {
		tokenize();
		messageF();
		paramsF();
		cmdHandler();
		_parse.clear();
	}
}

std::set<int> EventHandler::getFdTo() const {
	return _fdTo;
}
std::string EventHandler::getSendMsg() const {
	return _sendMsg;
}
bool EventHandler::isInFd(int fd) {
	if (*_fdTo.begin() == BROADCAST)
		return true;
	if (_fdTo.count(fd))
		return true;
	return false;
}

std::size_t EventHandler::findPos(std::string str, std::string del) {
	std::size_t i;
	for (i = 0; i < str.size(); i++) {
		for (std::size_t j = 0; j < del.size(); j++) {
			if (str[i] == del[j])
				return i;
		}
	}
	return std::string::npos;
}

void EventHandler::tokenize() {
	std::size_t pos;
	pos = findPos(_msg, "\r\n :");
	while (pos != std::string::npos) {
		if (pos != 0) {
			_parse.push_back(std::pair<int, std::string>(MESSAGE, _msg.substr(0, pos)));
			_msg.erase(_msg.begin(), _msg.begin() + pos);
		}

		if (_msg[0] == '\r') {
			_parse.push_back(std::pair<int, std::string>(MESSAGE, _msg.substr(0, 2)));
			_msg.erase(_msg.begin(), _msg.begin() + 2);
			break;
		} else if (_msg[0] == '\n') {
			_parse.push_back(std::pair<int, std::string>(MESSAGE, _msg.substr(0, 1)));
			_msg.erase(_msg.begin(), _msg.begin() + 1);
			break;
		} else {
			_parse.push_back(std::pair<int, std::string>(MESSAGE, _msg.substr(0, 1)));
			_msg.erase(_msg.begin(), _msg.begin() + 1);
		}

		pos = findPos(_msg, "\r\n :");
	}
}

void EventHandler::messageF() {
	std::vector<std::pair<int, std::string> >::iterator it = _parse.begin();
	while (it != _parse.end()) {
		if (it->second == "\r\n" || it->second == "\n") {
			it->first = CRLF;
			break;
		}
		if (it->second == ":") {
			it->first = COLON;
			it++;
			for (; it->second != " "; it++)
				it->first = PREFIX;
			it->first = SPACE;
			it++;
		}
		if (it->second == "PASS")
			it->first = PASS_;
		else if (it->second == "NICK")
			it->first = NICK_;
		else if (it->second == "USER")
			it->first = USER_;
		else if (it->second == "QUIT")
			it->first = QUIT_;
		else if (it->second == "JOIN")
			it->first = JOIN_;
		else if (it->second == "KICK")
			it->first = KICK_;
		else if (it->second == "PART")
			it->first = PART_;
		else if (it->second == "NAMES")
			it->first = NAMES_;
		else if (it->second == "PRIVMSG")
			it->first = PRIVMSG_;
		it++;
		for (; it->second != "\r\n" && it->second != "\n"; it++)
			it->first = PARAMS;
		it->first = CRLF;
		it++;
	}
}

void EventHandler::paramsF() {
	std::vector<std::pair<int, std::string> >::iterator it = _parse.begin();
	while (it != _parse.end() && it->first != PARAMS)
		it++;
	if (it == _parse.end())
		return;
	it->first = SPACE;
	it++;
	if (it->second == ":") {
		it->first = COLON;
		it++;
		for (; it->first != CRLF; it++)
			it->first = TRAILING;
	} else {
		it->first = MIDDLE;
		paramsF();
	}
}

void EventHandler::sendMessage(std::string msg) {
	for (std::set<int>::iterator it = _fdTo.begin();
			it != _fdTo.end(); it++) {
		std::map<int, FileDescriptor>::iterator fdit = _fdList.find(*it);
		if (fdit == _fdList.end())
			break; // error
		fdit->second.addSendMsg(msg);
	}
}

// void EventHandler::printParse() {
// 	for (std::vector<std::pair<int, std::string> >::iterator it = _parse.begin(); it != _parse.end(); it++) {
// 		switch (it->first) {
// 			case MESSAGE:
// 				std::cout << "MESSAGE : ";
// 				break;
// 			case PREFIX:
// 				std::cout << "PREFIX : ";
// 				break;
// 			case COMMAND:
// 				std::cout << "COMMAND : ";
// 				break;
// 			case SPACE:
// 				std::cout << "SPACE : ";
// 				break;
// 			case PARAMS:
// 				std::cout << "PARAMS : ";
// 				break;
// 			case MIDDLE:
// 				std::cout << "MIDDLE : ";
// 				break;
// 			case TRAILING:
// 				std::cout << "TRAILING : ";
// 				break;
// 			case CRLF:
// 				std::cout << "CRLF : ";
// 				break;
// 			case PASS_:
// 				std::cout << "PASS_ : ";
// 				break;
// 			case NICK_:
// 				std::cout << "NICK_ : ";
// 				break;
// 			case USER_:
// 				std::cout << "USER_ : ";
// 				break;
// 			case QUIT_:
// 				std::cout << "QUIT_ : ";
// 				break;
// 			case JOIN_:
// 				std::cout << "JOIN_ : ";
// 				break;
// 			case KICK_:
// 				std::cout << "KICK_ : ";
// 				break;
// 			case PART_:
// 				std::cout << "PART_ : ";
// 				break;
// 			case NAMES_:
// 				std::cout << "NAMES_ : ";
// 				break;
// 			case PRIVMSG_:
// 				std::cout << "PRIVMSG_ : ";
// 				break;
// 		}
// 		std::cout << "\"" << it->second << "\"";
// 		for (std::size_t i = 0; i < it->second.size(); i++) {
// 			if (!std::isprint(it->second[i]) || static_cast<char>(it->second[i]) == ' ')
// 				std::cout << " " << static_cast<int>(it->second[i]);
// 		}
// 		std::cout << std::endl;
// 	}
// }
