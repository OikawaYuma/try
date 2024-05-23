#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"
#include <string>
#include <vector>
#include <optional>
#include <map>
#include "ModelData.h"

struct EulerTransform {
	Vector3 Tscale;
	Vector3 rotate; //Eulerでの回転
	Vector3 translate;
};
struct QuaternionTransform{
	Vector3 scale;
	Quaternion rotate;
	Vector3 translate;
};

struct Joint {
	QuaternionTransform transform; // Transform情報
	Matrix4x4 localMatrix; // localMatrix
	Matrix4x4 skeletonSpaceMatrix; // skeletonでの変換行列
	std::string name; // 名前
	std::vector<int32_t> chaidren; // 子JointのIndexのりすと。いなければ空
	int32_t index; // 自身のIndex
	std::optional<int32_t> parent; // 親JointのIndex。いなければnull
};

struct  SkeletonData
{
	int32_t root; // RootJoointのIndex
	std::map<std::string, int32_t> jointMap; // Join名とIndexとの辞書
	std::vector<Joint> joints; // 所属しているジョイント
};
struct Node {
	QuaternionTransform transform;
	Matrix4x4 localMatrix;
	std::string name;
	std::vector<Node> children;
};

struct VertexWeightData {
	float weight;
	uint32_t vertexIndex;
};

struct JointWeightData {
	Matrix4x4 inverseBindPposeMatrix;
	std::vector<VertexWeightData> vertexWeights;
};
struct ModelData {
	std::map<std::string, JointWeightData> skinClusterData;
	std::vector<VertexData> vertices;
	std::vector<uint32_t> indices;
	MaterialData material;
	Node rootNode;

};

class Skeleton {
public:
	void Update(SkeletonData& skeleton);
	static int32_t CreateJoint(const Node& node, const std::optional<int32_t>& parent,std::vector<Joint>& joints);
	static SkeletonData CreateSkeleton(const Node& rootNode);
private:
};
