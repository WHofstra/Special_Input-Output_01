#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Controller
{
	public:
		Controller(std::string* anUrl, std::string* aPath, sf::RenderWindow* aWindow);
		~Controller();

		void Update();

	private:
		sf::Http http;
		sf::Http::Request request;
		sf::Http::Response response;
};

