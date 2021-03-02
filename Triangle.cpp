#include "Triangle.h"

Triangle::Triangle() {
    v[0] << 0, 0, 0, 1;
    v[1] << 0, 0, 0, 1;
    v[2] << 0, 0, 0, 1;

    color[0] << 0.0, 0.0, 0.0;
    color[1] << 0.0, 0.0, 0.0;
    color[2] << 0.0, 0.0, 0.0;
    
    normal[0] << 0, 0, 0;
    normal[1] << 0, 0, 0;
    normal[2] << 0, 0, 0;
}

void Triangle::setVertex(int ind, Eigen::Vector4f ver) {
    v[ind] = ver;
}

void Triangle::setColor(int ind, float r, float g, float b) {
    color[ind] = Eigen::Vector3f(r, g, b);
}
void Triangle::setNormal(int ind, Eigen::Vector3f n) {
    normal[ind] = n;
}