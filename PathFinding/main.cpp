


#include "include/controller/PathFinder.h"
#include "include/model/Map.h"
#include "include/view/MapView.h"
#include "include/view/ViewController.h"

#include <iostream>
#include <SDL.h>
#include <thread>
#include <chrono>

#define WBIT		16									// 16-bit colors
#define WFLAGS		SDL_HWSURFACE | SDL_DOUBLEBUF		// Set up for Video Hardware and Double Buffering
#define WINDOWTITLE "Path Finding"

SDL_Surface* display;	// Our main display surface
SDL_Surface* surfBlocks; // used to read from bmp

void GameDone();

int main(int argc, char* argv[])
{
	char pMap[] =
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	const int WIDTH = 21;
	const int HEIGHT = 30;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{

		std::cout << "Cannot Initialize SDL Systems: ";
		std::cout << SDL_GetError();
		return 0;
	}

	display = SDL_SetVideoMode(WIDTH * WBIT, HEIGHT * WBIT, WBIT, WFLAGS);

	if (!display)
	{
		std::cout << "Cannot set Video Mode: ";
		std::cout << SDL_GetError();
		return 0;
	}

	surfBlocks = SDL_LoadBMP("blocks.bmp");

	if (!surfBlocks)
	{
		std::cout << "File not Found: blocks.bmp: ";
		std::cout << SDL_GetError();
		return false;
	}

	SDL_WM_SetCaption(WINDOWTITLE, WINDOWTITLE);

	pathFinder::Map map(WIDTH, HEIGHT, pMap);
	pathFinder::PathFinder finder(map.getMapData(), 0, 29, 20, 0);
	pathFinder::MapView mapView(display, surfBlocks, map.getMapData(), 0, 0);
	pathFinder::ViewController controller(display, surfBlocks);

	controller.addChild(&mapView);

	while (finder.isRunning())
	{
		finder.onEvent();

		if (finder.isCreatingMap())
		{
			finder.onEvent();
			controller.Draw();
			continue;
		}

		if (!finder.isTargetFound())
		{
			//std::this_thread::sleep_for(std::chrono::microseconds(50000));
			controller.Draw();
			finder.updateCurrentNode();

			while (finder.isProcessingAdjacent())
			{
				finder.processAdjacent();
				finder.onEvent();
				//std::this_thread::sleep_for(std::chrono::microseconds(50000));
				controller.Draw();
			}
		}
		else
		{
			while (finder.isPathConstucting())
			{
				finder.findShortestPathTile();
				finder.onEvent();
				//std::this_thread::sleep_for(std::chrono::microseconds(50000));
				controller.Draw();
			}
		}

		//std::this_thread::sleep_for(std::chrono::microseconds(50000));
		controller.Draw();
	}

	atexit(GameDone);

	return EXIT_SUCCESS;
}

void GameDone()
{
	// Free all the Surfaces we created
	SDL_FreeSurface(display);
	SDL_FreeSurface(surfBlocks);

	// Shut down SDL
	SDL_Quit();
}