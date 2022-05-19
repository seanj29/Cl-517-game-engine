#include "MyEngineSystem.h"
#include "../../demo/MyGame.h"
#include "../GraphicsEngine.h"




ParticleSystem::ParticleSystem()
{
	m_ParticlePool.resize(1000);
}

void ParticleSystem::OnUpdate(float ts)
{
	
	for (auto& particle : m_ParticlePool)
		
	 {
		if (!particle.Active)
			continue;

		if (particle.LifeRemaining <= 0.0f)
		{
			particle.Active = false;
			continue;
		}

		particle.LifeRemaining -= ts;
		particle.Position.x += particle.Velocity.x * (float)ts;
		particle.Position.y += particle.Velocity.y * (float)ts;
		particle.Rotation += 0.01f * ts;
	}
}


void ParticleSystem::OnRender()
{
	GraphicsEngine* gx{};
	for (auto& particle : m_ParticlePool)
	{
		if (!particle.Active)
			continue;

		// Fade away particles
		float life = particle.LifeRemaining / particle.LifeTime;
		
		//color.a = color.a * life;
		SDL_Color color = lerp(particle.ColorBegin, particle.ColorEnd, life);
		float size = lerp(particle.SizeBegin, particle.SizeEnd, life);

		Rectf particlerect(particle.Position.x, particle.Position.y, particle.SizeBegin, particle.SizeBegin);
		SDL_Rect* rectpbuff[5] = { &particlerect.getSDLRect() };
		// Render
		for (int i = 0; i <= 4; i++) {
			gx->drawRect(rectpbuff[i]);
		}
	}
}

void ParticleSystem::Emit(const ParticleProps& particleProps)
{
	Particle& particle = m_ParticlePool[m_PoolIndex];
	particle.Active = true;
	particle.Position = particleProps.Position;
	particle.Rotation = (getRandom(0,100)/50) * (3.14);

	// Velocity
	particle.Velocity = particleProps.Velocity;
	particle.Velocity.x += particleProps.VelocityVariation.x * (getRandom(0,1) - 0.5f);
	particle.Velocity.y += particleProps.VelocityVariation.y * (getRandom(0, 1) - 0.5f);

	// Color
	particle.ColorBegin = particleProps.ColorBegin;
	particle.ColorEnd = particleProps.ColorEnd;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;
	particle.SizeBegin = particleProps.SizeBegin + particleProps.SizeVariation * (getRandom(0, 1) - 0.5f);
	particle.SizeEnd = particleProps.SizeEnd;

	m_PoolIndex = --m_PoolIndex % m_ParticlePool.size();
	
}

void ParticleSystem::EasterEgg() {
	std::cout << "Sean_Otto-Cl517-2021" << std::endl;
}

float ParticleSystem::lerp(float a, float b, float t) {
	
		return a + t * (b - a);
}

SDL_Color ParticleSystem::lerp(SDL_Color a, SDL_Color b, float t) {
	SDL_Color colour;
	colour.r =  a.r + t * (b.r - a.r);
	colour.b = a.b + t * (b.b - a.b);
	colour.g = a.g + t * (b.g - a.g);
	return colour;
}