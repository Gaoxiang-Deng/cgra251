
#include <iostream>

// glm
#include <glm/gtc/matrix_transform.hpp>

// project
#include "camera.hpp"
#include "opengl.hpp"


using namespace std;
using namespace glm;


void Camera::setPositionOrientation(const vec3 &pos, float yaw, float pitch) {
	m_position = pos;
	m_yaw = yaw;
	m_pitch = pitch;

	// update rotation matrix (based on yaw and pitch)
	m_rotation = rotate(mat4(1), m_yaw, vec3(0, 1, 0)) * rotate(mat4(1), m_pitch, vec3(1, 0, 0));
}


Ray Camera::generateRay(const vec2 &pixel) {
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Generate a ray in the scene using the camera position,
	// rotation field of view on the y axis (fovy) and the image
	// size. The pixel is given in image coordinates [0, imagesize]
	// This COULD be done by first creating the ray in ViewSpace
	// then transforming it by the position and rotation to get
	// it into worldspace.
	//-------------------------------------------------------------
	
	Ray ray;

	// YOUR CODE GOES HERE
	// ...
	float y = tan(m_fovy / 2);
	float x =(m_image_size.x / m_image_size.y) * y;
	
	float p_x = (-1 + (pixel.x / m_image_size.x ) * 2)*x;
	float p_y = (-1 + (pixel.y / m_image_size.y ) * 2)*y;

	
	ray.direction = normalize(vec3(p_x, p_y, -1));
	ray.direction = vec4(ray.direction, 0) * (m_rotation);

	ray.origin = m_position;
	return ray;
}
