#include "Player.h"

Player::Player(int aPosX, int aPosY, int aRot, CType aType, sf::Texture* aTexture)
	: Character::Character(aPosX, aPosY, aRot, aType, aTexture)
{
	planeValues[0] = 80.0f;
	planeValues[1] = 20.0f;

	SetSpriteProperties();
	plane = SetPlaneDisplay(&position, aRot, planeValues);

	/* Debug
	std::cout << "Color: { " << (int)plane.getFillColor().r << ", " << (int)plane.getFillColor().g << ", "
		      << (int)plane.getFillColor().b << ", " << (int)plane.getFillColor().a << " }" << std::endl;//*/
}

Player::~Player()
{

}

void Player::Update()
{
	Character::Update();
	plane.setPosition(position);
	plane.setRotation(rotation);
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
			//velocity.x = (cosf(rotation) * speed.x) + (sinf(rotation) * speed.y);
			velocity.x = -speed.x;
			rotation -= 5;
			break;
		case 3: //The 'D'-key, Move Right
			velocity.x = speed.x;
			rotation += 5;
			break;
		case 8: //The 'I'-key, Narrow Far Plane-of-view

			break;
		case 10: //The 'K'-key, Widen Near Plane-of-view

			break;
		case 11: //The 'L'-key, Narrow Near Plane-of-view

			break;
		case 14: //The 'O'-key, Widen Far Plane-of-view

			break;
		case 18 : //The 'S'-key, Move Backwards
			velocity.y = speed.y;
			break;
		case 22: //The 'W'-key, Move Forwards
			velocity.y = -speed.y;
			break;
	}

	if (rotation < 0)
	{
		rotation += 360;
	}
}

void Player::GetPlayerControllerRelease(sf::Event* event)
{
	switch (event->key.code)
	{
	case 0: //The 'A'-key, Move Left
		velocity.x = 0;
		break;
	case 3: //The 'D'-key, Move Right
		velocity.x = 0;
		break;
	case 18: //The 'S'-key, Move Backwards
		velocity.y = 0;
		break;
	case 22: //The 'W'-key, Move Forwards
		velocity.y = 0;
		break;
	}
}

sf::ConvexShape Player::SetPlaneDisplay(sf::Vector2f* aPos, int aRot, float aPlane[])
{
	sf::ConvexShape shape;
	//sf::ConvexShape* shapePntr = &shape;

	shape.setPointCount(4);
	shape.setOrigin(*aPos);

	//Draw Shape
	shape.setPoint(0, sf::Vector2f(aPos->x + (aPlane[1] / 2), aPos->y + (aPlane[1] / 2)));
	shape.setPoint(1, sf::Vector2f(aPos->x - (aPlane[0] / 2), aPos->y + (aPlane[0] / 2)));
	shape.setPoint(2, sf::Vector2f(aPos->x - (aPlane[0] / 2), aPos->y - (aPlane[0] / 2)));
	shape.setPoint(3, sf::Vector2f(aPos->x + (aPlane[1] / 2), aPos->y - (aPlane[1] / 2)));

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
