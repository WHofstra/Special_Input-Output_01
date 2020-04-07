#include "Character.h"

Character::Character(int aPosX, int aPosY, int aRot, CType aType, sf::Texture* aTexture)
	: currentCharacter(&aType)
{
	position = sf::Vector2f(aPosX, aPosY);
	velocity = sf::Vector2f(0, 0);
	speed = sf::Vector2f(0.05f, 0.075f);

	sprite = SetCharacterSprite(aTexture);
	sprite.setPosition((float)position.x, (float)position.y);

	SetRotation(aRot);
}

Character::~Character()
{

}

void Character::Update()
{
	position += velocity;
	sprite.setPosition(position);
	sprite.setRotation(rotation);
}

sf::Sprite Character::SetCharacterSprite(sf::Texture* aTexture)
{
	sf::Sprite* aSprite = &sprite;
	aSprite->setTexture(*aTexture);
	aSprite->setTextureRect(sf::IntRect(0, 0, 8, 8));
	aSprite->setOrigin(ceil(aSprite->getLocalBounds().width / 2), ceil(aSprite->getLocalBounds().height / 2));
	return *aSprite;
}

sf::Sprite Character::GetWindowSpriteDisplay()
{
	return sprite;
}

void Character::SetVelocity(int velX, int velY)
{
	velocity.x = velX;
	velocity.y = velY;
}

void Character::SetRotation(int aRot)
{
	rotation = aRot;
	sprite.setRotation((float)aRot);
}
