#pragma once
#include <vector>
#include <string>
class TMDL
{
	struct FileHeader
	{
		std::string label;
		uint32_t zero1;
		uint32_t unknown;
		uint32_t zero2;
	};

	struct SkeletonHeader
	{
		uint32_t modelNameOffset;
		uint32_t unknown2;
		uint32_t unknown3;
		uint32_t zeros[4];
	};

	struct Skeleton 
	{
		uint32_t boneCount;
		uint16_t boneUnknown1;
		uint16_t boneUnknown2;
		uint32_t zeros2[10];
		uint32_t zero3;
		uint32_t unknown4;
		uint32_t boneOffset;
		uint32_t boneEndOffset;
		uint32_t zero4;
		uint32_t unknownOffset;
		uint32_t unknownCount;
		uint32_t padding[3];
	};

	struct Header
	{
		uint32_t unknown1;
		uint16_t unknown2;
		uint16_t unknown3;
		uint32_t unknown4;
		uint32_t zero1, zero2;
		float f1, f2, f3, f4;
	};

	struct HeaderVNTAOTT
	{
		uint32_t count;
		float unknownFloat;
		uint32_t unknownInfoOffset;
	};

	struct UnknownInfoVNTAOTT
	{
		uint32_t count;
		uint32_t zero;
		uint32_t unknown;
		std::vector<float> pos;
	};

	struct LOD_MeshInfo
	{
		uint32_t unknown;
		uint32_t vertexCount;
		uint32_t faceCount;
		uint32_t indicesCount;
		uint32_t indicesOffset; //??
		uint32_t vertexOffset;
		uint32_t faceOffset;
		uint32_t zero;
		uint32_t unknown2;
		float f1, f2, f3, f4;
	};
	struct LOD_Mesh
	{
		uint32_t lod_meshInfoCount; //??
		uint32_t faceCount;
		uint32_t vertexCount;
		uint32_t meshNameOffset;
		uint32_t lodSubMeshInfoOffset;
		std::vector<LOD_MeshInfo> lod_meshInfo;
	};

	struct TWLD
	{
		struct Header
		{
			uint32_t modelFileNameOffset;
			uint32_t unknownInfoOffset;
			uint32_t unknownOffset;
			uint32_t unknown;
			uint32_t unknown2;
			std::vector<float> floats;
			uint32_t meshInfoOffsetOffset;
			uint32_t meshInfoOffset;
		} header;

		struct UnknownInfo
		{
			uint32_t unknown;
			uint32_t unknownInfo2OffsetOffset;
			uint32_t unknownInfo2Offset;
		} unknownInfo;

		struct UnknownInfo2
		{
			uint32_t count;
			uint32_t unknownInfo3OffsetOffset;
			uint32_t unknownInfo3Offset;
		} unknownInfo2;

		struct UnknownInfo3
		{
			uint32_t count;
			std::vector<uint32_t> padding;
		} unknownInfo3;

		struct MeshesInfo
		{
			uint32_t meshInfoOffsetsCount;
			uint32_t meshInfoOffsetsOffset;
			uint32_t unknownDataOffset;
			std::vector<uint32_t> meshInfoOffsets;
		} meshesInfo;

		struct UnknownData
		{
			uint32_t floats;
			uint32_t zero;
			uint32_t count;
			uint32_t zeros;
		};

		struct MeshInfo
		{
			std::vector<float> floats;
			uint32_t meshSubInfoOffset;
		};
		std::vector<MeshInfo> meshInfos;

		struct SubMeshInfo
		{
			uint32_t zero;
			uint32_t vertexCount;
			uint32_t normalCount;
			uint32_t faceCount;
			uint32_t meshNameOffset;
			uint32_t vertexOffset;
			uint32_t faceOffset;
			uint32_t count;
			uint32_t unknown;
		};
		std::vector<SubMeshInfo> subMeshInfos;

	};
	

	struct TMOD
	{
		struct Header 
		{
			uint32_t modelFileNameOffset;
			uint32_t modelCount;
			float unknown;
			uint32_t unknown1;
			uint32_t vertexStride;
			uint32_t referenceTomeshInfoOffsetBegin;
			uint32_t meshInfoOffsetOffset;
			uint32_t meshInfoOffset;
		};
		struct HeaderVNTAOTT
		{
			uint32_t modelFileNameOffset;
			uint32_t modelCount;
			float unknown;
			uint32_t unknown1;
			uint32_t vertexStride;
			uint32_t collisionInfoOffset;
			uint32_t unknownInfoOffset;
			uint32_t meshesInfoOffsetOffset;
			uint32_t meshesInfoOffset;
		};
		struct MeshesInfo
		{
			uint32_t offsetToOne;
			uint32_t meshInfoOffsetsOffset;
			uint32_t meshCount;
			std::vector<uint32_t> meshInfoOffsets;
		};
		struct MeshesInfoVNTAOTT
		{
			uint32_t zero;
			uint32_t zero2;
			uint32_t tmdlUnknownInfoOffset;
			uint32_t meshInfoOffsetOffset;
			uint32_t meshCount;
			std::vector<uint32_t> meshInfoOffsets;
		};
		struct MeshInfo
		{
			uint32_t zero;
			uint32_t one;
			uint32_t unknown1;
			uint32_t unknown2;
			uint32_t meshNameOffset;
			uint32_t meshSubInfoOffset;
		};
		struct MeshInfoV2
		{
			uint32_t unknown;
			uint32_t one;
			uint32_t unknown1;
			uint32_t zero;
			uint32_t unknown2;
			uint32_t unknown3;
			uint32_t meshSubInfoV2Offset;
			uint32_t unknown4;
			uint32_t meshNameOffset;
			uint32_t unknown5;
			uint8_t* flags;
		};
		struct MeshInfoVNTAOTT
		{
			uint32_t unknownFloatDataOffset;
			uint32_t zero;
			uint32_t count;
			uint32_t unknown;
			uint32_t unknown2;
			uint32_t defaultNameOffset;
			uint32_t count2;
			uint32_t unknownFloatDataOffset2;
		};
		struct SomeInfoVNTAOTT
		{
			uint32_t count;
			uint32_t meshSubInfoOffset;
		};
		struct MeshSubInfo
		{
			uint32_t vertexCount;
			uint32_t normalCount;
			uint32_t faceCount;
			uint32_t one;
			uint32_t offsetToOne; //Not to the one from MeshInfo!
			uint32_t vertexOffset;
			uint32_t faceOffset;
		};
		struct MeshSubInfoVNTAOTT
		{
			std::vector<float> matrix;
			uint32_t zero;
			uint32_t vertexOffset;
			uint32_t vertexCount;
			uint32_t faceOffset;
			uint32_t faceCount;
			uint32_t unknown;
			uint32_t unknown2;
			uint32_t zero2;
			uint32_t count;
			uint32_t unknownOffset;
			uint32_t unknownOffset2;
			uint32_t zero3;
		};
		struct MeshSubInfoV2
		{

		};
		Header header;
		MeshesInfo meshesInfo;
		MeshesInfoVNTAOTT meshesInfoVNTAOTT;
		SomeInfoVNTAOTT someInfoVNTAOTT;
		std::vector<MeshInfoVNTAOTT> meshInfoVNTAOTT;
		std::vector<MeshInfo> meshInfo;
		std::vector<MeshInfoV2> meshInfoV2;
		std::vector<MeshSubInfo> meshSubInfo;
		std::vector<MeshSubInfoVNTAOTT> meshSubInfoVNTAOTT;
	};
public:
	TMOD tmod;
	TWLD twld;
	FileHeader fileHeader;
	SkeletonHeader skeletonHeader;
	Skeleton skeleton;
	Header header;
	std::vector<LOD_Mesh> lodMesh;
};

