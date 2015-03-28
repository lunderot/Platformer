#include "Application.h"

Application::Application(Vec2i screenSize, std::string title) : System(screenSize, title)
{
	assetHandler = new AssetHandler(GetRenderer(), "assets/textures/");

	entityHandler = new EntityHandler();
	entityHandler->Add(new Player(assetHandler->GetTexture("tiles/box.png"), Vec2f(70, 70), Vec2f(10, 20)));
	entityHandler->Add(new Player(assetHandler->GetTexture("test.bmp"), Vec2f(64, 64), Vec2f(52, 20)));
}


Application::~Application()
{
	delete assetHandler;
	delete entityHandler;
}

void Application::HandleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	default:
		break;
	}
}

void Application::Update(float deltaTime)
{
	entityHandler->Update(deltaTime);
}

void Application::Render()
{
	entityHandler->Render(GetRenderer());
}