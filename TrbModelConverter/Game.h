#pragma once
class Game : public Reader
{
public: 
	enum Type
	{
		DEBLOB,
		NAOTT,
		NBFVI,
		NU,
		BARNYARD
	};

	void virtual read(FILE* f, Reader::Endian endian, std::string filename, System::Windows::Forms::ProgressBar^ pgb, System::Windows::Forms::ListView^ lv) = 0;
};
