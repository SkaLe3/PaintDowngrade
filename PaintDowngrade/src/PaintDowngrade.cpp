#include <Engine.h>
#include <Engine/Core/EntryPoint.h>
#include <iostream>

#include "AppLayer.h"




class PaintDowngradeApp : public  Engine::Application
{
public:
	PaintDowngradeApp() : Application("Paint Downgrade")
	{
		PushLayer(new AppLayer);
	}
	~PaintDowngradeApp()
	{

	}

private:



};

Engine::Application* Engine::CreateApplication()
{
	return new PaintDowngradeApp();
}