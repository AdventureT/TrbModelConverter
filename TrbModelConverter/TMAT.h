#pragma once
#include <cstdint>
#include <string>
struct tmat
{
	uint32_t zero;
	uint32_t unknown;
	uint32_t unknown2;
	uint32_t meshNameOffset;
	uint32_t one;
	uint32_t meshNameOffsetEnd;
	std::string meshNamebelong;
	uint32_t unknown3;
	uint32_t texNameOffset;
};