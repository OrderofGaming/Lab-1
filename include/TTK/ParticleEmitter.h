//////////////////////////////////////////////////////////////////////////
//
// This header is a part of the Tutorial Tool Kit (TTK) library. 
// You may not use this header in your GDW games.
//
// Michael Gharbharan 2015
//
//////////////////////////////////////////////////////////////////////////

#pragma once

#ifdef TTK_EXPORTS
#define TTK_API __declspec(dllexport)
#else
#define TTK_API __declspec(dllimport)
#endif

#include "TTK/Particle.h"

#include <math.h>

namespace TTK
{
	class TTK_API ParticleEmitter
	{
	public:
		ParticleEmitter();
		~ParticleEmitter();

		// Initialize memory for particles
		void initialize(unsigned int numParticles);

		// playback control
		inline void play() { playing = true; }
		inline void pause() { playing = false; }

		// Updates each particle in system
		void update(float dt);

		// Draws particles to screen
		void draw();

		// Used to recycle particles
		TTK::Particle respawnParticle();

		// Emitter position in world space
		// aka where the particles spawn
		TTK::Vector3 initialPosition;

		// locomotion properties
		TTK::Vector3 initialVelocity;
		TTK::Vector3 initialForce;

		float initialLife;
		float initialMass;
		int initialRespawns;

		// visual properties
		TTK::Vector4 colour0;
		TTK::Vector4 colour1;
		float initialSize;

		// Flags
		bool randomizeColour;
		bool randomizeVelocity;
		bool lerpColour;

	private:
		TTK::Particle* particles;
		unsigned int numParticles;

		float spawnTimer;
		int maxParticles;
		bool playing;
	};
}