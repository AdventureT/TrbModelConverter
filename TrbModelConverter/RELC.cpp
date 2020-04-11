#include "RELC.h"

// This is not a struct definer it is rather just an offset to an offset
void RELC::writeFile(FILE* f, int chunk, int id)
{
	if (structInfos.empty())
	{
		return;
	}

	FILE* fo;
	char str[10];
	sprintf(str, "%d", id);
	std::string fileName("./relc"); fileName += str; fileName += ".info";
	if (fopen_s(&fo, fileName.c_str(), "wb") != 0) // Security check
	{
		throw "Can't write info file";
	}
	fseek(f, chunk, SEEK_SET);
	int pos = 0;
	for (size_t i = 0; i < structInfos.size(); i++)
	{
		if (structInfos[i].hdrxIndex1 == id)
		{
			pos = i;
			break;
		}
	}
	int count = 0;
	int fromPos = pos;
	for (size_t i = 0; i < structInfos.size() && fromPos < structInfos.size()-1; i++)
	{
		if (structInfos[fromPos].hdrxIndex1 != id)
		{
			count = i;
			break;
		}
		fromPos++;
	}
	int returnHere = ftell(f);
	for (size_t i = 0; i < count-1; i++)
	{
		fseek(f, chunk + structInfos[pos].offset, SEEK_SET);
		int structSize = structInfos[pos+1].offset - structInfos[pos].offset;
		std::vector<uint8_t> structData;
		structData.resize(structSize);
		fread(structData.data(), structSize, 1, f);
		fwrite("Struct: ", 8, 1, fo);
		fwrite(structData.data(), structSize, 1, fo);
		pos++;
	}
	fseek(f, returnHere, SEEK_SET);
	fclose(fo);
}
