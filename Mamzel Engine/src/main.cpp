#include "SandboxApp.h"
#include "MinecraftScene.h"

int main()
{	
	auto app = new MinecraftScene;
	app->Run();
	delete app;
}