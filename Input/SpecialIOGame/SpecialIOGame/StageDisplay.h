#pragma once
#include <SFML/Graphics.hpp>
#include "Stage.h"
#include <iostream>

class StageDisplay
{
	public:
		StageDisplay(Stage* aStage, sf::RenderWindow* aWindow, int posX, int posY);
		~StageDisplay();

		void SetStageNames();
		void SetStage(Stage* aStage);

		sf::Sprite SetStageSprite(sf::Texture* aTexture, Stage::StageName aStageName, int* posX, int* posY);
		sf::Sprite GetStageWindowDisplay();
		std::string GetStageName();

	private:
		Stage* currentStage;
		sf::Texture texture;
		sf::Sprite sprite;
		std::map<Stage::StageName, std::string> stageNames;
};

