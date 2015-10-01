#include <iostream>
#include <SDL.h>

#include "Application.h"

int main(int argc, char* argv[])
{
	try
	{
		Application app(glm::ivec2(1280, 720), "Platformer", argc, argv);
		app.Run();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "SDL error: " << SDL_GetError() << std::endl;
	}
	return 0;
}