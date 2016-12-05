#include "World.h"

World::World()
{
    for(int i = 0; i < WORLD_SIZE; i++)
        for(int j = 0; j < WORLD_SIZE; j++)
            m_maps[i][j] = Map(i, j);
}

Map World::getMap(int x, int y)
{
    return m_maps[x][y];
}
