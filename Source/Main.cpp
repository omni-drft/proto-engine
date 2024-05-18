#include "ProtoApp.h"

int main()
{
	ProtoApp* App{ new ProtoApp("Test", 800, 600) };
	App->run();
	delete App;
	return 0;
}