#include "Bot.hpp"

Bot::Bot(std::string msg, std::string& port)
: _msg(msg), _port(port)
{}
// Bot::Bot(const Bot& obj) {(void)obj;}
Bot::~Bot() {}
// Bot& Bot::operator=(const Bot& obj) {(void)obj; return *this;}

std::vector<std::string> Bot::process() {
	int ret = checkCmd();
	switch (ret) {
		case HELP:
			return help();
			break;
		case INFO:
			return info();
			break;
		case JUMMECHU:
			return jummechu();
			break;
		default:
			return std::vector<std::string>();
			break;
	}
}

int Bot::checkCmd() {
	if (_msg.empty()) return NOTCMD;
	else if (_msg[0] != '@') return NOTCMD;

	std::size_t pos = _msg.find(' ');
	_cmd = _msg.substr(1, pos);
	_msg.erase(_msg.begin(), _msg.begin() + pos);
	while (_msg[0] == ' ')
		_msg.erase(_msg.begin(), _msg.begin() + 1);

	pos = _msg.find(' ');
	_arg = _msg.substr(0, pos);

	if (_cmd == "help") return HELP;
	else if (_cmd == "info") return INFO;
	else if (_cmd == "jummechu") return JUMMECHU;
	return NOTCMD;
}

std::vector<std::string> Bot::help() {
	std::vector<std::string> res;
	res.push_back("help : show command list");
	res.push_back("info : show server ip and port number");
	res.push_back("jummechu : recommend launch menu");
	return res;
}

std::vector<std::string> Bot::info() {
	char host[256];
	std::string IP;
	struct hostent *hostEntry;
	int hostname;
	std::vector<std::string> res;

	hostname = gethostname(host, sizeof(host)); //find the host name
	if (hostname == -1) {
		res.push_back("hostname error");
		return res;
	}
	hostEntry = gethostbyname(host); //find host information
	if (!hostEntry) {
		res.push_back("HostIp error");
		return res;
	}
	IP = inet_ntoa(*((struct in_addr*) hostEntry->h_addr_list[0]));
	res.push_back(host);
	res.push_back("BusChat.net");
	res.push_back(IP);
	res.push_back(_port);
	return res;
}

std::vector<std::string> Bot::jummechu() {
	std::vector<std::string> res;
	std::string menu[10];
	menu[0] = "중국집";
	menu[1] = "쌀국수";
	menu[2] = "피자";
	menu[3] = "치킨";
	menu[4] = "햄버거";
	menu[5] = "삼겹살";
	menu[6] = "덮밥";
	menu[7] = "돈까스";
	menu[8] = "떡볶이";
	menu[9] = "굶기";
	srand(time(NULL));
	int target = rand() % 10;
	res.push_back(menu[target]);
	return res;
}
