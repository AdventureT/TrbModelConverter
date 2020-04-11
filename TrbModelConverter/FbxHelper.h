#pragma once
#include <fbxsdk.h>
#include <vector>
///Just a class to help with fbx stuff
public class FbxHelper
{
private:
	FbxManager* lSdkManager;
	FbxScene* lScene;
public:
	struct Model
	{
		std::vector<float> vertices;
		std::vector<uint32_t> faces;
		std::vector<float> normals;
		std::vector<float> uvs;
		std::vector<uint32_t> vertCount;
		std::vector<uint32_t> faceCount;
		uint32_t meshCount;
		std::vector<std::string> meshNames;
	};
	FbxHelper();
	void CreateFbx(Model m, std::string fileName);
	static void Matrix33ToRS(float* Mat33, double R[3], double S[3], int RotationOrder);
	static void Matrix344ToTRS(float* Mat344, double T[3], double R[3], double S[3], int RotationOrder);
	std::vector<FbxNode*> CreateSkeleton(std::vector<std::string> boneNames, std::vector<short> parents, std::vector<std::vector<double>> TRS, std::vector<FbxAMatrix> mat = std::vector<FbxAMatrix>());

};

