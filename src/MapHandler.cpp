#include "MapHandler.h"


MapHandler::MapHandler(std::string filename, EntityHandler* entityHandler, AssetHandler* assetHandler, ScriptHandler* scriptHandler)
{
	tilesize = 70.0f;

	std::fstream mapFile(filename);
	if (mapFile.good())
	{
		while (!mapFile.eof())
		{
			char command;
			mapFile >> command;
			switch (command)
			{
				case 'i': //Map info
				{
					mapFile >> tilesize;
					break;
				}
				case 'l': //Add collision line
				{
					glm::vec2 point1;
					glm::vec2 point2;

					mapFile >> point1.x;
					mapFile >> point1.y;
					mapFile >> point2.x;
					mapFile >> point2.y;
					entityHandler->AddCollisionLine(new LineSegment(point1, point2));
					break;
				}
				case 'e': //Add entity
				{
					int readType;
					EntityType type;
					std::string textureFilename;
					float radius;

					mapFile >> readType;
					type = static_cast<EntityType>(readType);
					mapFile >> textureFilename;
					mapFile >> radius;

					entityHandler->Add(type, textureFilename, radius, assetHandler);
					break;
				}
				case 't': //Add tile
				{
					std::string textureFilename;
					glm::vec2 position;
					mapFile >> textureFilename;
					mapFile >> position.x;
					mapFile >> position.y;

					position = position;

					entityHandler->Add(new Tile(assetHandler->GetTexture(textureFilename), tilesize, position));
					break;
				}
				case 's': //Add script
				{
					std::string scriptFilename;
					mapFile >> scriptFilename;
					scriptHandler->AddFile(scriptFilename);
					break;
				}
				default:
				{
					std::string tempString;
					std::getline(mapFile, tempString);
					break;
				}
			}
		}
	}
	else
	{
		throw std::runtime_error("File error: " + filename);
	}
	mapFile.close();
}


MapHandler::~MapHandler()
{
}
