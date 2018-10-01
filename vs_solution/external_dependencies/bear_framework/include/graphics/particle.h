#pragma once

#include"../core/vector2.h"
#include"../core/color.h"

#include<vector>

#define PARTICLE_INCREMENT_CONST 1

namespace bear { namespace graphics {

	// Used when rendering a particle primitive
	struct ParticleVertex {
		core::Vector2f position;
		core::Color color;
		float size;
		core::Vector2f velocity;
		float aliveTime;
		float deathTime;
	};

	struct ParticleConfigFlags {
		enum Value {
			RANDOM_SIZE				 = 0x01,
			RANDOM_COLOR			 = 0x02,
			RANDOM_VELOCITY			 = 0x04,
			RANDOM_DEATHTIME		 = 0x08,
			RANDOM_POSITION		   	 = 0x10,
			RANDOM_POSITION_CIRCLE	 = 0x20,
		};
	};

	struct ParticleConfig {
		core::Vector2f position;
		core::Vector2f position1, position2;
		core::Vector2f circlePositionCenter;
		unsigned int circlePositionRadius;   // Used when RANDOM_POSITION_INSIDE_CIRCLE flag is set
		
		int size;
		int min_size, max_size;

		core::Color color;

		core::Vector2f velocity1, velocity2;
		core::Vector2f velocity;

		float deathTime1, deathTime2;
		float deathTime;		
	};

	struct Particle {
		core::Vector2f position;
		int size;
		core::Color color;
		core::Vector2f velocity;
		float aliveTime = 0;
		float deathTime;

		// Constructor
		Particle() { }
		Particle(ParticleConfig& a_Config, ParticleConfigFlags::Value a_Flags);
	};


	struct ParticlePool {
		std::vector<Particle> particle_list;

		void addParticles(int num, ParticleConfig& config, ParticleConfigFlags::Value a_Flags);
		void process(float delta_time);
	};


} }