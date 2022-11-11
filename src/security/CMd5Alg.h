#ifndef __CMD5ALG_H__
#define __CMD5ALG_H__

class CMd5Alg
{
public:
    CMd5Alg();
    ~CMd5Alg();

public:
    /**
	* @Title: ��ԭ�ļ���MD5ժҪ
	* @Description:��ԭ�ļ���MD5ժҪ
	* @param const char* pOrigTxt ԭ��
	* @param const char* pMdTxt ժҪ, �������ĳ���Ҫ����32���ַ�
	* @return char* ����ժҪ
	* @throw NULL
	*/
    char* MD5(const char* pOrigTxt, char* pMdTxt);

    /**
	* @Title: ��ԭ�ļ���MD5ժҪ
	* @Description:��ԭ�ļ���MD5ժҪ
	* @param const char* pFId �豸ID
	* @param const char* pPasswd �豸����
	* @param const char* pMdTxt ժҪ
	* @return char* ����ժҪ
	* @throw NULL
	*/
    char* MD5Token(const char* pFId, const char* pPasswd, char* pMdTxt);

    /**
	* @Title: �豸����MD5У��
	* @Description:�豸����MD5У��
	* @param const char* pMdTxt ժҪ
	* @param const char* pFId �豸ID
	* @param const char* pPasswd �豸����
	* @return int 0-��ʾƥ�䣬��0��ʾ��ƥ��
	* @throw NULL
	*/
    int cmpToken(const char* pMdTxt, const char* pFId, const char* pPasswd);
};



#endif // end of define __CMD5ALG_H__

