#include "TextureManager.h"

TextureManager* TextureManager::pTexMan = nullptr;

TextureManager::TextureManager() {
}

TextureManager::~TextureManager() {
}

TextureManager* TextureManager::Get()
{
	if (!pTexMan)
		pTexMan = new TextureManager();
	return pTexMan;
}

void TextureManager::addTexture(TextureID id, const char* filePath) {
	if (textMap.find(id) == textMap.end()) {
		textMap[id] = sf::Texture();
		textMap[id].loadFromFile(filePath);
	}
	else {
		throw "ID already assigned a texture";
	}
}

const sf::Texture& TextureManager::getTexture(TextureID id) {
	if (textMap.find(id) == textMap.end()) {
		throw "No texture at this ID";
	}
	else {
		return textMap[id];
	}
}