#pragma once
#define _USE_MATH_DEFINES

#include "Character.h"
#include <cmath>
//#include <iostream>

class Player :
	public Character
{
	public:
		Player(int aPosX, int aPosY, int aRot, CType aType, sf::Texture* aTexture);
		~Player();

		virtual void Update() override;

		void SetSpriteProperties();
		void GetPlayerControllerPress(sf::Event* event);
		void GetPlayerControllerRelease(sf::Event* event);

		sf::ConvexShape SetPlaneDisplay(sf::Vector2f* aPos, int aRot, float aPlane[]);
		sf::ConvexShape GetWindowPlaneDisplay();

	private:
		sf::ConvexShape plane;
		float planeValues[2];
};

