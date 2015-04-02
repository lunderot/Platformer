#include "Application.h"

Application::Application(Vec2i screenSize, std::string title) : System(screenSize, title)
{
	assetHandler = new AssetHandler(GetRenderer(), "assets/textures/");

	entityHandler = new EntityHandler();
	entityHandler->Add(new Player(assetHandler->GetTexture("tiles/castleCliffLeftAlt.png"), 35, Vec2f(300, 100), Vec2f(100, 0), Vec2f(0, 300)));
	entityHandler->Add(new Player(assetHandler->GetTexture("tiles/box.png"), 35, Vec2f(170, 120), Vec2f(30, 300) ));

	ScriptHandler::Init("assets/scripts/", entityHandler);
	ScriptHandler::AddFile("test.lua");
	ScriptHandler::TriggerEvent("test", 0);
}


Application::~Application()
{
	delete assetHandler;
	delete entityHandler;
	ScriptHandler::Close();
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