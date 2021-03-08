#include "Triangle.h"

Triangle::Triangle() {
    vertex[0] << 0, 0, 0, 1;
    vertex[1] << 0, 0, 0, 1;
    vertex[2] << 0, 0, 0, 1;

    color[0] << 0.0, 0.0, 0.0;
    color[1] << 0.0, 0.0, 0.0;
    color[2] << 0.0, 0.0, 0.0;
    
    normal[0] << 0, 0, 0;
    normal[1] << 0, 0, 0;
    normal[2] << 0, 0, 0;
}

void Triangle::setVertex(int ind, Eigen::Vector4f ver) {
    vertex[ind] = ver;
}

void Triangle::setColor(int ind, float r, float g, float b) {
    color[ind] = Eigen::Vector3f(r, g, b);
}
void Triangle::setNormal(int ind, Eigen::Vector3f n) {
    normal[ind] = n;
}

std::tuple<float, float, float> Triangle::BarycentricCoord(float u, float v) {
    float denominator = (vertex[1].x() - vertex[0].x()) * (vertex[2].y() - vertex[0].y()) - 
                        (vertex[2].x() - vertex[0].x()) * (vertex[1].y() - vertex[0].y());
    float beta_numerator = (u - vertex[0].x()) * (vertex[2].y() - vertex[0].y()) -
                           (vertex[2].x() - vertex[0].x()) * (v - vertex[0].y());
    float gamma_numerator = (vertex[1].x() - vertex[0].x()) * (v - vertex[0].y()) -
                            (u - vertex[0].x()) * (vertex[1].y() - vertex[0].y());
    float beta = beta_numerator / denominator;
    float gamma = gamma_numerator / denominator;
    float alpha = 1 - beta - gamma;
    return { alpha, beta, gamma };
}