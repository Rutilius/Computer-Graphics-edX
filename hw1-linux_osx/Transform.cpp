// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	float radiant = glm::radians(degrees);
	mat3 I(1.0);
	mat3 crossAxis = mat3(axis.x * axis.x, axis.x * axis.y, axis.x * axis.z, axis.y * axis.x, axis.y * axis.y, axis.y * axis.z, axis.z * axis.x, axis.z * axis.y, axis.z * axis.z);
	mat3 dualMatrix = mat3(0., axis.z, -axis.y, -axis.z, 0., axis.x, axis.y, -axis.x, 0.);
	return (glm::cos(radiant) * I) + ((1.f - glm::cos(radiant)) * crossAxis) + (glm::sin(radiant) * dualMatrix);
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	eye = rotate(degrees, up) * eye;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	vec3 rotAxis = glm::normalize(glm::cross(eye, up));
	eye = rotate(degrees, rotAxis) * eye;
	up = glm::normalize(glm::cross(rotAxis, eye));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
	return mat4(u.x, v.x, w.x, 0., u.y, v.y, w.y, 0., u.z, v.z, w.z, 0., -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1.);
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
