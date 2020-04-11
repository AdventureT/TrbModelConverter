#pragma once
#include "TSFL.h"
#include "TMDL.h"
#include "Game.h"
#include "FbxHelper.h"

class NTAOTT : public Game
{
	Endian en;
public:
	void virtual read(FILE* f, Reader::Endian endian, std::string filename, System::Windows::Forms::ProgressBar^ pgb, System::Windows::Forms::ListView^ lv) override;
};

