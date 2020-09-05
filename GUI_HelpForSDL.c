#include "GUI_HelpForSDL.h"

bool GUI_InitializeSDL2()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    return true;
}

void GUI_Messagebox(const char* header, const char* info)
{
	if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, header, info,	NULL) < 0) 
	{
		printf("ERROR! Messagebox creation filed %s\n", SDL_GetError());
	}
}

SDL_Texture* GUI_TextureBMP(SDL_Renderer* render, char* path)
{
	SDL_Surface* surface = SDL_LoadBMP(path);
	SDL_Texture* texture = NULL;

	if (surface == NULL) {
		printf("ERROR! surface was NULL %s\n", SDL_GetError());
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) printf("ERROR! surface was NULL %s\n", SDL_GetError());

	return texture;
}

SDL_Texture* GUI_TextureBMPWithoutBackground(SDL_Renderer* render, char* path, Uint8 red, Uint8 green, Uint8 blue)
{
		SDL_Surface* surface = SDL_LoadBMP(path);
		SDL_Texture* texture = NULL;

		if (surface == NULL) {
			printf("ERROR! surface was NULL %s\n", SDL_GetError());
			return NULL;
		}

		// ustawiamy kolor t³a na przeŸroczysty
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, red, green, blue));

		texture = SDL_CreateTextureFromSurface(render, surface);
		SDL_FreeSurface(surface);

		if (texture == NULL) printf("ERROR! Texture was NULL %s\n", SDL_GetError());

		return texture;
	
}

bool InitSDL2()
{
	if (SDL_Init(SDL_INIT_VIDEO))
	{
		printf("SDL_Init Error: %s", SDL_GetError());
		return false;
	}
	return true;
}

SDL_Window* CreateAWindow()
{
	SDL_Window* window = SDL_CreateWindow("Chess",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);

	if (!window)
	{
		printf("SDL_CreateWindow Error: %s", SDL_GetError() );
		SDL_Quit();
		return NULL;
	}
	return window;
}

SDL_Renderer* CreateARenderer(SDL_Window*window)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		printf("SDL_CreateRenderer Error: %s", SDL_GetError());
		SDL_Quit();
		return NULL;
	}
	return renderer;
}


