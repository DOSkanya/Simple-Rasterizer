#pragma once
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <Eigen/Dense>
#include "Object.h"
#include "Light.h"

class Rasterizer
{
public:
	std::vector<Eigen::Vector3f> pixel_color;
	std::vector<float> depth_buffer;

	Eigen::Matrix4f Model;
	Eigen::Matrix4f Camera;
	Eigen::Matrix4f Pers;//Perspective matrix
	Eigen::Matrix4f Orth;//Orthonomal projection matrix
	Eigen::Matrix4f Viewport;

	Eigen::Matrix4f M;

	float n, f, l, r, b, t;//Information about frustum
	int screen_height, screen_width;
	std::string image_name;

	Rasterizer(int width, int height, std::string title);

	void SetCameraMatrix(Eigen::Vector3f eye_pos, Eigen::Vector3f gaze_dir, Eigen::Vector3f up_vec);
	void SetFrustum(float ne, float fa, float le, float ri, float bo, float to);
	void SetPerspectiveMatrix();
	void SetOrthonomalMatrix();
	void SetViewportMatrix();
	void GenerateViewMatrix(); 

	void ModelTransform(float scale, float rotate, Object* model);
	void ApplyTransformation(Object* model);
	void RasterizeImage(Object model, Object model_copy, Light light);

	void GenerateImage();
};

