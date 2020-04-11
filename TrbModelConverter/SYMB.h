#pragma once
#include <vector>
#include <string>
class SYMB
{

public:
	struct Header
	{
		std::string symb;
		uint32_t size;
		uint32_t namesCount;
	};
	struct NameOffset
	{
		std::string name;
		uint16_t ID;
		uint32_t nameOffset;
		uint16_t nameID;
		uint32_t dataOffset;
	};

	std::vector<NameOffset> nameOffsets;
	Header header;
};

