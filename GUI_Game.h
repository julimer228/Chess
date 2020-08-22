/**@FILE*/
#ifndef GUI_GAME_H
#define GUI_GAME_H
#include "Game.h"
#include "HelpForSDL.h"

/*--------MASZYNA STAN�W--------*/

/*Typ wyliczeniowy definuj�cy stan gry*/
typedef enum gui_state
{
	GUI_STATE_INITIAL, //Stan pocz�tkowy, przed rozpocz�ciem gry (menu g��wne)
	GUI_STATE_PLAY, //Stan rozgrywki - tutaj znajduje si� g��wna p�tla gry
	GUI_STATE_HELP, //Stan w kt�rym wy�wietla si� okienko z pomoc�
	GUI_STATE_SAVE, //Stan w kt�rym gra zosta�a zako�czona zwyci�stwem jednego z graczy, i przebiego zostaje zapisany do pliku
	GUI_STATE_EXIT // Stan w kt�rym praca programu zostaje zako�czona
}GUI_State;

/*Struktura odpowiedzialna za gr�*/
typedef struct gui_game
{
	GUI_State gui_game_state_actual;
}GUI_Game;


/*Funkcja tworzy struktur� gry
@return utworzona struktura, je�li nie uda�o si� utworzy� struktury funkcja zwraca NULL*/
GUI_Game CreateGUI_Game();

/*Funkcja usuwa struktur� gry z pami�ci
@param GUI_game struktura do usuni�cia*/
void DestroyGUI_Game(GUI_Game* GUI_game);

/*---FUNKCJE ODPOWIEDZIALNE ZA POSZCZEG�LNE STANY---*/

/*Funkcja odpowiedzialna za stan pocz�tkowy gry
@param GUI_game 
@return kolejny stan gry*/
GUI_State do_GUI_STATE_INITIAL(GUI_Game* GUI_game);

/*Funkcja odpowiedzialna za stan rozgrywki
@param GUI_game
@return kolejny stan gry*/
GUI_State do_GUI_STATE_PLAY(GUI_Game* GUI_game);

/*Funkcja odpowiedzialna za stan wy�wietlenia pomocy
@param GUI_game
@return kolejny stan gry*/
GUI_State do_GUI_STATE_HELP(GUI_Game* GUI_game);

/*Funkcja odpowiedzialna za stan zapisu gry
@param GUI_game
@return kolejny stan gry*/
GUI_State do_GUI_STATE_SAVE(GUI_Game* GUI_game);

/*Funkcja odpowiedzialna za stan zako�czenia pracy programu
@param GUI_game
@return kolejny stan gry*/
GUI_State do_GUI_STATE_EXIT(GUI_Game* GUI_game);

typedef GUI_State GUI_State_func_t(GUI_Game* GUI_game);
GUI_State_func_t* const GUI_state_tab[] = {
	do_GUI_STATE_INITIAL, do_GUI_STATE_PLAY, do_GUI_STATE_HELP, do_GUI_STATE_SAVE, do_GUI_STATE_EXIT
};

/*Funkcja odpowiedzialna za przechodzenie do kolejnych stan�w (g��wna funkcja maszyny stan�w)
@param GUI_state_current aktualny stan gry
@param GUI_game struktura gry
@return kolejny stan gry*/
GUI_State Run_GUI_State(GUI_State GUI_state_current, GUI_Game* GUI_game);





#endif 