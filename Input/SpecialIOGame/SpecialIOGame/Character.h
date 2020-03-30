#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Character
{
	public:
		enum CType
		{
			MARIO, LUIGI, PEACH, YOSHI, TOAD,
			BOWSER, DONKEY_KONG, KOOPA_TROOPA, WARIO,
			DAISY, DRY_BONES, WALUIGI, SHY_GUY, ROB
		};

		Character(int aPosX, int aPosY, int aRot, CType* aType, sf::Texture aTexture);
		~Character();

		void SetCharacterSprite(sf::Texture* aTexture);

		std::string GetCharacterType();

	protected:
		CType* currentCharacter;
		sf::Sprite sprite;
		int posX, posY, rotation;
};