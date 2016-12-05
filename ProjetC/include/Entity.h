#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED

#include<cstdio>
#include<string>
#define BASIC_LIFE 100
#define BASIC_MANA 100

using namespace std;

class Entity {

    protected:

        int m_x;
        int m_y;
        int m_hp;
        int m_ad;   //Attack Dmg
        int m_md;   //Magio Dmg
        int m_def;
        int m_mana;

    public :

        Entity(int x=0, int y=0, int z=BASIC_LIFE, int ad=0,int md=0, int mana=BASIC_MANA, int def=0);
        int     getX();
        int     getY();
};

class Player : public Entity {

	private:

	public :

        void attack();

        void defend();

        void run();

};

#endif
