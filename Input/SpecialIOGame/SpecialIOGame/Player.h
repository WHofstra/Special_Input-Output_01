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

		void SetBoundaries(sf::RenderWindow* aWindow, int beginX = 0, int beginY = 0);
		void SetSpriteProperties();
		void GetPlayerControllerPress(sf::Event* event);
		void GetPlayerControllerRelease(sf::Event* event);
		void GetControllerJsonValues();

		void CheckBoundaries(sf::Vector2f* aPos, sf::Vector2i* aBound);
		void JsonValuesCheckHorizontal(Controller* aController, int valueIt, int aValue);
		void JsonValuesCheckVertical(Controller* aController, int valueIt, int aValue);

		sf::ConvexShape SetPlaneDisplay(sf::Vector2f* aPos, int aRot, float aPlane[]);
		sf::ConvexShape GetWindowPlaneDisplay();

	private:
		sf::ConvexShape plane;
		std::vector<int> bounds = { 0, 0, 0, 0 };
		float planeValues[2];

		Controller* controller = nullptr;
};

