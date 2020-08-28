#include "GUI_ChessboardWindow.h"

/*Funkcja umo�liwiaj�ca powr�t z ekranu gry do menu g��wnego*/
static void GUI_ChessboardWindowBack()
{
	GUI_UserEventPush(USER_EVENT_BACK_TO_MENU_WINDOW, NULL, NULL);
}

/*Funkcja tworzy przycisk powrotu do menu g��wnego*/
static bool GUI_CreateWidgets(GUI_ChessboardWindow* chessboardwindow)
{
	//Okre�lamy miejsce w kt�rym znajdzie si� przycisk powrotu do menu g��wnego
	SDL_Rect BackToMenu;
	BackToMenu.x = 779,
		BackToMenu.y = 134;
	BackToMenu.h = BUTTON_BACK_H;
	BackToMenu.w = BUTTON_BACK_W;

	//Okre�lamy po�o�enie szachownicy
	SDL_Rect chessboardrect;
	chessboardrect.x = START_X;
	chessboardrect.y = START_Y;
	chessboardrect.h = GUI_SQUARE * SIZE;
	chessboardrect.w = GUI_SQUARE * SIZE;


	//Tworzymy wid�ety

	//guzik powrotu do menu g��wnego
	chessboardwindow->back_button_widget = GUI_CreateButton(chessboardwindow->renderer, "./Graphics/button_menu_small", BackToMenu, GUI_ChessboardWindowBack);
	if (chessboardwindow->back_button_widget == NULL)
		return false; //je�li nie uda�o si� utworzy� przycisku
	//szachownica
	chessboardwindow->chessboard_widget = GUI_CreateChessboard(chessboardwindow->renderer, chessboardrect, NULL, chessboardwindow->game);
	if (chessboardwindow->chessboard_widget == NULL)
	{
		GUI_DestroyButton(chessboardwindow->back_button_widget);//Je�li nie uda�o si� utworzy� szachownicy
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
		//Okno z szachownic� jest oknem
		window->gui_window_data = chessboardwindow;

		chessboardwindow->window = window_t;
		chessboardwindow->renderer = renderer;
		chessboardwindow->game = game;
		chessboardwindow->menu_save = false;

		//�adujemy tekstur� t�a
		chessboardwindow->background = GUI_TextureBMP(renderer, "./Graphics/game_window_bg");
		//Sprawdzamy czy tekstura zosta�a poprawnie za�adowana
		if (chessboardwindow->background == NULL)
		{
			//usuwamy okno
			GUI_DestroyChessboardWindow(window);
			printf("ChessboardWindow background loading error");
			return NULL;
		}
		//Tworzymy szachownic� i przycisk
		if (GUI_CreateWidgets(chessboardwindow) == NULL)
		{
			//Je�li nie uda�o si� utworzy� wid�etu szachownicy lub przycisku
			printf("Widgets creation error!");
			GUI_DestroyChessboardWindow(window);
			return NULL;
		}

		//Przypisujemy odpowiednie funkcje
		window->WindowDestroy = GUI_DestroyChessboardWindow;
		window->WindowHandleEvent = GUI_HandleChessboardWindowEvent;
		window->WindowDraw = GUI_DrawChessboardWindow;
		//Zwracamy poprawnie utworzon� struktur�
		return window;
	}

	void GUI_DrawChessboardWindow(GUI_Window* window)
	{
		if (window == NULL)
			return;
		GUI_ChessboardWindow* chessboardwindow = (GUI_ChessboardWindow*)window->gui_window_data;

		//Rysujemy t�o

		//Na pocz�tku tworzymy prostok�t o wymiarach naszego okna
		SDL_Rect bg_rect;
		bg_rect.x = 0;
		bg_rect.y = 0;
		bg_rect.h = WINDOW_H;
		bg_rect.w = WINDOW_W;

		//Ustawiamy kolor na czarny
		SDL_SetRenderDrawColor(chessboardwindow->renderer, 255, 255, 255, 255);
		//Malujemy ca�e okno na czarno;
		SDL_RenderClear(chessboardwindow->renderer);
		//Kopiujemy t�o do naszego prostok�ta
		SDL_RenderCopy(chessboardwindow->renderer, chessboardwindow->background, NULL, &bg_rect);

		//Rysujemy przycisk powrotu do menu g��wnego
		chessboardwindow->back_button_widget->WidgetDraw(chessboardwindow->back_button_widget, chessboardwindow->renderer);

		//Prezentujemy okno na ekranie
		SDL_RenderPresent(chessboardwindow->renderer);
	}

	void GUI_DestroyChessboardWindow(GUI_Window* window)
	{
		if (window == NULL)
			return;

		//Tworzymy wska�nik na szachownic�
		GUI_ChessboardWindow* chessboardwindow = (GUI_ChessboardWindow*)window->gui_window_data;
		//Usuwamy okno
		free(window);

		//Je�eli okno z szachownic� by�o puste
		if (chessboardwindow == NULL)
			return;

		//Niszczymy wid�ety
		chessboardwindow->chessboard_widget->WidgetDestroy(chessboardwindow->chessboard_widget);
		chessboardwindow->back_button_widget->WidgetDestroy(chessboardwindow->back_button_widget);

		//Usuwamy gr�
		if(chessboardwindow->game!=NULL)
		DestroyGame(chessboardwindow->game);

		//Usuwamy tekstur� t�a 
		if (chessboardwindow->background != NULL)
			SDL_DestroyTexture(chessboardwindow->background);
	}

	void GUI_HandleChessboardWindowEvent(GUI_Window* window, SDL_Event*event)
	{
		GUI_ChessboardWindow* chessboardwindow = (GUI_ChessboardWindow*)window->gui_window_data;
		//Je�eli gracz klikn�� w przycisk powrotu do menu g��wnego
		if (event->type == SDL_USEREVENT && event->user.code == USER_EVENT_BACK_TO_MENU_WINDOW)
			GUI_UserEventPush(USER_EVENT_BACK_TO_MENU_WINDOW, NULL, NULL);

	}
	