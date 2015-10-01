#include "Application.h"

Application::Application(glm::ivec2 screenSize, std::string title, int argc, char* argv[]) : System(screenSize, title)
{
	assetHandler = new AssetHandler(GetRenderer());
	entityHandler = new EntityHandler();

	entityHandler->Add(new Camera(glm::vec2(static_cast<float>(screenSize.x), static_cast<float>(screenSize.y)), glm::vec2(0.0f, 0.0f)));

	scriptHandler = new ScriptHandler(entityHandler, assetHandler);
	std::string mapFile("assets/maps/editor.map");
	if (argc == 2)
	{
		mapFile = std::string(argv[1]);
	}
	mapHandler = new MapHandler(mapFile, entityHandler, assetHandler, scriptHandler);
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