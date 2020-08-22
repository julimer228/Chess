#include "HelpForSDL.h"

bool InitializeSDL2()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    return true;
}
