


#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <queue>
#include "../../include/model/Node.h"

// Forward Declarations
namespace pathFinder
{
	struct MapData;
}

namespace pathFinder
{
	class PathFinder;
}

class pathFinder::PathFinder
{

public:

	// Constructor
	PathFinder(MapData* mapData, int startX, int startY, int targetX, int targetY);

public:

	void updateCurrentNode();
	void processAdjacent();
	void findShortestPathTile();
	void onEvent();
	bool isRunning() const;
	bool isProcessingAdjacent() const;
	bool isTargetFound() const;
	bool isPathConstucting() const;
	bool isCreatingMap() const;

private:

	int computeGScore(const Node* const parent) const; 	// How much energy it takes to reach the node from the start
	int computeHScore(const Node* const node) const; // Heuristic score estimating how much energy it may take to reach the target
	int computeFScore(const Node* const node) const; // Score that describes Node
	void updateExistingNodeScore(Node* node);
	void createNewNode(Node** node, int x, int y);
	void addToOpenSet(Node* node);
	void mousePress(SDL_MouseButtonEvent& b);

private:

	int mStartX;
	int mStartY;
	int mTargetX;
	int mTargetY;
	MapData* mMapData;
	Node* mCurrentNode;
	bool mIsRunning; // Flag indicating that the path is not yet found
	bool mIsProcessingAdjacent; // Flag indicating that there are adjacent Nodes to process
	bool mIsTargetFound; // Flag indicating if the target is found
	bool mIsPathConstructing; // Flag indicating if the shortest path is still beeing constructed
	bool mIsCreatingMap; // Flag indicating if the user is creating map
	std::priority_queue<Node*, std::vector<Node*>, NodeGreater> openSet;

};

#endif // !PATHFINDER_H
