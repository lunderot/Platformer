#include "Application.h"

Application::Application(Vec2i screenSize, std::string title) : System(screenSize, title)
{
	assetHandler = new AssetHandler(GetRenderer());
	entityHandler = new EntityHandler();

	entityHandler->Add(new Player(assetHandler->GetTexture("assets/textures/tiles/boxAlt.png"), 35, Vec2f(300, 100), Vec2f(100, 0), Vec2f(0, 300)));
	entityHandler->Add(new Camera(Vec2f(static_cast<float>(screenSize.x), static_cast<float>(screenSize.y)), Vec2f(0.0f, 0.0f)));

	scriptHandler = new ScriptHandler(entityHandler, assetHandler);
	scriptHandler->AddFile("assets/scripts/test.lua");

	mapHandler = new MapHandler("assets/maps/testmap.map", entityHandler, assetHandler);
}


Application::~Application()
{
	delete assetHandler;
	delete entityHandler;
	delete scriptHandler;
	delete mapHandler;
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
	scriptHandler->TriggerEvent("update", deltaTime);
}

void Application::Render()
{
	entityHandler->Render(GetRenderer());
}