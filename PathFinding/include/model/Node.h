


#ifndef NODE_H
#define NODE_H

#include "../../include/util/DrawUtil.h"

namespace pathFinder
{
	struct Node;
	struct NodeGreater;
}

struct pathFinder::Node
{
	// Constructor
	Node(int x, int y, Node* parent = nullptr)
		: mX(x)
		, mY(y)
		, mParent(parent)
		, mFScore(0)
		, isProcessed(false)
		, isInOpenSet(false)
	{

	}

	void setParent(Node* const parent)
	{
		mParent = parent;
	}

	bool operator==(const Node& rhs) const
	{
		return mX == rhs.mX && mY == rhs.mY;
	}

	bool operator!=(const Node& rhs) const
	{
		return !(*this == rhs);
	}

	int mFScore; // Score which describes Node
	int mX;
	int mY;
	::DrawUtil::Colour mColour;
	bool isProcessed;
	bool isInOpenSet;  // OpenSet is a set where all the possible visitable locations are stored
	Node* mParent;
};

struct pathFinder::NodeGreater
{
	bool operator()(const Node* lhs, const Node* rhs)
	{
		return lhs->mFScore > rhs->mFScore;
	}
};

#endif // !NODE_H

