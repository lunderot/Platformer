#include "Application.h"

Application::Application(Vec2i screenSize, std::string title) : System(screenSize, title)
{
	assetHandler = new AssetHandler(GetRenderer(), "assets/textures/");

	entityHandler = new EntityHandler();
	entityHandler->Add(new Player(assetHandler->GetTexture("tiles/castleCliffLeftAlt.png"), Vec2f(70, 70), Vec2f(0, 0), Vec2f(10, 10), Vec2f(3, 3)));
	entityHandler->Add(new Player(assetHandler->GetTexture("tiles/box.png"), Vec2f(70, 70), Vec2f(120, 120)));
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