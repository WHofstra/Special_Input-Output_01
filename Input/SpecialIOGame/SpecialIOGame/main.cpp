#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

#include "Stage.h"
#include "StageDisplay.h"

int main()
{
	//Set Window Resolution to Super Nintendo Entertainment System/Super Famicom
	const int WIN_WIDTH  = 512;
	const int WIN_HEIGHT = 448;

	//Create Window
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Special Output",
		sf::Style::Titlebar | sf::Style::Close); //No Resizing Possible

	//Define Stages
	std::list<Stage*> stages = { new Stage(Stage::StageName::DONUT_PLAINS),
								 new Stage(Stage::StageName::MARIO_CIRCUIT),
								 new Stage(Stage::StageName::BOWSERS_CASTLE) };

	//List Iterator Pointing to Start of List
	std::list<Stage*>::iterator sIt = stages.begin();

	//Display Stage
	StageDisplay* stageDisplay = new StageDisplay(*sIt, &window, WIN_WIDTH/2, WIN_HEIGHT/2);

	//Start Game Loop
	//while (gameRunning) //Use This for OpenGL Rendering
	while(window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			//Close Window or Press 'Shift + Esc' to Quit.
			if (event.type == sf::Event::Closed ||
			   (event.type == sf::Event::KeyPressed && (event.key.shift && event.key.code == sf::Keyboard::Escape)))
			{
				//gameRunning = false; //Use This for OpenGL Rendering
				window.close();
			}
		}

		//Clear Window
		window.clear();

		//Draw Stage
		window.draw(stageDisplay->GetStageWindowDisplay());

		//Display Window
		window.display();
	}

	return 0;
}