#include "Application.h"

Application::Application(Vec2i screenSize, std::string title, int argc, char* argv[]) : System(screenSize, title)
{
	editorMode = (argc == 2 && std::string(argv[1]) == "editor");
	assetHandler = new AssetHandler(GetRenderer());
	entityHandler = new EntityHandler();

	entityHandler->Add(new Camera(Vec2f(static_cast<float>(screenSize.x), static_cast<float>(screenSize.y)), Vec2f(0.0f, 0.0f)));

	scriptHandler = new ScriptHandler(entityHandler, assetHandler);
	if (editorMode)
	{
		scriptHandler->AddFile("assets/scripts/editor/camera.lua");
		scriptHandler->AddFile("assets/scripts/editor/editor.lua");
	}
	else
	{
		entityHandler->Add(new Player(assetHandler->GetTexture("assets/textures/player.png"), 35, Vec2f(300, -100), Vec2f(100, 0), Vec2f(0, 300)));

		scriptHandler->AddFile("assets/scripts/game/camera.lua");
		scriptHandler->AddFile("assets/scripts/game/controls.lua");

		if (argc == 2)
		{
			mapHandler = new MapHandler(std::string(argv[1]), entityHandler, assetHandler, scriptHandler);
		}
	}
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