


#ifndef MAP_H
#define MAP_H

// Forward declaration of MapData
namespace pathFinder
{
	struct MapData;
}

namespace pathFinder
{
	class Map;
}

class pathFinder::Map
{

public:

	// Constructor
	Map(int width, int height, char* map);

	// Destructor
	~Map();

public:

	MapData* getMapData();

private:

	void init(char* map);

private:

	MapData* mMapData;

};

#endif // !MAP_H

