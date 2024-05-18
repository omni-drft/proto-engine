#include "ProtoApp.h"

int main()
{
	ProtoApp* App{ new ProtoApp("Test", 800, 600) };
	App->loop();
	delete App;
	return 0;
}