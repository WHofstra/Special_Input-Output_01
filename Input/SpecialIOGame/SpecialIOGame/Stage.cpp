#include "Stage.h"

Stage::Stage(StageName aName)//, std::list<sf::Vector2i>* aList)
	:stageName(aName)
{

}

Stage::~Stage()
{

}

Stage::StageName Stage::GetStageName()
{
	return stageName;
}
