#include "Rasterizer.h"

void Rasterizer::ModelTransform(float scale, float rotate, Object* model) {
	Eigen::Matrix4f ScaleMatrix;
	Eigen::Matrix4f RotateMatrix;
	ScaleMatrix << scale, 0, 0, 0,
				   0, scale, 0, 0,
				   0, 0, scale, 0,
				   0, 0, 0, 1;
	RotateMatrix << cos(rotate), 0, sin(rotate), 0,
					0, 1, 0, 0,
					-sin(rotate), 0, cos(rotate), 0,
					0, 0, 0, 1;
	Model = RotateMatrix * ScaleMatrix;

	for (auto Triangle : model->TriangleList) {
		for (int i = 0; i < 3; i++) {
			Triangle->vertex[i] = Model * Triangle->vertex[i];
			Triangle->normal[i] = RotateMatrix.block(0, 0, 3, 3) * Triangle->normal[i];
		}
	}
}

void Rasterizer::SetCameraMatrix(Eigen::Vector3f eye_pos, Eigen::Vector3f gaze_dir, Eigen::Vector3f up_vec) {
	Eigen::Vector3f w = -gaze_dir.normalized();
	Eigen::Vector3f u = (up_vec.cross(w)).normalized();
	Eigen::Vector3f v = w.cross(u);

	Eigen::Matrix4f Translation;
	Translation << 1, 0, 0, -eye_pos.x(),
				   0, 1, 0, -eye_pos.y(),
				   0, 0, 1, -eye_pos.z(),
				   0, 0, 0, 1;
	Eigen::Matrix4f AlterCoord;
	AlterCoord << u.x(), u.y(), u.z(), 0,
				  v.x(), v.y(), v.z(), 0,
				  w.x(), w.y(), w.z(), 0,
				  0, 0, 0, 1;

	Camera = AlterCoord * Translation;
}

void Rasterizer::SetFrustum(float ne, float fa, float le, float ri, float bo, float to) {
	n = ne; f = fa;
	l = le; r = ri;
	b = bo; t = to;
}

void Rasterizer::SetPerspectiveMatrix() {
	Pers << n, 0, 0, 0,
			0, n, 0, 0,
			0, 0, n+f, -n*f,
			0, 0, 1, 0;
}

void Rasterizer::SetOrthonomalMatrix() {
	Orth << 2 / (r - l), 0, 0, -(r + l) / (r - l),
			0, 2 / (t - b), 0, -(t + b) / (t - b),
			0, 0, 2 / (n - f), -(n + f) / (n - f),
			0, 0, 0, 1;
}

void Rasterizer::SetViewportMatrix() {
	Viewport << screen_height / 2, 0, 0, (screen_height - 1) / 2.,
				0, screen_width / 2, 0, (screen_width - 1) / 2.,
				0, 0, 1, 0,
				0, 0, 0, 1;
}

void Rasterizer::GenerateViewMatrix() {
	M = Viewport * Orth * Pers * Camera;
}

Rasterizer::Rasterizer(int width, int height, std::string title) {
	screen_height = height;
	screen_width = width;
	image_name = title;

	//initialize color buffer to black
	pixel_color.resize(screen_height * screen_width);
	for (int i = 0; i < pixel_color.size(); i++) {
		pixel_color[i] << 0, 0, 0;
	}

	//initialize depth buffer to minimum
	depth_buffer.resize(screen_height * screen_width);
	for (int i = 0; i < depth_buffer.size(); i++) {
		depth_buffer[i] = -std::numeric_limits<float>::max();
	}
}

void Rasterizer::ApplyTransformation(Object* model) {
	for (auto Triangle : model->TriangleList) {
		for (int i = 0; i < 3; i++) {
			Triangle->vertex[i] = M * Triangle->vertex[i];
			Triangle->vertex[i] = Triangle->vertex[i] / Triangle->vertex[i].w();//normalized
		}
	}
}

void Rasterizer::RasterizeImage(Object model, Object model_copy, Light light) {
	for (int i = 0; i < model.TriangleList.size(); i++) {
		Triangle* triangle = model.TriangleList[i];
		Triangle* triangle_copy = model_copy.TriangleList[i];
		//Axis_Aligned Bounding Box
		int xMin = (int)floor(std::min(triangle->vertex[0].x(), std::min(triangle->vertex[1].x(), triangle->vertex[2].x())));
		int xMax = (int)ceil(std::max(triangle->vertex[0].x(), std::max(triangle->vertex[1].x(), triangle->vertex[2].x())));
		int yMin = (int)floor(std::min(triangle->vertex[0].y(), std::min(triangle->vertex[1].y(), triangle->vertex[2].y())));
		int yMax = (int)ceil(std::max(triangle->vertex[0].y(), std::max(triangle->vertex[1].y(), triangle->vertex[2].y())));
		for (int v = yMin; v <= yMax; v++) {//Outside loop update rows
			for (int u = xMin; u <= xMax; u++) {//Inside loop update columns
				auto [alpha, beta, gamma] = triangle->BarycentricCoord((float)u, (float)v);
				if (alpha >= 0 && beta >= 0 && gamma >= 0) {
					float z_interpolated = alpha * triangle->vertex[0].z() + beta * triangle->vertex[1].z() + gamma * triangle->vertex[2].z();
					if (z_interpolated > depth_buffer[v * screen_width + u]) {
						depth_buffer[v * screen_width + u] = z_interpolated;
						//Per-fragment Shading
						Eigen::Vector3f normal_interpolated = alpha * triangle_copy->normal[0] + beta * triangle_copy->normal[1] + gamma * triangle_copy->normal[2];
						normal_interpolated.normalize();
						Eigen::Vector4f vertex_interpolated = alpha * triangle_copy->vertex[0] + beta * triangle_copy->vertex[1] + gamma * triangle_copy->vertex[2];
						Eigen::Vector3f l = light.Position - vertex_interpolated.segment(0, 3);
						l.normalize();
						pixel_color[v * screen_width + u] = light.Density * std::max(0.f, normal_interpolated.dot(l)) * light.Color;

					}
				}
			}
		}
	}
}

void Rasterizer::GenerateImage() {
	cv::Mat image(screen_height, screen_width, CV_32FC3, pixel_color.data());
	image.convertTo(image, CV_8UC3, 1.0f);
	cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
	cv::flip(image, image, 0);
	cv::imwrite(image_name, image);
}