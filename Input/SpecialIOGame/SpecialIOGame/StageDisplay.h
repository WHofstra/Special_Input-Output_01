#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include <string>

class StageDisplay
{
	public:
		StageDisplay(Stage* aStage, sf::RenderWindow* aWindow, int posX, int posY);
		~StageDisplay();

		void SetStage(Stage* aStage);

		sf::Sprite SetStageSprite(sf::Texture* aTexture, sf::RenderWindow* aWindow,
			Stage::StageName aStageName, int* posX, int* posY);

		sf::Sprite GetStageWindowDisplay();
		std::string GetStageName();

	private:
		Stage* currentStage;

		sf::RenderWindow* window;
		sf::Texture texture;
		sf::Sprite sprite;

		int position[2];
};

