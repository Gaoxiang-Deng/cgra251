// std
#include <algorithm>
#include <utility>

// glm
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// project
#include "shape.hpp"

#include <complex.h>
#include <iostream>
using namespace std;


using namespace glm;


RayIntersection AABB::intersect(const Ray& ray)
{
	RayIntersection intersect;
	vec3 rel_origin = ray.origin - m_center;

	// start magic
	// x
	float rdx_inv = 1 / ray.direction.x;
	float tx1 = (-m_halfsize.x - rel_origin.x) * rdx_inv;
	float tx2 = (m_halfsize.x - rel_origin.x) * rdx_inv;

	float tmin = std::min(tx1, tx2);
	float tmax = std::max(tx1, tx2);

	// y
	float rdy_inv = 1 / ray.direction.y;
	float ty1 = (-m_halfsize.y - rel_origin.y) * rdy_inv;
	float ty2 = (m_halfsize.y - rel_origin.y) * rdy_inv;

	tmin = std::max(tmin, std::min(ty1, ty2));
	tmax = std::min(tmax, std::max(ty1, ty2));

	// z
	float rdz_inv = 1 / ray.direction.z;
	float tz1 = (-m_halfsize.z - rel_origin.z) * rdz_inv;
	float tz2 = (m_halfsize.z - rel_origin.z) * rdz_inv;

	tmin = std::max(tmin, std::min(tz1, tz2));
	tmax = std::min(tmax, std::max(tz1, tz2));

	if (tmax < tmin) return intersect;
	// end magic

	intersect.m_distance = tmin < 0 ? tmax : tmin;
	intersect.m_position = ray.origin + intersect.m_distance * ray.direction;
	intersect.m_valid = tmax >= 0;
	vec3 work_out_a_name_for_it_later = abs((intersect.m_position - m_center) / m_halfsize);
	float max_v = std::max(work_out_a_name_for_it_later[0],
	                       std::max(work_out_a_name_for_it_later[1], work_out_a_name_for_it_later[2]));
	intersect.m_normal = normalize(mix(intersect.m_position - m_center, vec3(0),
	                                   lessThan(work_out_a_name_for_it_later, vec3(max_v))));
	intersect.m_uv_coord = (abs(intersect.m_normal.x) > 0)
		                       ? vec2(intersect.m_position.y, intersect.m_position.z)
		                       : vec2(intersect.m_position.x, intersect.m_position.y + intersect.m_position.z);
	intersect.m_shape = this;

	return intersect;
}


RayIntersection Sphere::intersect(const Ray& ray)
{
	RayIntersection intersect;
	//-------------------------------------------------------------
	// [Assignment 4] :
	// Implement the intersection method for Sphere that returns
	// a RayIntersection object with valid == false if the 
	// ray doesn't intersect and true otherwise. If true, then
	// remember to fill out each feild in the object correctly:
	// - m_valid : true if object is itersected
	// - m_distance : distance along the ray of the intersection
	// - m_position : position on the surface of the intersection
	// - m_normal : normal on the surface of the intersection
	// - m_shape : set to "this"
	// - m_uv_coord : texture coordinates (challenge only)
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...

	float a = dot(ray.direction, ray.direction);
	float b = 2 * dot(ray.origin - m_center, ray.direction);
	float c = dot((ray.origin - m_center), (ray.origin - m_center)) - (m_radius * m_radius);
	float discriminant = b * b - 4 * a * c;
	if (discriminant > 0 ) {
		float t1 = (-b - sqrt(discriminant)) / (2 * a);
		float t2 = (-b + sqrt(discriminant)) / (2 * a);
		
		if (t1 < t2 && t1 > 0) {
			vec3 p1 = ray.origin + t1 * ray.direction;
			intersect.m_position = p1;
			intersect.m_valid = true;
			intersect.m_normal = normalize(m_center - p1);
			intersect.m_shape = this;
			intersect.m_distance = t1;
		}
		else if (t2 < t1 && t2 > 0) {
			vec3 p2 = ray.origin + t2 * ray.direction;
			intersect.m_position = p2;
			intersect.m_valid = true;
			intersect.m_normal = normalize(m_center - p2);
			intersect.m_shape = this;
			intersect.m_distance = t2;
		}
	}else {
		intersect.m_valid = false;
    }
	
	return intersect;
}

RayIntersection Plane::intersect(const Ray& ray)
{
	RayIntersection intersect;
	if (abs(dot(ray.direction, m_normal)) < 3.5){
	float t1 = abs(dot(ray.direction, m_normal));
	vec3 normal = normalize(m_normal);
		float t = dot((m_point - ray.origin), normal) / dot(ray.direction, normal);
		vec3 p1 = ray.origin + t * ray.direction;
		intersect.m_position = p1;
		intersect.m_valid = true;
		intersect.m_normal = normalize(m_point - p1);
		intersect.m_shape = this;
		intersect.m_distance = t;
	}else
	 {
	   intersect.m_valid = false;
	}
	
	return intersect;
	
}

//RayIntersection Disc::intersect(const Ray& ray)
//{
	//Plane* P = new Plane(m_point, m_normal);
	//RayIntersection p_intersect = &intersect;
	//if ();



//}

RayIntersection Triangle::intersect(const Ray& ray)
{
	RayIntersection intersect;
	if (abs(dot(ray.direction, m_normal)) < 0.00001) {
		vec3 Qn = m_point - ray.origin;
		float t = dot(Qn, m_normal) / dot(ray.direction, m_normal);
		vec3 p1 = ray.origin + t * ray.direction;
		intersect.m_position = p1;
		intersect.m_valid = true;
		intersect.m_normal = normalize(m_point - p1);
		intersect.m_shape = this;
		intersect.m_distance = t;
	}
	else
	{
		intersect.m_valid = false;
	}

	return intersect;
}



