#pragma once
#include <map>
#include "SFMLBase.h"
#include "Types.h"


class TextureManager
{
	static TextureManager* pTexMan;
	TextureManager();
public:
	static TextureManager* Get();
	
	~TextureManager();

	void addTexture(TextureID, const char*);
	const sf::Texture& getTexture(TextureID);

private:
	std::map<TextureID, sf::Texture> textMap;
};

