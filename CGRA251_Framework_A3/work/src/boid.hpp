
#pragma once

// glm
#include <glm/glm.hpp>

// project
#include "scene.hpp"


class Boid {
private:
	glm::vec3 m_position;
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;
	int ispradator;
public:
	
	Boid(glm::vec3 pos, glm::vec3 dir, int isPradator) : m_position(pos), m_velocity(dir), ispradator(isPradator){ }

	glm::vec3 position() const { return m_position; }
	glm::vec3 velocity() const { return m_velocity; }
	glm::vec3 acceleration() const { return m_acceleration; }
	glm::vec3 color() const;
    int getPradator() const { return ispradator; }
	
	void calculateForces(Scene *scene);
	void update(float timestep, Scene *scene);
	
	
	glm::vec3 confinnment(Scene* scene) const;

	glm::vec3 sensible_speed() const;

};