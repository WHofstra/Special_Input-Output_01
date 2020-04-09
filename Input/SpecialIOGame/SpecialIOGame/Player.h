#pragma once
#define _USE_MATH_DEFINES

#include "Character.h"
#include "Controller.h"
#include <cmath>
#include <iostream>

class Player :
	public Character
{
	public:
		Player(int aPosX, int aPosY, int aRot, CType aType, sf::Texture* aTexture,
			Controller* aController = nullptr);
		~Player();

		virtual void Update() override;

		void SetSpriteProperties();
		void GetPlayerControllerPress(sf::Event* event);
		void GetPlayerControllerRelease(sf::Event* event);
		void GetControllerJsonValues();

		void JsonValuesCheckHorizontal(Controller* aController, int valueIt, int aValue);
		void JsonValuesCheckVertical(Controller* aController, int valueIt, int aValue);

		sf::ConvexShape SetPlaneDisplay(sf::Vector2f* aPos, int aRot, float aPlane[]);
		sf::ConvexShape GetWindowPlaneDisplay();

	private:
		sf::ConvexShape plane;
		float planeValues[2];

		Controller* controller = nullptr;
};

