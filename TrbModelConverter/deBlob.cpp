#include "deBlob.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

void deBlob::read(FILE* f, Reader::Endian endian, std::string filename, System::Windows::Forms::ProgressBar^ pgb, System::Windows::Forms::ListView^ lv)
{
	Reader::e = endian;
	TSFL tsfl(f, endian);
	pgb->Maximum = tsfl.symb.nameOffsets.size();
	long baseChunk = ftell(f);
	long chunk = ftell(f);
	TMDL tmdl;
	std::vector<std::string> meshNames;
	std::string directory;
	const size_t last_slash_idx = filename.rfind('\\');
	std::vector<std::vector<uint8_t>> ddsHeaders;
	std::vector<std::vector<uint8_t>> ddsDatas;
	std::vector<TextureInfo> textureInfos;
	int textureCounter = 1;
	if (std::string::npos != last_slash_idx)
	{
		directory = filename.substr(0, last_slash_idx);
	}
	for (size_t x = 0; x < tsfl.symb.nameOffsets.size(); x++)
	{
		if (tsfl.symb.nameOffsets[x].ID == 0)
		{
			fseek(f, chunk + tsfl.symb.nameOffsets[x].dataOffset, SEEK_SET);
			//if (x == 0)
			//{
			//	//tsfl.relc.writeFile(f, chunk, tsfl.symb.nameOffsets[x].ID);
			//}
		}
		else
		{
			chunk = tsfl.hdrx.tagInfos[tsfl.symb.nameOffsets[x].ID - 1].tagSize + baseChunk;
			fseek(f, chunk + tsfl.symb.nameOffsets[x].dataOffset, SEEK_SET);
			//if (tsfl.symb.nameOffsets[x].ID != tsfl.symb.nameOffsets[x - 1].ID)
			//{
			//	//tsfl.relc.writeFile(f, chunk, tsfl.symb.nameOffsets[x].ID);
			//}
		}
		if (tsfl.symb.nameOffsets[x].name == "tmat")
		{
			uint32_t zero = ReadUInt(f);
			uint32_t unknown = ReadUInt(f);
			zero = ReadUInt(f);
			uint32_t meshNameOffset = ReadUInt(f);
			uint32_t one = ReadUInt(f);
			uint32_t meshNameOffsetEnd = ReadUInt(f);
			fseek(f, meshNameOffset + chunk, SEEK_SET);
			std::string meshNamebelong = ReadString(f);
			fseek(f, meshNameOffsetEnd + chunk, SEEK_SET);
			zero = ReadUInt(f);
			uint32_t texNameOffset = ReadUInt(f);
			fseek(f, texNameOffset + chunk, SEEK_SET);
			std::string texname = ReadString(f);
		}
		else if (tsfl.symb.nameOffsets[x].name == "LocaleStrings")
		{
			uint32_t stringCount = ReadUInt(f);
			fseek(f, chunk, SEEK_SET);
			for (size_t i = 0; i < stringCount; i++)
			{
				uint32_t stringOffset = ReadUInt(f);
				long rt = ftell(f);
				fseek(f, stringOffset + chunk, SEEK_SET);
				uint16_t c = ReadUShort(f);
				fseek(f, -2, SEEK_CUR);
				if (c > 0xFF) // ASCII
				{
					lv->Items->Add(gcnew System::String(ReadString(f).c_str()));
				}
				else // Unicode
				{
					lv->Items->Add(gcnew System::String(ReadUnicodeString(f).c_str()));
				}
				fseek(f, rt, SEEK_SET);
			}
		}
		else if (tsfl.symb.nameOffsets[x].name == "txui") // Most hackiest shit i have ever sawn! This is Big Endian!
		{
			uint32_t zero = ReadUInt(f);
			uint32_t fileNameOffset = ReadUInt(f);
			fseek(f, fileNameOffset + chunk, SEEK_SET);
			std::string fileName = ReadString(f);
			System::Windows::Forms::ListViewItem^ lvi = gcnew System::Windows::Forms::ListViewItem(gcnew System::String(fileName.c_str()));
			lvi->Font = gcnew System::Drawing::Font(lvi->Font, System::Drawing::FontStyle::Bold);
			lv->Items->Add(lvi);
			fseek(f, tsfl.hdrx.tagInfos[tsfl.symb.nameOffsets[x].ID].tagSize + baseChunk, SEEK_SET);
			std::string XUIB = ReadString(f, 4);
			Reader::e = Reader::BIG;
			uint32_t unknown1 = ReadUInt(f);
			uint32_t unknown2 = ReadUInt(f);
			uint16_t unknown3 = ReadUShort(f);
			uint16_t unknown4 = ReadUShort(f);
			uint16_t xuibSize = ReadUShort(f);
			uint16_t subLabelCount = ReadUShort(f);
			if (unknown2 != 0)
			{
				fseek(f, 40, SEEK_CUR); // Unknown Data
			}
			for (size_t i = 0; i < subLabelCount; i++)
			{
				std::string subLabel = ReadString(f, 4);
				uint32_t subLabelOffset = ReadUInt(f);
				uint32_t subLabelSize = ReadUInt(f);
				if (subLabel == "STRN")
				{
					long remember = ftell(f);
					fseek(f, tsfl.hdrx.tagInfos[tsfl.symb.nameOffsets[x].ID].tagSize + baseChunk + subLabelOffset, SEEK_SET);
					while (ftell(f) < subLabelSize + tsfl.hdrx.tagInfos[tsfl.symb.nameOffsets[x].ID].tagSize + baseChunk)
					{
						uint16_t charCount = ReadUShort(f);
						std::wstring str = ReadUnicodeString(f, charCount);
						lv->Items->Add(gcnew System::String(str.c_str()));
					}
					fseek(f, remember, SEEK_SET);
				}
				else if (subLabel == "VECT") // Positions?
				{
				}
				else if (subLabel == "QUAT") // just a quat 4 floats
				{

				}
				else if (subLabel == "CUST") // No clue it isn't useless though because game crashes if you 0 it out
				{
				}
			}
			Reader::e = Endian::LITTLE;
		}
		else if (tsfl.symb.nameOffsets[x].name == "ttex")
		{
			TTEX ttex = { ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
			fseek(f, ttex.nameOffset + chunk, SEEK_SET);
			std::string textureNameOrginial = ReadString(f);
			std::string textureName = directory + "//";
			textureName += textureNameOrginial; textureName = textureName.erase(textureName.size() - 3); textureName += "dds";
			fseek(f, ttex.textureInfoOffset + chunk, SEEK_SET);
			TextureInfo ti = { ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadBytes(f,4), ReadUInt(f)};
			fseek(f, ttex.ddsOffset + chunk, SEEK_SET);

			std::vector<uint8_t> ddsData = ReadBytes(f, ttex.ddsSize);
			FILE* fTex;
			if (fopen_s(&fTex, textureName.c_str(), "wb") != 0) // Security check
			{
				return;
			}
			for (size_t j = 0; j < ttex.ddsSize; j++)
			{
				fwrite(&ddsData[j], 1, 1, fTex);
			}
			fclose(fTex);

			if (textureCounter == 6)
			{
				std::string textureNameRaw = textureNameOrginial.erase(textureNameOrginial.size() - 6);
				char buf[256];
				GetCurrentDirectoryA(256, buf);
				std::string test = buf;
				std::string cmdLinePart1 = "\"" + test + "\\ImageHelp\\montage.exe\"";
				std::string cmdLine = test + "\\ImageHelp\\montage.exe" + " \"" + directory + "\\" + textureNameRaw + "_1.dds" + "\" \"" +
					directory + "\\" + textureNameRaw + "_2.dds" + "\" \"" +
					directory + "\\" + textureNameRaw + "_3.dds" + "\" \"" +
					directory + "\\" + textureNameRaw + "_4.dds" + "\" \"" +
					directory + "\\" + textureNameRaw + "_5.dds" + "\" \"" +
					directory + "\\" + textureNameRaw + "_6.dds" + "\" " +
					"-mode Concatenate -tile 3x3 " + "\"" + directory + "\\" + textureNameRaw + ".png" + "\"\0";
				FILE* bFile;
				std::string test2 = test + "\\ImageHelp\\sample.bat";
				if (fopen_s(&bFile, test2.c_str(), "wb") != 0) // Security check
				{
					return;
				}
				fwrite(cmdLine.c_str(), cmdLine.size(), 1, bFile);
				fclose(bFile);
				STARTUPINFO info = { sizeof(info) };
				PROCESS_INFORMATION processInfo;
				if (CreateProcess(NULL, (char*)test2.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo))
				{
					WaitForSingleObject(processInfo.hProcess, INFINITE);
					CloseHandle(processInfo.hProcess);
					CloseHandle(processInfo.hThread);
				}
			}
			if (textureNameOrginial.substr(textureNameOrginial.size() - 6, 2) == "_" + std::to_string(textureCounter))
			{
				textureCounter++;
			}
		}
		else if (tsfl.symb.nameOffsets[x].name == "FileHeader")
		{
			tmdl.fileHeader = { ReadString(f,4), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
		}
		else if (tsfl.symb.nameOffsets[x].name == "SkeletonHeader")
		{
			tmdl.skeletonHeader = { ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
		}
		else if (tsfl.symb.nameOffsets[x].name == "Skeleton")
		{
			tmdl.skeleton = { ReadUInt(f), ReadUShort(f), ReadUShort(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f),
				ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
		}
		else if (tsfl.symb.nameOffsets[x].name == "Materials")
		{

		}
		else if (tsfl.symb.nameOffsets[x].name == "Collision")
		{

		}
		else if (tsfl.symb.nameOffsets[x].name == "tmod") //Toshi Model Big endian: Stride 12 Shorts!
		{
			tmdl.tmod.header = { ReadUInt(f), ReadUInt(f), ReadFloat(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
			fseek(f, tmdl.tmod.header.modelFileNameOffset + chunk, SEEK_SET);
			std::string modelName = ReadString(f);
			fseek(f, tmdl.tmod.header.meshInfoOffset + chunk, SEEK_SET);
			tmdl.tmod.meshesInfo = { ReadUInt(f), ReadUInt(f), ReadUInt(f) };
			for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
			{
				tmdl.tmod.meshesInfo.meshInfoOffsets.push_back(ReadUInt(f));
			}
			std::vector<std::string> meshNames;
			std::vector<uint32_t> verticesCount;
			std::vector<uint32_t> facesCount;
			for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
			{
				fseek(f, tmdl.tmod.meshesInfo.meshInfoOffsets[i] + chunk, SEEK_SET);
				tmdl.tmod.meshInfo.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) });
				fseek(f, tmdl.tmod.meshInfo[i].meshNameOffset + chunk, SEEK_SET);
				meshNames.push_back(ReadString(f));
			}
			for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
			{
				fseek(f, tmdl.tmod.meshInfo[i].meshSubInfoOffset + chunk, SEEK_SET);
				tmdl.tmod.meshSubInfo.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) });
				verticesCount.push_back(tmdl.tmod.meshSubInfo[i].vertexCount);
				facesCount.push_back(tmdl.tmod.meshSubInfo[i].faceCount);
			}
			std::vector<float> vertices;
			std::vector<float> normals;
			std::vector<uint32_t> faces;
			std::vector<float> uvs;

			for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
			{
				fseek(f, tmdl.tmod.meshSubInfo[i].vertexOffset + chunk, SEEK_SET);
				for (size_t j = 0; j < tmdl.tmod.meshSubInfo[i].vertexCount; j++)
				{
					vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f));
					normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f));
					fseek(f, 8, SEEK_CUR);
					uvs.push_back(ReadFloat(f)); uvs.push_back(-ReadFloat(f));
					fseek(f, 4, SEEK_CUR);
				}
				fseek(f, tmdl.tmod.meshSubInfo[i].faceOffset + chunk, SEEK_SET);
				for (size_t y = 0; y < tmdl.tmod.meshSubInfo[i].faceCount; y++)
				{
					faces.push_back(ReadUShort(f));
				}
			}
			std::string currentFileName = directory + "\\" + modelName.erase(modelName.size() - 4);
			FbxHelper::Model m = { vertices,faces,normals,uvs,verticesCount,facesCount,tmdl.tmod.meshesInfo.meshCount, meshNames };
			FbxHelper fbxH;
			fbxH.CreateFbx(m, currentFileName);
			tmdl.tmod = {};
		}
		else if (tsfl.symb.nameOffsets[x].name == "twld")
		{
			std::vector<std::string> meshNames;
			std::string modelName;
			tmdl.twld.header = { ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), { ReadFloat(f), ReadFloat(f), ReadFloat(f), ReadFloat(f)}, ReadUInt(f), ReadUInt(f) };
			fseek(f, tmdl.twld.header.modelFileNameOffset + chunk, SEEK_SET);
			modelName = ReadString(f);
			fseek(f, tmdl.twld.header.unknownInfoOffset + chunk, SEEK_SET);
			tmdl.twld.unknownInfo = { ReadUInt(f), ReadUInt(f), ReadUInt(f) };
			fseek(f, tmdl.twld.unknownInfo.unknownInfo2Offset + chunk, SEEK_SET);
			tmdl.twld.unknownInfo2 = { ReadUInt(f), ReadUInt(f), ReadUInt(f) };
			if (tmdl.twld.unknownInfo2.count != 0)
			{
				fseek(f, tmdl.twld.unknownInfo2.unknownInfo3Offset + chunk, SEEK_SET);
				tmdl.twld.unknownInfo3 = { ReadUInt(f), { ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f),
					ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f),
					ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f),
					ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) } };
				tmdl.twld.meshesInfo = { ReadUInt(f), ReadUInt(f), ReadUInt(f) };
				for (size_t i = 0; i < tmdl.twld.meshesInfo.meshInfoOffsetsCount; i++)
				{
					fseek(f, tmdl.twld.meshesInfo.meshInfoOffsetsOffset + chunk, SEEK_SET);
					tmdl.twld.meshesInfo.meshInfoOffsets.push_back(ReadUInt(f));
				}
				for (size_t i = 0; i < tmdl.twld.meshesInfo.meshInfoOffsetsCount; i++)
				{
					fseek(f, tmdl.twld.meshesInfo.meshInfoOffsets[i] + chunk, SEEK_SET);
					tmdl.twld.meshInfos.push_back({ { ReadFloat(f), ReadFloat(f), ReadFloat(f), ReadFloat(f)}, ReadUInt(f) });
				}
				std::vector<uint32_t> facesCount;
				std::vector<uint32_t> verticesCount;
				for (size_t i = 0; i < tmdl.twld.meshesInfo.meshInfoOffsetsCount; i++)
				{
					fseek(f, tmdl.twld.meshInfos[i].meshSubInfoOffset + chunk, SEEK_SET);
					tmdl.twld.subMeshInfos.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f),
						ReadUInt(f), ReadUInt(f), ReadUInt(f) });
					fseek(f, tmdl.twld.subMeshInfos[i].meshNameOffset + chunk, SEEK_SET);
					meshNames.push_back(ReadString(f));
					facesCount.push_back(tmdl.twld.subMeshInfos[i].faceCount);
					verticesCount.push_back(tmdl.twld.subMeshInfos[i].vertexCount);
				}
				std::vector<float> vertices;
				std::vector<float> normals;
				std::vector<float> uvs;
				std::vector<uint32_t> faces;
				for (size_t i = 0; i < tmdl.twld.meshesInfo.meshInfoOffsetsCount; i++)
				{
					fseek(f, tmdl.twld.subMeshInfos[i].vertexOffset + chunk, SEEK_SET);
					for (size_t j = 0; j < tmdl.twld.subMeshInfos[i].vertexCount; j++)
					{
						vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f));
						//normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f));
						fseek(f, 24, SEEK_CUR);
						uvs.push_back(ReadFloat(f)); uvs.push_back(-ReadFloat(f));
						fseek(f, 8, SEEK_CUR);
					}
					fseek(f, tmdl.twld.subMeshInfos[i].faceOffset + chunk, SEEK_SET);
					for (size_t j = 0; j < tmdl.twld.subMeshInfos[i].faceCount; j++)
					{
						faces.push_back(ReadUShort(f));
					}
				}
				std::string currentFileName = directory + "\\" + modelName.erase(modelName.size() - 4);
				FbxHelper::Model m = { vertices,faces,std::vector<float>(),uvs,verticesCount,facesCount,tmdl.twld.meshesInfo.meshInfoOffsetsCount, meshNames };
				FbxHelper fbxH;
				fbxH.CreateFbx(m, currentFileName);
			}
			tmdl.twld = {};
		}
		pgb->Value = x + 1;
	}
}