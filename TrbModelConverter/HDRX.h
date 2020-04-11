#pragma once
#include <string>
#include <vector>
class HDRX
{
public:
	std::string label;
	struct Header 
	{
		uint32_t size;
		uint16_t flag1;
		uint16_t flag2;
		uint32_t files;
	} header;
	struct TagInfo
	{
		uint16_t unknown;
		uint16_t unknown2;
		uint32_t tagSize;
		uint32_t zero;
		uint32_t flag;
	};
	std::vector<TagInfo> tagInfos;
};

