#include "GUI_Button.h"
#include <stdio.h>
#include <stdlib.h>

GUI_Widget* GUI_CreateButton(SDL_Renderer* renderer, const char* imagepath, SDL_Rect location, void(*ButtonAction)(void))
{
	// rezerwujemy pamiêæ dla wid¿etu
	GUI_Widget* widget = (GUI_Widget*)malloc(sizeof(GUI_Widget));
	if (widget == NULL)
		return NULL;

	//rezerwujemy pamiêæ dla danych zwi¹zanych z przyciskiem
	GUI_Button* button = (GUI_Button*)malloc(sizeof(GUI_Button));
	if (button == NULL)
	{
		free(widget);
		return NULL;
	}

	//£adujemy grafikê dla przycisku
	SDL_Surface* surface = SDL_LoadBMP(imagepath);
	if (surface == NULL) {
		free(widget);
		free(button);
		return NULL;
	}

	//Tworzymy teksturê
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		free(widget);
		free(button);
		SDL_FreeSurface(surface);
		return NULL;
	}

	//je¿eli uda³o siê stworzyæ teksturê, to SDL_surface nie jest ju¿ potrzebna
	SDL_FreeSurface(surface);

	// ustawiamy pola przycisku
	button->texture = texture;
	button->location = location;
	button->ButtonAction = ButtonAction;

	//ustawiamy pola wid¿etu
	widget->WidgetDestroy = GUI_DestroyButton;
	widget->WidgetDraw = GUI_DrawButton;
	widget->WidgetHandleEvent = GUI_HandleButtonEvent;
	widget->gui_widget_data = button;
	return widget;
}

void GUI_DestroyButton(GUI_Widget* widget)
{
	GUI_Button* button = (GUI_Button*)widget->gui_widget_data;
	SDL_DestroyTexture(button->texture);
	free(button);
	free(widget);
}

void GUI_HandleButtonEvent(GUI_Widget* widget, SDL_Event* event)
{
	//je¿eli klikniêto w przycisk
	if (event->type == SDL_MOUSEBUTTONUP) 
	{
		GUI_Button* button = (GUI_Button*)widget->gui_widget_data;
		
		//Tworzymy punkt, o wspó³rzêdnych w jakich wyst¹pi³o klikniêcie
		SDL_Point point = { .x = event->button.x,.y = event->button.y };

		//sprawdzamy czy klikniêto w obszar w jakim znajduje siê przycisk
		if (SDL_PointInRect(&point, &button->location))
		{
			//jeœli tak wywo³amy odpowiedni¹ funkcjê
			button->ButtonAction();
		}
	}
}

void GUI_DrawButton(GUI_Widget* widget, SDL_Renderer* render)
{
	GUI_Button* button = (GUI_Button*)widget->gui_widget_data;
	SDL_RenderCopy(render, button->texture, NULL, &button->location);
}