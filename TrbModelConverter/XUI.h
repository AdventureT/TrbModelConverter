#pragma once
#include <cstdint>
#include <string>
struct XUI
{
	uint32_t zero;
	union FileName
	{
		uint32_t fileNameOffset;
		std::string fileName;
	};
	
};
