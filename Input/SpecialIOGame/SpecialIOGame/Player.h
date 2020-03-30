#pragma once
#include "Character.h"
#include <list>

class Player :
	public Character
{
	public:
		Player(int aPosX, int aPosY, int aRot, CType aType, sf::Texture* aTexture);
		~Player();

		void SetSpriteProperties();
		void GetPlayerController(sf::Event* event);
		void SetPlayerVelocity(int velX, int velY);
		void SetPlayerRotation(int anAngle);

		std::list<sf::Keyboard::Key> GetPlayerControls(std::list<sf::Keyboard::Key> aList);

	private:
		std::list<sf::Keyboard::Key> playerControls;
		std::list<sf::Keyboard::Key>::iterator controlIt;
};

