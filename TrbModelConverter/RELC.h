#pragma once
#include <vector>
#include "Reader.h"
// This might be a struct relocation table
// It is!
class RELC : Reader
{
public:
	struct Header
	{
		uint32_t size;
		uint32_t count;
	} header;

	struct OffsetInfo
	{
		uint16_t hdrxIndex1;
		uint16_t hdrxIndex2;
		uint32_t offset;
	};

	std::vector<OffsetInfo> structInfos;

	void writeFile(FILE* f, int chunk, int id);
};

