#include "StringHandle.hpp"

bool isAllDigit(std::string str) {
	for (std::size_t i = 0; i < str.size(); i++) {
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

std::string joinString(std::size_t num, ...) {
	va_list ap;
	va_start(ap, num);
	std::string res;
	for (std::size_t i = 0; i < num; i++)
		res.append(va_arg(ap, char*));
	va_end(ap);
	return res;
}
