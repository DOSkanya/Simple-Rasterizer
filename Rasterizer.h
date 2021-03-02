#pragma once
#include <opencv2/core.hpp>
#include <vector>
#include <Eigen/Dense>

class Rasterizer
{
public:
	cv::Mat image;

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

	Rasterizer(int height, int width, std::string title);

	void SetModelMatrix(float scale, float rotate);
	void SetCameramatrix(Eigen::Vector3f eye_pos, Eigen::Vector3f gaze_dir, Eigen::Vector3f up_vec);
	void SetFrustum(float n, float f, float l, float r, float b, float t);
	void SetPerspectiveMatrix();
	void SetOrthonomalMatrix();
	void SetViewportMatrix();
	void GenerateViewMatrix();

	void GenerateImage();
};

