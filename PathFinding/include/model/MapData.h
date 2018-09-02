


#ifndef MAPDATA_H
#define MAPDATA_H

#include "../../include/model/Node.h"

namespace pathFinder
{
	struct MapData;
}

struct pathFinder::MapData
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Enum declarations

	enum class TerrainType : int
	{
		IMPOSSIBLE = 0,
		POSSIBLE = 1,
	};

	enum class EnergyCost : int
	{
		CLASSIC_ENERGY_ORTHOGONAL = 10,
	};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	MapData(int w, int h)
		: mWidth(w)
		, mHeight(h)
	{
		mNodes = new Node**[mWidth]();
		for (int i = 0; i < mWidth; ++i)
		{
			mNodes[i] = new Node*[mHeight]();
		}
	}

	~MapData()
	{
		for (int i = 0; i < mWidth; ++i)
		{
			for (int j = 0; j < mHeight; ++j)
			{
				delete mNodes[i][j];
			}

			delete[] mColorMap[i];
			delete[] mNodes[i];
		}

		delete[] mMap;
		delete[] mColorMap;
		delete[] mNodes;

		mMap = nullptr;
		mColorMap = nullptr;
		mNodes = nullptr;
	}

	bool isInMap(int x, int y)
	{
		if (x >= 0 && y >= 0 && x < mWidth && y < mHeight)
		{
			return true;
		}

		return false;
	}

	int mWidth;
	int mHeight;
	
	char* mMap; // Contains the given map
	int** mColorMap; // Contains the colours of map terrain
	Node*** mNodes;

};

#endif // !MAPDATA_H
