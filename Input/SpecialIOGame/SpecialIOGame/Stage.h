#pragma once
#include <SFML/Graphics.hpp>
#include <list>

class Stage
{
	public:
		enum StageName
		{
			DONUT_PLAINS, MARIO_CIRCUIT, BOWSERS_CASTLE
		};

		Stage(StageName aName);// , std::list<sf::Vector2i>* aList);
		~Stage();

		StageName GetStageName();

		void SetCollisions();
		void SetCharacterPositions(std::list<sf::Vector2i>* aPosList);
		void SetHazards();

	private:
		StageName stageName;
};

