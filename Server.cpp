#include "Server.hpp"

Server::Server(int ac, char** av)
:_multiplex(_fdList) {
	_pass = _multiplex.init(ac, av);
}

Server::~Server() {
	for (std::map<int, FileDescriptor>::iterator it = _fdList.begin();
		it != _fdList.end(); it++)
		close(it->first);
}

void Server::start() {
	while (1) {
		recvData res = _multiplex.sequence();
		if (res.fdFrom == -1 && res.msg == "") { // error
			continue; // do nothing
		} else if (res.msg == "\3") { // disconnect
			closeClient(res.fdFrom);
			deleteBuffer();
			continue;
		} else if (res.msg == "") { // connect or write
			continue;
		} // else get msg

		// search fdFrom in data
		std::vector<recvData>::iterator it;
		for (it = _recvBuffer.begin(); it != _recvBuffer.end(); it++) {
			if (it->fdFrom == res.fdFrom) {
				it->msg.append(res.msg);
				break;
			}
		}
		// if not exist, add new
		if (it == _recvBuffer.end()) {
			_recvBuffer.push_back(res);
			it = _recvBuffer.begin();
			it += _recvBuffer.size() - 1;
		}
		// if msg end with \n or \r\n, start process and delete
		if (it->msg[it->msg.size() - 1] == '\n') {
			EventHandler ev(*it, _fdList, _channelList, _pass);
			_recvBuffer.erase(it);
		}

		// if fd not exist, erase recvData
		deleteBuffer();
	}
}

void Server::closeClient(int fd) {
	std::cout << "client disconnected: " << fd << std::endl;
	std::map<int, FileDescriptor>::iterator it = _fdList.find(fd);
	for (std::map<std::string, Channel>::iterator channelIter = _channelList.begin();
			channelIter != _channelList.end(); channelIter++)
		channelIter->second.leave(fd);
	if (it == _fdList.end())
		return ;
	_fdList.erase(it);
	close(fd);
}

void Server::deleteBuffer() {
	for (std::vector<recvData>::iterator it = _recvBuffer.begin();
			it != _recvBuffer.end(); it++) {
		if (_fdList.find(it->fdFrom) == _fdList.end()) {
			_recvBuffer.erase(it);
			return;
		}
	}
}
