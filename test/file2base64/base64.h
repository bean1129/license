#ifndef __BASE64_H
#define __BASE64_H

#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

class CBase64
{
	public:		
		void base64Encode(const char* input, size_t len, std::string& output);
		void base64Decode(const std::string& input, unsigned char *output, size_t& sz);
			
	public:
		CBase64();
		~CBase64();
};


#endif
