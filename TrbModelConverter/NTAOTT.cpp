#include "NTAOTT.h"

void NTAOTT::read(FILE* f, Reader::Endian endian, std::string filename, System::Windows::Forms::ProgressBar^ pgb, System::Windows::Forms::ListView^ lv)
{
	Reader::e = endian;
	TSFL tsfl(f, endian);
	long baseChunk = ftell(f);
	long chunk = ftell(f);
	long current = 0;
	size_t symbCounter = 0;
	TMDL tmdl;
	size_t lodCounter = 0;
	int32_t meshCounter = 1;
	size_t counter = 0;
	std::vector<std::string> meshNames;
	std::string lodname = "LOD0_Mesh_0";
	std::string prevLodName = "LOD0_Mesh_0";
	uint32_t meshCount = 0;
	std::string directory;
	const size_t last_slash_idx = filename.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		directory = filename.substr(0, last_slash_idx);
	}
	for (size_t x = 0; x < tsfl.symb.nameOffsets.size(); x++)
	{
		if (tsfl.symb.nameOffsets[x].ID == 0)
		{
			fseek(f, chunk + tsfl.symb.nameOffsets[x].dataOffset, SEEK_SET);
			if (x == 0)
			{
				tsfl.relc.writeFile(f, chunk, tsfl.symb.nameOffsets[x].ID);
			}
		}
		else
		{
			chunk = tsfl.hdrx.tagInfos[tsfl.symb.nameOffsets[x].ID - 1].tagSize + baseChunk;
			fseek(f, chunk + tsfl.symb.nameOffsets[x].dataOffset, SEEK_SET);
			if (tsfl.symb.nameOffsets[x].ID != tsfl.symb.nameOffsets[x - 1].ID)
			{
				tsfl.relc.writeFile(f, chunk, tsfl.symb.nameOffsets[x].ID);
			}
		}
		if (tsfl.symb.nameOffsets[x].name == "FileHeader")
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
		else if (tsfl.symb.nameOffsets[x].name == "ttex")
		{
			fseek(f, 4, SEEK_CUR);
		}
		//else if (tsfl.symb.nameOffsets[x].name == "tmod") //Toshi Model Stride 16
		//{
		//	tmdl.tmod.header = { ReadUInt(f), ReadUInt(f), ReadFloat(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
		//	fseek(f, tmdl.tmod.header.modelFileNameOffset + chunk, SEEK_SET);
		//	std::string modelName = ReadString(f);
		//	fseek(f, tmdl.tmod.header.meshInfoOffset + chunk, SEEK_SET);
		//	uint32_t meshesInfoOffset = ReadUInt(f);
		//	fseek(f, meshesInfoOffset + chunk, SEEK_SET);
		//	tmdl.tmod.meshesInfoVNTAOTT = { ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
		//	for (size_t i = 0; i < tmdl.tmod.meshesInfoVNTAOTT.meshCount; i++)
		//	{
		//		tmdl.tmod.meshesInfoVNTAOTT.meshInfoOffsets.push_back(ReadUInt(f));
		//	}

		//	std::vector<std::string> meshNames;
		//	for (size_t i = 0; i < tmdl.tmod.meshesInfoVNTAOTT.meshCount; i++)
		//	{
		//		fseek(f, tmdl.tmod.meshesInfoVNTAOTT.meshInfoOffsets[i] + chunk, SEEK_SET);
		//		tmdl.tmod.meshInfoVNTAOTT.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) });
		//		fseek(f, tmdl.tmod.meshInfoVNTAOTT[i].defaultNameOffset + chunk, SEEK_SET);
		//		meshNames.push_back(ReadString(f));
		//	}
		//	/*
		//	for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
		//	{
		//		fseek(f, tmdl.tmod.meshInfo[i].meshSubInfoOffset + chunk, SEEK_SET);
		//		//tmdl.tmod.meshSubInfoVNTAOTT.push_back({{ ReadUInt(f) }, ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f)

		//	}
		//	*/
		//	std::vector<uint32_t> verticesCount;
		//	std::vector<uint32_t> facesCount;
		//	fseek(f, tmdl.tmod.header.referenceTomeshInfoOffsetBegin + chunk, SEEK_SET);
		//	tmdl.tmod.someInfoVNTAOTT = { ReadUInt(f), ReadUInt(f) };
		//	fseek(f, tmdl.tmod.someInfoVNTAOTT.meshSubInfoOffset + chunk, SEEK_SET);
		//	if (tmdl.tmod.someInfoVNTAOTT.count != 0)
		//	{
		//		for (size_t i = 0; i < tmdl.tmod.someInfoVNTAOTT.count; i++)
		//		{
		//			tmdl.tmod.meshSubInfoVNTAOTT.push_back({ { ReadFloat(f), ReadFloat(f), ReadFloat(f), ReadFloat(f),
		//				ReadFloat(f), ReadFloat(f), ReadFloat(f), ReadFloat(f),
		//				ReadFloat(f), ReadFloat(f), ReadFloat(f), ReadFloat(f),
		//				ReadFloat(f), ReadFloat(f), ReadFloat(f), ReadFloat(f)}, ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f),
		//				ReadUInt(f) , ReadUInt(f) , ReadUInt(f) , ReadUInt(f) , ReadUInt(f) , ReadUInt(f) });
		//			verticesCount.push_back(tmdl.tmod.meshSubInfoVNTAOTT[i].vertexCount / 3);
		//			facesCount.push_back(tmdl.tmod.meshSubInfoVNTAOTT[i].faceCount);
		//		}
		//		std::vector<float> vertices;
		//		std::vector<float> normals;
		//		std::vector<uint32_t> faces;
		//		std::vector<float> uvs;

		//		for (size_t i = 0; i < tmdl.tmod.someInfoVNTAOTT.count; i++)
		//		{
		//			fseek(f, tmdl.tmod.meshSubInfoVNTAOTT[i].vertexOffset + chunk, SEEK_SET);
		//			for (size_t j = 0; j < tmdl.tmod.meshSubInfoVNTAOTT[i].vertexCount; j++)
		//			{
		//				vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f));
		//				//normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f));
		//				//fseek(f, 8, SEEK_CUR);
		//				//uvs.push_back(ReadFloat(f)); uvs.push_back(-ReadFloat(f));
		//				fseek(f, 4, SEEK_CUR);
		//			}
		//			fseek(f, tmdl.tmod.meshSubInfoVNTAOTT[i].faceOffset + chunk, SEEK_SET);
		//			for (size_t y = 0; y < tmdl.tmod.meshSubInfoVNTAOTT[i].faceCount; y++)
		//			{
		//				faces.push_back(ReadUShort(f));
		//			}
		//		}
		//		FbxHelper::Model m = { vertices,faces,std::vector<float>(),std::vector<float>(),verticesCount,facesCount,tmdl.tmod.someInfoVNTAOTT.count, meshNames };
		//		FbxHelper fbxH;
		//		fbxH.CreateFbx(m, "C://Users//Leon//Desktop//test");
		//	}
		//	tmdl.tmod = {};
		//}
		else if (tsfl.symb.nameOffsets[x].name == "twld")
		{
			long tell = ftell(f);
			tell = ftell(f);
			/*
			vector<string> meshNames;
			string modelName;
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
					ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) } };
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
				for (size_t i = 0; i < tmdl.twld.meshesInfo.meshInfoOffsetsCount; i++)
				{
					fseek(f, tmdl.twld.meshInfos[i].meshSubInfoOffset + chunk, SEEK_SET);
					tmdl.twld.subMeshInfos.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f),
						ReadUInt(f), ReadUInt(f), ReadUInt(f) });
					fseek(f, tmdl.twld.subMeshInfos[i].meshNameOffset + chunk, SEEK_SET);
					meshNames.push_back(ReadString(f));
				}

			}
			*/
		}
	}
}
