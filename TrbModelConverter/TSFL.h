#pragma once
#include "TRBF.h"
#include "HDRX.h"
#include "SECT.h"
#include "RELC.h"
#include "SYMB.h"
#include "Reader.h"
#include <string>
class TSFL : Reader
{
public:
	std::string label;
	uint32_t size;

	TRBF trbf;
	HDRX hdrx;
	SECT sect;
	RELC relc;
	SYMB symb;

	TSFL(FILE* f, Reader::Endian endian);
};

