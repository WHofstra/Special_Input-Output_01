#include "Character.h"

Character::Character(int aPosX, int aPosY, int aRot, CType* aType, sf::Texture aTexture)
	:currentCharacter(aType)
{

}

Character::~Character()
{

}

void Character::SetCharacterSprite(sf::Texture* aTexture)
{
	sf::Sprite aSprite(*aTexture);
}

std::string Character::GetCharacterType()
{
	switch (*currentCharacter)
	{
		case 0:  return "Mario";
		case 1:  return "Luigi";
		case 2:  return "Peach";
		case 3:  return "Yoshi";
		case 4:  return "Toad";
		case 5:  return "Bowser";
		case 6:  return "Donkey Kong";
		case 7:  return "Koopa Troopa";
		case 8:  return "Wario";
		case 9:  return "Daisy";
		case 10: return "Dry Bones";
		case 11: return "Waluigi";
		case 12: return "Shy Guy";
		case 13: return "R.O.B.";
	}
	return "[TBA]";
}
