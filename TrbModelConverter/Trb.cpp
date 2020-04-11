#include "pch.h"
#include "TMDL.h"
#include "Trb.h"
#include "TTL.h"
#include <direct.h>
#include <algorithm>


Trb::Trb(std::string filePath, Endian e, System::Windows::Forms::ProgressBar^ pgb, System::Windows::Forms::ListView^ lv, Game::Type game)
{
	this->filename = filePath;
	this->e = e;
	if (fopen_s(&f, filename.c_str(), "rb+") != 0) // Security check
	{
		throw "Can't open the trb file";
	}
	output = readTrb(pgb, lv ,game);
	fclose(f);
}
std::string Trb::readTrb(System::Windows::Forms::ProgressBar^ pgb, System::Windows::Forms::ListView^ lv, Game::Type game)
{
	if (game == Game::DEBLOB)
	{
		deBlob deblob;
		deblob.read(f, e, filename, pgb, lv);
	}
	else if (game == Game::NAOTT)
	{
		NTAOTT naott;
		naott.read(f, e, filename, pgb, lv);
	}
	return "Finished!";
	//	long baseChunk = ftell(f);
	//	long chunk = ftell(f);
	//	long current = 0;
	//	size_t symbCounter = 0;
	//	TMDL tmdl;
	//	size_t lodCounter = 0;
	//	int32_t meshCounter = 1;
	//	size_t counter = 0;
	//	std::vector<std::string> meshNames;
	//	std::string lodname = "LOD0_Mesh_0";
	//	std::string prevLodName = "LOD0_Mesh_0";
	//	uint32_t meshCount = 0;
	//	for (size_t x = 0; x < tsfl.symb.nameOffsets.size(); x++)
	//	{
	//		if (tsfl.symb.nameOffsets[x].ID == 0)
	//		{
	//			fseek(f, chunk + tsfl.symb.nameOffsets[x].dataOffset, SEEK_SET);
	//		}
	//		else
	//		{
	//			chunk = tsfl.hdrx.tagInfos[tsfl.symb.nameOffsets[x].ID - 1].tagSize + baseChunk;
	//			fseek(f, chunk + tsfl.symb.nameOffsets[x].dataOffset, SEEK_SET);
	//		}
	//		if (tsfl.symb.nameOffsets[x].name == "FileHeader")
	//		{
	//			tmdl.fileHeader = { ReadString(f,4), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
	//		}
	//		else if (tsfl.symb.nameOffsets[x].name == "SkeletonHeader")
	//		{
	//			tmdl.skeletonHeader = { ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
	//		}
	//		else if (tsfl.symb.nameOffsets[x].name == "Skeleton")
	//		{
	//			tmdl.skeleton = { ReadUInt(f), ReadUShort(f), ReadUShort(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f),
	//				ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
	//		}
	//		else if (tsfl.symb.nameOffsets[x].name == "Database")
	//		{
	//			return "Not supported yet";
	//		}
	//		else if (tsfl.symb.nameOffsets[x].name.find("TTL") != std::string::npos)
	//		{
	//			TTL ttl;
	//			ttl.ddsFileCount = ReadUInt(f); ttl.ddsFilesOffset = ReadUInt(f); ttl.currentFileNameOffset = ReadUInt(f);
	//			fseek(f, ttl.currentFileNameOffset + chunk, SEEK_SET);
	//			ttl.currentFileName = ReadString(f);
	//			fseek(f, ttl.ddsFilesOffset + chunk, SEEK_SET);
	//			for (size_t i = 0; i < ttl.ddsFileCount; i++)
	//			{
	//				TTL::ddsFile ddsFile; 
	//				ddsFile.flag = ReadUInt(f); ddsFile.ddsFileNameOffset = ReadUInt(f); 
	//				ddsFile.ddsFileSize = ReadUInt(f); ddsFile.ddsDataOffset = ReadUInt(f);
	//				long rh = ftell(f);
	//				fseek(f, ddsFile.ddsFileNameOffset + chunk, SEEK_SET);
	//				ddsFile.ddsFileName = ReadString(f);
	//				fseek(f, rh, SEEK_SET);
	//				ttl.ddsFiles.push_back(ddsFile);
	//			}
	//			std::string path = filename;
	//			int found = path.find_last_of("/\\");
	//			std::string folder = path.substr(0, found + 1);
	//			std::string textureFileNamePath = folder;
	//			for (size_t i = 0; i < ttl.ddsFileCount; i++)
	//			{
	//				fseek(f, ttl.ddsFiles[i].ddsDataOffset + chunk, SEEK_SET);
	//				std::vector<uint8_t> ddsData = ReadBytes(f, ttl.ddsFiles[i].ddsFileSize);
	//				FILE* fTex;
	//				std::string textureFileName = ttl.ddsFiles[i].ddsFileName.replace(ttl.ddsFiles[i].ddsFileName.size() - 4, ttl.ddsFiles[i].ddsFileName.size(), ".dds");
	//				textureFileNamePath += textureFileName;
	//				std::string path2 = textureFileNamePath;
	//				int found = path2.find_last_of("/\\");
	//				std::string folder2= path2.substr(0, found + 1);
	//				mkdir(folder2.c_str());
	//				if (fopen_s(&fTex, textureFileNamePath.c_str(), "wb") != 0) // Security check
	//				{
	//					
	//				}
	//				for (size_t j = 0; j < ttl.ddsFiles[i].ddsFileSize; j++)
	//				{
	//					fwrite(&ddsData[j], 1, 1, fTex);
	//				}
	//				fclose(fTex);
	//				textureFileNamePath = folder;
	//			}

	//		}
	//		else if (tsfl.symb.nameOffsets[x].name == "Materials")
	//		{

	//		}
	//		else if (tsfl.symb.nameOffsets[x].name == "Collision")
	//		{

	//		}
	//		else if (tsfl.symb.nameOffsets[x].name.find("Header") != std::string::npos)
	//		{
	//			uint32_t unknown = ReadUInt(f);
	//			float unknown2 = ReadFloat(f);
	//			meshCount = ReadUInt(f);
	//		}
	//		else if (tsfl.symb.nameOffsets[x].name.find(lodname) != std::string::npos)
	//		{
	//			if (counter == 0)
	//			{
	//				prevLodName = tsfl.symb.nameOffsets[x].name;
	//				counter++;
	//			}
	//			if (tsfl.symb.nameOffsets[x].name[tsfl.symb.nameOffsets[x].name.find("LOD") - 2] != prevLodName[tsfl.symb.nameOffsets[x].name.find("LOD") - 2])
	//			{
	//				meshCounter = 1;
	//				lodCounter = 0;
	//				meshNames.clear();
	//			}
	//			else if (counter > 0)
	//			{
	//				prevLodName = tsfl.symb.nameOffsets[x].name;
	//				counter++;
	//			}
	//			tmdl.lodMesh.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) });
	//			fseek(f, tmdl.lodMesh[lodCounter].meshNameOffset + chunk, SEEK_SET);
	//			meshNames.push_back(ReadString(f));
	//			fseek(f, tmdl.lodMesh[lodCounter].lodSubMeshInfoOffset + chunk, SEEK_SET);
	//			for (size_t i = 0; i < tmdl.lodMesh[lodCounter].lod_meshInfoCount; i++)
	//			{
	//				tmdl.lodMesh[lodCounter].lod_meshInfo.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f),
	//					ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadFloat(f), ReadFloat(f), ReadFloat(f), ReadFloat(f) });
	//			}
	//			lodname.replace(lodname.size()-1, lodname.size(), to_string(meshCounter-1));
	//			if (meshCounter == meshCount)
	//			{
	//				vector<float> vertices;
	//				vector<float> normals;
	//				vector<uint16_t> faces;
	//				vector<float> uvs;
	//				vector<uint32_t> faceCounts;

	//				for (size_t i = 0; i < tmdl.lodMesh.size(); i++)
	//				{
	//					fseek(f, tmdl.lodMesh[i].lod_meshInfo[0].vertexOffset + chunk, SEEK_SET);
	//					for (size_t j = 0; j < tmdl.lodMesh[i].vertexCount; j++)
	//					{
	//						vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f));
	//						normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f));
	//						fseek(f, 8, SEEK_CUR);
	//						uvs.push_back(ReadFloat(f)); uvs.push_back(-ReadFloat(f));
	//					}
	//					uint32_t counter = 0;
	//					for (size_t y = 0; y < tmdl.lodMesh[i].lod_meshInfoCount; y++)
	//					{
	//						fseek(f, tmdl.lodMesh[i].lod_meshInfo[y].faceOffset + chunk, SEEK_SET);
	//						// Source: https://forum.xentax.com/viewtopic.php?t=5621
	//						int32_t startDirection = -1;
	//						uint32_t indexCounter = 2;
	//						int32_t faceDirection = startDirection;

	//						uint16_t faceA = ReadUShort(f) + 1;
	//						uint16_t faceB = ReadUShort(f) + 1;
	//						do
	//						{
	//							uint16_t faceC = ReadUShort(f);
	//							indexCounter++;
	//							if (faceC == 0xFFFF)
	//							{
	//								faceA = ReadUShort(f) + 1;
	//								faceB = ReadUShort(f) + 1;
	//								indexCounter += 2;
	//								faceDirection = startDirection;
	//							}
	//							else
	//							{
	//								faceC++;
	//								faceDirection *= -1;
	//								if (faceA != faceB && faceB != faceC && faceC != faceA)
	//								{
	//									if (faceDirection > 0)
	//									{
	//										faces.push_back(faceA); faces.push_back(faceB); faces.push_back(faceC);
	//									}
	//									else
	//									{
	//										faces.push_back(faceA); faces.push_back(faceC); faces.push_back(faceB);
	//									}
	//									counter += 3;
	//								}
	//								faceA = faceB;
	//								faceB = faceC;
	//							}
	//						} while ((unsigned)ftell(f) < (tmdl.lodMesh[i].lod_meshInfo[y].faceCount * 2 + tmdl.lodMesh[i].lod_meshInfo[y].faceOffset + chunk));
	//					}
	//					faceCounts.push_back(counter);
	//				}
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
	//				for (size_t i = 0; i < tmdl.lodMesh.size(); i++)
	//				{
	//					FbxNode* lMeshNode = FbxNode::Create(lScene, meshNames[i].c_str());
	//					FbxMesh* lMesh = FbxMesh::Create(lScene, meshNames[i].c_str());
	//					lMeshNode->SetNodeAttribute(lMesh);
	//					FbxNode* lRootNode = lScene->GetRootNode();
	//					FbxNode* lPatchNode = lScene->GetRootNode();
	//					lRootNode->AddChild(lMeshNode);
	//					lMesh->InitControlPoints(tmdl.lodMesh[i].vertexCount);
	//					FbxVector4* lControlPoints = lMesh->GetControlPoints();
	//					FbxLayer* lLayer = lMesh->GetLayer(0);
	//					FbxLayerElementNormal* lLayerElementNormal = NULL;
	//					FbxLayerElementUV* lLayerElementUV = NULL;

	//					if (lLayer == NULL) {
	//						lMesh->CreateLayer();
	//						lLayer = lMesh->GetLayer(0);
	//					}
	//					lLayerElementNormal = FbxLayerElementNormal::Create(lMesh, "");
	//					lLayerElementNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
	//					lLayerElementNormal->SetReferenceMode(FbxLayerElement::eDirect);
	//					lLayerElementUV = FbxLayerElementUV::Create(lMesh, "");
	//					lLayerElementUV->SetMappingMode(FbxLayerElement::eByControlPoint);
	//					lLayerElementUV->SetReferenceMode(FbxLayerElement::eDirect);


	//					for (size_t j = 0; j < tmdl.lodMesh[i].vertexCount; j++)
	//					{
	//						FbxVector4 vertex(vertices[Viord], vertices[Viord + 1], vertices[Viord + 2]);
	//						FbxVector4 normal(normals[Niord], normals[Niord + 1], normals[Niord + 2]);
	//						FbxVector2 uv(uvs[remeberU], uvs[remeberU + 1]);
	//						lLayerElementUV->GetDirectArray().Add(uv);
	//						lLayerElementNormal->GetDirectArray().Add(normal);
	//						lControlPoints[j] = vertex;
	//						Viord += 3;
	//						Niord += 3;
	//						remeberU += 2;
	//					}
	//					for (size_t y = 0; y < faceCounts[i] / 3; y++)
	//					{
	//						lMesh->BeginPolygon();
	//						lMesh->AddPolygon(faces[rememberI] - 1);
	//						lMesh->AddPolygon(faces[rememberI + 1] - 1);
	//						lMesh->AddPolygon(faces[rememberI + 2] - 1);
	//						lMesh->EndPolygon();
	//						rememberI += 3;
	//					}
	//					lLayer->SetNormals(lLayerElementNormal);
	//					lLayer->SetUVs(lLayerElementUV);
	//					lMeshNode->LclRotation.Set(FbxVector4(270, 0, 0.0)); //Right rotation
	//				}
	//				FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");
	//				lSdkManager->GetIOSettings()->SetBoolProp(EXP_FBX_EMBEDDED, true);
	//				std::string currentFileName = filename;
	//				bool lExportStatus = lExporter->Initialize(currentFileName.c_str(), -1, lSdkManager->GetIOSettings());
	//				if (!lExportStatus) {
	//					throw gcnew System::Exception(gcnew System::String("Call to FbxExporter::Initialize() failed."));
	//				}
	//				lExporter->Export(lScene);
	//				lExporter->Destroy();
	//				meshCounter = 1;
	//				lodCounter++;
	//				meshNames.clear();
	//			}
	//			else
	//			{
	//				meshCounter++;
	//			}
	//		}
	//		else if (tsfl.symb.nameOffsets[x].name == "tmod") //Toshi Model Big endian: Stride 12 Shorts!
	//		{
	//			tmdl.tmod.header = { ReadUInt(f), ReadUInt(f), ReadFloat(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) };
	//			fseek(f, tmdl.tmod.header.modelFileNameOffset + chunk, SEEK_SET);
	//			std::string modelName = ReadString(f);
	//			fseek(f, tmdl.tmod.header.meshInfoOffset + chunk, SEEK_SET);
	//			x += 5;
	//			tmdl.tmod.meshesInfo = { ReadUInt(f), ReadUInt(f), ReadUInt(f) };
	//			for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
	//			{
	//				tmdl.tmod.meshesInfo.meshInfoOffsets.push_back(ReadUInt(f));
	//			}
	//			vector<std::string> meshNames;
	//			for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
	//			{
	//				fseek(f, tmdl.tmod.meshesInfo.meshInfoOffsets[i] + chunk, SEEK_SET);
	//				if (true)
	//				{
	//					tmdl.tmod.meshInfoV2.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f)
	//						, ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadBytes(f,4).data() });
	//					fseek(f, tmdl.tmod.meshInfoV2[i].meshNameOffset + chunk, SEEK_SET);
	//				}
	//				else
	//				{
	//					tmdl.tmod.meshInfo.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) });
	//					fseek(f, tmdl.tmod.meshInfo[i].meshNameOffset + chunk, SEEK_SET);
	//				}

	//				meshNames.push_back(ReadString(f));
	//			}
	//			for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
	//			{
	//				fseek(f, tmdl.tmod.meshInfo[i].meshSubInfoOffset + chunk, SEEK_SET);
	//				tmdl.tmod.meshSubInfo.push_back({ ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f), ReadUInt(f) });
	//			}
	//			vector<float> vertices;
	//			vector<float> normals;
	//			vector<uint16_t> faces;
	//			vector<float> uvs;

	//			for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
	//			{
	//				fseek(f, tmdl.tmod.meshSubInfo[i].vertexOffset + chunk, SEEK_SET);
	//				for (size_t j = 0; j < tmdl.tmod.meshSubInfo[i].vertexCount; j++)
	//				{
	//					vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f)); vertices.push_back(ReadFloat(f));
	//					normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f)); normals.push_back(ReadFloat(f));
	//					fseek(f, 8, SEEK_CUR);
	//					uvs.push_back(ReadFloat(f)); uvs.push_back(-ReadFloat(f));
	//					fseek(f, 4, SEEK_CUR);
	//				}
	//				fseek(f, tmdl.tmod.meshSubInfo[i].faceOffset + chunk, SEEK_SET);
	//				for (size_t y = 0; y < tmdl.tmod.meshSubInfo[i].faceCount; y++)
	//				{
	//					faces.push_back(ReadUShort(f));
	//				}
	//			}
	//			FbxManager* lSdkManager = FbxManager::Create();
	//			FbxScene* lScene = FbxScene::Create(lSdkManager, "myScene");
	//			FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	//			lSdkManager->SetIOSettings(ios);
	//			int sumVertices = 0;
	//			int Viord = 0;
	//			int index = 0;
	//			int rememberI = 0;
	//			int remeberU = 0;
	//			int Niord = 0;
	//			for (size_t i = 0; i < tmdl.tmod.meshesInfo.meshCount; i++)
	//			{
	//				FbxNode* lMeshNode = FbxNode::Create(lScene, meshNames[i].c_str());
	//				FbxMesh* lMesh = FbxMesh::Create(lScene, meshNames[i].c_str());
	//				lMeshNode->SetNodeAttribute(lMesh);
	//				FbxNode* lRootNode = lScene->GetRootNode();
	//				FbxNode* lPatchNode = lScene->GetRootNode();
	//				lRootNode->AddChild(lMeshNode);
	//				lMesh->InitControlPoints(tmdl.tmod.meshSubInfo[i].vertexCount);
	//				FbxVector4* lControlPoints = lMesh->GetControlPoints();
	//				FbxLayer* lLayer = lMesh->GetLayer(0);
	//				FbxLayerElementNormal* lLayerElementNormal = NULL;
	//				FbxLayerElementUV* lLayerElementUV = NULL;

	//				if (lLayer == NULL) {
	//					lMesh->CreateLayer();
	//					lLayer = lMesh->GetLayer(0);
	//				}
	//				lLayerElementNormal = FbxLayerElementNormal::Create(lMesh, "");
	//				lLayerElementNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
	//				lLayerElementNormal->SetReferenceMode(FbxLayerElement::eDirect);
	//				lLayerElementUV = FbxLayerElementUV::Create(lMesh, "");
	//				lLayerElementUV->SetMappingMode(FbxLayerElement::eByControlPoint);
	//				lLayerElementUV->SetReferenceMode(FbxLayerElement::eDirect);


	//				for (size_t j = 0; j < tmdl.tmod.meshSubInfo[i].vertexCount; j++)
	//				{
	//					FbxVector4 vertex(vertices[Viord], vertices[Viord + 1], vertices[Viord + 2]);
	//					FbxVector4 normal(normals[Niord], normals[Niord + 1], normals[Niord + 2]);
	//					FbxVector2 uv(uvs[remeberU], uvs[remeberU + 1]);
	//					lLayerElementUV->GetDirectArray().Add(uv);
	//					lLayerElementNormal->GetDirectArray().Add(normal);
	//					lControlPoints[j] = vertex;
	//					Viord += 3;
	//					Niord += 3;
	//					remeberU += 2;
	//				}
	//				for (size_t y = 0; y < tmdl.tmod.meshSubInfo[i].faceCount / 3; y++)
	//				{
	//					lMesh->BeginPolygon();
	//					lMesh->AddPolygon(faces[rememberI]);
	//					lMesh->AddPolygon(faces[rememberI + 1]);
	//					lMesh->AddPolygon(faces[rememberI + 2]);
	//					lMesh->EndPolygon();
	//					rememberI += 3;
	//				}
	//				lLayer->SetNormals(lLayerElementNormal);
	//				lLayer->SetUVs(lLayerElementUV);
	//				lMeshNode->LclRotation.Set(FbxVector4(180, 0, 0.0)); //Right rotation
	//			}
	//			FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");
	//			lSdkManager->GetIOSettings()->SetBoolProp(EXP_FBX_EMBEDDED, true);
	//			std::string currentFileName = modelName.erase(modelName.size() - 5);
	//			bool lExportStatus = lExporter->Initialize(currentFileName.c_str(), -1, lSdkManager->GetIOSettings());
	//			if (!lExportStatus) {
	//				throw gcnew System::Exception(gcnew System::String("Call to FbxExporter::Initialize() failed."));
	//			}
	//			lExporter->Export(lScene);
	//			lExporter->Destroy();
	//		}
	//	}
	//	return "Finished!";
}
