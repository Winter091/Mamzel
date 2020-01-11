#include "SandboxApp.h"
#include "MinecraftScene.h"

int main()
{	
	auto app = new SandboxApp;
	app->Run();
	delete app;
}