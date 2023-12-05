#include "Server.hpp"

int main(int ac, char **av)
{
	Server ser(ac, av);
	ser.start();
}
