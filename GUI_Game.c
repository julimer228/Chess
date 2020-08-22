#include "GUI_Game.h"

GUI_State do_GUI_STATE_INITIAL(GUI_Game* GUI_game)
{
	if (InitializeSDL2())
	{
		//Nacisnieto play
		return GUI_STATE_PLAY;
		//Nacisnieto help
		return GUI_STATE_HELP;
		//Nacisnieto exit
		return GUI_STATE_EXIT;
	}
	else return GUI_STATE_EXIT;
}

GUI_State do_GUI_STATE_PLAY(GUI_Game* GUI_game)
{
	//Gra dobieg³a koñca
	return GUI_STATE_SAVE;
	//Zamknieto okno 
	return GUI_STATE_EXIT;
	//Nacisnieto back
	return GUI_STATE_INITIAL;
}

GUI_State do_GUI_STATE_HELP(GUI_Game* GUI_game)
{
	//Nacisnieto OK
	return GUI_STATE_INITIAL;
}

GUI_State do_GUI_STATE_SAVE(GUI_Game* GUI_game)
{
	//Zapisano -> powrót do menu g³ównego
	return GUI_STATE_INITIAL;

	//Nacisnieto [x] -> SDL_QUIT??
	return GUI_STATE_EXIT;
}

GUI_State do_GUI_STATE_EXIT(GUI_Game* GUI_game)
{
	//SDL_QUIT??
	return;
}


	GUI_State Run_GUI_State(GUI_State GUI_state_current, GUI_Game * GUI_game)
	{
		return GUI_state_tab[GUI_state_current](GUI_game);
	}
