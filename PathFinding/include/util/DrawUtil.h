


#ifndef DRAWUTIL_H
#define DRAWUTIL_H

#include "SDL.h"

class DrawUtil
{
public:

	enum Colour
	{
		TILE_NODRAW = -1,
		TILE_BLACK,
		TILE_GREY,
		TILE_BLUE,
		TILE_RED,
		TILE_GREEN,
		TILE_YELLOW,
		TILE_WHITE,
		TILE_STEEL,
		TILE_PURPLE,

		TILE_SIZE = 16
	};

	// Blitting --- Basically it means copying the image from one surface to another
	// Makes it easier to Blit a Surface to another Surface
	static void Blit(SDL_Surface* Dest, int DestX, int DestY, SDL_Surface* Src);
	static void Blit(SDL_Surface* Dest, int DestX, int DestY, SDL_Surface* Src, int SrcX, int SrcY, int SrcW, int SrcH);

	static void DrawTile(int x, int y, int tile, SDL_Surface* display, SDL_Surface* surfBlock); // coordinates & tile type
};

#endif // !DRAWUTIL_H

