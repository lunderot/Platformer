#include "Application.h"

Application::Application(Vec2i screenSize, std::string title) : System(screenSize, title)
{
	assetHandler = new AssetHandler(GetRenderer(), "assets/textures/");

	entityHandler = new EntityHandler();
	entityHandler->Add(new Player(assetHandler->GetTexture("tiles/boxAlt.png"), 35, Vec2f(300, 100), Vec2f(100, 0), Vec2f(0, 300)));

	scriptHandler = new ScriptHandler("assets/scripts/", entityHandler, assetHandler);
	scriptHandler->AddFile("test.lua");
}


Application::~Application()
{
	delete assetHandler;
	delete entityHandler;
	delete scriptHandler;
}

void Application::HandleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONUP:
	case SDL_MOUSEBUTTONDOWN:
		scriptHandler->TriggerEvent(event.button);
		break;
	case SDL_MOUSEMOTION:
		scriptHandler->TriggerEvent(event.motion);
		break;
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		scriptHandler->TriggerEvent(event.key);
		break;
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