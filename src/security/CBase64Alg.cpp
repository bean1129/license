#include "CBase64Alg.h"
#include "base64.h"
#include "../lic_def.hpp"
#include <string>
#include <string.h>


CBase64Alg::CBase64Alg()
{

}


CBase64Alg::~CBase64Alg()
{

}

int CBase64Alg::encode(void *str, int str_len, char *encode, int encode_len)
{
    /*BIO *bmem,*b64;
    BUF_MEM *bptr;
    b64=BIO_new(BIO_f_base64());
    bmem=BIO_new(BIO_s_mem());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    b64=BIO_push(b64,bmem);
    BIO_write(b64,str,str_len); //encode
    BIO_flush(b64);
    BIO_get_mem_ptr(b64,&bptr);
    if(bptr->length > (size_t)encode_len)
    {
        return ERR_CHAR_LEN_SHORT; 
    }   
    encode_len=bptr->length;
    memcpy(encode,bptr->data,bptr->length);
    BIO_free_all(b64);
    return encode_len;*/
    std::string sOutput = "";
    CBase64 cBase64Tool;
    cBase64Tool.base64Encode((const char*)str, str_len, sOutput);

    if (sOutput.length() + 1 > encode_len)
    {
        return ERR_CHAR_LEN_SHORT; 
    }
    else 
    {
        memcpy(encode, sOutput.c_str(), sOutput.length());
    }

    return sOutput.length();
}

int CBase64Alg::decode(char *str, int str_len, void *decode, int decode_len)
{
    /*int len=0;
    if (decode_len < str_len)
    {
        return ERR_CHAR_LEN_SHORT;
    }
    BIO *b64,*bmem;
    b64=BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bmem=BIO_new_mem_buf(str,str_len);
    bmem=BIO_push(b64,bmem);
    len=BIO_read(bmem,decode,str_len);
    BIO_free_all(b64);
    return len;*/

    if (decode_len < str_len)
    {
        return ERR_CHAR_LEN_SHORT;
    }

    CBase64 cBase64Tool;
    std::string sCodeStr = str;
    std::size_t tLen = decode_len;
    cBase64Tool.base64Decode(sCodeStr, (unsigned char *)decode, tLen);
    return tLen;
}

