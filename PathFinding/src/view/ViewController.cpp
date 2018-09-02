


#include "../../include/view/ViewController.h"

#include "SDL.h"

pathFinder::ViewController::ViewController(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks)
	: View(display, surfBlocks, 0, 0)
{
}

void pathFinder::ViewController::Draw()
{
	View::VIEWS::iterator it;

	for (it = getViews()->begin(); it != getViews()->end(); ++it)
	{
		(*it)->Draw();
	}
}
