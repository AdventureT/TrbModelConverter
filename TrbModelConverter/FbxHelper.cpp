#include "FbxHelper.h"

FbxHelper::FbxHelper()
{
	lSdkManager = FbxManager::Create();
	lScene = FbxScene::Create(lSdkManager, "myScene");
	FbxIOSettings* ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
	lSdkManager->SetIOSettings(ios);
}

void FbxHelper::Matrix33ToRS(float* Mat33, double R[3], double S[3], int RotationOrder)
{
	float Rot[9];
	double PI = 3.1415926535897932;

	S[0] = sqrt((double)(Mat33[0] * Mat33[0] + Mat33[1] * Mat33[1] + Mat33[2] * Mat33[2]));
	S[1] = sqrt((double)(Mat33[3] * Mat33[3] + Mat33[4] * Mat33[4] + Mat33[5] * Mat33[5]));
	S[2] = sqrt((double)(Mat33[6] * Mat33[6] + Mat33[7] * Mat33[7] + Mat33[8] * Mat33[8]));

	// Create a copy of the 3x3 rotation matrix
	memcpy_s(Rot, sizeof(float) * 9, Mat33, sizeof(float) * 9);
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			Rot[i + j] /= (float)S[i];
	switch (RotationOrder)
	{
	default:
	case 0:
		R[0] = atan2((double)Rot[7], (double)Rot[8]);
		R[1] = atan2(-(double)Rot[6], (double)Rot[7] * sin(R[0]) + (double)Rot[8] * cos(R[0]));
		R[2] = atan2((double)Rot[3], (double)Rot[0]);
		break;
	case 1:
		R[0] = atan2(-(double)Rot[5], (double)Rot[4]);
		R[1] = atan2(-(double)Rot[6], (double)Rot[0]);
		R[2] = atan2((double)Rot[3], (double)Rot[0] * cos(R[1]) - (double)Rot[6] * sin(R[1]));
		break;
	case 2:
		R[0] = atan2((double)Rot[7], (double)Rot[4]);
		R[1] = atan2((double)Rot[2], (double)Rot[0]);
		R[2] = atan2(-(double)Rot[1], (double)Rot[0] * cos(R[1]) + (double)Rot[2] * sin(R[1]));
		break;
	case 3:
		R[2] = atan2(-(double)Rot[1], (double)Rot[4]);
		R[1] = atan2(-(double)Rot[6], (double)Rot[8]);
		R[0] = atan2((double)Rot[7], (double)Rot[4] * cos(R[2]) - (double)Rot[1] * sin(R[2]));
		break;
	case 4:
		R[2] = atan2((double)Rot[3], (double)Rot[4]);
		R[1] = atan2((double)Rot[2], (double)Rot[8]);
		R[0] = atan2(-(double)Rot[5], (double)Rot[3] * sin(R[2]) + (double)Rot[4] * cos(R[2]));
		break;
	case 5:
		R[0] = atan2(-(double)Rot[5], (double)Rot[8]);
		R[1] = atan2((double)Rot[2], (double)Rot[8] * cos(R[0]) - (double)Rot[5] * sin(R[0]));
		R[2] = atan2(-(double)Rot[1], (double)Rot[0]);
		break;
	}
	for (int i = 0; i < 3; i++)
		R[i] *= 180.0 / PI;
}
void FbxHelper::Matrix344ToTRS(float* Mat344, double T[3], double R[3], double S[3], int RotationOrder)
{
	float Rot[9];


	T[0] = Mat344[12];
	T[1] = Mat344[13];
	T[2] = Mat344[14];

	// Convert 4x matrix to 3x3 rotation matrix
	memcpy(Rot, Mat344, sizeof(float) * 3);
	memcpy(Rot + 3, Mat344 + 4, sizeof(float) * 3);
	memcpy(Rot + 6, Mat344 + 8, sizeof(float) * 3);

	Matrix33ToRS(Rot, R, S, RotationOrder);
}

void FbxHelper::CreateFbx(Model m, std::string fileName)
{
	bool noNormals = false;
	bool noUvs = false;
	int sumVertices = 0;
	int Viord = 0;
	int index = 0;
	int rememberI = 0;
	int remeberU = 0;
	int Niord = 0;

	if (m.normals.empty())
	{
		noNormals = true;
	}
	else if (m.uvs.empty())
	{
		noUvs = true;
	}
	for (size_t i = 0; i < m.meshCount; i++)
	{
		FbxNode* lMeshNode = FbxNode::Create(lScene, m.meshNames[i].c_str());
		FbxMesh* lMesh = FbxMesh::Create(lScene, m.meshNames[i].c_str());
		lMeshNode->SetNodeAttribute(lMesh);
		FbxNode* lRootNode = lScene->GetRootNode();
		FbxNode* lPatchNode = lScene->GetRootNode();
		lRootNode->AddChild(lMeshNode);
		lMesh->InitControlPoints(m.vertCount[i]);
		FbxVector4* lControlPoints = lMesh->GetControlPoints();
		FbxLayer* lLayer = lMesh->GetLayer(0);
		FbxLayerElementNormal* lLayerElementNormal = NULL;
		FbxLayerElementUV* lLayerElementUV = NULL;
		if (lLayer == NULL) {
			lMesh->CreateLayer();
			lLayer = lMesh->GetLayer(0);
		}
		if (!m.normals.empty())
		{
			lLayerElementNormal = FbxLayerElementNormal::Create(lMesh, "");
			lLayerElementNormal->SetMappingMode(FbxLayerElement::eByControlPoint);
			lLayerElementNormal->SetReferenceMode(FbxLayerElement::eDirect);
		}
		if (!m.uvs.empty())
		{
			lLayerElementUV = FbxLayerElementUV::Create(lMesh, "");
			lLayerElementUV->SetMappingMode(FbxLayerElement::eByControlPoint);
			lLayerElementUV->SetReferenceMode(FbxLayerElement::eDirect);
		}


		for (size_t j = 0; j < m.vertCount[i]; j++)
		{
			FbxVector4 vertex(m.vertices[Viord], m.vertices[Viord + 1], m.vertices[Viord + 2]);
			if (!m.normals.empty())
			{
				FbxVector4 normal(m.normals[Niord], m.normals[Niord + 1], m.normals[Niord + 2]);
				lLayerElementNormal->GetDirectArray().Add(normal);
			}
			if (!m.uvs.empty())
			{
				FbxVector2 uv(m.uvs[remeberU], m.uvs[remeberU + 1]);
				lLayerElementUV->GetDirectArray().Add(uv);
			}
			lControlPoints[j] = vertex;
			//if (m.vertices[Viord + 3] == 1)
			//{
			//	Viord += 4;
			//}
			//else
			//{
			//	Viord += 3;
			//}
			Viord += 3;
			Niord += 3;
			remeberU += 2;
		}
		for (size_t y = 0; y < m.faceCount[i] / 3; y++)
		{
			lMesh->BeginPolygon();
			lMesh->AddPolygon(m.faces[rememberI]);
			lMesh->AddPolygon(m.faces[rememberI + 1]);
			lMesh->AddPolygon(m.faces[rememberI + 2]);
			lMesh->EndPolygon();
			rememberI += 3;
		}
		if (!m.normals.empty())
		{
			lLayer->SetNormals(lLayerElementNormal);
		}
		if (!m.uvs.empty())
		{
			lLayer->SetUVs(lLayerElementUV);
		}
		lMeshNode->LclRotation.Set(FbxVector4(180, 0, 0.0)); //Right rotation

		FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");
		lSdkManager->GetIOSettings()->SetBoolProp(EXP_FBX_EMBEDDED, true);
		std::string currentFileName = fileName + ".fbx";
		bool lExportStatus = lExporter->Initialize(currentFileName.c_str(), -1, lSdkManager->GetIOSettings());
		if (!lExportStatus) {
			throw gcnew System::Exception(gcnew System::String("Call to FbxExporter::Initialize() failed."));
		}
		lExporter->Export(lScene);
		lExporter->Destroy();
	}
	
}

std::vector<FbxNode*> FbxHelper::CreateSkeleton(std::vector<std::string> boneNames, std::vector<short> parents, std::vector<std::vector<double>> TRS, std::vector<FbxAMatrix> mat)
{
	FbxNode* lRootNode = lScene->GetRootNode();
	FbxNode* lSkeletonRoot = FbxNode::Create(lScene, "Root");
	FbxSkeleton* skel = FbxSkeleton::Create(lScene, "test");
	std::vector<FbxNode*> fbxNodes;
	for (size_t i = 0; i < boneNames.size(); i++)
	{
		std::string bName = boneNames[i].c_str();
		FbxNode* node = FbxNode::Create(lScene, boneNames[i].c_str());
		bool found = false;
		for (size_t j = 0; j < fbxNodes.size(); j++)
		{
			if (!fbxNodes[j])
			{
				found = false;
				break;
			}
			std::string name = fbxNodes[j]->GetName();
			if (name == bName)
			{
				node = fbxNodes[j];
				found = true;
			}
		}
		if (!found)
		{
			node = FbxNode::Create(lScene, bName.c_str());
		}

		FbxSkeleton* lSkeletonRootAttribute = FbxSkeleton::Create(lScene, boneNames[i].c_str());
		if (parents[i] == -1) lSkeletonRootAttribute->SetSkeletonType(FbxSkeleton::eRoot);
		else lSkeletonRootAttribute->SetSkeletonType(FbxSkeleton::eLimbNode);

		node->SetNodeAttribute(lSkeletonRootAttribute);

		FbxAMatrix nodeTM = {};
		FbxAMatrix nodeTM2 = {};
		FbxVector4 rot(FbxDouble3(mat[i].GetR()));
		rot.FixIncorrectValue();
		//rot.Normalize();
		nodeTM.SetT(FbxVector4(TRS[i][0], TRS[i][1], TRS[i][2]));
		nodeTM.SetR(rot);
		//nodeTM.SetS(FbxVector4(TRS[i][6], TRS[i][7], TRS[i][8]));
		if (parents[i] > -1)
		{
			nodeTM2 = {};
			fbxNodes[parents[i]]->AddChild(node);
			//nodeTM2.SetT(fbxNodes[parents[i]]->LclTranslation.Get());
			//nodeTM2.SetR(fbxNodes[parents[i]]->LclRotation.Get());
			//nodeTM2.SetS(fbxNodes[parents[i]]->LclScaling.Get());
			//nodeTM *= nodeTM2;
		}
		else
			//nodeTM *= lRootNode->EvaluateLocalTransform();
		node->LclRotation.Set(nodeTM.GetR());
		node->LclTranslation.Set(nodeTM.GetT());
		//node->LclScaling.Set(nodeTM.GetS());
		fbxNodes.push_back(node);
	}

	lRootNode->AddChild(fbxNodes[0]);
	FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");
	lSdkManager->GetIOSettings()->SetBoolProp(EXP_FBX_EMBEDDED, true);
	std::string currentFileName = "test.fbx";
	bool lExportStatus = lExporter->Initialize(currentFileName.c_str(), -1, lSdkManager->GetIOSettings());
	if (!lExportStatus) {
		throw gcnew System::Exception(gcnew System::String("Call to FbxExporter::Initialize() failed."));
	}
	lExporter->Export(lScene);
	lExporter->Destroy();
	return fbxNodes;
}
