#include "Npc.h"

Npc::Npc()
{
    this->m_npcId = 0;
    this->m_x = 0;
    this->m_y = 0;
    this->m_linkId = -1;
}

Npc::Npc(int npcId, int x, int y, int linkId)
{
    this->m_npcId = npcId;
    this->m_x = x;
    this->m_y = y;
    this->m_linkId = linkId;
}

int Npc::getLinkId(){
    return m_linkId;
}

int Npc::getNpcId(){
    return m_npcId;
}


