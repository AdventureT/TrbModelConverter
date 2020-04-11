#include "TrbBig.h"
#include "Trb.h"

namespace TrbBig
{

	TrbBig::Trb(System::String^ filePath)
	{
		readTrb(filePath);
	}
	void Trb::readTrb(System::String^ filePath)
	{
		BinaryReader^ br = gcnew BinaryReader(File::Open((filePath), FileMode::Open), System::Text::Encoding::ASCII);
		readTSFL(br);
		readTRBF(br);
		readHDRX(br);
		readSECT(br);
		br->Close();
	}


	void Trb::readTSFL(BinaryReader^ br)
	{
		System::String^ tsfl = gcnew System::String(br->ReadChars(4));
		if (tsfl == "TSFL")
		{
			ts.size = br->ReadInt32();
		}
		else
		{
			throw gcnew Exception("Chosen File is not from the TOSHI Game Engine");
		}
	}
	void Trb::readTRBF(BinaryReader^ br)
	{
		System::String^ trbf = gcnew System::String(br->ReadChars(4));
		if (trbf != "TRBF")
		{
			throw gcnew Exception("Chosen File is currently unsupported");
		}
	}
	void Trb::readHDRX(BinaryReader^ br)
	{
		System::String^ hdrx = gcnew System::String(br->ReadChars(4));
		if (hdrx != "HDRX")
		{
			throw gcnew Exception("Chosen File is currently unsupported");
		}
		h.size = br->ReadInt32();
		br->BaseStream->Seek(4, SeekOrigin::Current); //Some unknown flags
		h.files = br->ReadInt32();
		br->BaseStream->Seek(4, SeekOrigin::Current); //Just 0's
		//h.chunkSizes = new List<long>(); //Init the List

		for (int i = 0; i < h.files; i++)
		{
			if (i == 0)
			{
				h.chunkSizes.push_back(br->ReadInt64());
			}
			else
			{
				h.chunkSizes.push_back(br->ReadInt64() + h.chunkSizes[i - 1]);
			}
			br->BaseStream->Seek(8, SeekOrigin::Current); //Some unknown flags
		}
		br->BaseStream->Seek(h.size + 20, SeekOrigin::Begin);
	}
	void Trb::readSECT(BinaryReader^ br)
	{
		System::String^ sect = gcnew System::String(br->ReadChars(4));
		if (sect != "SECT")
		{
			throw gcnew Exception("Chosen File is currently unsupported");
		}
		se.size = br->ReadInt32();
		se.chunkOffset = br->BaseStream->Position;
		br->BaseStream->Seek(se.size, SeekOrigin::Current);
		readRELC(br);
		readSYMB(br);
	}

	void Trb::readRELC(BinaryReader^ br)
	{
		System::String^ relc = gcnew System::String(br->ReadChars(4));
		if (relc != "RELC")
		{
			throw gcnew Exception("Chosen File is currently unsupported");
		}
		r.size = br->ReadInt32();
		br->BaseStream->Seek(r.size, SeekOrigin::Current);
	}

	void Trb::readSYMB(BinaryReader^ br)
	{
		System::String^ symb = gcnew System::String(br->ReadChars(4));
		if (symb != "SYMB")
		{
			throw gcnew Exception("Chosen File is currently unsupported");
		}
		sy.size = br->ReadInt32();
		sy.namesCount = br->ReadInt32();
		for (int i = 0; i < sy.namesCount; i++)
		{
			NameOffset nameOffset;
			nameOffset.ID = br->ReadInt16();
			nameOffset.nameOffset = br->ReadInt32();
			nameOffset.name = br->ReadInt16();
			nameOffset.dataOffset = br->ReadInt32();
			sy.nameOffsets.push_back(nameOffset);
		}
	}
	//Trb::Trb(char* fileName)
	//{
	//	_fileName = fileName;
	//	ReadTrbFile();
	//}
	//void Trb::ReadTrbFile()
	//{
	//	FILE* f;
	//	fopen_s(&f, _fileName, "rb");
	//	long tsfl = 0;
	//	long fileSize = 0;
	//	long trbf = 0;
	//	long chunkOffset = 0;
	//	long chunkSize = 0;
	//	long files = 0;
	//	long TMDLsize = 0;

	//	std::vector<float> vertices;
	//	std::vector<float> normals;
	//	std::vector<float> uvs;
	//	std::vector<unsigned long> faces;
	//	std::vector<float> verticesAll;
	//	std::vector<float> normalsAll;
	//	std::vector<half> uvsAll;
	//	std::vector<unsigned long> facesAll;
	//	std::vector<long> verticesCount;
	//	std::vector<long> faceIndicesCount;
	//	int fscale = 1;
	//	int meshCount = 0;
	//	std::vector<long> sizes;
	//	std::vector<long> offsets;
	//	std::vector<long> renderOffsets;
	//	std::vector<long> allSizes;
	//	std::vector<long> vertexOffsets;
	//	std::vector<long> meshInfoOffsets;
	//	std::vector<long> faceOffsets;
	//	std::vector<long> meshCounts;
	//	std::string chunkTag;
	//	fread_s(&tsfl, 4, 4, 1, f);
	//	fread_s(&fileSize, 4, 4, 1, f);
	//	fileSize += 8;
	//	fread_s(&trbf, 4, 4, 1, f);

	//	bool _break = false;

	//	if (tsfl != 1279677268 && trbf != 1178751572)
	//	{
	//		throw gcnew Exception("Wrong file");
	//	}
	//	do
	//	{
	//		char temp[5];
	//		fread_s(temp, 4, 4, 1, f);
	//		chunkTag = temp;
	//		chunkTag.erase(4);
	//		fread_s(&chunkSize, 4, 4, 1, f);
	//		chunkOffset = ftell(f);
	//		long nextOffset = chunkOffset;
	//		short flag1 = 0;
	//		short flag2 = 0;
	//		if (chunkTag == "HDRX")
	//		{
	//			fseek(f, 4, SEEK_CUR);
	//			fread_s(&files, 4, 4, 1, f);
	//			fseek(f, 4, SEEK_CUR);
	//			for (int i = 0; i < files; i++)
	//			{
	//				fread_s(&TMDLsize, 4, 4, 1, f);
	//				fseek(f, 4, SEEK_CUR);
	//				flag1 = ReadShort(f);
	//				fseek(f, 4, SEEK_CUR);
	//				flag2 = ReadShort(f);
	//				if (i == 0)
	//				{

	//				}
	//				else
	//				{
	//					TMDLsize += allSizes[i - 1];
	//				}

	//				allSizes.push_back(TMDLsize);
	//				if (flag1 == 0 && flag2 == 0)
	//				{
	//					sizes.push_back(TMDLsize);
	//				}
	//				else
	//				{
	//					renderOffsets.push_back(TMDLsize);
	//				}
	//				/*
	//				if (flag2 == 16 && flag1 == 1) //TMDL
	//				{
	//					fseek(f, 4, SEEK_CUR);
	//					flag2 = ReadShort(f);
	//					TMDLsize += allSizes[i - 1];
	//					allSizes.push_back(TMDLsize);
	//					if (flag2 == 0)
	//					{
	//						sizes.push_back(TMDLsize);
	//					}
	//					else
	//					{
	//						renderOffsets.push_back(TMDLsize);
	//					}

	//				}
	//				else
	//				{
	//					fseek(f, 4, SEEK_CUR);
	//					flag2 = ReadShort(f);
	//					if (i == 0)
	//					{

	//					}
	//					else
	//					{
	//						TMDLsize += allSizes[i - 1];
	//					}

	//					allSizes.push_back(TMDLsize);
	//					if (flag1 == 0 && flag2 == 0)
	//					{
	//						sizes.push_back(TMDLsize);
	//					}
	//					else
	//					{
	//						renderOffsets.push_back(TMDLsize);
	//					}
	//				}
	//				*/
	//			}
	//		}
	//		else if (chunkTag == "SECT")
	//		{
	//			/*
	//			long unknownChunkSize; //Transformations?
	//			fread_s(&unknownChunkSize, 4, 4, 1, f);
	//			long unknownChunkOffset; //Transformations?
	//			fread_s(&unknownChunkOffset, 4, 4, 1, f);
	//			unknownChunkOffset += chunkOffset;
	//			*/
	//			//fseek(f, 4, SEEK_CUR);
	//			for (int i = 0; i < sizes.size(); i++)
	//			{
	//				nextOffset = sizes[i];
	//				offsets.push_back(nextOffset);
	//			}
	//			long tmdlOffset = chunkOffset;
	//			System::String^ fileName = gcnew String(_fileName);;
	//			/*
	//			long transformationOffset = offsets[0];
	//			long unknownTableOffset = offsets[1];
	//			long defaultOffset = offsets[2]; //default is 8 byte string
	//			long nameOffset = offsets[3]; //name is 4 byte string
	//			long unknownOffset = offsets[4];
	//			long unknownOffset2 = offsets[5];
	//			long unknownOffset3 = offsets[6];
	//			long renderHeaderOffset = offsets[7];
	//			long renderNameOffset = offsets[8]; // 8 byte string
	//			long renderInfoOffset1 = offsets[9];
	//			long renderInfoOffset2 = offsets[10];
	//			long renderInfoOffset3 = offsets[11];
	//			long renderInfoOffset4 = offsets[12];
	//			tmdlOffset = offsets[12];
	//			*/
	//			std::string meshName;
	//			bool firstTime = true;
	//			for (int l = 0; l < offsets.size(); l++)
	//			{
	//				long tmdl;
	//				int marker;
	//				int currently;
	//				int vertexStride;
	//				if (!firstTime)
	//				{
	//					chunkOffset = tmdlOffset + offsets[l];

	//				}
	//				else
	//				{
	//					l--;
	//					firstTime = false;
	//				}

	//				fseek(f, chunkOffset, SEEK_SET);
	//				if (ReadLong(f) == 0)
	//				{
	//					return;
	//				}
	//				fseek(f, -4, SEEK_CUR);
	//				tmdl = ReadLong(f);
	//				int currently2 = ftell(f);
	//				if (tmdl != 1279544660) //There are two types of Models, TMDL and this one without any tag (why?)
	//				{
	//					if (ReadLong(f) == 0)
	//					{
	//						return;
	//					}
	//					fseek(f, -4, SEEK_CUR);
	//					vertexStride = 52;
	//					//vertexStride 52!
	//					fseek(f, 44, SEEK_CUR);
	//					long UnknowntableOffset;
	//					fread_s(&UnknowntableOffset, 4, 4, 1, f);
	//					fseek(f, chunkOffset, SEEK_SET);
	//					long meshNameOffset;
	//					fread_s(&meshNameOffset, 4, 4, 1, f);
	//					fseek(f, meshNameOffset + chunkOffset, SEEK_SET);
	//					meshName = ReadString(f);
	//					meshName = meshName.erase(meshName.length() - 4);
	//					fseek(f, UnknowntableOffset + chunkOffset, SEEK_SET);
	//					fseek(f, 8, SEEK_CUR);
	//					long meshNameOffsetEnd;
	//					fread_s(&meshNameOffsetEnd, 4, 4, 1, f);
	//					fseek(f, meshNameOffsetEnd + chunkOffset, SEEK_SET);
	//					fseek(f, 132, SEEK_CUR);
	//					int meshInfoCount;
	//					fread_s(&meshInfoCount, 4, 4, 1, f);
	//					long beginOfMeshInfoOffsets;
	//					fread_s(&beginOfMeshInfoOffsets, 4, 4, 1, f);
	//					long firstMeshOffset;
	//					fread_s(&firstMeshOffset, 4, 4, 1, f);
	//					fseek(f, beginOfMeshInfoOffsets + chunkOffset, SEEK_SET);
	//					long meshInfoOffset;
	//					long meshInfoOffsetEnd;
	//					long test;
	//					int k = 0;
	//					for (int i = 0; i < meshInfoCount; i++)
	//					{
	//						fread_s(&meshInfoOffset, 4, 4, 1, f);
	//						meshInfoOffsets.push_back(meshInfoOffset);
	//					}
	//					fseek(f, firstMeshOffset + chunkOffset, SEEK_SET);
	//					fseek(f, 20, SEEK_CUR);
	//					int unknownCount;
	//					fread_s(&unknownCount, 4, 4, 1, f);
	//					long skip;
	//					/*
	//					if (unknownCount == 1)
	//					{
	//						fseek(f, 4, SEEK_CUR);
	//					}
	//					else
	//					{
	//						skip = unknownCount * 2;
	//						fseek(f, skip, SEEK_CUR);
	//					}
	//					fseek(f, 16, SEEK_CUR);
	//					fseek(f, 4, SEEK_CUR);
	//					*/
	//					fseek(f, 12, SEEK_CUR);
	//					long vertexCount;
	//					fread_s(&vertexCount, 4, 4, 1, f);
	//					fseek(f, 4, SEEK_CUR);
	//					long faceCount;
	//					fread_s(&faceCount, 4, 4, 1, f);
	//					long vertexInfoOffset;
	//					fread_s(&vertexInfoOffset, 4, 4, 1, f);
	//					long vertexOffset;
	//					fread_s(&vertexOffset, 4, 4, 1, f);
	//					long faceOffset;
	//					fread_s(&faceOffset, 4, 4, 1, f);
	//					faceIndicesCount.push_back(faceCount);
	//					verticesCount.push_back(vertexCount);
	//					faceOffsets.push_back(faceOffset);
	//					vertexOffsets.push_back(vertexOffset);
	//					if (meshInfoCount > 1)
	//					{
	//						for (int x = 0; x < meshInfoOffsets.size()-1; x++)
	//						{
	//							fseek(f, meshInfoOffsets[x] + chunkOffset, SEEK_SET);
	//							fseek(f, 24, SEEK_CUR);
	//							fseek(f, 16, SEEK_CUR);
	//							if (ftell(f) == (vertexOffsets[0] + chunkOffset))
	//							{
	//								break;
	//							}
	//							
	//							fseek(f, -16, SEEK_CUR);
	//							long vertexCount;
	//							fread_s(&vertexCount, 4, 4, 1, f);
	//							fseek(f, 4, SEEK_CUR);
	//							long faceCount;
	//							fread_s(&faceCount, 4, 4, 1, f);
	//							long vertexInfoOffset;
	//							fread_s(&vertexInfoOffset, 4, 4, 1, f);
	//							long vertexOffset;
	//							fread_s(&vertexOffset, 4, 4, 1, f);
	//							long faceOffset;
	//							fread_s(&faceOffset, 4, 4, 1, f);

	//							faceIndicesCount.push_back(faceCount);
	//							verticesCount.push_back(vertexCount);
	//							faceOffsets.push_back(faceOffset);
	//							vertexOffsets.push_back(vertexOffset);
	//						}
	//					}

	//				}
	//				else
	//				{
	//					vertexStride = 44;
	//					
	//					/*
	//					fseek(f, currently, SEEK_SET);
	//					fseek(f, 12, SEEK_CUR);
	//					fread_s(&meshNameOffset, 4, 4, 1, f);
	//					long meshNameOffset;

	//					if (meshNameOffset != 0)
	//					{
	//						fseek(f, meshNameOffset + chunkOffset, SEEK_SET);

	//						meshName = ReadString(f);


	//					}
	//					else
	//					{
	//						fseek(f, 88, SEEK_CUR); //Unknown
	//						fread_s(&meshNameOffset, 4, 4, 1, f);
	//						fseek(f, meshNameOffset + chunkOffset, SEEK_SET);
	//						fseek(f, -16, SEEK_CUR); //Unknown
	//						meshName = ReadString(f);
	//					}
	//					*/
	//					fseek(f, 44, SEEK_CUR); //Unknown
	//					short AnimationCount;
	//					fread_s(&AnimationCount, 2, 2, 1, f);
	//					fseek(f, 50, SEEK_CUR); //Unknown
	//					long AnimationOffset;
	//					fread_s(&AnimationOffset, 4, 4, 1, f);
	//					fseek(f, 4, SEEK_CUR);
	//					long UnknownlistOffset;
	//					fread_s(&UnknownlistOffset, 4, 4, 1, f);
	//					int UnknownlistCount;
	//					fread_s(&UnknownlistCount, 4, 4, 1, f);
	//					fseek(f, UnknownlistOffset + chunkOffset, SEEK_SET);
	//					long skip = UnknownlistCount * 16;
	//					fseek(f, skip, SEEK_CUR);
	//					long switchTableOffset = ftell(f);
	//					fseek(f, AnimationOffset + chunkOffset, SEEK_SET);
	//					skip = AnimationCount * 24;
	//					fseek(f, skip, SEEK_CUR);
	//					long test;
	//					fread_s(&test, 4, 4, 1, f);
	//					if (test == 0)
	//					{
	//						fseek(f, 20, SEEK_CUR);
	//					}
	//					fseek(f, 28, SEEK_CUR);
	//					fseek(f, 20, SEEK_CUR);
	//					long nameOffset;
	//					fread_s(&nameOffset, 4, 4, 1, f);
	//					fseek(f, 4, SEEK_CUR);
	//					long meshInfoInfoOffset;
	//					fread_s(&meshInfoInfoOffset, 4, 4, 1, f);
	//					fseek(f, nameOffset + chunkOffset, SEEK_SET);
	//					fseek(f, 4, SEEK_CUR);
	//					meshName = ReadString(f);
	//					fseek(f, meshInfoInfoOffset + chunkOffset, SEEK_SET);
	//					fseek(f, 8, SEEK_CUR);
	//					int meshInfoCount;
	//					fread_s(&meshInfoCount, 4, 4, 1, f);
	//					long meshNameOffset;
	//					long meshInfoOffset;
	//					std::vector<long> meshInfoOffsets1;
	//					for (int i = 0; i < meshInfoCount; i++)
	//					{
	//						long c;
	//						fread_s(&c, 4, 4, 1, f);
	//						meshInfoOffsets1.push_back(c + chunkOffset);
	//					}
	//					for (int i = 0; i < meshInfoOffsets1.size(); i++)
	//					{
	//						fseek(f, meshInfoOffsets1[i], SEEK_SET);
	//						fseek(f, 16, SEEK_CUR);
	//						fread_s(&meshNameOffset, 4, 4, 1, f);
	//						fread_s(&meshInfoOffset, 4, 4, 1, f);
	//						meshInfoOffsets.push_back(meshInfoOffset);
	//					}
	//					/*

	//					fseek(f, NamelistOffset + chunkOffset, SEEK_SET);
	//					long animationNamelistOffset;
	//					fread_s(&animationNamelistOffset, 4, 4, 1, f);
	//					fseek(f, animationNamelistOffset + chunkOffset, SEEK_SET);
	//					fseek(f, 16, SEEK_CUR);
	//					long txsFileNameOffset = ftell(f);
	//					fseek(f, switchTableOffset, SEEK_SET);
	//					fseek(f, 16, SEEK_CUR);
	//					long meshNameOffset;
	//					long meshInfoOffset;
	//					long test;
	//					int k = 0;
	//					while (true)
	//					{
	//						fread_s(&meshNameOffset, 4, 4, 1, f);
	//						if (k == 0)
	//						{
	//							int before = ftell(f);
	//							fseek(f, meshNameOffset + chunkOffset, SEEK_SET);
	//							meshName = ReadString(f);
	//							fseek(f, before, SEEK_SET);
	//						}
	//						fread_s(&meshInfoOffset, 4, 4, 1, f);
	//						fread_s(&test, 4, 4, 1, f);
	//						fseek(f, 12, SEEK_CUR);
	//						int tell = ftell(f);
	//						if (test > 0xFFFF)
	//						{

	//							fseek(f, -48, SEEK_CUR);
	//							fread_s(&meshNameOffset, 4, 4, 1, f);
	//							fread_s(&meshInfoOffset, 4, 4, 1, f);
	//							break;
	//						}
	//						meshInfoOffsets.push_back(meshInfoOffset);
	//						k++;
	//					}
	//											*/
	//					for (int x = 0; x < meshInfoOffsets.size(); x++)
	//					{
	//						fseek(f, meshInfoOffsets[x] + chunkOffset, SEEK_SET);
	//						long vertexCount;
	//						fread_s(&vertexCount, 4, 4, 1, f);
	//						fseek(f, 4, SEEK_CUR);
	//						long faceCount;
	//						fread_s(&faceCount, 4, 4, 1, f);

	//						long meshCount;
	//						fread_s(&meshCount, 4, 4, 1, f);
	//						long vertexInfoOffset;
	//						fread_s(&vertexInfoOffset, 4, 4, 1, f);
	//						long vertexOffset;
	//						fread_s(&vertexOffset, 4, 4, 1, f);
	//						long faceOffset;
	//						fread_s(&faceOffset, 4, 4, 1, f);

	//						faceIndicesCount.push_back(faceCount);
	//						verticesCount.push_back(vertexCount);
	//						faceOffsets.push_back(faceOffset);
	//						vertexOffsets.push_back(vertexOffset);
	//						meshCounts.push_back(meshCount);
	//					}
	//				}
	//				if (vertexStride == 44)
	//				{
	//					for (int j = 0; j < vertexOffsets.size(); j++)
	//					{
	//						fseek(f, vertexOffsets[j] + chunkOffset, SEEK_SET);
	//						int tell = ftell(f);
	//						for (int y = 0; y < verticesCount[j]; y++)
	//						{
	//							float vertexX;
	//							fread_s(&vertexX, 4, 4, 1, f);
	//							float vertexY;
	//							fread_s(&vertexY, 4, 4, 1, f);
	//							float vertexZ;
	//							fread_s(&vertexZ, 4, 4, 1, f);
	//							float normalX;
	//							fread_s(&normalX, 4, 4, 1, f);
	//							float normalY;
	//							fread_s(&normalY, 4, 4, 1, f);
	//							float normalZ;
	//							fread_s(&normalZ, 4, 4, 1, f);
	//							fseek(f, 4, SEEK_CUR);
	//							half uvU;;
	//							fread_s(&uvU, 2, 2, 1, f);
	//							half uvV;
	//							fread_s(&uvV, 2, 2, 1, f);
	//							fseek(f, 12, SEEK_CUR);

	//							vertices.push_back(vertexX * fscale);
	//							vertices.push_back(vertexY * fscale);
	//							vertices.push_back(vertexZ * fscale);
	//							normals.push_back(normalX);
	//							normals.push_back(normalY);
	//							normals.push_back(normalZ);
	//							uvs.push_back(uvU);
	//							uvs.push_back((half)1.0 - uvV);
	//						}
	//						fseek(f, faceOffsets[j] + chunkOffset, SEEK_SET);
	//						for (int a = 0; a < faceIndicesCount[j] / 3; a++)
	//						{
	//							int tell = ftell(f);
	//							unsigned short faceA = 0;
	//							unsigned short faceB = 0;
	//							unsigned short faceC = 0;

	//							fread_s(&faceA, 2, 2, 1, f);
	//							fread_s(&faceB, 2, 2, 1, f);
	//							fread_s(&faceC, 2, 2, 1, f);
	//							faces.push_back(faceA);
	//							faces.push_back(faceB);
	//							faces.push_back(faceC);
	//						}
	//						int tell2 = ftell(f);
	//						tell2 = ftell(f);
	//					}
	//				}
	//				else
	//				{
	//					for (int j = 0; j < vertexOffsets.size(); j++)
	//					{
	//						fseek(f, vertexOffsets[j] + chunkOffset, SEEK_SET);
	//						int tell = ftell(f);
	//						for (int y = 0; y < verticesCount[j]; y++)
	//						{
	//							float vertexX;
	//							fread_s(&vertexX, 4, 4, 1, f);
	//							float vertexY;
	//							fread_s(&vertexY, 4, 4, 1, f);
	//							float vertexZ;
	//							fread_s(&vertexZ, 4, 4, 1, f);
	//							float normalX;
	//							fread_s(&normalX, 4, 4, 1, f);
	//							float normalY;
	//							fread_s(&normalY, 4, 4, 1, f);
	//							float normalZ;
	//							fread_s(&normalZ, 4, 4, 1, f);
	//							fseek(f, 4, SEEK_CUR);
	//							half uvU;;
	//							fread_s(&uvU, 2, 2, 1, f);
	//							half uvV;
	//							fread_s(&uvV, 2, 2, 1, f);
	//							fseek(f, 20, SEEK_CUR);

	//							vertices.push_back(vertexX * fscale);
	//							vertices.push_back(vertexY * fscale);
	//							vertices.push_back(vertexZ * fscale);
	//							normals.push_back(normalX);
	//							normals.push_back(normalY);
	//							normals.push_back(normalZ);
	//							uvs.push_back(uvU);
	//							uvs.push_back((half)1.0 - uvV);
	//						}
	//						fseek(f, faceOffsets[j] + chunkOffset, SEEK_SET);
	//						for (int a = 0; a < faceIndicesCount[j] / 3; a++)
	//						{
	//							int tell = ftell(f);
	//							unsigned short faceA = 0;
	//							unsigned short faceB = 0;
	//							unsigned short faceC = 0;

	//							fread_s(&faceA, 2, 2, 1, f);
	//							fread_s(&faceB, 2, 2, 1, f);
	//							fread_s(&faceC, 2, 2, 1, f);
	//							faces.push_back(faceA);
	//							faces.push_back(faceB);
	//							faces.push_back(faceC);
	//						}
	//						int tell2 = ftell(f);
	//						tell2 = ftell(f);
	//					}
	//				}

	//				//
	//				//long test1;
	//				//int tell1 = ftell(f);
	//				//do
	//				//{
	//				//	tell1 = ftell(f);
	//				//	fread_s(&test1, 4, 4, 1, f);
	//				//} while (test1 < 0xFF && test1 >= 0 );
	//				///*
	//				//fseek(f, 24, SEEK_CUR);

	//				//Byte skip32;
	//				//fread_s(&skip32, 1, 1, 1, f);
	//				//if (skip32 != 0)
	//				//{
	//				//	fseek(f, 31, SEEK_CUR);
	//				//}
	//				//else
	//				//{
	//				//	fseek(f, 3, SEEK_CUR);
	//				//}
	//				//*/
	//				//fseek(f, -4, SEEK_CUR);
	//				//tell1 = ftell(f);
	//				//float vertexX = 0;
	//				//bool _break = false;
	//				////Here MeshDataBegins!
	//				//do
	//				//{
	//				//	do
	//				//	{
	//				//		int tell = ftell(f);
	//				//		unsigned short faceA = 0;
	//				//		unsigned short faceB = 0;
	//				//		fread_s(&faceA, 2, 2, 1, f);
	//				//		fread_s(&faceB, 2, 2, 1, f);

	//				//		if (faceA == 0 && faceB == 1)
	//				//		{
	//				//			fseek(f, -4, SEEK_CUR);
	//				//			break;
	//				//		}
	//				//		else
	//				//		{
	//				//			fseek(f, -4, SEEK_CUR);
	//				//		}
	//				//		fread_s(&vertexX, 4, 4, 1, f);
	//				//		float vertexY;
	//				//		fread_s(&vertexY, 4, 4, 1, f);
	//				//		float vertexZ;
	//				//		fread_s(&vertexZ, 4, 4, 1, f);
	//				//		float normalX;
	//				//		fread_s(&normalX, 4, 4, 1, f);
	//				//		float normalY;
	//				//		fread_s(&normalY, 4, 4, 1, f);
	//				//		float normalZ;
	//				//		fread_s(&normalZ, 4, 4, 1, f);
	//				//		fseek(f, 4, SEEK_CUR);
	//				//		half uvU;;
	//				//		fread_s(&uvU, 2, 2, 1, f);
	//				//		half uvV;
	//				//		fread_s(&uvV, 2, 2, 1, f);
	//				//		fseek(f, 12, SEEK_CUR);

	//				//		vertices.push_back(vertexX * fscale);
	//				//		vertices.push_back(vertexY * fscale);
	//				//		vertices.push_back(vertexZ * fscale);
	//				//		normals.push_back(normalX);
	//				//		normals.push_back(normalY);
	//				//		normals.push_back(normalZ);
	//				//		uvs.push_back(uvU);
	//				//		uvs.push_back((float)1.0 - uvV);

	//				//		verticesAll.push_back(vertexX * fscale);
	//				//		verticesAll.push_back(vertexY * fscale);
	//				//		verticesAll.push_back(vertexZ * fscale);
	//				//		normalsAll.push_back(normalX);
	//				//		normalsAll.push_back(normalY);
	//				//		normalsAll.push_back(normalZ);
	//				//		uvsAll.push_back(uvU);
	//				//		uvsAll.push_back((float)1.0 - uvV);
	//				//	} while (true);
	//				//	int tell = ftell(f);
	//				//	long cur = ftell(f);
	//				//	long stop = 0;
	//				//	do
	//				//	{
	//				//		long t = 0;
	//				//		long t1 = 0;

	//				//		fread_s(&t, 4, 4, 1, f);
	//				//		fread_s(&t1, 4, 4, 1, f);
	//				//		if ((t < 0xFF && t >= 0) && (t1 >= 0 && t1 < 0xFF))
	//				//		{
	//				//			/*
	//				//			if ((MeshOffsetEnd + chunkOffset) < ftell(f))
	//				//			{
	//				//				int tell = ftell(f);
	//				//				fseek(f, offsets[i], SEEK_SET);
	//				//				chunkOffset = offsets[i];
	//				//				_break = true;
	//				//			}
	//				//			else
	//				//			{
	//				//				int tell3 = ftell(f);
	//				//				do
	//				//				{
	//				//					fread_s(&t, 4, 4, 1, f);
	//				//				} while (t < 0xFF && t >= 0);
	//				//				//fread_s(&t, 4, 4, 1, f);
	//				//				int tell = ftell(f);
	//				//				fseek(f, -4, SEEK_CUR);

	//				//			}
	//				//			break;
	//				//			*/
	//				//			fseek(f, -8, SEEK_CUR);
	//				//			stop = ftell(f);
	//				//			break;
	//				//		}
	//				//	} while (true);
	//				//	do
	//				//	{
	//				//		int tell = ftell(f);
	//				//		unsigned short faceA = 0;
	//				//		unsigned short faceB = 0;
	//				//		unsigned short faceC = 0;


	//				//		//if (faceA == 1 && faceB == 0 && faceC == 0)
	//				//		//{
	//				//		//	fseek(f, 10, SEEK_CUR);
	//				//		//	break;
	//				//		//}
	//				//		//if (faceA == 0 && faceB != 1 && faceC != 2)
	//				//		//{
	//				//		//	fseek(f, 6, SEEK_CUR);
	//				//		//	_break = true;
	//				//		//	break;
	//				//		//}

	//				//		fread_s(&faceA, 2, 2, 1, f);
	//				//		fread_s(&faceB, 2, 2, 1, f);
	//				//		fread_s(&faceC, 2, 2, 1, f);
	//				//		faces.push_back(faceA);
	//				//		faces.push_back(faceB);
	//				//		faces.push_back(faceC);

	//				//		facesAll.push_back(faceA);
	//				//		facesAll.push_back(faceB);
	//				//		facesAll.push_back(faceC);
	//				//	} while (ftell(f) < stop);
	//				//	int tell3 = ftell(f);
	//				//	long t = 0;

	//				//	if (ftell(f) > (faceOffset + chunkOffset))
	//				//	{
	//				//		fseek(f, offsets[i], SEEK_SET);
	//				//		chunkOffset = offsets[i];
	//				//		_break = true;
	//				//	}
	//				//	else
	//				//	{
	//				//		do
	//				//		{
	//				//			fread_s(&t, 4, 4, 1, f);
	//				//		} while (t < 0xFF && t >= 0);
	//				//		//fread_s(&t, 4, 4, 1, f);
	//				//		int tell = ftell(f);
	//				//		fseek(f, -4, SEEK_CUR);
	//				//	}
	//				//	if (_break == false)
	//				//	{
	//				//		meshCount++;
	//				//	}


	//				//	verticesCount.push_back(vertices.size());
	//				//	faceIndicesCount.push_back(faces.size());
	//				//	vertices.clear();
	//				//	faces.clear();
	//				//	uvs.clear();
	//				//	normals.clear();

	//				//} while (_break == false);


	//				//fseek(f, NamelistOffsetEnd + chunkOffset, SEEK_SET);
	//				//fseek(f, animationNamelistOffset + chunkOffset, SEEK_SET);

	//				int tell = ftell(f);
	//				/*
	//				tmdlOffset = offsets[0];
	//				printf("");
	//				*/
	//				FbxManager* lSdkManager = FbxManager::Create();
	//				FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
	//				FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	//				lSdkManager->SetIOSettings(ios);
	//				int sumVertices = 0;
	//				int Viord = 0;
	//				int index = 0;
	//				int rememberI = 0;
	//				int remeberU = 0;
	//				int Niord = 0;
	//				for (int z = 0; z < vertexOffsets.size(); z++)
	//				{
	//					char meshNode[8];
	//					snprintf(meshNode, sizeof meshNode, "Mesh_%d", z);
	//					char mesh[8];
	//					snprintf(mesh, sizeof mesh, "Mesh_%d", z);
	//					FbxNode* lMeshNode = FbxNode::Create(lScene, meshNode);
	//					FbxMesh* lMesh = FbxMesh::Create(lScene, mesh);
	//					lMeshNode->SetNodeAttribute(lMesh);
	//					FbxNode* lRootNode = lScene->GetRootNode();
	//					FbxNode* lPatchNode = lScene->GetRootNode();
	//					lRootNode->AddChild(lMeshNode);
	//					lMesh->InitControlPoints(verticesCount[z]);
	//					FbxVector4* lControlPoints = lMesh->GetControlPoints();
	//					FbxLayer* lLayer = lMesh->GetLayer(0);
	//					if (lLayer == NULL) {
	//						lMesh->CreateLayer();
	//						lLayer = lMesh->GetLayer(0);
	//					}

	//					FbxLayerElementNormal* lLayerElementNormal = FbxLayerElementNormal::Create(lMesh, "");
	//					FbxLayerElementUV* lLayerElementUV = FbxLayerElementUV::Create(lMesh, "");
	//					// Set its mapping mode to map each normal vector to each control point.
	//					lLayerElementNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
	//					lLayerElementUV->SetMappingMode(FbxLayerElement::eByControlPoint);
	//					// Set the reference mode of so that the n'th element of the normal array maps to the n'th
	//					// element of the control point array.
	//					lLayerElementNormal->SetReferenceMode(FbxLayerElement::eDirect);
	//					lLayerElementUV->SetReferenceMode(FbxLayerElement::eDirect);
	//					for (int j = 0; j < verticesCount[z]; j++)
	//					{
	//						FbxVector4 vertex(vertices[Viord], vertices[Viord + 1], vertices[Viord + 2]);
	//						FbxVector4 normal(normals[Niord], normals[Niord + 1], normals[Niord + 2]);
	//						FbxVector2 uv(uvs[remeberU], uvs[remeberU + 1]);
	//						lLayerElementNormal->GetDirectArray().Add(normal);
	//						lLayerElementUV->GetDirectArray().Add(uv);
	//						lControlPoints[j] = vertex;
	//						Viord += 3;
	//						Niord += 3;
	//						remeberU += 2;

	//					}
	//					for (int y = 0; y < faceIndicesCount[z] / 3; y++)
	//					{
	//						lMesh->BeginPolygon();
	//						lMesh->AddPolygon(faces[rememberI]);
	//						lMesh->AddPolygon(faces[rememberI + 1]);
	//						lMesh->AddPolygon(faces[rememberI + 2]);
	//						lMesh->EndPolygon();
	//						rememberI += 3;

	//					}
	//					lLayer->SetNormals(lLayerElementNormal);
	//					lLayer->SetUVs(lLayerElementUV);
	//					//lMeshNode->LclRotation.Set(FbxVector4(-90.0, -90.0, 0.0)); //Right rotation
	//					TCHAR  dir[1024] = { 0 };
	//					const char* pChar = strrchr(_fileName, 92);

	//					if (pChar == NULL)				// If no backslash is found
	//						pChar = _fileName;			// Reset pChar
	//					else
	//						pChar++;	// Skip the last backslash
	//					std::string lFilename;
	//					System::String^ path = gcnew String(_fileName);
	//					System::String^ file = System::IO::Path::GetFileNameWithoutExtension(path);
	//					System::String^ NewPath = path->Replace(file, gcnew String(meshName.c_str()));
	//					lFilename = (char*)(void*)Marshal::StringToHGlobalAnsi(NewPath);
	//					int length = lFilename.length();
	//					lFilename.erase(length - 4);
	//					lFilename.append(".fbx");
	//					strcat_s(dir, 256, lFilename.c_str());

	//					getDir(_fileName, dir);
	//					FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");
	//					bool lExportStatus = lExporter->Initialize(dir, -1, lSdkManager->GetIOSettings());
	//					if (!lExportStatus) {
	//						throw gcnew System::Exception(gcnew System::String("Call to FbxExporter::Initialize() failed."));
	//					}
	//					lExporter->Export(lScene);
	//					lExporter->Destroy();
	//				}

	//				/*
	//				char temp[5];
	//				fread_s(temp, 4, 4, 1, f);
	//				chunkTag = temp;
	//				chunkTag.erase(4);
	//				if (chunkTag == "TMDL")
	//				{
	//					fseek(f, 12, SEEK_CUR); //Unknown
	//					long nameOffset = 0;
	//					fread_s(&nameOffset, 4, 4, 1, f);

	//				}
	//				chunkOffset = ftell(f);
	//				*/
	//				vertices.clear();
	//				faces.clear();
	//				normals.clear();
	//				uvs.clear();
	//				verticesCount.clear();
	//				faceIndicesCount.clear();
	//				faceOffsets.clear();
	//				vertexOffsets.clear();
	//				meshInfoOffsets.clear();
	//				meshName.clear();
	//			}



	//		}
	//		if (_break == true)
	//		{
	//			break;
	//		}
	//		chunkOffset += chunkSize;
	//		fseek(f, chunkOffset, SEEK_SET);

	//	} while (chunkOffset != fileSize - 1);
	//}
	//int Trb::getDir(TCHAR* fullPath, TCHAR* dir)
	//{
	//	
	//	const int buffSize = 1024;

	//	TCHAR buff[buffSize] = { 0 };
	//	int buffCounter = 0;
	//	int dirSymbolCounter = 0;

	//	for (unsigned int i = 0; i < strlen(fullPath); i++) {
	//		if (fullPath[i] != L'\\') {
	//			if (buffCounter < buffSize) buff[buffCounter++] = fullPath[i];
	//			else return -1;
	//		}
	//		else {
	//			for (int i2 = 0; i2 < buffCounter; i2++) {
	//				dir[dirSymbolCounter++] = buff[i2];
	//				buff[i2] = 0;
	//			}

	//			dir[dirSymbolCounter++] = fullPath[i];
	//			buffCounter = 0;
	//		}
	//	}

	//	return dirSymbolCounter;
	//}
}
