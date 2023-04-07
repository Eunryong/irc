/*
_fd : client 의 fd 값
_nick : client 의 닉네임
_name : client 의 real name
_hostname : client 의 호스트 이름
_channel : client 가 join 해 있는 채널들, 채널이름, 채널에서의 operator 여부를 pair 로 저장
_channelNow : client 가 현재 채팅중인(활성화된) 채널, _channel 에서 포인터로 받아와 저장

joinChannel() : 인자로 들어온 채널을 _channel 에 push back
partChannel() : 인자로 들어온 채널을 _channel 에서 찾아 erase
*/

#ifndef __FILEDESCRIPTOR_HPP__
#define __FILEDESCRIPTOR_HPP__

#include <iostream>
#include <string>
#include <vector>

#include "Channel.hpp"

#define ISOPER bool
#define SucNick 0
#define SucPass 1
#define SucUser 2
#define Welcome 3

class Channel;

class FileDescriptor {
	public:
		FileDescriptor(int fd = -1, std::string nick = "",
						std::string name = "", std::string hostname = "");
		~FileDescriptor();

		FileDescriptor(const FileDescriptor& other);
		FileDescriptor& operator= (const FileDescriptor& other);

	public:
		const int& getFd() const;
		const std::string& getNick() const;
		const std::string& getUser() const;
		const std::string& getHostname() const;
		const std::vector<Channel>& getChannel() const;

		// init connection
		bool isConnection() const;
		bool isSuccessNick() const;
		bool isSuccessPass() const;
		bool isSuccessUser() const;
		bool getWelcome() const;
		// const std::pair<Channel, ISOPER>* getChannelNow() const;

		void setFd(int fd);
		void setNick(std::string nick);
		void setName(std::string name);
		void setHostname(std::string hostname);

		// init connection
		void successNick();
		void successPass();
		void successUser();
		void setWelcome();
		// void setChannelNow(std::pair<Channel, ISOPER>* now);

		void joinChannel(Channel channel);
		void partChannel(std::string channelName);

		const std::string& getSendMsg() const;
		void addSendMsg(std::string msg);
		void clearSendMsg();

	private:
		int _fd;
		std::string _nick;
		std::string _name;
		std::string _hostname;
		std::vector<Channel> _channel;
		std::string _sendMsg;

		// init connection
		bool _isConnected[4];
};

#endif
