#include "GUI_Window.h"

void GUI_DestroyWindow(GUI_Window* window)
{
	//je�li okno istnia�o, to usu� okno
	if (window)
	window->WindowDestroy(window);
}
