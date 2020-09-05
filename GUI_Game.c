#include "GUI_Game.h"

GUI_Game* CreateGUI_Game()
{
    GUI_Game* guigame = (GUI_Game*)malloc(sizeof(GUI_Game));
    guigame->window = CreateAWindow();
    if (guigame->window == NULL)
    {
        free(guigame);
        return NULL;
    }
    guigame->renderer = CreateARenderer(guigame->window);
    if (guigame->renderer == NULL)
    {
        SDL_DestroyWindow(guigame->window);
        free(guigame);
        return NULL;
    }

    guigame->game = CreateGame();
    if (guigame->game == NULL)
    {
        SDL_DestroyRenderer(guigame->renderer);
        SDL_DestroyWindow(guigame->window);
        free(guigame);
        return NULL;
    }

    SDL_Rect location = {.x=START_X, .y=START_Y, .h=SIZE*GUI_SQUARE, .w=SIZE*GUI_SQUARE};
    guigame->chessboard_location = location;
    guigame->guichessboard = GUI_CreateChessboard(guigame->renderer,guigame->chessboard_location, guigame->game);
    if (guigame->guichessboard == NULL)
    {
        DestroyGame(&guigame->game);
        SDL_DestroyRenderer(guigame->renderer);
        SDL_DestroyWindow(guigame->window);
        free(guigame);
        return NULL;
    }
    guigame->background_tx = GUI_TextureBMP(guigame->renderer, "./Graphics/game_window_bg.bmp");
    if (guigame->background_tx == NULL)
    {
        GUI_DestroyChessboard(guigame->guichessboard);
        DestroyGame(&guigame->game);
        SDL_DestroyRenderer(guigame->renderer);
        SDL_DestroyWindow(guigame->window);
        free(guigame);
        return NULL;
    }
    return guigame;
}

void GUI_DrawGameWindow(GUI_Game* guigame, SDL_Renderer* renderer)
{
    if (guigame == NULL) return;

    SDL_Rect bg_location = { .x = 0,.y = 0,.h = WINDOW_H,.w = WINDOW_W };

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, guigame->background_tx, NULL, &bg_location);
    GUI_DrawChessboard(guigame->guichessboard,renderer);

    SDL_Rect turn_rect = { .x = 790,.y = WINDOW_H /4+20 ,.h = WINDOW_H/2,.w = 200 };
    if (guigame->game->CurrentPlayer == black)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderFillRect(renderer, &turn_rect);
    }
    if (guigame->game->CurrentPlayer == white)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderFillRect(renderer, &turn_rect);
    }
    SDL_RenderPresent(renderer);
}

void GUI_GameDestroy(GUI_Game* guigame)
{
    
    if (guigame == NULL)
        return;
    DestroyGame(guigame->game);
    GUI_DestroyChessboard(guigame->guichessboard);
    SDL_DestroyTexture(guigame->background_tx);
    SDL_DestroyRenderer(guigame->renderer);
    SDL_DestroyWindow(guigame->window);
}

void GameRun()
{
    if (InitSDL2())
    {
        GUI_Game* guigame = CreateGUI_Game();
        if (guigame == NULL)
        {
            printf("Error!");
            return;
        }

        SDL_Event event;
        while (guigame->guichessboard->game->HasGameEnded==false)
        {
            GUI_DrawGameWindow(guigame, guigame->renderer);
        
            SDL_WaitEvent(&event);
           

            if (event.type == SDL_MOUSEBUTTONUP)
            {
                
                GUI_handleChessboardEvent(guigame->guichessboard, &event);
          
            }
            else if (event.type == SDL_QUIT)
            {
                break;
            }
            
        }
        GUI_GameDestroy(guigame);
        SDL_Quit();
    }
}
