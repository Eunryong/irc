#include "Channel.hpp"

Channel::Channel(std::string channelName, std::map<int, FileDescriptor>& fds)
: _channelName(channelName), _fds(fds)
{}
Channel::Channel(const Channel& obj)
: _channelName(obj._channelName), _connectList(obj._connectList), _fds(obj._fds)
{}
Channel::~Channel() {}
Channel& Channel::operator=(const Channel& obj) {
	_channelName = obj._channelName;
	_connectList = obj._connectList;
	_fds = obj._fds;
	return *this;
}

bool Channel::join(int fd) {
	_connectList.insert(std::pair<int, FileDescriptor>(_fds.find(fd)->first, _fds.find(fd)->second));
	_fds.find(fd)->second.joinChannel(*this);
	return true;
}

bool Channel::isInChannel(int fd) {
	std::map<int, FileDescriptor>::iterator it;
	it = _connectList.find(fd);
	if (it == _connectList.end())
		return false;
	return true;
}

void Channel::leave(int fd) {
	std::map<int, FileDescriptor>::iterator it;
	it = _connectList.find(fd);
	if (it == _connectList.end())
		return;
	if (_operFd == fd)
		_operFd = -1;
	_connectList.erase(it);
	_fds.find(fd)->second.partChannel(_channelName);
}

std::vector<int> Channel::getList() {
	std::vector<int> res;
	std::map<int, FileDescriptor>::iterator it = _connectList.begin();
	for (; it != _connectList.end(); it++)
		res.push_back(it->first);
	return res;
}
std::vector<std::string> Channel::getNick() {
	std::vector<std::string> res;
	std::map<int, FileDescriptor>::iterator it = _connectList.begin();
	for (; it != _connectList.end(); it++)
		res.push_back(it->second.getNick());
	return res;
}

std::string Channel::getChannelName() const {
	return _channelName;
}

int Channel::getOper() const {
	return _operFd;
}

void	Channel::setOper(int fd)	{
	_operFd = fd;
}
