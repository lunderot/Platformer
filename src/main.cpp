#include <iostream>
#include <SDL.h>

#include "System.h"

int main(int argc, char* argv[])
{
	try
	{
		System system(Vec2i(1280, 720));
		system.Run();
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		std::cout << "SDL error: " << SDL_GetError() << std::endl;
	}
	return 0;
}