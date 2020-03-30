#pragma once
#include "Character.h"

class Player :
	public Character
{
	public:
		Player(int aPosX, int aPosY, int aRot, CType* aType, sf::Texture aTexture);
		~Player();

		void PlayerController();
		void MovePlayer(int velX, int velY);
		void RotatePlayer(int anAngle);

	private:
		
};

