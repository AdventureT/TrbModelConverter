#pragma once
#include <cstdio>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Reader.h"
#include "fbxsdk.h"
#include <tchar.h>

namespace TrbBig
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Runtime::InteropServices;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace std;
	using namespace System::IO;
	class TrbBig : Reader
	{
	private:
		char* _fileName = new char[256];
	public:

		struct HDRX
		{
			int size;
			int files;
			std::vector<long long> chunkSizes;
		};

		/// <summary>
		/// Contains main data of the specific trb file
		/// </summary>
		struct SECT
		{
			int size;
			long long chunkOffset;
		};

		struct RELC
		{
			int size;
		};

		struct NameOffset
		{
			short ID;
			int nameOffset;
			unsigned short name;
			int dataOffset;
		};


		struct SYMB
		{
			int size;
			int namesCount;
			std::vector<NameOffset> nameOffsets;
			std::vector<std::string> names;
		};

		/// <summary>
		/// Magic for trb files
		/// </summary>
		struct TSFL
		{
			int size;
		};

		/// <summary>
		/// TRBF is always empty
		/// </summary>
		struct TRBF
		{

		};

		TrbBig::TSFL ts;
		TrbBig::TRBF tr;
		TrbBig::HDRX h;
		TrbBig::SECT se;
		TrbBig::RELC r;
		TrbBig::SYMB sy;
		Trb(System::String^ fileName); //Constructor
	protected:
		void readSYMB(BinaryReader^ br);
		void readRELC(BinaryReader^ br);
		void readSECT(BinaryReader^ br);
		void readHDRX(BinaryReader^ br);
		void readTRBF(BinaryReader^ br);
		void readTSFL(BinaryReader^ br);

		void readTrb(System::String^ filePath);
	};
}