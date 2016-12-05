#ifndef TILE_H
#define TILE_H
#include "GraphicParam.h"
#include "PhysicParam.h"
#include "Configuration.h"

class Tile
{
    public:
        Tile();
        Tile(int x, int y, GraphicParam graphicParam, PhysicParam physicParam, int linkId, int secondLevelObject, int thirdLevelObject);
        GraphicParam getGraphicParam();
        PhysicParam getPhysicParam();
        int getLinkId();
        int getSecondLevelObject();
        int getThirdLevelObject();
    protected:
    private:
        int m_x,m_y;
        GraphicParam m_graphicParam;
        PhysicParam m_physicParam;
        int m_linkId;
        int m_secondLevelObject;
        int m_thirdLevelObject;
};

#endif // TILE_H
