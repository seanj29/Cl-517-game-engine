#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "../engine/custom/MyEngineSystem.h"

struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;

		Vector2i velocity;

		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score, numKeys, lives;
		bool gameWon;
		float initialTime;
	
		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
		ParticleProps m_Particle;
		ParticleSystem m_ParticleSystem;

	public:
        MyGame();
		~MyGame();
	
};

#endif