#include "AssetHandler.h"

AssetHandler::AssetHandler(SDL_Renderer* renderer, std::string path)
{
	this->renderer = renderer;
	this->path = path;
}

AssetHandler::~AssetHandler()
{
	for (std::map<std::string, SDL_Texture*>::iterator i = textures.begin(); i != textures.end(); ++i)
	{
		SDL_DestroyTexture(i->second);
	}
}

SDL_Texture* AssetHandler::GetTexture(std::string filename)
{
	SDL_Texture* returnTexture;
	if (textures.find(filename) != textures.end()) //Texture is found
	{
		returnTexture = textures[filename];
	}
	else
	{
		returnTexture = LoadTexture(filename);
		textures[filename] = returnTexture;
	}
	return returnTexture;
}

SDL_Texture* AssetHandler::LoadTexture(std::string filename)
{
	SDL_Texture* returnTexture;
	std::string tempFilename = path + filename;
	SDL_Surface* tempSurface = SDL_LoadBMP(tempFilename.c_str());

	if (!tempSurface)
	{
		throw std::runtime_error("Failed to load texture: " + tempFilename);
	}
	returnTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!returnTexture)
	{
		throw std::runtime_error("Failed to create texture from surface");
	}
	SDL_FreeSurface(tempSurface);

	return returnTexture;
}
