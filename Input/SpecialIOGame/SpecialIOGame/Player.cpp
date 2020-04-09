#include "Player.h"

Player::Player(int aPosX, int aPosY, int aRot, CType aType, sf::Texture* aTexture,
	Controller* aController)
	: Character::Character(aPosX, aPosY, aRot, aType, aTexture), controller(aController)
{
	planeValues[0] = 80.0f;
	planeValues[1] = 20.0f;

	SetSpriteProperties();
	plane = SetPlaneDisplay(&position, aRot, planeValues);
}

Player::~Player()
{

}

void Player::Update()
{
	Character::Update();
	GetControllerJsonValues();
	plane.setPosition(position);
	plane.setRotation(rotation);
}

void Player::SetBoundaries(sf::RenderWindow* aWindow, int beginX, int beginY)
{
	bounds[0] = beginX;
	bounds[1] = beginY;
	bounds[2] = aWindow->getSize().x;
	bounds[3] = aWindow->getSize().y;
}

void Player::SetSpriteProperties()
{
	sprite.setColor(sf::Color(253, 0, 45, 255));
}

void Player::GetPlayerControllerPress(sf::Event* event)
{
	//std::cout << event->key.code << std::endl; //Debug
	switch (event->key.code)
	{
		case 0: //The 'A'-key, Move Left
			if (position.x > (float)bounds[0])
			{
				velocity.x = -speed.x;
			}
			else
			{
				velocity.x = 0;
			}
			break;

		case 3: //The 'D'-key, Move Right
			if (position.x < (float)bounds[2])
			{
				velocity.x = speed.x;
			}
			else
			{
				velocity.x = 0;
			}
			break;

		case 18 : //The 'S'-key, Move Backwards
			if (position.y < (float)bounds[3])
			{
				velocity.y = speed.y;
			}
			else
			{
				velocity.y = 0;
			}
			break;

		case 22: //The 'W'-key, Move Forwards
			if (position.y > (float)bounds[1])
			{
				velocity.y = -speed.y;
			}
			else
			{
				velocity.y = 0;
			}
			break;
	}

	rotation = (int)(atan2f(velocity.y, velocity.x) * (180 / M_PI));
}

void Player::GetPlayerControllerRelease(sf::Event* event)
{
	switch (event->key.code)
	{
	case 0: //The 'A'-key, Move Left
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { velocity.x = 0; }
		break;
	case 3: //The 'D'-key, Move Right
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { velocity.x = 0; }
		break;
	case 18: //The 'S'-key, Move Backwards
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { velocity.y = 0; }
		break;
	case 22: //The 'W'-key, Move Forwards
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { velocity.y = 0; }
		break;
	}
}

void Player::GetControllerJsonValues()
{
	JsonValuesCheckHorizontal(controller, 5, controller->GyZ_VALUE_TRIGGER);
	JsonValuesCheckVertical(controller, 4, controller->GyY_VALUE_TRIGGER);
}

void Player::CheckBoundaries(sf::Vector2f* aPos, sf::Vector2i* aBound)
{
}

void Player::JsonValuesCheckHorizontal(Controller* aController, int valueIt, int aValue)
{
	if (aController->GetValues().at(aController->GetValueNames().at(valueIt)) > aValue)
	{
		if (position.x > (float)bounds[0])
		{
			velocity.x = -speed.x;
		}
		else
		{
			velocity.x = 0;
		}
	}
	else if (aController->GetValues().at(aController->GetValueNames().at(valueIt)) < -aValue)
	{
		if (position.x < (float)bounds[2])
		{
			velocity.x = speed.x;
		}
		else
		{
			velocity.x = 0;
		}
	}
	else
	{
		velocity.x = 0;
	}

	if (aController->GetValues().at(aController->GetValueNames().at(valueIt)) > aValue ||
		aController->GetValues().at(aController->GetValueNames().at(valueIt)) < -aValue)
	{
		rotation = (int)(atan2f(velocity.y, velocity.x) * (180 / M_PI));
		std::cout << aController->GetValueNames().at(valueIt) << ": " <<
			aController->GetValues().at(aController->GetValueNames().at(valueIt)) << std::endl;
	}
}

void Player::JsonValuesCheckVertical(Controller* aController, int valueIt, int aValue)
{
	if (aController->GetValues().at(aController->GetValueNames().at(valueIt)) > aValue)
	{
		if (position.y > (float)bounds[1])
		{
			velocity.y = -speed.y;
		}
		else
		{
			velocity.y = 0;
		}
	}
	else if (aController->GetValues().at(aController->GetValueNames().at(valueIt)) < -aValue)
	{
		if (position.y < (float)bounds[3])
		{
			velocity.y = speed.y;
		}
		else
		{
			velocity.y = 0;
		}
	}
	else
	{
		velocity.y = 0;
	}

	if (aController->GetValues().at(aController->GetValueNames().at(valueIt)) > aValue ||
	    aController->GetValues().at(aController->GetValueNames().at(valueIt)) < -aValue)
	{
		rotation = (int)(atan2f(velocity.y, velocity.x) * (180 / M_PI));
		std::cout << aController->GetValueNames().at(valueIt) << ": " <<
		aController->GetValues().at(aController->GetValueNames().at(valueIt)) << std::endl;
	}
}

sf::ConvexShape Player::SetPlaneDisplay(sf::Vector2f* aPos, int aRot, float aPlane[])
{
	sf::ConvexShape shape;
	//sf::ConvexShape* shapePntr = &shape;

	shape.setPointCount(4);
	shape.setOrigin(*aPos);

	//Draw Shape
	shape.setPoint(0, sf::Vector2f(aPos->x + (aPlane[0] / 2), aPos->y + (aPlane[0] / 2)));
	shape.setPoint(1, sf::Vector2f(aPos->x - (aPlane[1] / 2), aPos->y + (aPlane[1] / 2)));
	shape.setPoint(2, sf::Vector2f(aPos->x - (aPlane[1] / 2), aPos->y - (aPlane[1] / 2)));
	shape.setPoint(3, sf::Vector2f(aPos->x + (aPlane[0] / 2), aPos->y - (aPlane[0] / 2)));

	//Define Shape Properties
	shape.setPosition(*aPos);
	shape.setFillColor(sf::Color(253, 0, 65, 115));
	shape.setRotation((float) aRot);

	return shape;
}

sf::ConvexShape Player::GetWindowPlaneDisplay()
{
	return plane;
}
