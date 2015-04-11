#include "MapHandler.h"


MapHandler::MapHandler(std::string filename, EntityHandler* entityHandler, AssetHandler* assetHandler)
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
				case 'i':
				{
					mapFile >> tilesize;
					break;
				}
				case 'l': //Add collision line
				{
					Vec2f point1;
					Vec2f point2;

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
					Vec2f position;
					mapFile >> textureFilename;
					mapFile >> position.x;
					mapFile >> position.y;

					position = position * tilesize;

					entityHandler->Add(new Tile(assetHandler->GetTexture(textureFilename), tilesize, position));
					break;
				}
				default:
				{
					break;
				}
			}
		}
	}
	mapFile.close();
}


MapHandler::~MapHandler()
{
}
