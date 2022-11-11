if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()
#编译位数
if(CMAKE_CL_64)
set(ADDRESS_MODEL 64)
set(NODE_TARGET x64)
else()
set(ADDRESS_MODEL 32)
set(NODE_TARGET x86)
endif()
#SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${PROJECT_SOURCE_DIR}/lib)
SET (LIBLICENSE_SRC 
		lic_interface.cpp 
		lic_implement.cpp 
		lic_def.cpp
		tinyxml/tinyxml.cpp
		tinyxml/tinystr.cpp
		tinyxml/tinyxmlerror.cpp
		tinyxml/tinyxmlparser.cpp
		security/base64.cpp
		security/CBase64Alg.cpp
		security/CMd5Alg.cpp
		security/des.cpp
		security/md5base.cpp)
ADD_LIBRARY (license SHARED ${LIBLICENSE_SRC})
#ADD_LIBRARY (license_static STATIC ${LIBLICENSE_SRC})
#SET_TARGET_PROPERTIES (license_static PROPERTIES OUTPUT_NAME "license")
#GET_TARGET_PROPERTY (OUTPUT_VALUE license_static OUTPUT_NAME)
#SET_TARGET_PROPERTIES (license_static PROPERTIES CLEAN_DIRECT_OUTPUT 1) 