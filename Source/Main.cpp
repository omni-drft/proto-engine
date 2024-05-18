#include "ProtoApp.h"

int main()
{
	// Creating ProtoApp object
	ProtoApp* App{ new ProtoApp("Test", 800, 600) };
	// Starting up the application
	App->run();
	// Destructing the dynamicly allocated App object
	delete App;
	return 0;
}