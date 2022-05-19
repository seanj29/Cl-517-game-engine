#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include <vector>

struct ParticleProps {
	Vector2f Position;
	Vector2f Velocity;
	Vector2f VelocityVariation;
	SDL_Color ColorBegin;
	SDL_Color ColorEnd;
	float SizeBegin;
	float SizeEnd;
	float SizeVariation;
	float LifeTime = 1.0f;
};
	struct Particle 
	{

		Vector2f Position;
		Vector2f Velocity;
		SDL_Color ColorBegin;
		SDL_Color ColorEnd;
		float Rotation = 0.0f;
		float SizeBegin;
		float SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
	};

class ParticleSystem 
{
private:
	std::vector<Particle> m_ParticlePool;
	uint32_t m_PoolIndex = 999;

public:
	
	ParticleSystem();
	void OnUpdate(float ts);
	void OnRender();
	void Emit(const ParticleProps& particleProps);
	void EasterEgg();
	float lerp(float a, float b, float t);
	SDL_Color lerp(SDL_Color a, SDL_Color b, float t);
	

};

#endif