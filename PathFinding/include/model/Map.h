


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
	Map(int width, int height, const char* map);

	// Destructor
	~Map();

public:

	MapData* getMapData() const;

private:

	void init(const char* map) const;

private:

	MapData* mMapData;

};

#endif // !MAP_H

