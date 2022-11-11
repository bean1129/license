/*
 * license_imple.cpp
 *
 *  Created on: 2022年11月1日
 *      Author: biny
 */

#ifndef LICENSE_IMPLEMENT_HPP_
#define LICENSE_IMPLEMENT_HPP_

#include <vector>
#include <set>
#include <sstream>
#include "tinyxml/tinyxml.h"
#include "lic_def.hpp"

namespace lic{

using namespace std;

class LicImplement
{
public:
	LicImplement();

	~LicImplement();

	bool Verify(const char* pApp,const char*pLicPath);

	bool Create(const string& sFileName);

	inline const char* GetError()const {
		return m_errMsg.desc;

	}

	inline const char* GetTitle()const {
		return m_iInitFlag==true?m_sTitle.c_str():"";
	}

	inline const char* GetAbout()const {
		return m_iInitFlag==true?m_sAbout.c_str():"";
	}

	inline const char* GetMark()const {
		return m_iInitFlag==true?m_sImage.c_str():"";
	}

	inline const char* GetModules()const {
		return m_iInitFlag==true?m_sModule.c_str():"";
	}

private:

	int CheckAuthAlter(const string &sCompany,
			   const string &sMac,
			   const string &sIp,
			   const string &sExpiryDate,
			   const char* szAuthMD5);

	int CheckAlter(const vector<string>& VecVal,const char* szMD5);


	int Create(const string &sCompany,
			   const string &sMac,
			   const string &sIp,
			   const string &sExpiryDate,
			   const vector<string>& vecCert,
			   const vector<string>& vecInfo,
			   const vector<string>& vecServ,
			   const vector<string>& vecUser,
			   char* szCertMD5,
			   char* szAuthMD5,
			   char* szInfoMD5,
			   char* szServMD5,
			   char* szUserMD5);

	char* Sign(const string &sCompany,
               const string &sMac,
               const string &sIp,
               const string &sExpiryDate,
               char* szMD5);

	char* Sign(const vector<string>& vecParam,char* szMD5);

	int CheckComponent(const string& sMac, const string& sIp,const string& sExpireDate);

	void CacheWater(const char* pType,const char* pData,int iLength);

	void CacheModule(const vector<string>& vecModule);

	int GetElementKV(TiXmlNode* nodeChild,const char* pKey,const char* pVal,
			vector<string>& vecVal);

private:
	string& AllReplace(string & str,const string & oldstr,const string & newstr);

    template<class T>
    std::string toString(const T &t) {
        ostringstream oss;
        oss << t;
        return oss.str();
    }

    string GetCurDate(int n = 0);

    int GetDecodeLicFile(const string& sSrcFile,const string& sDestFile);


private:
	bool   		m_iInitFlag;
	string      m_sScopeType;//GV,TV,CV
	string 		m_sTitle;
	string 		m_sAbout;
	string      m_sModule;
	string      m_sImage;//水印图片,前四位表示大小

	ErrorType 	m_errMsg;
};

}


#endif /* LICENSE_IMPLEMENT_HPP_ */



