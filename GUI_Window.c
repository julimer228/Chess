#include "GUI_Window.h"

void GUI_DestroyWindow(GUI_Window* window)
{
	//jeœli okno istnia³o, to usuñ okno
	if (window)
	window->WindowDestroy(window);
}
