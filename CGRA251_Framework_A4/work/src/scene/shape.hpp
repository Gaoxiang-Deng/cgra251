
#pragma once

// glm
#include <glm/glm.hpp>

// project
#include "ray.hpp"
#include "scene.hpp"


class Shape {
public:
	virtual RayIntersection intersect(const Ray &ray) = 0;
};


class AABB : public Shape {
private:
	glm::vec3 m_center;
	glm::vec3 m_halfsize;

public:
	AABB(const glm::vec3 &c, float hs) : m_center(c), m_halfsize(hs) { }
	AABB(const glm::vec3 &c, const glm::vec3 &hs) : m_center(c), m_halfsize(hs) { }
	virtual RayIntersection intersect(const Ray &ray) override;
};


class Sphere : public Shape {
private:
	glm::vec3 m_center;
	float m_radius;

public:
	Sphere(const glm::vec3 &c, float radius) : m_center(c), m_radius(radius) { }
	virtual RayIntersection intersect(const Ray &ray) override;
};

//-------------------------------------------------------------
// [Assignment 4] :
// Implement the following additional Shapes :
// - Plane
// - Disk
// - Triangle
// Follow the pattern shown by AABB and Sphere for implementing
// a class that subclasses Shape making sure that you implement
// the intersect method for each new Shape.
//-------------------------------------------------------------

// YOUR CODE GOES HERE
// ...
class Plane : public Shape {
private:
	glm::vec3 m_normal;
	glm::vec3 m_point;

public:
	Plane(const glm::vec3& normal, glm::vec3 point) : m_normal(normal), m_point(point) { }
	virtual RayIntersection intersect(const Ray& ray) override;
};

class Disc : public Shape {
private:
	glm::vec3 m_normal;
	glm::vec3 m_point;
	float m_radius;

public:
	Disc(const glm::vec3& normal, glm::vec3 point, float radius) : m_normal(normal), m_point(point), m_radius(radius) { }
	virtual RayIntersection intersect(const Ray& ray) override;
};

class Triangle : public Shape {
private:
	glm::vec3 m_normal;
	glm::vec3 m_point;

public:
	Triangle(const glm::vec3& normal, float point) : m_normal(normal), m_point(point) { }
	virtual RayIntersection intersect(const Ray& ray) override;
};

