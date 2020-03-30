#include "Player.h"

Player::Player(int aPosX, int aPosY, int aRot, CType aType, sf::Texture* aTexture)
	: Character::Character(aPosX, aPosY, aRot, aType, aTexture)
{
	//playerControls = GetPlayerControls(playerControls);
	//controlIt = playerControls.begin();
	SetSpriteProperties();
}

Player::~Player()
{

}

void Player::SetSpriteProperties()
{
	sprite.setColor(sf::Color(253, 0, 45, 255));
}

void Player::GetPlayerController(sf::Event* event)
{
	if (event->type == sf::Event::KeyPressed)
	{

	}
}

void Player::SetPlayerVelocity(int velX, int velY)
{

}

void Player::SetPlayerRotation(int anAngle)
{

}

std::list<sf::Keyboard::Key> Player::GetPlayerControls(std::list<sf::Keyboard::Key> aList)
{
	aList.push_back(sf::Keyboard::W); //Move Upwards
	aList.push_back(sf::Keyboard::A); //Move Downwards
	aList.push_back(sf::Keyboard::D); //Move Right
	aList.push_back(sf::Keyboard::S); //Move Left
	aList.push_back(sf::Keyboard::E); //Turn Clockwise
	aList.push_back(sf::Keyboard::Q); //Turn Counter-clockwise

	return aList;
}
