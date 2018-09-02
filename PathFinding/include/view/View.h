



#ifndef VIEW_H
#define VIEW_H

#include "../../include/view/AbstractView.h"
#include "SDL.h"
#include <vector>

namespace pathFinder
{
	class View;
}

class pathFinder::View : public UI::AbstractView
{

public:

	typedef std::vector<View*> VIEWS;

	typedef SDL_Surface* DISPLAY_REF;
	typedef SDL_Surface* SURF_BLOCKS_REF;

public:

	// constructor
	View(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks, int x, int y)
		: mDisplay(display)
		, mSurfBlocks(surfBlocks)
		, mX(x)
		, mY(y)
	{
	}

public:

	virtual void addChild(View* childView)
	{
		mViews.push_back(childView);
	}

	VIEWS* getViews()
	{
		return &mViews;
	}

	DISPLAY_REF getDisplay()
	{
		return mDisplay;
	}

	SURF_BLOCKS_REF getSurfBlocks()
	{
		return mSurfBlocks;
	}

protected:

	int mX;
	int mY;

private:

	VIEWS mViews;
	DISPLAY_REF mDisplay;
	SURF_BLOCKS_REF mSurfBlocks;
};

#endif // !VIEW_H

