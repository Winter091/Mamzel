#include "SandboxApp.h"

int main()
{	
	SandboxApp* app = new SandboxApp;
	app->Run();
	delete app;
}