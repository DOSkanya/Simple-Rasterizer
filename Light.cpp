#include "Light.h"

void Light::SetLightPosition(Eigen::Vector3f P) {
	Position = P;
}

void Light::SetLightColor(Eigen::Vector3f C) {
	Color = C;
}

void Light::SetLightDensity(float D) {
	Density = D;
}

void Light::DiffuseColor(Object* Model) {
	for (auto Triangle : Model->TriangleList) {
		for (int i = 0; i < 3; i++) {
			Eigen::Vector3f l = Position - Triangle->vertex[i].segment(0, 3);
			l.normalize();
			Triangle->color[i] = Density * std::max(0.f, Triangle->normal[i].dot(l)) * Color;
		}
	}
}
