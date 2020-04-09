#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include <string>
#include <iostream>
#include <sstream>

class Controller
{
	public:
		const int AcX_VALUE_TRIGGER = 1;
		const int AcY_VALUE_TRIGGER = 1;
		const int AcZ_VALUE_TRIGGER = 1;
		const int GyX_VALUE_TRIGGER = 120;
		const int GyY_VALUE_TRIGGER = 120;
		const int GyZ_VALUE_TRIGGER = 120;

		Controller(std::string* anUrl, std::string* aPath, sf::RenderWindow* aWindow);
		~Controller();

		void Update();

		std::vector<std::string> AddToValueNames(std::vector<std::string>* aList, std::string aName);
		std::map<std::string, int> AddToValueTriggers(std::map<std::string, int>* aList,
			std::map<std::string, int>::iterator anIt, int amount);

		nlohmann::json GetResponseInObject(sf::Http::Response* aResponse, nlohmann::json* val);
		nlohmann::json GetValues();

		std::vector<std::string> GetValueNames();

	private:
		sf::Http http;
		sf::Http::Request request;
		sf::Http::Response response;

		sf::RenderWindow* window;
		nlohmann::json values;

		std::vector<std::string> valueNames;
		//std::map<std::string, int> valueTriggers;
};

