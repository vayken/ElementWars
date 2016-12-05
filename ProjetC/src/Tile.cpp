#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(int x, int y, GraphicParam graphicParam, PhysicParam physicParam, int linkId, int secondLevelObject, int thirdLevelObject)
{
    this->m_x = x;
    this->m_y = y;
    this->m_graphicParam = graphicParam;
    this->m_physicParam = physicParam;
    this->m_linkId = linkId;
    this->m_secondLevelObject = secondLevelObject;
    this->m_thirdLevelObject = thirdLevelObject;
}


GraphicParam Tile::getGraphicParam()
{
    return m_graphicParam;
}

PhysicParam Tile::getPhysicParam()
{
    return m_physicParam;
}

int Tile::getLinkId()
{
    return m_linkId;
}

int Tile::getSecondLevelObject()
{
    return m_secondLevelObject;
}

int Tile::getThirdLevelObject()
{
    return m_thirdLevelObject;
}
