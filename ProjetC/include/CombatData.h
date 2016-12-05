#ifndef COMBATDATA_H
#define COMBATDATA_H
#include <string>
#include "CombatAttack.h"

using namespace std;

class CombatData
{
    public:
        CombatData();
        CombatData(string name, string path, int hitpoints, int level);
        static CombatData getCombatData(string fighterName);
        string  getFighterName();
        string  getFighterSprite();
        void  setFighterName(string name);
        void  setFighterSprite(string path);
        CombatAttack getAttack(int i);
        void    setAttacks(string attackTab[4]);
        int     getHitPoints();
        int     getCurrentHitPoints();
        int     getLevel();
        int     getAttack();
        int     getDefense();
        void    setHitPoints(int hp);
        void    setCurrentHitPoints(int hp);
        void    setLevel(int lv);
        void    setAttack(int n);
        void    setDefense(int n);
    protected:
    private:
        string fighterName;
        string fighterSpritePath;
        int fighterHitpoints;
        int currentHitPoints;
        int fighterLevel;
        int attack;
        int defense;
        CombatAttack attacks[4];

};

#endif // COMBATDATA_H
