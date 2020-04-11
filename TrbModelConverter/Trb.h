#pragma once
#include "deBlob.h"
#include "NTAOTT.h"

class Trb : Reader
{
public:

	std::string output;
	Trb(std::string fileName, Endian e, System::Windows::Forms::ProgressBar^ pgb, System::Windows::Forms::ListView^ lv, Game::Type game); //Constructor
protected:
	std::string filename;
	Endian e;
	FILE* f;
	std::string readTrb(System::Windows::Forms::ProgressBar^ pgb, System::Windows::Forms::ListView^ lv, Game::Type game);
};
