#include <iostream>
#include "reinterpret.h"
int main(int argc, char**)
{
	float a = float(-1.70318e+038);
	int x = aw::reinterpret<int>(a);
	std::cout << std::hex << x << std::endl;
	return x;
}
