



#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include "../../include/view/View.h"

namespace pathFinder
{
	class ViewController;
}

class pathFinder::ViewController : public View
{

public:

	ViewController(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks);

public:

	virtual void Draw();
};

#endif // !VIEWCONTROLLER_H
