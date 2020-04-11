#pragma once
#include <string>
#include <vector>
class TTL
{
public:
	uint32_t ddsFileCount;
	uint32_t ddsFilesOffset;
	uint32_t currentFileNameOffset;
	std::string currentFileName;
	struct ddsFile
	{
		uint32_t flag; //?
		uint32_t ddsFileNameOffset;
		uint32_t ddsFileSize;
		uint32_t ddsDataOffset;
		std::string ddsFileName;
	};
	std::vector<ddsFile> ddsFiles;
};
struct TTLNTU
{
	uint32_t ddsFileCount;
	uint32_t ddsFilesOffset;
	struct ddsFile
	{
		uint32_t flag; //?
		uint32_t flag2; //?
		uint32_t compression; //?
		uint32_t ddsFileNameOffset;
		uint32_t width;
		uint32_t height;
		uint32_t zero; //?
		uint32_t ddsDataOffset;
		uint32_t ddsFileSize;
		std::string ddsFileName;
	};
};

