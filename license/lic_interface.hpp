/*
 * license_interface.hpp
 *
 *  Created on: 2022年11月1日
 *      Author: biny
 */

#ifndef LICENSE_INTERFACE_HPP_
#define LICENSE_INTERFACE_HPP_

#include <iostream>
using namespace std;

//namespace lic{

#if defined(_LINUX)
#ifdef __cplusplus
#define LIC_EXT_API  extern "C"
#endif
#elif defined(_WIN32)
#ifdef __cplusplus
#define LIC_EXT_API  extern "C" __declspec(dllexport)
#elif
#define LIC_EXT_API  __declspec(dllexport)
#endif
#endif


/*****************************************c++调用接口类***********************************/
//class  LicImplement;
//class DLLEXPORT LicInterface
//{
//public:
//	LicInterface();
//	virtual ~LicInterface();
//	int Init(const string& sAppCode);
//	int Create(const string& sAppCode);
//	const char* GetError() const;
//	const char* GetTitle() const;
//	const char* GetAbout() const;
//	const char* GetMark() const;
//	const char* GetModules() const;
//
//private:
//	LicImplement* m_pImpl;
//};
//
//}

/*****************************************c调用接口***********************************/

LIC_EXT_API int  Init(const char*pApp,const char* pLicPath);
LIC_EXT_API const char* GetError();
LIC_EXT_API const char* GetTitle();
LIC_EXT_API const char* GetAbout();
LIC_EXT_API const char* GetMark();
LIC_EXT_API const char* GetModules();


#endif /* LICENSE_INTERFACE_HPP_ */



