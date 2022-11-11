
/****************************************************************
*
*Copyright (c) 2010,������Դ�Ͽ���Ϣ�����ɷ����޹�˾�з�һ��
*All rights reserved.
*
*�ļ�����: md5.h
*�ļ���ʶ: �μ����ù���
*ժ    Ҫ: basr64����ͽ���
*
*��ǰ�汾: 1.0
*��    �ߣ�taozj
*���ʱ��: 2010��3��20��
*
******************************************************************/

#ifndef _MD5BASE_H
#define _MD5BASE_H

#include <stdio.h>
#include <stdlib.h>

#ifndef uint8
#define uint8  unsigned char
#endif

#ifndef uint32
#define uint32 unsigned long int
#endif

typedef struct
{
    uint32 total[2];
    uint32 state[4];
    uint8 buffer[64];
}md5_context;

class CMd5
{
	public:		
	/*�ⲿ���ýӿ�
	szSrcΪ��Ҫ����MD5���ܵ��ַ�������0��β��
	szDestΪ�Ѿ�������ڴ���ַ������������������ַ����У�
	�ַ�������Ϊ32����0��β��Ҳ����˵szDest����ҪԤ�ȷ���33���ֽڳ��ȡ�
	*/
	void md5Enc(const char* szSrc, const char *szKey, char* szDest);
			
	public:
		CMd5();
		~CMd5();
		
	private:
		void md5_starts( md5_context *ctx );
		void md5_update( md5_context *ctx, uint8 *input, uint32 length );
		void md5_finish( md5_context *ctx, uint8 digest[16] );	
	private:	
		void md5_process( md5_context *ctx, uint8 data[64]);
		
};



 
#endif



