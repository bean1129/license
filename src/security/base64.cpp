#include "base64.h"

static	char rstr[] = {
    	0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
		0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
		0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  62,   0,   0,   0,  63, 
		52,  53,  54,  55,  56,  57,  58,  59,  60,  61,   0,   0,   0,   0,   0,   0, 
		0,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14, 
		15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,   0,   0,   0,   0,   0, 
		0,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40, 
		41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,   0,   0,   0,   0,   0};

static	char *bstr =
		"ABCDEFGHIJKLMNOPQ"
		"RSTUVWXYZabcdefgh"
		"ijklmnopqrstuvwxy"
		"z0123456789+/";


CBase64::CBase64()
{
	
}

CBase64::~CBase64()
{
	
}


void CBase64::base64Encode(const char* input,size_t len,std::string& output)
{
		size_t i = 0;
		size_t o = 0;

		output = "";
		while (i < len)
		{
			size_t remain = len - i;

			switch (remain)
			{
			case 1:
				output += bstr[ ((input[i] >> 2) & 0x3f) ];
				output += bstr[ ((input[i] << 4) & 0x30) ];
				output += "==";
				break;
			case 2:
				output += bstr[ ((input[i] >> 2) & 0x3f) ];
				output += bstr[ ((input[i] << 4) & 0x30) + ((input[i + 1] >> 4) & 0x0f) ];
				output += bstr[ ((input[i + 1] << 2) & 0x3c) ];
				output += "=";
				break;
			default:
				output += bstr[ ((input[i] >> 2) & 0x3f) ];
				output += bstr[ ((input[i] << 4) & 0x30) + ((input[i + 1] >> 4) & 0x0f) ];
				output += bstr[ ((input[i + 1] << 2) & 0x3c) + ((input[i + 2] >> 6) & 0x03) ];
				output += bstr[ (input[i + 2] & 0x3f) ];
			}
			o += 4;
			i += 3;
		}

	return ;	
}


void CBase64::base64Decode(const std::string& input, unsigned char *output, size_t& sz)
{
		size_t i = 0;
		size_t l = input.size();
		size_t j = 0;

		while (i < l)
		{
			while (i < l && (input[i] == 13 || input[i] == 10))
				i++;
			if (i < l)
			{
				unsigned char b1 = (unsigned char)((rstr[(int)input[i]] << 2 & 0xfc) +
					(rstr[(int)input[i + 1]] >> 4 & 0x03));
				if (output)
				{
					output[j] = b1;
				}
				j++;
				if (input[i + 2] != '=')
				{
					unsigned char b2 = (unsigned char)((rstr[(int)input[i + 1]] << 4 & 0xf0) +
						(rstr[(int)input[i + 2]] >> 2 & 0x0f));
					if (output)
					{
						output[j] = b2;
					}
					j++;
				}
				if (input[i + 3] != '=')
				{
					unsigned char b3 = (unsigned char)((rstr[(int)input[i + 2]] << 6 & 0xc0) +
						rstr[(int)input[i + 3]]);
					if (output)
					{
						output[j] = b3;
					}
					j++;
				}
				i += 4;
			}
		}
		sz = j;

	return ;	
}
