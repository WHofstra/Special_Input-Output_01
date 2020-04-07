#include "StageDisplay.h"

StageDisplay::StageDisplay(Stage* aStage, sf::RenderWindow* aWindow, int posX, int posY)
	:currentStage(aStage), window(aWindow)
{
	position = sf::Vector2i(posX, posY);

	//Load Texture
	if (!texture.loadFromFile("Assets/Maps.png"))
	{
		EXIT_FAILURE;
		aWindow->close();
	}
	texture.setSmooth(true);

	sprite = SetStageSprite(&texture, window, currentStage->GetStageName(), &position.x, &position.y);
}

StageDisplay::~StageDisplay()
{

}

void StageDisplay::SetStage(Stage* aStage)
{
	currentStage = aStage;
	sprite = SetStageSprite(&texture, window, currentStage->GetStageName(), &position.x, &position.y);
}

sf::Sprite StageDisplay::SetStageSprite(sf::Texture* aTexture, sf::RenderWindow* aWindow,
	Stage::StageName aStageName, int* posX, int* posY)
{
	sf::Sprite* aSprite = &sprite;
	aSprite->setTexture(*aTexture);

	switch (aStageName)
	{ //Get a Part of the Texture
	    case 0:
			aSprite->setTextureRect(sf::IntRect(0, 0, 1023, 1023));
		    break;
	}
	aSprite->setOrigin(ceil(aSprite->getLocalBounds().width / 2), ceil(aSprite->getLocalBounds().height / 2));
	aSprite->setPosition((float)*posX, (float)*posY);
	return *aSprite;
}

sf::Sprite StageDisplay::GetStageWindowDisplay()
{
	return sprite;
}

std::string StageDisplay::GetStageName()
{
	switch (currentStage->GetStageName())
	{
		case 0: return "Donut Plains";
		case 1: return "Mario Circuit";
		case 2: return "Bowser's Castle";
	}
	return "[TBA]";
}
