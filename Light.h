#pragma once
#include "Object.h"

class Light
{
public:
	Eigen::Vector3f Position;
	Eigen::Vector3f Color;
	float Density;

	void SetLightPosition(Eigen::Vector3f P);
	void SetLightColor(Eigen::Vector3f C);
	void SetLightDensity(float D);
	void DiffuseColor(Object* Model);
};

