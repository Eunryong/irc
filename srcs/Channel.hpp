#ifndef __CHANNEL_HPP__
#define __CHANNEL_HPP__

#include <map>
#include <string>

#include "FileDescriptor.hpp"

class FileDescriptor;

class Channel {
	public:
		Channel(std::string channelName, std::map<int, FileDescriptor>& fds);
		Channel(const Channel& obj);
		~Channel();
		Channel& operator=(const Channel& obj);

		bool join(int fd);
		bool isInChannel(int fd);
		void leave(int fd);
		void setOper(int fd);

		std::vector<int> getList();
		std::vector<std::string> getNick();
		std::string getChannelName() const;
		int getOper() const;

	private:
		std::string _channelName;
		std::map<int, FileDescriptor> _connectList;

		std::map<int, FileDescriptor>& _fds;
		int _operFd;
};

#endif
