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

		Character(int aPosX, int aPosY, int aRot, CType aType, sf::Texture* aTexture);
		~Character();

		virtual void Update();

		sf::Sprite SetCharacterSprite(sf::Texture* aTexture);
		sf::Sprite GetWindowSpriteDisplay();

		std::string GetCharacterType();
		float GetCharacterSpeed();

		void SetCharacterSpeed(CType* aType);
		void SetVelocity(int velX, int velY);
		void SetRotation(int aRot);

	protected:
		CType* currentCharacter;
		sf::Sprite sprite;

		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Vector2f speed;
		int rotation;
};