#include "Entity.h"

/***************** GENERIC ENTITY **************************/
Entity::Entity(int x, int y, int z, int ad,int md, int mana, int def){
            m_x = x;
            m_y = y;
            m_hp = z;
            m_ad = ad;
            m_md = md;
            m_def = def;
            m_mana = mana;
}

int Entity::getX(){
    return m_x;
}

int Entity::getY(){
    return m_y;
}


/***************** PLAYER CHARACTER **************************/



/***************** NON PLAYING CHARACTER *********************/
