#include "GUI_GameHandler.h"

GUI_Handler* CreateHandler()
{
	 GUI_Handler* handler = (GUI_Handler*)malloc(sizeof(GUI_Handler));
	if (handler == NULL)
	{
		printf("Handler allocation error!");
		return NULL;
	}

	//Tworzymy okno SDL
	handler->window = SDL_CreateWindow("Chess for two players", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_BORDERLESS|SDL_WINDOW_SHOWN);

	//Sprawdzamy czy okno zosta³o poprawnie utworzone
	if (handler->window == NULL)
	{
		printf("SDL window creation error! %s ", SDL_GetError());
		free(handler);
		return NULL;
	}

	//Tworzymy render
	handler->renderer = SDL_CreateRenderer(handler->window, -1, SDL_RENDERER_SOFTWARE);
	//Sprawdzamy czy zosta³ poprawnie utworzony
	if (handler->renderer == NULL)
	{
		printf("SDL Renderer creation error! %s", SDL_GetError());
		SDL_DestroyWindow(handler->window);
		free(handler);
	}

	//Ustawiamy pozosta³e pola
	handler->actual_window = NULL;
	handler->previous_window = NULL;
	handler->stop = false;
	handler->duringTheGame = false;
	handler->game = CreateGame();

	return handler;
}

void DestroyHandler(GUI_Handler* handler)
{
	if (handler == NULL)
		return;

	if (handler->renderer != NULL)
		SDL_DestroyRenderer(handler->renderer);
	if (handler->window != NULL)
		SDL_DestroyWindow(handler->window);
	if (handler->actual_window != NULL)
		handler->actual_window->WindowDestroy(handler->actual_window);
	free(handler);
}

static void GoToNextWindow(GUI_Handler* handler, GUI_WindowType next)
{

	if (handler == NULL)
		return;

	//Usuwamy aktualne okno z pamiêci
	handler->actual_window->WindowDestroy(handler->actual_window);
	//Partia nie jest rozgrywna
	handler->duringTheGame = false;

	//Ustawiamy kolejne okno
	switch (next)
	{
	case MENU_WINDOW:
		handler->actual_window = GUI_MenuWindowCreate(handler->window, handler->renderer);
	case HELP_WINDOW:
	/// <summary>
	/// Uzupe³niæ powstawanie okna menu pomocy!!!
	/// </summary>
	case GAME_WINDOW:
		//Znajdujemy siê w trakcie partii
		handler->duringTheGame = true;
		//Sprawdziæ!!!
		handler->actual_window = GUI_CreateChessboardWindow(handler->window,handler->renderer, CreateGame());
		
	default:
		break;
	}

	//Sprawdzenie, czy wyst¹pi³y jakieœ b³êdy - jeœli tak to zatrzymaj dzia³anie programu
	if (handler->actual_window == NULL)
	{
		handler->stop = true;
		return;
	}
	//Rysujemy okno
	handler->actual_window->WindowDraw(handler->actual_window);
}
bool RunGraphicalGame()
{
	//Rozpoczynamy pracê z bibliotek¹ SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init error: %s", SDL_GetError());
		return false;
	}
	atexit(SDL_Quit);

	//Tworzymy grê
	GUI_Handler* handler = CreateHandler();
	if (handler == NULL)
		return false;


	//Tworzymy wskaŸnik na zdarzenie 
	SDL_Event event;
	//Rozpoczynamy od okna menu start
	GoToNextWindow(handler, MENU_WINDOW);
	if (handler->stop)
	{
		printf("Error!");
		return false;
	}

	while (handler->stop == false)
	{
		SDL_WaitEvent(&event);

		//zamykanie okna
		if (event.type == SDL_QUIT)
		{

		}//Jeœli zdarzenie pochodzi od gracza
		else if (event.type == SDL_USEREVENT)
		{
			switch (event.user.code)
			{
			case USER_EVENT_PLAY:
			case USER_EVENT_HELP:
			case USER_EVENT_EXIT:
			case USER_EVENT_BACK_TO_MENU_WINDOW:
			case USER_EVENT_OK:
			default:
				break;
			}



		}
	}
}
