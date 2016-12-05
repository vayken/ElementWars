#ifndef WORLD_H
#define WORLD_H
#define WORLD_SIZE 30
#include "Map.h"

class World
{
    public:
        World();
        Map getMap(int x, int y);
    protected:
    private:
        Map m_maps[WORLD_SIZE][WORLD_SIZE];
};

#endif // WORLD_H
