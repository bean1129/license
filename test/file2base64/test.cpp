#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include "base64.h"

using namespace std;

int File2Base64(const char * inFile,const char* outFile)
{
	ifstream ifile(inFile);
	ostringstream buf;
	char ch;
	while(buf&&ifile.get(ch))
		buf.put(ch);

	CBase64 base64;
    std::string sOutput = "";
    base64.base64Encode(buf.str().c_str(), buf.str().size(), sOutput);
	ofstream ofile(outFile);
	ofile.write(sOutput.data(),sOutput.size());

//	size_t iLength = buf.str().size();
//	char szTmp[iLength];
//	size_t iRetLength = 0;
//	base64.base64Decode(sOutput,(unsigned char *)szTmp,iRetLength);
//	ofstream osrcfile(outSrcFile);
//	osrcfile.write(szTmp,iLength);
//	std::cout << iLength << "," << iRetLength << std::endl;

	return 0;
}

int main(int argc,char const * argv[])
{
	if(3 != argc){
		std::cout << "args error "<< std::endl;
		return -1;
	}
	//文件名
	File2Base64(argv[1],argv[2]);
	return 0;
}
