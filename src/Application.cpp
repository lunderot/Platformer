#include "Application.h"

Application::Application(Vec2i screenSize, std::string title) : System(screenSize, title)
{
	this->assetHandler = new AssetHandler(GetRenderer(), "assets/textures/");
}


Application::~Application()
{
	delete assetHandler;
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

}

void Application::Render()
{
	SDL_Rect dest = { 0, 0, 0, 0 };
	SDL_QueryTexture(assetHandler->GetTexture("test.bmp"), nullptr, nullptr, &dest.w, &dest.h);
	SDL_RenderCopy(GetRenderer(), assetHandler->GetTexture("test.bmp"), nullptr, &dest);
}