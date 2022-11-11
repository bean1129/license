
/*
* lic_implement.cpp
*
*  Created on: 2022年11月2日
*      Author: biny
*/
#include "security/CBase64Alg.h"
#include "security/CMd5Alg.h"
#include "security/des.h"
#include "security/md5base.h"

#if defined(_LINUX)
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#elif defined(_WIN32)
#include <Winsock2.h>
#include <Iphlpapi.h>
#include "dirent.hpp"
#pragma comment(lib,"Iphlpapi.lib")
#endif
#include "lic_implement.hpp"
#include <iostream>
#include <fstream>



using namespace lic;

LicImplement::LicImplement() :m_iInitFlag(false)
, m_errMsg(0, "")
, m_sTitle("")
, m_sAbout("")
, m_sModule("")
, m_sImage("")
, m_sScopeType("")

{

}

LicImplement::~LicImplement()
{

}

bool LicImplement::Verify(const char* pApp,const char* pLicPath){

	//解析证书进行认证
	int iRet = 0;
	m_errMsg = ERR_OK;
	string sLicenseInfoSign = "";
	string sLicenseServSign = "";
	string sLicenseUserSign = "";
	string sLicenseAuthSign = "";
	string sLicenseCertSign = "";
	string sLicensePath = "";
	string sFullLicenseFile = "";
	char *pCfgPath;
	m_iInitFlag = false;

	string sCompany = "";
	string sMac = "";
	string sIp = "";
	string sExpiryDate = "";
	string sEffective = "";
	vector<string> vecCert;
	vector<string> vecInfo;
	vector<string> vecServ;
	vector<string> vecUser;
	TiXmlElement* itemElement;


	do{
		string sDecodeFile = "";
	    DIR* pHandle = opendir(pLicPath);

	    if (NULL == pHandle)
	    {
	    	break;
	    }

	    string sRet = "";
	    bool m_bEof = false;
	    struct dirent*  pEntry;
	    if (!m_bEof)
	    {
	        while(pEntry = readdir(pHandle))
	        {

	            if (0 != strcmp(".", pEntry->d_name) && 0 != strcmp("..", pEntry->d_name))
	            {
	                sRet = pEntry->d_name;
	                if(sRet.find(pApp) != string::npos){
	                	sFullLicenseFile = pLicPath + string("/")+sRet;
		                break;
	                }
	            }
	        }

	        if (NULL == pEntry)
	        {
	            m_bEof = true;
	        }
	    }

        closedir(pHandle);
#if defined(_LINUX)
        //解密文件
        sDecodeFile = "./.tmp.lic";
#elif defined(_WIN32)
        sDecodeFile = ".\\.tmp.lic";
#endif

        GetDecodeLicFile(sFullLicenseFile,sDecodeFile);
		TiXmlDocument xCfgDoc(sDecodeFile.c_str());

		bool loadOkay = xCfgDoc.LoadFile();

		//删除临时文件
		remove(sDecodeFile.c_str());

		if (!loadOkay)
		{
			m_errMsg = ERR_PARASE_XML_FAILED;
			break;
		}

		TiXmlNode* node = xCfgDoc.FirstChild("ZOCLicense");

		m_sScopeType = node->ToElement()->Attribute("scope");
		if (m_sScopeType.empty()){
			m_errMsg = ERR_INVAILD_XML_SCOPE;
			break;
		}

		if (node == NULL)
		{
			m_errMsg = ERR_INVAILD_XML_NODE;
			break;
		}

		for (node = node->FirstChildElement(); node != NULL; node = node->NextSibling())
		{
			if (TiXmlNode::TINYXML_COMMENT == node->Type()) {
				continue;
			}
			itemElement = node->ToElement();
			const char *pLicenseScene = itemElement->Attribute("component");
			const char *pLicenseVal = itemElement->Attribute("signature");

			if (NULL == pLicenseScene)
			{
				m_errMsg = ERR_INVAILD_XML_COMPEONENT;
				break;
			}

			if (NULL == pLicenseVal)
			{
				m_errMsg = ERR_INVAILD_XML_SIGNATURE;
				break;
			}

			TiXmlNode* nodeChild = node;
			if (strcmp(pLicenseScene, "Auth") == 0) {
				sLicenseAuthSign = pLicenseVal;
				for (nodeChild = nodeChild->FirstChildElement(); nodeChild != NULL; nodeChild = nodeChild->NextSibling()) {
					itemElement = nodeChild->ToElement();
					pLicenseScene = itemElement->Attribute("component");
					pLicenseVal = itemElement->Attribute("value");
					if (0 == strcmp("Company", pLicenseScene))
					{
						sCompany = pLicenseVal;
					}
					else if (0 == strcmp("MAC", pLicenseScene))
					{
						sMac = pLicenseVal;
					}
					else if (0 == strcmp("Host", pLicenseScene))
					{
						sIp = pLicenseVal;
					}
					else if (0 == strcmp("Expiration", pLicenseScene))
					{
						sExpiryDate = pLicenseVal;
						sExpiryDate = AllReplace(sExpiryDate, "-", "") + "235959";
					}
				}
			}
			else if (strcmp(pLicenseScene, "Cert") == 0) {
				sLicenseCertSign = pLicenseVal;
				if (GetElementKV(nodeChild, "component", "value", vecCert)>0){
					break;
				}
				bool bEffect = false;
				for (int i = 0; i <vecCert.size(); i = i + 2){
					if ("Effective" == vecCert[i] && !vecCert[i + 1].empty()){
						bEffect = true;
					}
				}
				if (!bEffect){
					m_errMsg = ERR_INVAILD_XML_CERT_EFF;
					break;
				}
			}
			else if (strcmp(pLicenseScene, "Info") == 0) {
				sLicenseInfoSign = pLicenseVal;
				GetElementKV(nodeChild, "component", "value", vecInfo);
			}
			else if (strcmp(pLicenseScene, "Serv") == 0){
				sLicenseServSign = pLicenseVal;
				GetElementKV(nodeChild, "component", "desc", vecServ);
			}
			else if (strcmp(pLicenseScene, "User") == 0){
				sLicenseUserSign = pLicenseVal;
				GetElementKV(nodeChild, "component", "max", vecUser);
			}
			else{
				continue;
			}

			if (m_errMsg.code > 0)break;

		}

		if (m_errMsg.code > 0)break;


		if (CheckAuthAlter(sCompany, sMac, sIp, sExpiryDate, sLicenseAuthSign.c_str()) != 0
			|| CheckAlter(vecCert, sLicenseCertSign.c_str()) != 0
			|| CheckAlter(vecInfo, sLicenseInfoSign.c_str()) != 0
			|| CheckAlter(vecServ, sLicenseServSign.c_str()) != 0
			|| CheckAlter(vecUser, sLicenseUserSign.c_str()) != 0)
		{
			m_errMsg = ERR_LICNESE_HAVE_ALTERED;
			break;
		}


		// 文件未被撺改，需要校验各个参数的准确值
		std::cout << "check componet mac and ip" << std::endl;
		if (CheckComponent(sMac, sIp, sExpiryDate) == 0)
		{
			m_iInitFlag = true;
		}

	} while (false);


	return m_iInitFlag;
}

bool LicImplement::Create(const string& sFullLicenseFile)
{

	int m_iInitFlag = 0;
	int iRet = 0;
	string sLicensePath = "";


	do{

		TiXmlDocument xCfgDoc(sFullLicenseFile.c_str());

		bool loadOkay = xCfgDoc.LoadFile();

		if (!loadOkay)
		{
			m_errMsg = ERR_PARASE_XML_FAILED;
			printf("License file[%s],check env[LIC_SDK_INIT_CFG_PATH]\n", sFullLicenseFile.c_str());
			break;
		}

		char *szSign = NULL;

		string sCompany = "";
		string sMac = "";
		string sIp = "";
		string sExpiryDate = "";
		vector<string> vecValue;
		TiXmlElement* itemElement = NULL;

		TiXmlNode* node = xCfgDoc.FirstChild("ZOCLicense");

		if (node == NULL)
		{
			m_errMsg = ERR_INVAILD_XML_NODE;
			break;
		}

		for (node = node->FirstChildElement(); node != NULL; node = node->NextSibling())
		{

			if (TiXmlNode::TINYXML_COMMENT == node->Type()) {
				continue;
			}
			itemElement = node->ToElement();
			TiXmlElement* itemChildElement = NULL;
			const char *pLicenseScene = itemElement->Attribute("component");
			const char *pLicenseVal = itemElement->Attribute("signature");

			if (NULL == pLicenseScene)
			{
				m_errMsg = ERR_INVAILD_XML_COMPEONENT;
				break;
			}

			if (NULL == pLicenseVal)
			{
				m_errMsg = ERR_INVAILD_XML_SIGNATURE;
				break;
			}

			TiXmlNode* nodeChild = node;
			memset(szSign, 0, sizeof(szSign));
			vecValue.clear();
			if (strcmp(pLicenseScene, "Auth") == 0) {
				for (nodeChild = nodeChild->FirstChildElement(); nodeChild != NULL; nodeChild = nodeChild->NextSibling()) {
					itemChildElement = nodeChild->ToElement();
					pLicenseScene = itemChildElement->Attribute("component");
					pLicenseVal = itemChildElement->Attribute("value");
					if (0 == strcmp("Company", pLicenseScene))
					{
						sCompany = pLicenseVal;
					}
					else if (0 == strcmp("MAC", pLicenseScene))
					{
						sMac = pLicenseVal;
					}
					else if (0 == strcmp("Host", pLicenseScene))
					{
						sIp = pLicenseVal;
					}
					else if (0 == strcmp("Expiration", pLicenseScene))
					{
						sExpiryDate = pLicenseVal;
						sExpiryDate = AllReplace(sExpiryDate, "-", "") + "235959";
					}
				}

				Sign(sCompany, sMac, sIp, sExpiryDate, szSign);

			}
			else if (strcmp(pLicenseScene, "Cert") == 0) {
				if (GetElementKV(nodeChild, "component", "value", vecValue)>0){
					break;
				}
				Sign(vecValue, szSign);
			}
			else if (strcmp(pLicenseScene, "Info") == 0) {
				GetElementKV(nodeChild, "component", "value", vecValue);
				Sign(vecValue, szSign);
			}
			else if (strcmp(pLicenseScene, "Serv") == 0){
				GetElementKV(nodeChild, "component", "desc", vecValue);
				Sign(vecValue, szSign);

			}
			else if (strcmp(pLicenseScene, "User") == 0){
				GetElementKV(nodeChild, "component", "max", vecValue);
				Sign(vecValue, szSign);
			}
			else{
				continue;
			}

			if (strlen(szSign) == 0){
				m_errMsg = ERR_CRT_SIGN_FAILED;
				m_iInitFlag = 0;
				break;
			}
			else{
				m_iInitFlag = 1;
				itemElement->SetAttribute("signature", szSign);
			}
		}

		TiXmlPrinter printer;
		xCfgDoc.Accept(&printer);
		xCfgDoc.SaveFile(sFullLicenseFile.c_str());

	} while (false);



	return m_iInitFlag;

}


int LicImplement::CheckAuthAlter(const string &sCompany,
	const string &sMac,
	const string &sIp,
	const string &sExpiryDate,
	const char* szAuthMD5)
{
	char szSign[128] = { 0 };
	return strcmp(Sign(sCompany, sMac, sIp, sExpiryDate, szSign), szAuthMD5);
}

int LicImplement::CheckAlter(const vector<string>& VecVal, const char* szMD5){
	char szSign[128] = { 0 };
	return strcmp(Sign(VecVal, szSign), szMD5);
}

int LicImplement::Create(const string &sCompany,
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
	char* szUserMD5)
{
	Sign(sCompany, sMac, sIp, sExpiryDate, szAuthMD5);
	Sign(vecCert, szCertMD5);
	Sign(vecInfo, szInfoMD5);
	Sign(vecServ, szServMD5);
	Sign(vecUser, szUserMD5);
	return 0;
}

char* LicImplement::Sign(const string &sCompany,
	const string &sMac,
	const string &sIp,
	const string &sExpiryDate,
	char* szMD5)
{
	string sOrigSign = "|Company:" + sCompany + "|Host:" + sIp + "|MAC:" + sMac + "|Expiration:" + sExpiryDate + "|";
	CMd5Alg cMd5Alger;
	char s1[33] = { 0 };
	char s2[33] = { 0 };
	char s3[33] = { 0 };
	sOrigSign = "ZOC#@666//" + sOrigSign;
	cMd5Alger.MD5(sOrigSign.c_str(), s1);
	sOrigSign = "Z1573Q2486D0901//" + sOrigSign;
	cMd5Alger.MD5(sOrigSign.c_str(), s2);
	sOrigSign = "//X888@#" + sOrigSign;
	cMd5Alger.MD5(sOrigSign.c_str(), s3);
	char szEnCodeStr[4086] = { 0 };
	sprintf(szMD5, "%s%s%s", s1, s2, s3);

	return szMD5;
}

char* LicImplement::Sign(const vector<string>& vecParam, char* szMD5){
	string sOrigSign = "";
	for (int i = 0; i < vecParam.size(); i = i + 2){
		sOrigSign = "|" + vecParam[i] + ":" + vecParam[i + 1];
	}

	char szEnCodeStr[4086] = { 0 };
	CSimpDes cDesAlger;
	cDesAlger.strDesEncrpt(sOrigSign.c_str(), "lyy20201207", szEnCodeStr);
	CMd5Alg cMd5Alger;
	cMd5Alger.MD5(szEnCodeStr, szMD5);

	return szMD5;

}

int LicImplement::CheckComponent(const string& sMac, const string& sIp, const string& sExpireDate)
{

	int fd;
	int if_len;
	char szLocalIp[32];
	char szLocalMac[32];
	m_errMsg.code = 0;

	if (!sExpireDate.empty()){
			string sCurDate = GetCurDate();
			if (sCurDate > sExpireDate){
				if (XML_SCOPE_TYPE_TV == m_sScopeType){
					m_errMsg = ERR_AUTH_PROBATION;
				}
				else{
					m_errMsg = ERR_AUTH_EXPIREDATE;
				}
				return m_errMsg.code;
			}
	}

	if (XML_SCOPE_TYPE_CV != m_sScopeType){
		return m_errMsg.code;
	}

	m_errMsg = ERR_INVAILD_MAC_IP;

#if defined(_LINUX)
	struct ifreq buf[MAXINTERFACES];
	struct ifconf ifc;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		m_errMsg = ERR_SOCKET_INIT_FAILED;
		return m_errMsg.code;
	}

	ifc.ifc_len = sizeof(buf);
	ifc.ifc_buf = (caddr_t)buf;

	if (ioctl(fd, SIOCGIFCONF, (char *)&ifc) == -1)
	{
		m_errMsg = ERR_SOCKET_SIOCGIFCONF_FAILED;
		return m_errMsg.code;
	}

	if_len = ifc.ifc_len / sizeof(struct ifreq);

	while (if_len-- > 0)
	{
		if (!(ioctl(fd, SIOCGIFADDR, (char *)&buf[if_len])))
		{
			memset(szLocalIp, 0x00, sizeof(szLocalIp));
			strcpy(szLocalIp, (char*)inet_ntoa(((struct sockaddr_in*) (&buf[if_len].ifr_addr))->sin_addr));
		}
		else
		{
			m_errMsg = ERR_SOCKET_SIOCGIFADDR_FAILED;
			return m_errMsg.code;
		}

		if (!(ioctl(fd, SIOCGIFHWADDR, (char *)&buf[if_len])))
		{
			memset(szLocalMac, 0x00, sizeof(szLocalMac));
			sprintf(szLocalMac, "%02X:%02X:%02X:%02X:%02X:%02X",
				(unsigned char)buf[if_len].ifr_hwaddr.sa_data[0],
				(unsigned char)buf[if_len].ifr_hwaddr.sa_data[1],
				(unsigned char)buf[if_len].ifr_hwaddr.sa_data[2],
				(unsigned char)buf[if_len].ifr_hwaddr.sa_data[3],
				(unsigned char)buf[if_len].ifr_hwaddr.sa_data[4],
				(unsigned char)buf[if_len].ifr_hwaddr.sa_data[5]);
		}
		else
		{
			m_errMsg = ERR_SOCKET_SIOCGIFHWADDR_FAILED;
			m_errMsg.code;
		}

		if (strcasecmp(szLocalIp, sIp.c_str()) == 0 && strcasecmp(szLocalMac, sMac.c_str()) == 0)
		{
			m_errMsg = ERR_OK;
			break;
		}
		else{
			printf("Check local ip[%s],mac[%s],verfiy ip[%s],mac[%s]\n", szLocalIp, szLocalMac, sIp.c_str(), sMac.c_str());
			m_errMsg = ERR_INVAILD_MAC_IP;
		}
	}//–while end

	//关闭socket
	close(fd);
#elif defined(_WIN32)
    PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO();
    unsigned long stSize = sizeof(IP_ADAPTER_INFO);
    int nRel = GetAdaptersInfo(pIpAdapterInfo,&stSize);
    int netCardNum = 0;
    int IPnumPerNetCard = 0;
    if (ERROR_BUFFER_OVERFLOW == nRel) {
        delete pIpAdapterInfo;
        pIpAdapterInfo = (PIP_ADAPTER_INFO)new BYTE[stSize];
        nRel=GetAdaptersInfo(pIpAdapterInfo,&stSize);
    }
    if (ERROR_SUCCESS == nRel) {
    	while (pIpAdapterInfo)
    	{
			memset(szLocalMac, 0x00, sizeof(szLocalMac));
    		//for (int i=0;i<pIpAdapterInfo->AddressLength;i++){
    			sprintf_s(szLocalMac,sizeof(szLocalMac),"%02X:%02X:%02X:%02X:%02X:%02X"
    					,pIpAdapterInfo->Address[0]
						 ,pIpAdapterInfo->Address[1]
						,pIpAdapterInfo->Address[2]
						,pIpAdapterInfo->Address[3]
						,pIpAdapterInfo->Address[4]
						,pIpAdapterInfo->Address[5]);
    			//if (i < pIpAdapterInfo->AddressLength-1)
    			//{
    				//printf("%02X-", pIpAdapterInfo->Address[i]);
    			//}else {
	               // printf("%02X\n", pIpAdapterInfo->Address[i]);
	            //}
    		//}

            	IP_ADDR_STRING *pIpAddrString=&(pIpAdapterInfo->IpAddressList);
            	do
            	{
            		memset(szLocalIp, 0x00, sizeof(szLocalIp));
            		strcpy(szLocalIp,pIpAddrString->IpAddress.String);
            		if (_stricmp(szLocalIp, sIp.c_str()) == 0
            				&& _stricmp(szLocalMac, sMac.c_str()) == 0)
            		{
            			m_errMsg = ERR_OK;
            			break;
            		}
    				printf("Not match mac[%s],ip[%s]\n",szLocalMac,szLocalIp);
            		pIpAddrString=pIpAddrString->Next;
            	}while(pIpAddrString);

            	if(m_errMsg.code == ERR_OK.code)break;
            pIpAdapterInfo = pIpAdapterInfo->Next;
    	}
    }

    if (pIpAdapterInfo) {
        delete pIpAdapterInfo;
    }
#endif

	return m_errMsg.code;
}

void LicImplement::CacheWater(const char* pType, const char* pData, int iLength)
{
	m_sImage = "{\"type\":\"" + string(pType)
		+ "\",\"length\":" + toString(iLength)
		+ ",\"data\":\"" + string(pData) + "\"}";
}

void LicImplement::CacheModule(const vector<string>& vecVal)
{
	for (int i = 0; i < vecVal.size(); i = i + 2){
		if (0 == i){
			m_sModule = "{\"serv_list\":[{\"code\":\"" + vecVal[i] + "\",\"desc\":\"" + vecVal[i + 1] + "\"}";
		}
		else{
			m_sModule += ",{\"code\":\"" + vecVal[i] + "\",\"desc\":\"" + vecVal[i + 1] + "\"}";
		}

	}
	m_sModule += "]}";
}

int LicImplement::GetElementKV(TiXmlNode* nodeChild, const char* pKey, const char* pVal,
	vector<string>& vecVal)
{

	TiXmlElement* itemChildElement = NULL;
	const char* pLicenseScene = NULL;
	const char* pLicenseVal = NULL;
	string sGroup = nodeChild->ToElement()->Attribute("component");
	for (nodeChild = nodeChild->FirstChildElement(); nodeChild != NULL; nodeChild = nodeChild->NextSibling()) {
		itemChildElement = nodeChild->ToElement();
		pLicenseScene = itemChildElement->Attribute(pKey);
		pLicenseVal = itemChildElement->Attribute(pVal);
		if (NULL == pLicenseScene){
			m_errMsg = ERR_INVAILD_XML_SERVER;
			return m_errMsg.code;
		}
		vecVal.push_back(pLicenseScene);
		vecVal.push_back(pLicenseVal);

		if ("Info" == sGroup){
			if (strcmp(pLicenseScene, "Title") == 0){
				m_sTitle = pLicenseVal;

			}
			else if (strcmp(pLicenseScene, "About") == 0){
				m_sAbout = pLicenseVal;

			}
			else if (strcmp(pLicenseScene, "Watemark") == 0){
				int iLength = 0;
				itemChildElement->Attribute("length", &iLength);
				CacheWater(itemChildElement->Attribute("type")
					, pLicenseVal
					, iLength);
			}
		}
	}

	if ("Serv" == sGroup){
		CacheModule(vecVal);
	}

	return 0;
}

string& LicImplement::AllReplace(string & str, const string & oldstr, const string & newstr)
{
	string::size_type tmpPos(0);
	while (true)   {
		string::size_type   pos(0);
		if ((pos = str.find(oldstr, tmpPos)) != string::npos) {
			str.replace(pos, oldstr.length(), newstr);
			tmpPos = pos + newstr.length();
		}
		else {
			break;
		}
	}

	return str;
}

string LicImplement::GetCurDate(int n)
{
#if defined(_LINUX)
	time_t tt = time(NULL);
	tm tm;
	localtime_r(&tt, &tm);
	if (1 == n) {
		char buf[20];
		strftime(buf, 20, "%Y-%m-%d %H:%M:%S", &tm);
		return buf;
	}
	else {
		char buf[15];
		strftime(buf, 15, "%Y%m%d%H%M%S", &tm);
		return buf;
	}
#elif defined(_WIN32)
	char buf[15];

	SYSTEMTIME stTime;
	GetLocalTime(&stTime);
	WORD wYear = stTime.wYear;
	WORD wMonth = stTime.wMonth;
	WORD wDay = stTime.wDay;
	WORD wHour = stTime.wHour;
	WORD wMinute = stTime.wMinute;
	WORD wSecond = stTime.wSecond;
	//m_date字符串即为当前时间。如：2010年4月23日 11:12:45
	if (1 == n){
		char buf[20];
		sprintf_s(buf, 20, "%4d-%2d-%2d %2d:%2d:%2d", wYear, wMonth, wDay, wHour, wMinute, wSecond);
		return buf;
	}
	else{
		char buf[20];
		sprintf_s(buf, 20, "%4d%2d%2d%2d%2d%2d", wYear, wMonth, wDay, wHour, wMinute, wSecond);
		return buf;
	}
#endif
	return "";
}


int LicImplement::GetDecodeLicFile(const string& sSrcFile,const string& sDestFile)
{
	ifstream ifile(sSrcFile);
	ostringstream buf;
	char ch;
	while(buf&&ifile.get(ch))
		buf.put(ch);

	CBase64 base64;
    std::string sOutput = "";
	size_t iLength = buf.str().size();
	char *szTmp = new char[iLength];
	size_t retLength = 0;
	base64.base64Decode(buf.str(),(unsigned char *)szTmp,retLength);
	szTmp[retLength] = '\0';
	ofstream osrcfile(sDestFile);
	osrcfile.write(szTmp,retLength);
	ifile.close();
	osrcfile.close();
	delete[]szTmp;
	szTmp = NULL;
	return 0;
}
