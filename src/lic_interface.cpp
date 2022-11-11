/*
 * lic_interface.cpp
 *
 *  Created on: 2022年11月1日
 *      Author: biny
 */


#include <iostream>
#include <map>
#include "../license/lic_interface.hpp"
#include "lic_implement.hpp"


using namespace lic;

//static std::map<int,LicImplement *> g_mapLicObj;
static LicImplement licImplementObj;

//LicInterface::LicInterface()
//{
//	m_pImpl = new LicImplement;
//}
//
//LicInterface::~LicInterface()
//{
//	if(m_pImpl)
//		delete m_pImpl;
//}
//
//int LicInterface::Init(const string& sAppCode){
//	if(!m_pImpl->Verify(sAppCode)){
//		return 0;
//	}
//
//	return 1;
//}
//
//int LicInterface::Create(const string& sFile){
//	if(!m_pImpl->Create(sFile)){
//		return 0;
//	}
//
//	return 1;
//}
//
//const char* LicInterface::GetError()const{
//	return m_pImpl->GetError();
//}
//
//const char* LicInterface::GetTitle()const{
//	return m_pImpl->GetTitle();
//}
//
//const char* LicInterface::GetAbout()const{
//	return m_pImpl->GetAbout();
//}
//
//const char* LicInterface::GetMark()const{
//	return m_pImpl->GetMark();
//}
//
//const char* LicInterface::GetModules()const{
//	return m_pImpl->GetModules();
//}

int Init(const char*pApp,const char* pLicPath){
	int ret = 0;
	if(licImplementObj.Verify(pApp,pLicPath)){
		ret = 1;
	}
	return ret;
}

const char* GetError(){
	return licImplementObj.GetError();
}

const char* GetTitle(){
	return licImplementObj.GetTitle();
}

const char* GetAbout(){
	return licImplementObj.GetAbout();
}

const char* GetMark(){
	return licImplementObj.GetMark();

}

const char* GetModules(){
	return licImplementObj.GetModules();
}
