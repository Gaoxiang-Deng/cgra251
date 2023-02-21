// glm
#include <glm/gtc/random.hpp>

// project
#include "boid.hpp"
#include "scene.hpp"
#include "cgra/cgra_mesh.hpp"


using namespace glm;
using namespace std;


vec3 Boid::color() const
{
	return vec3(0, 1, 0);
}


void Boid::calculateForces(Scene* scene)
{
	//-------------------------------------------------------------
	// [Assignment 3] :
	// Calculate the forces affecting the boid and update the
	// acceleration (assuming mass = 1).
	// Do NOT update velocity or position in this function.
	// Core : 
	//  - Cohesion
	//  - Alignment
	//  - Avoidance
	//  - Soft Bound (optional)
	// Completion : 
	//  - Cohesion and Alignment with only boids in the same flock
	//  - Predator Avoidance (boids only)
	//  - Predator Chase (predator only)
	// Challenge : 
	//  - Obstacle avoidance
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE

	int neighbours = 0;
	glm::vec3 centroid = vec3(0,0,0);
	glm::vec3 mean_velocity = vec3(0,0,0);
	glm::vec3 avoidance = vec3(0,0,0);


	for (auto& other : scene->boids())
	{
		if (this != &other){
		glm::vec3 displacement = this->m_position - other.m_position;
		float distance = glm::length(displacement);
		if (distance < scene->m_neighbourhood_radius && distance != 0)
		{
			neighbours += 1;
			avoidance += displacement / (distance * distance);
			centroid += other.m_position;
			mean_velocity += other.m_velocity;
		}
	 }
	}
		
	

	if (neighbours > 0)
	{
		centroid /= neighbours;
		mean_velocity /= neighbours;
		avoidance *= scene->m_avoidance_weight;
		glm::vec3 cohesion = scene->m_cohesion_weight * (centroid - this->m_position);
		glm::vec3 alignment = scene->m_alignment_weight * (mean_velocity - this->m_velocity);
		this->m_acceleration = cohesion + alignment + avoidance;
	}else
	{
		this->m_acceleration = vec3(0, 0, 0);
	}
}


void Boid::update(float timestep, Scene* scene)
{
	//-------------------------------------------------------------
	// [Assignment 3] :
	// Integrate the velocity of the boid using the timestep.
	// Update the position of the boid using the new velocity.
	// Take into account the bounds of the scene which may
	// require you to change the velocity (if bouncing) or
	// change the position (if wrapping).
	//-------------------------------------------------------------

	// YOUR CODE GOES HERE
	// ...
	// //
	// std::cout << m_acceleration.x << " " << m_acceleration.y << " " << m_acceleration.z << std::endl                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       n ;
	//

	float min_speed = 1;
	float max_speed = 100;
	float speed = length(m_velocity);
	speed = clamp(speed, min_speed, max_speed);
	m_velocity = speed * normalize(m_velocity);
	vec3 position = scene->bound();
	m_position = -position + mod(m_position - -position, position - -position);
	
	// if(m_position.x > scene->.x&& m_velocity.x > 0)
	// {
	// 	m_velocity.x = -m_velocity.x;
	// }
	// if (m_position.x < -scene->bound().x && m_velocity.x < 0)
	// {
	// 	m_velocity.x = -m_velocity.x;
	// }
	// if (m_position.y > scene->bound().y && m_velocity.y > 0)
	// {
	// 	m_velocity.y = -m_velocity.y;
	// }
	// if (m_position.y < -scene->bound().y && m_velocity.y < 0)
	// {
	// 	m_velocity.y = -m_velocity.y;
	// }
	// if (m_position.z > scene->bound().z && m_velocity.z > 0)
	// {
	// 	m_velocity.z = -m_velocity.z;
	// }
	// if (m_position.z < -scene->bound().z && m_velocity.z < 0)
	// {
	// 	m_velocity.z = -m_velocity.z;
	// }
	//
	m_velocity += m_acceleration * timestep;
	m_position += m_velocity * timestep;

}


//
// //
//

//
