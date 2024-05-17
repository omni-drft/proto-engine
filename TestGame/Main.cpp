#include "ProtoEngine.hpp"

int main()
{
	ProtoEngine::ProtoApp Application;
	Application.init();
	Application.mainLoop();
	Application.cleanup();
	return 0;
}