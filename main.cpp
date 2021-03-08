#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <OBJ_Loader.h>
#include "Rasterizer.h"
#include "Object.h"
#include "Light.h"

int main() {
	//Load obj model from file
	objl::Loader Model;
	Model.LoadFile("./Resource/african_head.obj");
	
	//Read relative information from obj file
	Object HumanFace, HumanFace_copy;
	for (auto mesh : Model.LoadedMeshes) {
		for (int i = 0; i < mesh.Vertices.size(); i += 3) {
			Triangle* t = new Triangle();
			Triangle* t_copy = new Triangle();
			for (int j = 0; j < 3; j++) {
				t->setVertex(j, Eigen::Vector4f(mesh.Vertices[i + j].Position.X, mesh.Vertices[i + j].Position.Y, mesh.Vertices[i + j].Position.Z, 1.0));
				t->setNormal(j, Eigen::Vector3f(mesh.Vertices[i + j].Normal.X, mesh.Vertices[i + j].Normal.Y, mesh.Vertices[i + j].Normal.Z));
				t_copy->setVertex(j, Eigen::Vector4f(mesh.Vertices[i + j].Position.X, mesh.Vertices[i + j].Position.Y, mesh.Vertices[i + j].Position.Z, 1.0));
				t_copy->setNormal(j, Eigen::Vector3f(mesh.Vertices[i + j].Normal.X, mesh.Vertices[i + j].Normal.Y, mesh.Vertices[i + j].Normal.Z));
			}
			HumanFace.TriangleList.push_back(t);
			HumanFace_copy.TriangleList.push_back(t_copy);
		}
	}


	//Set information of camera
	Eigen::Vector3f eye_pos, gaze_dir, up_vec;
	eye_pos << 0, 0, 800;
	gaze_dir << 0, 0, -1;
	up_vec << 0, 1, 0;

	//Set information of light source
	Light light;
	light.SetLightPosition(Eigen::Vector3f(0, 0, 1600));
	light.SetLightColor(Eigen::Vector3f(128, 128, 128));
	light.SetLightDensity(1);

	//Relative transformation
	Rasterizer rst(1000, 1000, "output.png");
	rst.ModelTransform(400, 45, &HumanFace);
	rst.ModelTransform(400, 45, &HumanFace_copy);
	//Compute color under illumination
	//light.DiffuseColor(&HumanFace);
	
	//Rest of Transformation
	rst.SetCameraMatrix(eye_pos, gaze_dir, up_vec);
	rst.SetFrustum(-400, -1200, -400, 400, -400, 400);//Set scene
	rst.SetPerspectiveMatrix();
	rst.SetOrthonomalMatrix();
	rst.SetViewportMatrix();

	rst.GenerateViewMatrix();
	rst.ApplyTransformation(&HumanFace);
	rst.RasterizeImage(HumanFace, HumanFace_copy, light);
	rst.GenerateImage();
	return 0;
}