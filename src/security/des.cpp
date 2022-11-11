
/****************************************************************
*
*Copyright (c) 2010,������Դ�Ͽ���Ϣ�����ɷ����޹�˾�з�һ��
*All rights reserved.
*
*�ļ�����: des.h
*�ļ���ʶ: �μ����ù���
*ժ    Ҫ: des����ͽ���
*
*��ǰ�汾: 1.0
*��    �ߣ�taozj
*���ʱ��: 2010��3��20��
*
******************************************************************/
#include "des.h"
#include "McbDESImpl.hpp"
#include <stdio.h>


CSimpDes::CSimpDes()
{
	
}

CSimpDes::~CSimpDes()
{
	
}

int CSimpDes::strDesEncrpt(const char *_s_in, const char *_key, char *_s_out)
{
	int s_len_offset,s_len_left;
	char s_temp[17],s_temp_enc[25];
	string str_enc_out;
	int dest_len;

	s_len_left = strlen(_s_in);
	s_len_offset=0;

	char *fill_s_in;
	fill_s_in= new char[s_len_left+8];

	memset(fill_s_in, 0, sizeof(fill_s_in));
	strcpy(fill_s_in, _s_in);

	int	l_div = s_len_left%8;
	if (l_div>0)
	{
		int i = 0;
		for ( i=0; i<(8-l_div); i++)
		{
			fill_s_in[s_len_left+i]=0x06;
		}

		fill_s_in[s_len_left+i] = '\0';
	}
	//end

	if (_s_out)
	{
		memset(_s_out, 0, strlen(_s_out));
	}

	while(s_len_left >0)
	{
		memset(s_temp,0,sizeof(s_temp));
		memset(s_temp_enc,0,sizeof(s_temp_enc));

		dest_len = strlen(fill_s_in+s_len_offset);

		if(dest_len >= 8)
			dest_len = 8;

		strncpy(s_temp,fill_s_in+s_len_offset,dest_len);

		desEncrypt(s_temp, (char*)_key, str_enc_out);
		strncpy(s_temp_enc,str_enc_out.c_str(),12);
		s_temp_enc[12]='\0';

		strcat(_s_out,s_temp_enc);

		s_len_left -= 8;
		s_len_offset += 8;
	}

	delete []fill_s_in;
	fill_s_in = NULL;

	return 0;	
}


int CSimpDes::strDesDecrpt(const char *_s_in, const char *_key,char *_s_out)
{
	int s_len_offset,s_len_left;
	char s_temp[25],s_temp_desc[17];
	string str_enc_out;

	s_len_left = strlen(_s_in);
	s_len_offset=0;

	if (_s_out)
	{
		memset(_s_out, 0, strlen(_s_out));
	}


	if (s_len_left%12 != 0)
	{
		return -1;
	}

	while(s_len_left >0)
	{
		memset(s_temp,0,sizeof(s_temp));
		memset(s_temp_desc,0,sizeof(s_temp_desc));

		strncpy(s_temp,_s_in+s_len_offset,12);
		s_temp[12] = '\0';

		if (s_temp[11] != '=')
		{
			memset(_s_out, 0, sizeof(_s_out));

			return -1;
		}

		str_enc_out = s_temp;
		desDescrypt(str_enc_out,(char*)_key,s_temp_desc);

		strcat(_s_out,s_temp_desc);

		s_len_left -= 12;
		s_len_offset += 12;
	}

	for (int i=0; i<strlen(_s_out); i++)
	{
		if (_s_out[i] == 0x06)
		{
			_s_out[i]='\0';
			break;
		}
	}

	return 0;
}


int CSimpDes::desEncrypt(char *ori_pwd, char *key, std::string& output)
{
	std::basic_string<char> strCryptogram;
	strCryptogram = encrypt_des(ori_pwd,key);

	//for encode
	string s_out;
	char in_base64[9];
	s_out.erase();

    memset(in_base64, 0, sizeof(in_base64));
	memcpy(in_base64, strCryptogram.c_str(), 8);
	in_base64[8]='\0';

	Cbase64.base64Encode((char *)in_base64,8,s_out);

	output = s_out;

	return 0;	
}
		
int CSimpDes::desDescrypt(const std::string& input, char *key, char *ori_pwd)
{
	  std::basic_string<char> strCryptogram_out;
	  unsigned char base64_out[9];
	  char s_ori_pwd[9];
	  //unsigned long out_size = 0;
      size_t out_size = 0;

	  memset(base64_out,0,sizeof(base64_out));
      Cbase64.base64Decode(input,base64_out,out_size);
      base64_out[8] = '\0';

      strCryptogram_out.resize(9);
      memcpy((void*)strCryptogram_out.data(),base64_out,8);

      decrypt_des(strCryptogram_out,key,s_ori_pwd);
      s_ori_pwd[8] = '\0';

      memcpy(ori_pwd,s_ori_pwd,8);
	
	return 0;	
}
		



