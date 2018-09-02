


#include "../../include/controller/PathFinder.h"
#include "../../include/model/MapData.h"
#include "../../include/model/Node.h"
#include "../../include/util/DrawUtil.h"

// Constructor
pathFinder::PathFinder::PathFinder(MapData* mapData, int startX, int startY, int targetX, int targetY)
	: mMapData(mapData)
	, mStartX(startX)
	, mStartY(startY)
	, mTargetX(targetX)
	, mTargetY(targetY)
	, mIsRunning(true)
	, mIsProcessingAdjacent(true)
	, mIsTargetFound(false)
	, mIsPathConstructing(false)
	, mIsCreatingMap(true)
{
	mMapData->mNodes[mStartX][mStartY] = new Node(mStartX, mStartY);
	mMapData->mNodes[mTargetX][mTargetY] = new Node(mTargetX, mTargetY);

	addToOpenSet(mMapData->mNodes[mStartX][mStartY]);
	mMapData->mNodes[mTargetX][mTargetY]->mColour = ::DrawUtil::Colour::TILE_YELLOW;
}

////////////////////////////////////////////////////////////////////////////////////
// Public Member Functions
////////////////////////////////////////////////////////////////////////////////////

void pathFinder::PathFinder::updateCurrentNode()
{
	if (!openSet.empty())
	{
		openSet.top()->isInOpenSet = false;
		mCurrentNode = openSet.top();
		mCurrentNode->mColour = ::DrawUtil::TILE_BLUE;
		openSet.pop();

		mIsProcessingAdjacent = true; // There are unprocessed Nodes adjacent to updated mCurrentNode
	}
	else
	{
		mIsRunning = false;
	}
}

void pathFinder::PathFinder::processAdjacent()
{
	// DIAGONAL locations are NOT considered adjacent
	const int ADJACENT_COUNT = 4;
	int adjacentCoordinates[] = { -1, 0, 0, 1, 1, 0, 0, -1 }; // Left, bottom, right, up
	static int offset = 0; // Used to come back to the part where the function was stopped

	for (int i = offset; i < ADJACENT_COUNT; ++i)
	{
		int tmpX = mCurrentNode->mX + adjacentCoordinates[2 * i];
		int tmpY = mCurrentNode->mY + adjacentCoordinates[2 * i + 1];

		// Check if the coordinate is valid and if there is a wall in the coordinate
		if (
			mMapData->isInMap(tmpX, tmpY)
			&&
			MapData::TerrainType::POSSIBLE == static_cast<MapData::TerrainType>(mMapData->mMap[tmpY * mMapData->mWidth + tmpX])
			)
		{
			if (tmpX == mTargetX && tmpY == mTargetY)
			{
				mIsProcessingAdjacent = false;
				mIsTargetFound = true;
				mIsPathConstructing = true;
				mMapData->mNodes[tmpX][tmpY]->mParent = mCurrentNode;
				return;
			}

			Node** tmpNode = &mMapData->mNodes[tmpX][tmpY];

			if (!(*tmpNode))
			{
				createNewNode(tmpNode, tmpX, tmpY);
				addToOpenSet(*tmpNode);
				offset = i + 1;
				return; // Stop the function so the updated map will be drawn
			}
			else if((*tmpNode)->isProcessed && (*tmpNode)->isInOpenSet)
			{
				updateExistingNodeScore(*tmpNode);
				// No need to redraw, so continue the loop
			}
		}
	}

	mIsProcessingAdjacent = false;
	offset = 0;
}

void pathFinder::PathFinder::findShortestPathTile()
{
	static Node* tmpNode = mMapData->mNodes[mTargetX][mTargetY];

	if (tmpNode != mMapData->mNodes[mStartX][mStartY])
	{
		tmpNode->mColour = ::DrawUtil::TILE_PURPLE;
		tmpNode = tmpNode->mParent;
	}
	else
	{
		// For updating the start node
		tmpNode->mColour = ::DrawUtil::TILE_PURPLE;
		mIsPathConstructing = false;
	}
}

void pathFinder::PathFinder::onEvent()
{
	SDL_Event Event;

	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
			case SDL_QUIT:		// Found a quit event
			{
				mIsRunning = false;
				mIsProcessingAdjacent = false;
				mIsPathConstructing = false;
			} break;

			case SDL_KEYDOWN:	// A key has been pressed
			{
				int Sym = Event.key.keysym.sym;

				switch (Sym)
				{
					case SDLK_ESCAPE:
					{
						mIsRunning = false;
						mIsProcessingAdjacent = false;
						mIsPathConstructing = false;
					} break;

					case SDLK_KP_ENTER:
					case SDLK_RETURN:
					{
						mIsCreatingMap = false;
					} break;

				}
			}

			case SDL_MOUSEBUTTONDOWN:
			{
				mousePress(Event.button);
			} break;
		}
	}
}

bool pathFinder::PathFinder::isRunning() const
{
	return mIsRunning;
}

bool pathFinder::PathFinder::isProcessingAdjacent() const
{
	return mIsProcessingAdjacent;
}

bool pathFinder::PathFinder::isTargetFound() const
{
	return mIsTargetFound;
}

bool pathFinder::PathFinder::isPathConstucting() const
{
	return mIsPathConstructing;
}

bool pathFinder::PathFinder::isCreatingMap() const
{
	return mIsCreatingMap;
}

////////////////////////////////////////////////////////////////////////////////////
// Private Member Functions
////////////////////////////////////////////////////////////////////////////////////

int pathFinder::PathFinder::computeGScore(const Node* const parent) const
{
	int parentHScore = computeHScore(parent);

	// When the parent node is the starting node the return statement will give invalid number
	if (0 == parent->mFScore) // mFscore is 0 only for starting node
	{
		parentHScore = 0; // Set hScore to 0 to prevent errors
	}

	return parent->mFScore - parentHScore + static_cast<int>(MapData::EnergyCost::CLASSIC_ENERGY_ORTHOGONAL);
}

int pathFinder::PathFinder::computeHScore(const Node* const node) const
{
	return (abs(mTargetX - node->mX) + abs(mTargetY - node->mY)) * static_cast<int>(MapData::EnergyCost::CLASSIC_ENERGY_ORTHOGONAL);
}

int pathFinder::PathFinder::computeFScore(const Node* const node) const
{
	return computeHScore(node) + computeGScore(node->mParent);
}

void pathFinder::PathFinder::updateExistingNodeScore(Node* node)
{
	if (computeGScore(node->mParent) > computeGScore(mCurrentNode))
	{
		node->setParent(mCurrentNode);
		node->mFScore = computeFScore(node);
	}
}

void pathFinder::PathFinder::createNewNode(Node** node, int x, int y)
{
	*node = new Node(x, y, mCurrentNode);

	(*node)->mFScore = computeFScore(*node);
}

void pathFinder::PathFinder::addToOpenSet(Node* node)
{
	node->isInOpenSet = true;
	node->isProcessed = true;
	node->mColour = ::DrawUtil::TILE_GREEN;
	openSet.push(node);
}

void pathFinder::PathFinder::mousePress(SDL_MouseButtonEvent& b)
{
	if (mIsCreatingMap)
	{
		if (b.button == SDL_BUTTON_LEFT)
		{
			int x = ceil(b.x / ::DrawUtil::TILE_SIZE);
			int y = ceil(b.y / ::DrawUtil::TILE_SIZE);

			switch (static_cast<MapData::TerrainType> (mMapData->mMap[y * mMapData->mWidth + x]))
			{

				case MapData::TerrainType::IMPOSSIBLE:
				{
					mMapData->mMap[y * mMapData->mWidth + x] = static_cast<char> (MapData::TerrainType::POSSIBLE);
					mMapData->mColorMap[x][y] = ::DrawUtil::Colour::TILE_WHITE;
				} break;

				case MapData::TerrainType::POSSIBLE:
				{
					mMapData->mMap[y * mMapData->mWidth + x] = static_cast<char> (MapData::TerrainType::IMPOSSIBLE);
					mMapData->mColorMap[x][y] = ::DrawUtil::Colour::TILE_BLACK;
				} break;

				default:
					break;
			}
		}
	}
}
