#include "Application.h"

Application::Application(Vec2i screenSize, std::string title) : System(screenSize, title)
{
	assetHandler = new AssetHandler(GetRenderer(), "assets/textures/");
	player = new Player(assetHandler->GetTexture("test.bmp"), Vec2f(32, 32), Vec2f(10, 20), Vec2f(0, -20), Vec2f(0, 10));
}


Application::~Application()
{
	delete assetHandler;
	delete player;
}

void Application::HandleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		player->SetPosition(Vec2f(event.button.x, event.button.y));
		break;
	default:
		break;
	}
}

void Application::Update(float deltaTime)
{
	player->Update(deltaTime);
}

void Application::Render()
{
	player->Render(GetRenderer());
}