cmake_minimum_required(VERSION 2.8)
if(CMAKE_CL_64)
set(ADDRESS_MODEL 64)
set(NODE_TARGET x64)
else()
set(ADDRESS_MODEL 32)
set(NODE_TARGET x86)
endif()
if(UNIX)
	message("current platform: Linux ")
	ADD_DEFINITIONS( -D_LINUX="1")
elseif(WIN32)
	message("current platform: Windows,bit:${ADDRESS_MODEL} ,cl:${CMAKE_CL_64}")
	ADD_DEFINITIONS( -D_WIN32="1")
	add_definitions(-w)
	SET(OPENSSL_ROOT_DIR "C:\\Program Files\\OpenSSL-Win64")
	SET(OPENSSL_CRYPTO_LIBRARY "C:\\Program Files\\OpenSSL-Win64\\lib")
	SET(OPENSSL_INCLUDE_DIR "C:\\Program Files\\OpenSSL-Win64\\include")
	find_package(OpenSSL REQUIRED)
	include_directories(${OPENSSL_INCLUDE_DIR})
	message("windows openssl include: ${OPENSSL_INCLUDE_DIR} ")

else()
	message("current platform: unkonw ")
endif()

PROJECT(LICENSELIB)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(src)
