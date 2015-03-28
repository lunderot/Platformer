#include <iostream>
#include <SDL.h>

#include "Application.h"

int main(int argc, char* argv[])
{
	try
	{
		Application app(Vec2i(1280, 720), "Platformer");
		app.Run();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "SDL error: " << SDL_GetError() << std::endl;
	}
	return 0;
}