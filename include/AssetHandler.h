#pragma once

#include <string>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

class AssetHandler
{
private:
	SDL_Renderer* renderer;
	std::map<std::string, SDL_Texture*> textures;
public:
	AssetHandler(SDL_Renderer* renderer);
	~AssetHandler();

	SDL_Texture* GetTexture(std::string filename);
	std::string GetFilenameFromPointer(SDL_Texture* texture);
private:
	SDL_Texture* LoadTexture(std::string filename);
};

