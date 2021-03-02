#include "Rasterizer.h"

void Rasterizer::SetModelMatrix(float scale, float rotate) {

}

void Rasterizer::SetCameramatrix(Eigen::Vector3f eye_pos, Eigen::Vector3f gaze_dir, Eigen::Vector3f up_vec) {

}

void Rasterizer::SetFrustum(float n, float f, float l, float r, float b, float t) {

}

void Rasterizer::SetPerspectiveMatrix() {

}

void Rasterizer::SetOrthonomalMatrix() {

}

void Rasterizer::SetViewportMatrix() {

}

void Rasterizer::GenerateViewMatrix() {

}

Rasterizer::Rasterizer(int height, int width, std::string title) {
	screen_height = height;
	screen_width = width;
	image_name = title;
}

void Rasterizer::GenerateImage() {

}