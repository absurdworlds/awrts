#include <iostream>
#include <cstdlib>


int main()
{
	std::string str1;
	std::string str2;
	std::string str3;

	while (std::cin >> str1 >> str2 >> str3) {
		uint16_t x = strtoul(str1.c_str(), 0, 16) & 0xFFFF;
		uint16_t y = strtoul(str2.c_str(), 0, 16) & 0xFFFF;
		uint16_t z = strtoul(str3.c_str(), 0, 16) & 0xFFFF;
		x = ((x & 0xFF) << 8) | (x >> 8);
		y = ((y & 0xFF) << 8) | (y >> 8);
		z = ((z & 0xFF) << 8) | (z >> 8);
		//short xa = (x & 0x7FFF) * ((x & 0x8000) ? -1 : 1);
		//short ya = (y & 0x7FFF) * ((y & 0x8000) ? -1 : 1);
		//short za = (z & 0x7FFF) * ((z & 0x8000) ? -1 : 1);
		std::cout << std::hex << x << ", " << y << ", " << z << std::endl;
		//std::cout << xa << ", " << ya << ", " << za << std::endl;
		float xx = *reinterpret_cast<int16_t*>(&x);
		float yy = *reinterpret_cast<int16_t*>(&y);
		float zz = *reinterpret_cast<int16_t*>(&z);
		//float xx = xa;
		//float yy = ya;
		//float zz = za;
		xx /= 0x200;
		yy /= 0x200;
		zz /= 0x200;
		std::cout << xx << ", " << yy << ", " << zz << std::endl;
	}
}
