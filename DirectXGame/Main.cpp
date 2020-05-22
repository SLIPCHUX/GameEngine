#include "AppWindow.h"
	

int main()
{
	AppWindow app;
	if (app.InitWindow())
	{
		while (app.isRunning())
		{
			app.BroadCast();
		}
	}

	return 0;
}