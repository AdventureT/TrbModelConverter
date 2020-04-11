#include "TSFL.h"

TSFL::TSFL(FILE* f, Reader::Endian endian)
{
	Reader::e = endian;
	label = ReadString(f, 4);
	size = ReadUInt(f);
	trbf = { ReadString(f,4) };
	hdrx.label = ReadString(f, 4);
	hdrx.header = { ReadUInt(f), ReadUShort(f) ,ReadUShort(f), ReadUInt(f) };
	for (size_t i = 0; i < hdrx.header.files; i++)
	{
		HDRX::TagInfo h = { ReadUShort(f), ReadUShort(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
		if (i != 0)
		{
			h.tagSize += hdrx.tagInfos[i - 1].tagSize;
		}
		hdrx.tagInfos.push_back(h);
	}
	sect = { ReadString(f,4), ReadUInt(f) };
	long retHere = ftell(f);
	fseek(f, sect.size, SEEK_CUR);
	if (ReadString(f, 4) == "RELC")
	{
		relc.header = { ReadUInt(f), ReadUInt(f) };
		for (size_t i = 0; i < relc.header.count; i++)
		{
			relc.structInfos.push_back({ ReadUShort(f), ReadUShort(f), ReadUInt(f) });
		}
	}
	symb.header = { ReadString(f,4), ReadUInt(f), ReadUInt(f) };
	long symbChunkOffset = ftell(f);
	bool tsfb = false;
	for (size_t i = 0; i < symb.header.namesCount; i++)
	{
		SYMB::NameOffset no;
		if (label[3] == 'B')
		{
			tsfb = true;
			no.ID = ReadUShort(f); no.nameOffset = ReadUShort(f); fseek(f, 2, SEEK_CUR); no.nameID = ReadUShort(f); no.dataOffset = ReadUInt(f);
		}
		else
		{
			no = { "", ReadUShort(f),ReadUInt(f),ReadUShort(f),ReadUInt(f) };
		}
		long returnHere = ftell(f);
		fseek(f, symbChunkOffset + (symb.header.namesCount * 12) + no.nameOffset, SEEK_SET);
		no.name = ReadString(f);
		fseek(f, returnHere, SEEK_SET);
		symb.nameOffsets.push_back(no);
	}
	fseek(f, retHere, SEEK_SET);
}