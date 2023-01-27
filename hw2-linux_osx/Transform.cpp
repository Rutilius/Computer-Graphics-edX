// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
  mat3 ret;
  // YOUR CODE FOR HW2 HERE
  // Please implement this.  Likely the same as in HW 1.  
  // -------------------------------------------------
  float radiant = glm::radians(degrees);
  vec3 normAxis = glm::normalize(axis);
	mat3 R(glm::cos(radiant));
	mat3 crossAxis = mat3(
                    normAxis.x * normAxis.x, normAxis.x * normAxis.y, normAxis.x * normAxis.z,
                    normAxis.y * normAxis.x, normAxis.y * normAxis.y, normAxis.y * normAxis.z,
                    normAxis.z * normAxis.x, normAxis.z * normAxis.y, normAxis.z * normAxis.z
                  );
	mat3 dualMatrix = mat3(
                      0.         , normAxis.z, -normAxis.y,
                      -normAxis.z, 0.        , normAxis.x ,
                      normAxis.y ,-normAxis.x, 0.
                    );
  float invCos = 1.f - glm::cos(radiant);
  mat3 CA = invCos * crossAxis;
  mat3 DM = glm::sin(radiant) * dualMatrix;
	ret = R + CA + DM;
  // -------------------------------------------------
  return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.  
  // -------------------------------------------------
  eye = rotate(degrees, up) * eye;
  // -------------------------------------------------
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE 
  // Likely the same as in HW 1.  
  // -------------------------------------------------
  vec3 rotAxis = glm::normalize(glm::cross(eye, up));
	eye = rotate(degrees, rotAxis) * eye;
	up = glm::normalize(glm::cross(rotAxis, eye));
  // -------------------------------------------------
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.  
  // -------------------------------------------------
  vec3 w = glm::normalize(eye - center);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);
  
	ret = mat4(
            u.x              ,              v.x ,               w.x, 0.,
            u.y              ,              v.y ,               w.y, 0.,
            u.z              ,              v.z ,               w.z, 0.,
            -glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1.
          );
  // -------------------------------------------------
  return ret;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret(0);
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.  
  // -------------------------------------------------
  float t = glm::radians(fovy) / 2;
  float d = 1 / glm::tan(t);
  float zDistance = zFar - zNear;
  ret[0][0] = d / aspect;
  ret[1][1] = d;
  ret[2][2] = - ((zFar + zNear) / zDistance);
  ret[2][3] = -1;
  ret[3][2] = - ((2 * zFar * zNear) / zDistance);
  // -------------------------------------------------
  return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  mat4 ret(1);
  // YOUR CODE FOR HW2 HERE
  // Implement scaling 
  // -------------------------------------------------
  ret[0][0] = sx;
  ret[1][1] = sy;
  ret[2][2] = sz;
  // -------------------------------------------------
  return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  mat4 ret(1);
  // YOUR CODE FOR HW2 HERE
  // Implement translation 
  // -------------------------------------------------
  ret[3][0] = tx;
  ret[3][1] = ty;
  ret[3][2] = tz;
  // -------------------------------------------------
  return ret;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
