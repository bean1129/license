/*
 * lic_def.cpp
 *
 *  Created on: 2022年11月7日
 *      Author: biny
 */
#include "lic_def.hpp"

ErrorType ERR_OK                         = { 0, "Success" };
ErrorType ERR_FAIL                       = { 1, "Fail" };
ErrorType ERR_FATAL                      = { 2, "Fatal" };
ErrorType ERR_UNDEFINED                  = { 3, "undefined" };
ErrorType ERR_EFFECTIVE_DATE             = { 4, "application effective date is null or invaild" };
ErrorType ERR_PARASE_XML_FAILED          = { 5, "Parse xml license failed" };
ErrorType ERR_INVAILD_XML_NODE           = { 6, "Root node:[ZOCLicense] not found." };
ErrorType ERR_INVAILD_XML_COMPEONENT     = { 7, "Acquire license component failed." };
ErrorType ERR_INVAILD_XML_SIGNATURE      = { 8, "Acquire license signature failed." };
ErrorType ERR_LICNESE_HAVE_ALTERED       = { 9, "License file has been alterd!!!" };
ErrorType ERR_LICENSE_NOT_ALLOEWD        = { 10, "License file is not allowed!!!" };
ErrorType ERR_SOCKET_INIT_FAILED         = { 11, "Create socket failed!!!" };
ErrorType ERR_SOCKET_SIOCGIFCONF_FAILED  = { 12, "SIOCGIFCONF ioctl failed!!!" };
ErrorType ERR_SOCKET_SIOCGIFADDR_FAILED  = { 13, "SIOCGIFADDR ioctl  faield!!!" };
ErrorType ERR_SOCKET_SIOCGIFHWADDR_FAILED= { 14, "SIOCGIFHWADDR ioctl  faield!!!" };
ErrorType ERR_AUTH_EXPIREDATE            = { 15, "License over expireDate" };
ErrorType ERR_INVAILD_MAC_IP             = { 16, "Local ip or local mac address not match" };
ErrorType ERR_LIC_SDK_INIT_CFG_PATH      = { 17, "env LIC_SDK_INIT_CFG_PATH path not exists" };
ErrorType ERR_INVAILD_XML_SERVER         = { 18, "Not find Server component" };
ErrorType ERR_INVAILD_XML_USER           = { 19, "Not find user component" };
ErrorType ERR_CRT_SIGN_FAILED            = { 20, "Create license sign failed." };
ErrorType ERR_INVAILD_XML_CERT_EFF       = { 21, "Acquire license cert component[Effective] failed." };
ErrorType ERR_INVAILD_XML_SCOPE          = { 22, "Acquire ZOCLicense scope failed" };
ErrorType ERR_AUTH_PROBATION             = { 23, "License over probation" };

const std::string XML_SCOPE_TYPE_GV = "GV";
const std::string XML_SCOPE_TYPE_TV = "TV";
const std:: string XML_SCOPE_TYPE_CV = "CV";
