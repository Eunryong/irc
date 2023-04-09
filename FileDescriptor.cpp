#include "FileDescriptor.hpp"

FileDescriptor::FileDescriptor(int fd, std::string nick,
	std::string name, std::string hostname)
: _fd(fd), _nick(nick), _name(name), _hostname(hostname), _sendMsg("") {
	for (int i = 0; i < 4; i++)
		_isConnected[i] = false;
}

FileDescriptor::FileDescriptor(const FileDescriptor& other)
: _fd(other._fd), _nick(other._nick), _name(other._name),
	_hostname(other._hostname), _channel(other._channel), _sendMsg(other._sendMsg) {
	for (int i = 0; i < 4; i++)
		_isConnected[i] = other._isConnected[i];
	}

FileDescriptor::~FileDescriptor()
{}

FileDescriptor& FileDescriptor::operator= (const FileDescriptor& other) {
	_fd = other._fd;
	_nick = other._nick;
	_name = other._name;
	_hostname = other._hostname;
	_channel = other._channel;
	for (int i = 0; i < 4; i++)
		_isConnected[i] = other._isConnected[i];
	_sendMsg = other._sendMsg;
	return *this;
}

// getter setter
const int& FileDescriptor::getFd() const {
	return _fd;
}
const std::string& FileDescriptor::getNick() const {
	return _nick;
}
const std::string& FileDescriptor::getUser() const {
	return _name;
}
const std::string& FileDescriptor::getHostname() const {
	return _hostname;
}
const std::vector<Channel>& FileDescriptor::getChannel() const {
	return _channel;
}
bool FileDescriptor::isConnection() const {
	for (int i = 0; i < 3; i++)
		if (!_isConnected[i])
			return false;
	return true;
}
bool FileDescriptor::isSuccessNick() const {
	return _isConnected[SucNick];
}
bool FileDescriptor::isSuccessPass() const {
	return _isConnected[SucPass];
}
bool FileDescriptor::isSuccessUser() const {
	return _isConnected[SucUser];
}
bool FileDescriptor::getWelcome() const {
	return _isConnected[Welcome];
}
void FileDescriptor::setFd(int fd) {
	_fd = fd;
}
void FileDescriptor::setNick(std::string nick) {
	_nick = nick;
}
void FileDescriptor::setName(std::string name) {
	_name = name;
}
void FileDescriptor::setHostname(std::string hostname) {
	_hostname = hostname;
}
void FileDescriptor::successNick() {
	_isConnected[SucNick] = true;
}
void FileDescriptor::successPass() {
	_isConnected[SucPass] = true;
}
void FileDescriptor::successUser() {
	_isConnected[SucUser] = true;
}
void FileDescriptor::setWelcome() {
	_isConnected[Welcome] = true;
}
// void FileDescriptor::setChannelNow(std::pair<Channel, ISOPER>* now) {
// 	_channelNow = now;
// }

// channel join, part
void FileDescriptor::joinChannel(Channel channel) {
	_channel.push_back(channel);
}

void FileDescriptor::partChannel(std::string channelName) {
	std::vector<Channel>::iterator it;
	for (it = _channel.begin(); it != _channel.end(); it++) {
		if (it->getChannelName() == channelName)
			break;
	}
	if (it == _channel.end())
		return ;
	_channel.erase(it);
}

const std::string& FileDescriptor::getSendMsg() const {
	return _sendMsg;
}
void FileDescriptor::addSendMsg(std::string msg) {
	_sendMsg.append(msg);
}
void FileDescriptor::clearSendMsg() {
	_sendMsg.clear();
}
