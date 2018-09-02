


#include "../../include/view/MapView.h"
#include "../../include/model/MapData.h"
#include "../../include/util/DrawUtil.h"


pathFinder::MapView::MapView(DISPLAY_REF display, SURF_BLOCKS_REF surfBlocks, MapData* data, int x, int y)
	: View(display, surfBlocks, x, y)
	, mMapData(data)
{

}

void pathFinder::MapView::Draw()
{
	int xmy;
	int ymx;

	// Draw the board
	// Loop through the positions
	for (xmy = 0; xmy < mMapData->mWidth; ++xmy)
	{
		for (ymx = 0; ymx < mMapData->mHeight; ++ymx)
		{
			if (mMapData->mNodes[xmy][ymx])
			{
				::DrawUtil::DrawTile(xmy + mX, ymx + mY, mMapData->mNodes[xmy][ymx]->mColour, getDisplay(), getSurfBlocks());
			}
			else
			{
				::DrawUtil::DrawTile(xmy + mX, ymx + mY, mMapData->mColorMap[xmy][ymx], getDisplay(), getSurfBlocks());
			}			
		}
	}

	// Redraw the entire Display
	SDL_Flip(getDisplay());
}
