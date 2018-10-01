#pragma once

#include"../particle.h"
#include"../vertex.h"
#include"unlit_batch.h"
#include"../../core/clock.h"

#define PARTICLE_SIZE sizeof(bear::graphics::Vertex)*4
#define MAX_PARTICLES 10000
#define PARTICLE_BUFFER_SIZE PARTICLE_SIZE * MAX_PARTICLES
#define INDICES_COUNT MAX_PARTICLES*6

namespace bear { namespace graphics {

	struct Image;
	class Texture;
	class View;

	// Struct to describe how the particle source should burst/emitt it's particles
	struct ParticleEmission {
		unsigned int count = 0; // number of particles to emitt on each burst 
		unsigned int cycle_count = 0;  // number of bursts, if 0 repeat infinite
		float repeat_interval = 0; // how often to repeat the burst, in milliseconds
	};

	struct ParticleSourceConfiguration {
		core::Vector2f gravity_vector;
		std::string texture_name;
	};

	class ParticleSource {
	private:
		// Rendering values
		UnlitBatcher* m_Batch;
		unsigned int m_ParticleCount = 0;
		Texture* m_Texture;
		static View &defaultView;

		// Emission values
		ParticlePool m_ParticlePool; 
		
		ParticleConfig m_ParticleConfig;		   // Particle unique configuration
		ParticleConfigFlags::Value m_ConfigFlags;

		ParticleSourceConfiguration m_SourceConfig; // Particle shared across system configuration

		ParticleEmission m_Emitter;
		core::Clock m_EmissionClock;

	public:
		ParticleSource() { }
		~ParticleSource();

		// Init required stuff for particle buffer
		void init();
		// Very important to call if this source uses an emitter
		void update(float dt); 

		// Call to render each particle currently on the source
		void render(View& a_View = defaultView);
		void begin();
		void submit(ParticlePool& a_ParticlePool);
		void flush(View& a_View);

		// Config methods
		void setGravityAcceleration(core::Vector2f& a_Vector);
		void setActiveTexture(const std::string& a_TextureName);
		void setParticleEmitter(ParticleEmission& a_ParticleEmitter);
		void setParticleConfiguration(ParticleConfig& a_ParticleConfig, ParticleConfigFlags::Value m_Flags);
	};

} }