#pragma once
#include <string>
#include <fstream>
#include "EntityHandler.h"

class MapHandler
{
private:
	float tilesize;
public:
	MapHandler(std::string filename, EntityHandler* entityHandler, AssetHandler* assetHandler);
	~MapHandler();
};

