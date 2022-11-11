/*
 * lic_common.hpp
 *
 *  Created on: 2022年11月2日
 *      Author: biny
 */

#ifndef LICENSE_LIC_DEF_HPP_
#define LICENSE_LIC_DEF_HPP_
#include <iostream>

#if defined(_LINUX)

#ifdef __GNUG__
	#define NULL __null
#else
	#ifndef __cplusplus
		#define NULL ((void*)0)
	#else
		#define NULL 0
	#endif
#endif


#elif defined(_WIN32)

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif
#endif

struct ErrorType
{
    int code = 0;
    const char* desc = "";

    ErrorType(int cd, const char* dsc)
        :code(cd), desc(dsc)
    {
    }

    inline bool operator==(const ErrorType& et) const
    {
        return (code == et.code);
    }

    inline bool operator!=(const ErrorType& et) const
    {
        return (code != et.code);
    }

    inline ErrorType& operator=(const ErrorType& et)
    {
        code = et.code;
        desc = et.desc;

        return *this;
    }

};

enum ENUM_INIT_TYPE{
	ENUM_INIT_TYPE_NA = 0,
	ENUM_INIT_TYPE_Ver,
	ENUM_INIT_TYPE_Crt
};


extern const std::string XML_SCOPE_TYPE_GV ;
extern const std::string XML_SCOPE_TYPE_TV ;
extern  const std:: string XML_SCOPE_TYPE_CV ;


#define MAXINTERFACES 16

#define AUTH_NAME_LEN   128
#define AUTH_TOKEN_LEN  128

#define MD5_BIN_LEN     16
#define MD5_CHR_LEN     32
#define AUTH_PARAM_ID_LEN   2
#define SIGN_PARAM_ID_LEN   4
#define SIGN_ORIG_MAX_LEN   2048

#define DES_KEY_LEN     8
#define DES_CODE_LEN    8
#define FG_ENCODE_TYPE  1
#define FG_DECODE_TYPE  0
#define FG_CODE_LEN         1024
#define FG_KEY_ENCODE_LEN   12

#define UUID_LEN    64
#define CODE_LEN    64
#define PWD_LEN     96
#define MAC_LEN     24
#define MAIL_LEN    129
#define TEL_LEN     21
#define ADDR_LEN    513
#define LISENCE_LEN 257

// 变量异常错误范围: -60000~-69999
#define ERR_POINTER_NULL                -60000
#define ERR_ALLOC_EXP                   -60001
#define ERR_NO_INIT                     -60002
#define ERR_CHAR_LEN_SHORT              -60003
#define ERR_TIME_FMT_ERROR              -60004
#define ERR_TIME_TYPE_ERROR             -60005
#define ERR_TIME_NOT_ENOUGH             -60006
#define ERR_MAP_NO_FIND                 -60100
#define ERR_ENUM_VAL_INVAILD            -60200
#define ERR_ENV_NOT_EXIST               -61000
#define ERR_PARAM_INVAILD               -62000
#define ERR_DATAFORMAT_ERROR            -63000

extern ErrorType ERR_OK;
extern ErrorType ERR_FAIL;
extern ErrorType ERR_FATAL;
extern ErrorType ERR_UNDEFINED;
extern ErrorType ERR_EFFECTIVE_DATE;
extern ErrorType ERR_PARASE_XML_FAILED;
extern ErrorType ERR_INVAILD_XML_NODE;
extern ErrorType ERR_INVAILD_XML_COMPEONENT;
extern ErrorType ERR_INVAILD_XML_SIGNATURE;
extern ErrorType ERR_LICNESE_HAVE_ALTERED;
extern ErrorType ERR_LICENSE_NOT_ALLOEWD;
extern ErrorType ERR_SOCKET_INIT_FAILED;
extern ErrorType ERR_SOCKET_SIOCGIFCONF_FAILED ;
extern ErrorType ERR_SOCKET_SIOCGIFADDR_FAILED  ;
extern ErrorType ERR_SOCKET_SIOCGIFHWADDR_FAILED;
extern ErrorType ERR_AUTH_EXPIREDATE          ;
extern ErrorType ERR_INVAILD_MAC_IP             ;
extern ErrorType ERR_LIC_SDK_INIT_CFG_PATH      ;
extern ErrorType ERR_INVAILD_XML_SERVER         ;
extern ErrorType ERR_INVAILD_XML_USER           ;
extern ErrorType ERR_CRT_SIGN_FAILED            ;
extern ErrorType ERR_INVAILD_XML_CERT_EFF       ;
extern ErrorType ERR_INVAILD_XML_SCOPE          ;
extern ErrorType ERR_AUTH_PROBATION 			;




#endif /* LICENSE_LIC_DEF_HPP_ */
