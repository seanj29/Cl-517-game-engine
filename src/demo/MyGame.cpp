#include "MyGame.h"
#include "../engine/custom/MyEngineSystem.h"

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), box(5, 5, 30, 30), initialTime(gameTime) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);


    
	m_Particle.ColorBegin = { getRandomColor(0,255) };
	m_Particle.SizeBegin = 10.5f, m_Particle.SizeVariation = 0.3f, m_Particle.SizeEnd = 0.0f;
	m_Particle.LifeTime = 1.0f;
	m_Particle.Velocity = { 3.0f, 3.0f };
	m_Particle.VelocityVariation = { 3.0f, 1.0f };
	m_Particle.Position = { 0, 0 };

	
}
MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {

	if (eventSystem->isPressed(Key::M)) {

		for (int i = 0; i < 5; i++) {
			m_ParticleSystem.Emit(m_Particle);
		}
	}
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
		
		
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
		
		
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
		
		
		
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
		
		
		
	}
}

void MyGame::update() {
	float currentTime = gameTime;
	float timeDiff = currentTime - initialTime;
	initialTime = gameTime;
	m_ParticleSystem.OnUpdate(timeDiff);
	for (int i = 0; i < 5; i++) {
		m_ParticleSystem.Emit(m_Particle);
	}

	box.x += velocity.x;
	box.y += velocity.y;
	float boxxf = box.x;
	float boxyf = box.y;
	m_Particle.Position = { boxxf, boxyf };

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 200;
			key->isAlive = false;
			numKeys--;
		}
	}

	velocity.x = 0;
    velocity.y = 0;

	if (numKeys == 0) {
		gameWon = true;
	}
}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);
	gfx->setDrawColor(SDL_COLOR_VIOLET);
	m_ParticleSystem.OnRender();
}

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);
	if (gameWon)
		gfx->drawText("tt", 250, 500);
}