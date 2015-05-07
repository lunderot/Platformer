#include "AssetHandler.h"

AssetHandler::AssetHandler(SDL_Renderer* renderer)
{
	this->renderer = renderer;
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

std::string AssetHandler::GetFilenameFromPointer(SDL_Texture* texture)
{
	for (std::map<std::string, SDL_Texture*>::iterator i = textures.begin(); i != textures.end(); ++i)
	{
		if ((*i).second == texture)
		{
			return (*i).first;
		}
	}
}

SDL_Texture* AssetHandler::LoadTexture(std::string filename)
{
	SDL_Texture* returnTexture;
	SDL_Surface* tempSurface = IMG_Load(filename.c_str());

	if (!tempSurface)
	{
		throw std::runtime_error("Failed to load texture: " + filename);
	}
	returnTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	if (!returnTexture)
	{
		throw std::runtime_error("Failed to create texture from surface");
	}
	SDL_FreeSurface(tempSurface);

	return returnTexture;
}
