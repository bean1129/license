#include "CMd5Alg.h"
#include "md5base.h"
#include "../lic_def.hpp"
#include <stdio.h>
#include <string.h>


CMd5Alg::CMd5Alg()
{

}

CMd5Alg::~CMd5Alg()
{

}

char* CMd5Alg::MD5(const char* pOrigTxt, char* pMdTxt)
{
    //ASSERT_PRT_NULL(pOrigTxt);
    //ASSERT_PRT_NULL(pMdTxt);

    char szTmpChar[3] = {0};
    unsigned char outmd[MD5_BIN_LEN] ={0};
    //::MD5((const unsigned char*)pOrigTxt, strlen(pOrigTxt), outmd);
    CMd5 cMd5Tool;
    cMd5Tool.md5Enc(pOrigTxt, "", pMdTxt);
    /*md5_context tMd5Ctx;
    cMd5Tool.md5_starts(&tMd5Ctx);
    cMd5Tool.md5_update(&tMd5Ctx, (unsigned char*)pOrigTxt, strlen(pOrigTxt));
    cMd5Tool.md5_finish(&tMd5Ctx, outmd);

    for(int i = 0; i < MD5_BIN_LEN; i++)
    {
        sprintf(szTmpChar, "%02X", outmd[i]);
        strcat(pMdTxt, szTmpChar);
    }*/

    return pMdTxt;
}

char* CMd5Alg::MD5Token(const char* pFId, const char* pPasswd, char* pMdTxt)
{
    //ASSERT_PRT_NULL(pFId);
    //ASSERT_PRT_NULL(pPasswd);
    //ASSERT_PRT_NULL(pMdTxt);

    char szTmpChar[3] = {0};
    unsigned char outmd[MD5_BIN_LEN] ={0};
    char inorgitxt[UUID_LEN+PWD_LEN+UUID_LEN] = {0};
    sprintf(inorgitxt, "%s%s%s", pFId, pPasswd, pFId);
    //::MD5((unsigned char*)inorgitxt, strlen(inorgitxt), outmd);
    CMd5 cMd5Tool;
    cMd5Tool.md5Enc(inorgitxt, "", pMdTxt);
    /*md5_context tMd5Ctx;
    cMd5Tool.md5_starts(&tMd5Ctx);
    cMd5Tool.md5_update(&tMd5Ctx, (unsigned char*)inorgitxt, strlen(inorgitxt));
    cMd5Tool.md5_finish(&tMd5Ctx, outmd);

    for(int i = 0; i < MD5_BIN_LEN; i++)
    {
        sprintf(szTmpChar, "%02X", outmd[i]);
        strcat(pMdTxt, szTmpChar);
    }*/

    return pMdTxt;
}

int CMd5Alg::cmpToken(const char* pMdTxt, const char* pFId, const char* pPasswd)
{
    char szCmpMd5[MD5_CHR_LEN + 1] = {0};
    return strcmp(pMdTxt, MD5Token(pFId, pPasswd, szCmpMd5));
}



