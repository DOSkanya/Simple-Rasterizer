#include <Eigen/Dense>
#include <opencv2/core.hpp>
#include <OBJ_Loader.h>
#include "Object.h"

int main() {
	//Load obj model from file
	objl::Loader Model;
	Model.LoadFile("/Resource/african_head.obj");
	
	//Read relative information from obj file
	Object HumanFace;
	for (auto mesh : Model.LoadedMeshes) {
		for (int i = 0; i < mesh.Vertices.size(); i += 3) {
			Triangle* t;
			for (int j = 0; j < 3; j++) {
				t->setVertex(j, Eigen::Vector4f(mesh.Vertices[i + j].Position.X, mesh.Vertices[i + j].Position.Y, mesh.Vertices[i + j].Position.Z, 1.0));
				t->setNormal(j, Eigen::Vector3f(mesh.Vertices[i + j].Normal.X, mesh.Vertices[i + j].Normal.Y, mesh.Vertices[i + j].Normal.Z));
			}
			HumanFace.TriangleList.push_back(t);
		}
	}



}