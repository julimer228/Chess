#include "GUI_HelpForSDL.h"

bool GUI_InitializeSDL2()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }
    return true;
}
void GUI_UserEventPush(GUI_UserEvent userevent, void* a, void* b)
{
	//Tworzymy zdarzenie
	SDL_Event event;
	SDL_memset(&event, 0, sizeof(event));

	event.type = SDL_USEREVENT;
	event.user.code = userevent;
	event.user.data1 =a;
	event.user.data2 =b;

	SDL_PushEvent(&event);
}

void GUI_Messagebox(const char* header, const char* info)
{
	// jeœli biblioteka SDL nie zadzia³a informacja wyœwietli siê na ekranie konsoli
	if (SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, header, info,	NULL) < 0) 
	{
		printf("ERROR! messagebox creation failed: %s\n", SDL_GetError());
		printf("Message:\n%s: %s\n", header, info);
	}
}

SDL_Texture* GUI_TextureBMP(SDL_Renderer* render, char* path)
{
	SDL_Surface* surface = SDL_LoadBMP(path);
	SDL_Texture* texture = NULL;

	if (surface == NULL) {
		printf("ERROR! loading BMP failed: %s\n", SDL_GetError());
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(render, surface);
	SDL_FreeSurface(surface);

	if (texture == NULL) printf("ERROR! texture creation failed: %s\n", SDL_GetError());

	return texture;
}

SDL_Texture* GUI_TextureBMPWithoutBackground(SDL_Renderer* render, char* path, Uint8 red, Uint8 green, Uint8 blue)
{
		SDL_Surface* surface = SDL_LoadBMP(path);
		SDL_Texture* texture = NULL;

		if (surface == NULL) {
			printf("ERROR! loading BMP failed: %s\n", SDL_GetError());
			return NULL;
		}

		// ustawiamy kolor t³a na przeŸroczysty
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, red, green, blue));

		texture = SDL_CreateTextureFromSurface(render, surface);
		SDL_FreeSurface(surface);

		if (texture == NULL) printf("ERROR! texture creation failed: %s\n", SDL_GetError());

		return texture;
	
}


void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, int w, int h) 
{
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = w;
	dst.h = h;
	SDL_RenderCopy(ren, tex, NULL, &dst);
}


