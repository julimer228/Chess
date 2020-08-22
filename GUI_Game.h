/**@FILE*/
#ifndef GUI_GAME_H
#define GUI_GAME_H
#include "Game.h"
#include "HelpForSDL.h"

/*--------MASZYNA STANÓW--------*/

/*Typ wyliczeniowy definuj¹cy stan gry*/
typedef enum gui_state
{
	GUI_STATE_INITIAL, //Stan pocz¹tkowy, przed rozpoczêciem gry (menu g³ówne)
	GUI_STATE_PLAY, //Stan rozgrywki - tutaj znajduje siê g³ówna pêtla gry
	GUI_STATE_HELP, //Stan w którym wyœwietla siê okienko z pomoc¹
	GUI_STATE_SAVE, //Stan w którym gra zosta³a zakoñczona zwyciêstwem jednego z graczy, i przebiego zostaje zapisany do pliku
	GUI_STATE_EXIT // Stan w którym praca programu zostaje zakoñczona
}GUI_State;

/*Struktura odpowiedzialna za grê*/
typedef struct gui_game
{
	GUI_State gui_game_state_actual;
}GUI_Game;


/*Funkcja tworzy strukturê gry
@return utworzona struktura, jeœli nie uda³o siê utworzyæ struktury funkcja zwraca NULL*/
GUI_Game CreateGUI_Game();

/*Funkcja usuwa strukturê gry z pamiêci
@param GUI_game struktura do usuniêcia*/
void DestroyGUI_Game(GUI_Game* GUI_game);

/*---FUNKCJE ODPOWIEDZIALNE ZA POSZCZEGÓLNE STANY---*/

/*Funkcja odpowiedzialna za stan pocz¹tkowy gry
@param GUI_game 
@return kolejny stan gry*/
GUI_State do_GUI_STATE_INITIAL(GUI_Game* GUI_game);

/*Funkcja odpowiedzialna za stan rozgrywki
@param GUI_game
@return kolejny stan gry*/
GUI_State do_GUI_STATE_PLAY(GUI_Game* GUI_game);

/*Funkcja odpowiedzialna za stan wyœwietlenia pomocy
@param GUI_game
@return kolejny stan gry*/
GUI_State do_GUI_STATE_HELP(GUI_Game* GUI_game);

/*Funkcja odpowiedzialna za stan zapisu gry
@param GUI_game
@return kolejny stan gry*/
GUI_State do_GUI_STATE_SAVE(GUI_Game* GUI_game);

/*Funkcja odpowiedzialna za stan zakoñczenia pracy programu
@param GUI_game
@return kolejny stan gry*/
GUI_State do_GUI_STATE_EXIT(GUI_Game* GUI_game);

typedef GUI_State GUI_State_func_t(GUI_Game* GUI_game);
GUI_State_func_t* const GUI_state_tab[] = {
	do_GUI_STATE_INITIAL, do_GUI_STATE_PLAY, do_GUI_STATE_HELP, do_GUI_STATE_SAVE, do_GUI_STATE_EXIT
};

/*Funkcja odpowiedzialna za przechodzenie do kolejnych stanów (g³ówna funkcja maszyny stanów)
@param GUI_state_current aktualny stan gry
@param GUI_game struktura gry
@return kolejny stan gry*/
GUI_State Run_GUI_State(GUI_State GUI_state_current, GUI_Game* GUI_game);





#endif 