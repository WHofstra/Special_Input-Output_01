#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>

#include "Stage.h"
#include "StageDisplay.h"
#include "Player.h"
#include "Controller.h"

int main()
{
	//Set Window Resolution to Super Nintendo Entertainment System/Super Famicom
	const int WIN_WIDTH  = 512;
	const int WIN_HEIGHT = 448;

	//Define Server Info
	std::string serverUrl = "http://29980.hosts2.ma-cloud.nl";
	std::string filePath  = "/bewijzenmap/SpIO/test.json";

	//Create Window
	sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Special Output",
		sf::Style::Titlebar | sf::Style::Close); //No Resizing Possible

	//Set Controller
	Controller* controller = new Controller(&serverUrl, &filePath, &window);

	//Define Stages
	std::list<Stage*> stages = { new Stage(Stage::StageName::DONUT_PLAINS),
								 new Stage(Stage::StageName::MARIO_CIRCUIT),
								 new Stage(Stage::StageName::BOWSERS_CASTLE) };

	//Define Texture Character Sprite References
	sf::Texture objectTexture;
	if (!objectTexture.loadFromFile("Assets/CharacterSprites.png"))
	{
		return EXIT_FAILURE;
	}
	objectTexture.setSmooth(true);

	//Define Characters
	Player* player = new Player(WIN_WIDTH / 2, WIN_HEIGHT / 2, 0, Character::CType::WALUIGI, &objectTexture);

	//List Iterator Pointing to Start of List
	std::list<Stage*>::iterator sIt = stages.begin();

	//Display Stage
	StageDisplay* stageDisplay = new StageDisplay(*sIt, &window, WIN_WIDTH/2, WIN_HEIGHT/2);
	//std::cout << stageDisplay->GetStageName() << std::endl; //For Debug Purposes

	//Start Game Loop
	//while (gameRunning) //Use This for OpenGL Rendering
	while(window.isOpen())
	{
		//Update
		player->Update();
		controller->Update();

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
			//Check Key Input
			else if (event.type == sf::Event::KeyPressed)
			{
				player->GetPlayerControllerPress(&event);
			}
			//Check Key Release
			else if (event.type == sf::Event::KeyReleased)
			{
				player->GetPlayerControllerRelease(&event);
			}
		}

		//Clear Window
		window.clear();

		//Draw
		window.draw(stageDisplay->GetStageWindowDisplay());
		window.draw(player->GetWindowSpriteDisplay());
		window.draw(player->GetWindowPlaneDisplay());

		//Display Window
		window.display();
	}

	return 0;
}