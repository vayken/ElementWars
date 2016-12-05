#include "Map.h"
#include <iostream>


using namespace std;

Map::Map()
{

}

Map::Map(int x, int y)
{
    this->m_x = x;
    this->m_y = y;
    this->m_linkedId = -1;
    for(int i = 0; i < MAP_SIZE; i++)
        for(int j = 0; j < MAP_SIZE; j++){

           m_tiles[i][j] = Tile(i, j, GraphicParam(defaultMap[i][j]),
                                   PhysicParam(DEFAULT_PHYSICAL_PARAM), -1, -1, -1);
        }

}
Map::Map(int x, int y, int linkedId)
{
    this->m_x = x;
    this->m_y = y;
    this->m_linkedId = linkedId;
    for(int i = 0; i < MAP_SIZE; i++)
        for(int j = 0; j < MAP_SIZE; j++){

           m_tiles[i][j] = Tile(i, j, GraphicParam(linkedId == -1 ? defaultMap[i][j] : defaultBuilding[i][j]),
                                   m_linkedId != -1 && defaultBuilding[i][j] != 84 ? (defaultBuilding[i][j] == 17 || defaultBuilding[i][j] == 18) ? PhysicParam(3) : PhysicParam(0) : PhysicParam(DEFAULT_PHYSICAL_PARAM), -1, -1, -1);
        }

}

int Map::getX()
{
    return m_x;
}
int Map::getY()
{
    return m_y;
}
int Map::getLinkedId()
{
    return m_linkedId;
}

void Map::modifyTile(int x, int y, int graphicId, int physicId, int linkId, int secondObject, int thirdObject)
{
   m_tiles[x][y] = Tile(x, y, graphicId, physicId, linkId, secondObject, thirdObject);
}


Tile Map::getTile(int x, int y){
    return m_tiles[x][y];
}
