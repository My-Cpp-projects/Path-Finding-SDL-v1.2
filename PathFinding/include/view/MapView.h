



#ifndef MAPVIEW_H
#define MAPVIEW_H

#include "../../include/view/View.h"

// forward declaration of MapData
namespace pathFinder
{
	struct MapData;
}

namespace pathFinder
{
	class MapView;
}

class pathFinder::MapView : public View
{

public:

	MapView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks, MapData* data, int x, int y);

public:

	virtual void Draw();

private:

	MapData* mMapData;
};

#endif // !MAPVIEW_H
