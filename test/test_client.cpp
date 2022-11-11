/*
 * test_client.cpp
 *
 *  Created on: 2022年11月1日
 *      Author: biny
 */

#include <iostream>
#include "../license/lic_interface.hpp"

int main()
{
	std::cout << "sdk test start ..." << std::endl;
#if defined(_LINUX)
	if(Init("TEST_CLIENT","./") == 0){
		std::cout << GetError() << std::endl;
		return -1;
	}else{
		std::cout << "verify license file success. "<< std::endl;
	}
#elif defined(_WIN32)
	if(Init("TEST_CLIENT",".\\") == 0){
		std::cout << GetError() << std::endl;
		return -1;
	}else{
		std::cout << "verify license file success. "<< std::endl;
	}
#endif

	std::cout << "GetTitle : "    << GetTitle() << std::endl;
	std::cout << "GetAbout : "    << GetAbout() << std::endl;
	std::cout << "GetMark : "     << GetMark() << std::endl;
	std::cout << "GetModules : "  << GetModules() << std::endl;

	return 0;
}

