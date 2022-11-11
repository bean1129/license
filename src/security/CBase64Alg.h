#ifndef __CBASE64ALG_H__
#define __CBASE64ALG_H__

class CBase64Alg
{
public:
    CBase64Alg();
    ~CBase64Alg();

public:
     /**
	* @Title: ����base64�ı���
	* @Description:���ڴ�����תΪ�ַ�����
	* @param void* str ԭ��
	* @param int str_len ԭ�ĳ���
	* @param char *encode ����
	* @param int encode_len ���ĳ��ȿռ�
	* @return int ���ؼӱ��볤��
	* @throw NULL
	*/
    int encode(void *str, int str_len, char *encode, int encode_len);

    /**
	* @Title: ����base64�Ľ���
	* @Description:���ַ�תΪ�ڴ����ݱ���
	* @param char* str ����
	* @param int str_len ���ĳ���
	* @param char *decode ԭ��
	* @param int decode_len ԭ�ĳ��ȿռ�
	* @return int ���ؼӱ��볤��
	* @throw NULL
	*/
    int decode(char *str, int str_len, void *decode, int decode_len);
     
};


#endif // end of define __CBASE64ALG_H__

