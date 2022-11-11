
#ifndef __DES_H
#define __DES_H

#include "base64.h"

using namespace std;

class CSimpDes
{
	public:
		CSimpDes();
		~CSimpDes();

	public:
		int strDesEncrpt(const char *_s_in, const char *_key, char *_s_out);
		int strDesDecrpt(const char *_s_in, const char *_key, char *_s_out);

	private:
		int desEncrypt(char *ori_pwd, char *key, std::string& output);
		int desDescrypt(const std::string& input, char *key, char *ori_pwd);

	private:
		CBase64 Cbase64;
};


#endif
