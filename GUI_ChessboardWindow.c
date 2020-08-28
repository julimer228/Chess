#include "GUI_ChessboardWindow.h"

/*Funkcja umo¿liwiaj¹ca powrót z ekranu gry do menu g³ównego*/
static void GUI_ChessboardWindowBack()
{
	GUI_UserEventPush(USER_EVENT_BACK_TO_MENU_WINDOW, NULL, NULL);
}

/*Funkcja tworzy przycisk powrotu do menu g³ównego*/
static bool GUI_CreateWidgets(GUI_ChessboardWindow* chessboardwindow)
{
	//Okreœlamy miejsce w którym znajdzie siê przycisk powrotu do menu g³ównego
	SDL_Rect BackToMenu;
	BackToMenu.x = 779,
		BackToMenu.y = 134;
	BackToMenu.h = BUTTON_BACK_H;
	BackToMenu.w = BUTTON_BACK_W;

	//Okreœlamy po³o¿enie szachownicy
	SDL_Rect chessboardrect;
	chessboardrect.x = START_X;
	chessboardrect.y = START_Y;
	chessboardrect.h = GUI_SQUARE * SIZE;
	chessboardrect.w = GUI_SQUARE * SIZE;


	//Tworzymy wid¿ety

	//guzik powrotu do menu g³ównego
	chessboardwindow->back_button_widget = GUI_CreateButton(chessboardwindow->renderer, "./Graphics/button_menu_small", BackToMenu, GUI_ChessboardWindowBack);
	if (chessboardwindow->back_button_widget == NULL)
		return false; //jeœli nie uda³o siê utworzyæ przycisku
	//szachownica
	chessboardwindow->chessboard_widget = GUI_CreateChessboard(chessboardwindow->renderer, chessboardrect, NULL, chessboardwindow->game);
	if (chessboardwindow->chessboard_widget == NULL)
	{
		GUI_DestroyButton(chessboardwindow->back_button_widget);//Jeœli nie uda³o siê utworzyæ szachownicy
		return false;
	}
	return true;
}

	GUI_Window* GUI_CreateChessboardWindow(SDL_Window* window_t, SDL_Renderer* renderer, Game* game)
	{
		if (game == NULL)
		{
			printf("game==NULL");
			return;
		}
		GUI_Window* window = malloc(sizeof(GUI_Window));
		if (window == NULL)
		{
			return NULL;
			printf("Chessboard window alocation error!\n");
		}
		GUI_ChessboardWindow* chessboardwindow = calloc(sizeof(GUI_Window), 1);
		if (chessboardwindow == NULL)
		{
			printf("Chessborad window alocation error!\n");
			free(window);
			return NULL;
		}
		//Okno z szachownic¹ jest oknem
		window->gui_window_data = chessboardwindow;

		chessboardwindow->window = window_t;
		chessboardwindow->renderer = renderer;
		chessboardwindow->game = game;
		chessboardwindow->menu_save = false;

		//£adujemy teksturê t³a
		chessboardwindow->background = GUI_TextureBMP(renderer, "./Graphics/game_window_bg");
		//Sprawdzamy czy tekstura zosta³a poprawnie za³adowana
		if (chessboardwindow->background == NULL)
		{
			//usuwamy okno
			GUI_DestroyChessboardWindow(window);
			printf("ChessboardWindow background loading error");
			return NULL;
		}
		//Tworzymy szachownicê i przycisk
		if (GUI_CreateWidgets(chessboardwindow) == NULL)
		{
			//Jeœli nie uda³o siê utworzyæ wid¿etu szachownicy lub przycisku
			printf("Widgets creation error!");
			GUI_DestroyChessboardWindow(window);
			return NULL;
		}

		//Przypisujemy odpowiednie funkcje
		window->WindowDestroy = GUI_DestroyChessboardWindow;
		window->WindowHandleEvent = GUI_HandleChessboardWindowEvent;
		window->WindowDraw = GUI_DrawChessboardWindow;
		//Zwracamy poprawnie utworzon¹ strukturê
		return window;
	}

	void GUI_DrawChessboardWindow(GUI_Window* window)
	{
		if (window == NULL)
			return;
		GUI_ChessboardWindow* chessboardwindow = (GUI_ChessboardWindow*)window->gui_window_data;

		//Rysujemy t³o

		//Na pocz¹tku tworzymy prostok¹t o wymiarach naszego okna
		SDL_Rect bg_rect;
		bg_rect.x = 0;
		bg_rect.y = 0;
		bg_rect.h = WINDOW_H;
		bg_rect.w = WINDOW_W;

		//Ustawiamy kolor na czarny
		SDL_SetRenderDrawColor(chessboardwindow->renderer, 255, 255, 255, 255);
		//Malujemy ca³e okno na czarno;
		SDL_RenderClear(chessboardwindow->renderer);
		//Kopiujemy t³o do naszego prostok¹ta
		SDL_RenderCopy(chessboardwindow->renderer, chessboardwindow->background, NULL, &bg_rect);

		//Rysujemy przycisk powrotu do menu g³ównego
		chessboardwindow->back_button_widget->WidgetDraw(chessboardwindow->back_button_widget, chessboardwindow->renderer);

		//Prezentujemy okno na ekranie
		SDL_RenderPresent(chessboardwindow->renderer);
	}

	void GUI_DestroyChessboardWindow(GUI_Window* window)
	{
		if (window == NULL)
			return;

		//Tworzymy wskaŸnik na szachownicê
		GUI_ChessboardWindow* chessboardwindow = (GUI_ChessboardWindow*)window->gui_window_data;
		//Usuwamy okno
		free(window);

		//Je¿eli okno z szachownic¹ by³o puste
		if (chessboardwindow == NULL)
			return;

		//Niszczymy wid¿ety
		chessboardwindow->chessboard_widget->WidgetDestroy(chessboardwindow->chessboard_widget);
		chessboardwindow->back_button_widget->WidgetDestroy(chessboardwindow->back_button_widget);

		//Usuwamy grê
		if(chessboardwindow->game!=NULL)
		DestroyGame(chessboardwindow->game);

		//Usuwamy teksturê t³a 
		if (chessboardwindow->background != NULL)
			SDL_DestroyTexture(chessboardwindow->background);
	}

	void GUI_HandleChessboardWindowEvent(GUI_Window* window, SDL_Event*event)
	{
		GUI_ChessboardWindow* chessboardwindow = (GUI_ChessboardWindow*)window->gui_window_data;
		//Je¿eli gracz klikn¹³ w przycisk powrotu do menu g³ównego
		if (event->type == SDL_USEREVENT && event->user.code == USER_EVENT_BACK_TO_MENU_WINDOW)
			GUI_UserEventPush(USER_EVENT_BACK_TO_MENU_WINDOW, NULL, NULL);

	}
	