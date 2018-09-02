


#include "../../include/util/DrawUtil.h"

void DrawUtil::Blit(SDL_Surface* Dest, int DestX, int DestY, SDL_Surface* Src)
{
	// Create a Rect, and store the coordinates in it.
	// Because SDL likes it this way. 
	SDL_Rect DestR;
	DestR.x = DestX;
	DestR.y = DestY;

	// Use this function to perform a fast surface copy to a destination surface.
	// int SDL_BlitSurface( SDL_Surface*    src,
	//						const SDL_Rect* srcrect,
	//						SDL_Surface*    dst,
	//						SDL_Rect*       dstrect
	//						)
	//
	// src --- SDL_surface structure to be copied from
	// srcrect --- the rectangle to be copied, or NULL to copy the entire surface
	// dst --- destination target
	// dstrect --- representing the rectangle that is copied into
	//
	// Draw to the Dest
	SDL_BlitSurface(Src, NULL, Dest, &DestR);
}

void DrawUtil::Blit(SDL_Surface* Dest, int DestX, int DestY, SDL_Surface* Src, int SrcX, int SrcY, int SrcW, int SrcH)
{
	// Create 2 Rects. The first is for where we want to Blit to.
	// The other is for clipping the 'Src' so we only draw the portion we want

	SDL_Rect DestR;
	DestR.x = DestX;
	DestR.y = DestY;

	SDL_Rect SrcR;
	SrcR.x = SrcX;
	SrcR.y = SrcY;
	SrcR.w = SrcW;
	SrcR.h = SrcH;

	// Draw to the Dest
	SDL_BlitSurface(Src, &SrcR, Dest, &DestR);
}

void DrawUtil::DrawTile(int x, int y, int tile, SDL_Surface* display, SDL_Surface* surfBlocks)
{
	// Draw the Tile
	Blit(display, x * TILE_SIZE, y * TILE_SIZE, surfBlocks, tile * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
}