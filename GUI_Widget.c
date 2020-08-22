#include "GUI_Widget.h"

void destroyWidget(GUI_Widget* widget)
{
	if (widget)
		widget->WidgetDestroy(widget);
}
