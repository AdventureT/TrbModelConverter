#pragma once
#include <string>
#include <vector>
struct DDSHeader
{
	std::string magic;
	uint32_t size;
	std::vector<uint8_t> flags;
	uint32_t height;
	uint32_t width;
	uint32_t pitchOrLinearSize;
	uint32_t depth;
	std::vector<uint32_t> mipMapCount;
	struct DDSPixelFormat
	{
		uint32_t size;
		std::vector<uint8_t> flags;
		std::string fourCC;
		uint32_t RGBBitCount;
		uint32_t RBitMask;
		uint32_t GBitMask;
		uint32_t BBitMask;
		uint32_t ABitMask;
	};
	uint32_t caps;
	uint32_t caps2;
	uint32_t caps3;
	uint32_t caps4;
	uint32_t reserved2;
};