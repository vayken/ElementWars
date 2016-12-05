#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include "Entity.h"
#include<cstdio>
#include<string>
#define BASIC_LIFE 100
#define BASIC_MANA 100

class Npc : public Entity {
    public:
        Npc();
        Npc(int npcId, int x, int y, int linkId);
        int     getNpcId();
        int     getLinkId();
    protected:
    private:
	    int m_npcId;
	    int m_linkId;
};
#endif
