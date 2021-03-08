#pragma once
#include <Eigen/Dense>

class Triangle
{
public:
	Eigen::Vector4f vertex[3];
	Eigen::Vector3f color[3];
	Eigen::Vector3f normal[3];

	Triangle();

	void setVertex(int ind, Eigen::Vector4f ver);
	void setColor(int ind, float r, float g, float b);
	void setNormal(int ind, Eigen::Vector3f n);

	std::tuple<float, float, float> BarycentricCoord(float u, float v);
};

