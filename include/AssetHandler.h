#pragma once

#include <string>
#include <map>

#include <SDL.h>
#include <SDL_image.h>

class AssetHandler
{
private:
	SDL_Renderer* renderer;
	std::string path;
	std::map<std::string, SDL_Texture*> textures;
public:
	AssetHandler(SDL_Renderer* renderer, std::string path);
	~AssetHandler();

	SDL_Texture* GetTexture(std::string filename);
private:
	SDL_Texture* LoadTexture(std::string filename);
};

