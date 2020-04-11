#pragma once
#include <cstdint>
#include <string>
#include <vector>
struct TTEX
{
	uint32_t zero; // Even Relc skips this? wtf
	uint32_t nameOffset;
	uint32_t textureInfoOffset;
	uint32_t ddsSize;
	uint32_t ddsOffset;
	// After this there will come unknown territory which isn't too important
};
struct TextureInfo
{
	uint32_t width;
	uint32_t height;
	uint32_t mipMapsCount;
	uint32_t width2;
	uint32_t height2;
	std::vector<uint8_t> compression; // 4 bytes (0x15 = Alpha Color / DXT5 = DXT5)
	uint32_t unknown;
};