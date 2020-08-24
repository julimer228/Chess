#include "GUI_MenuWindow.h"
//Warning wy�wietla si� z powodu s�owa STATIC -> sprawdzi� to!!!
static void GUI_MenuWindowExit()
{
	//tworzymy zdarzenie zamykaj�ce okno
	SDL_Event event = { .type = SDL_QUIT };
	//wywo�ujemy zdarzenie
	SDL_PushEvent(&event);
}

static void GUI_MenuWindowPlay() 
{
	GUI_UserEventPush(USER_EVENT_PLAY, 0, NULL);
}
static void GUI_MenuWindowHelp()
{
	GUI_UserEventPush(USER_EVENT_HELP, 0, NULL);
}

bool GUI_MenuWindowButtons(GUI_MenuWindow* menu)
{
	//Ustawiamy wysoko�� i szeroko�� ka�dego przycisku
	SDL_Rect Play = { .x = 341,.y = 225,.h =BUTTON_H*1.2,.w = BUTTON_W }; //przycisk nowej gry
	SDL_Rect Help = { .x = 341, .y = 325, .h = BUTTON_H*1.2,.w = BUTTON_W }; //przycisk pomocy
	SDL_Rect Exit = { .x = 341,.y = 425,.h =BUTTON_H*1.2,.w =BUTTON_W}; //przycisk zamkni�cia programu

	// create
	menu->widgettab[0] = GUI_CreateButton(menu->renderer, "./Graphics/play_button.bmp", Play, GUI_MenuWindowPlay);
	//Wymaga narysowania nowego przycisku z napisem [HELP]
	menu->widgettab[1] = GUI_CreateButton(menu->renderer, "./Graphics/play_button.bmp", Help, GUI_MenuWindowHelp);
	menu->widgettab[2] = GUI_CreateButton(menu->renderer, "./Graphics/play_button.bmp", Exit, GUI_MenuWindowExit);

	// sprawdzamy, czy przyciski zosta�y poprawnie utworzone
	for (int i = 0; i <3; i++)
	{
		//je�eli kt�rykolwiek z przycisk�w nie zosta� utworzony zwracamy false
		if (menu->widgettab[i] == NULL)
			return false;
	}

	return true;
}

GUI_Window* GUI_MenuWindowCreate(SDL_Window* window, SDL_Renderer* renderer)
{
	GUI_Window* window_t = malloc(sizeof(GUI_Window));
	GUI_MenuWindow* menu = calloc(sizeof(GUI_MenuWindow), 1);

	//Je�eli nie uda�o si� zaalokowa� odpowiedniej ilo�ci pami�ci
	if (menu == NULL || window_t == NULL)
	{
		free(window_t);
		free(menu);
		printf("GUI_MenuWindowCreate() Error!\n");
		return NULL;
	}

	window_t->gui_window_data = menu;
	menu->window = window;
	menu->renderer = renderer;

	// �adujemy grafik� t�a
	menu->background = GUI_TextureBMP(menu->renderer, "./Graphics/menu_start.bmp");

	//Je�eli nie uda�o si� poprawnie za�adowa� pliku wy�wietl informacj� o b��dzie
	if (menu->background == NULL) 
	{
		//zwolnij pami��
		GUI_MenuWindowDestroy(window_t);
		printf("Background creation error! %s\n", SDL_GetError());
		return NULL;
	}

	// Tworzenie menu wyboru, je�li nie uda�o si� za�adowa� przycisk�w wy�wietl informacj� o b��dzie
	if (!GUI_MenuWindowButtons(menu))
	{
		//zwolnij pami��
		GUI_MenuWindowDestroy(window_t);
		printf("Button creation error! %s\n", SDL_GetError());
		return NULL;
	}

	//Przypisujemy odpowiednie funkcje dla okna menu
	window_t->WindowDestroy = GUI_MenuWindowDestroy;
	window_t->WindowDraw = GUI_MenuWindowDraw;
	window_t->WindowHandleEvent = GUI_MenuWindowHandleEvent;
	return window_t;
}

void GUI_MenuWindowDestroy(GUI_Window* window)
{
	//je�eli okno nie istnia�o nie musimy nic robi�
	if (window == NULL) 
		return;

	GUI_MenuWindow* menu = (GUI_MenuWindow*)window->gui_window_data;
	free(window);

	if (menu == NULL)
		return;

	// usuwamy przyciski menu wyboru
	for (int i = 0; i < 3; i++)
	{
		if (menu->widgettab[i] != NULL)
			menu->widgettab[i]->WidgetDestroy(menu->widgettab[i]);
	}

	// usuwamy tekstur� t�a
	if (menu->background != NULL)
		SDL_DestroyTexture(menu->background);

	free(menu);
}

void GUI_MenuWindowDraw(GUI_Window* window)
 {
	if (window == NULL)
		return;
	//Okno jest oknem menu start
	GUI_MenuWindow* menu = (GUI_MenuWindow*)window->gui_window_data;

	//Tworzymy prostok�t o wymiarach t�a
	SDL_Rect background = { .x = 0, .y = 0, .h = WINDOW_H, .w =WINDOW_W};

	//Ustawiamy kolor czarny
	SDL_SetRenderDrawColor(menu->renderer, 255, 255, 255, 255);

	//Czy�cimy render
	SDL_RenderClear(menu->renderer);

	//Kopiujemy grafik� t�a do rendera
	SDL_RenderCopy(menu->renderer, menu->background, NULL, &background);

	// Rysowanie przycisk�w
	for (unsigned int i = 0; i < 3; i++) 
	{
		menu->widgettab[i]->WidgetDraw(menu->widgettab[i], menu->renderer);
	}

	//Prezentujemy wynik naszych dzia�a� na ekranie
	SDL_RenderPresent(menu->renderer);
}

void GUI_MenuWindowHandleEvent(GUI_Window* window, SDL_Event* event)
{
	
	GUI_MenuWindow* menu = (GUI_MenuWindow*)window->gui_window_data;

	for (unsigned int i = 0; i < 3; i++) 
	{
		menu->widgettab[i]->WidgetHandleEvent(menu->widgettab[i], event);
	}
}