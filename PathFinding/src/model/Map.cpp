


#include "../../include/model/Map.h"
#include "../../include/model/MapData.h"
#include "../../include/util/DrawUtil.h"

pathFinder::Map::Map(int widht, int height, const char* map)
	: mMapData(new MapData(widht, height))
{
	init(map);
}

pathFinder::Map::~Map()
{
	delete mMapData;
}

pathFinder::MapData* pathFinder::Map::getMapData() const
{
	return mMapData;
}


//////////////////////////////////////////////////////////////
// Private Functions
//////////////////////////////////////////////////////////////

void pathFinder::Map::init(const char* map) const
{
	mMapData->mColorMap = new int*[mMapData->mWidth];

	mMapData->mMap = new char[mMapData->mWidth * mMapData->mHeight];
	memcpy(mMapData->mMap, map, sizeof(char) * mMapData->mWidth * mMapData->mHeight);

	for (int i = 0; i < mMapData->mWidth; ++i)
	{
		mMapData->mColorMap[i] = new int[mMapData->mHeight];

		for (int j = 0; j < mMapData->mHeight; ++j)
		{
			switch (static_cast<MapData::TerrainType>(map[j * mMapData->mWidth + i]))
			{
				case MapData::TerrainType::POSSIBLE :
				{
					mMapData->mColorMap[i][j] = ::DrawUtil::TILE_WHITE;
					break;
				}

				case MapData::TerrainType::IMPOSSIBLE :
				{
					mMapData->mColorMap[i][j] = ::DrawUtil::TILE_BLACK;
					break;
				}

				default:
				{
					// Unkown type of terrain is encountered
					mMapData->mColorMap[i][j] = ::DrawUtil::TILE_RED;
					break;
				}
			}
		}
	}
}
