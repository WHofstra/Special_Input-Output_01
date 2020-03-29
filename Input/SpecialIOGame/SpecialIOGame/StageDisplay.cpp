#include "StageDisplay.h"

StageDisplay::StageDisplay(Stage* aStage, sf::RenderWindow* aWindow, int posX, int posY)
	:currentStage(aStage)
{
	//Load Texture
	if (!texture.loadFromFile("Assets/Maps.png"))
	{
		EXIT_FAILURE;
		aWindow->close();
	}
	texture.setSmooth(true);

	SetStageNames();
	sprite = SetStageSprite(&texture, currentStage->GetStageName(), &posX, &posY);
}

StageDisplay::~StageDisplay()
{

}

void StageDisplay::SetStageNames()
{
	//Add the Stage Names
	stageNames[Stage::StageName::DONUT_PLAINS]   = "Donut Plains";
	stageNames[Stage::StageName::MARIO_CIRCUIT]  = "Mario Circuit";
	stageNames[Stage::StageName::BOWSERS_CASTLE] = "Bowser's Castle";
}

void StageDisplay::SetStage(Stage* aStage)
{
	currentStage = aStage;
}

sf::Sprite StageDisplay::SetStageSprite(sf::Texture* aTexture, Stage::StageName aStageName, int* posX, int* posY)
{
	sf::Sprite aSprite(*aTexture);

	switch (aStageName)
	{ //Get a Part of the Texture
	    case 0:
			aSprite.setTextureRect(sf::IntRect(0, 0, 1023, 1023));
		    break;
	}
	aSprite.setOrigin(ceil(aSprite.getLocalBounds().width / 2), ceil(aSprite.getLocalBounds().height / 2));
	aSprite.setPosition(*posX, *posY);
	return aSprite;
}

sf::Sprite StageDisplay::GetStageWindowDisplay()
{
	return sprite;
}

std::string StageDisplay::GetStageName()
{
	return stageNames[currentStage->GetStageName()];
}
