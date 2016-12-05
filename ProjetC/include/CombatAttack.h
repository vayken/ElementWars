#ifndef COMBATATTACK_H
#define COMBATATTACK_H
#include <string>
#include <map>

using namespace std;


class CombatAttack
{
    public:
        CombatAttack();
        CombatAttack(string name);
        CombatAttack(string name, string type, float power, int accuracy, int points);
        CombatAttack(string name, string type, float power, int accuracy, int points, string messageOnHit);
        string  getAttackName();
        string  getAttackType();
        float  getAttackPower();
        string  getOnHitMessage();
        int     getAttackAccuracy();
        int     getAttackPoints();
        void    setAttackName(string name);
        static void    initializeAttackList();
    protected:
    private:
        string attackName;
        string attackType;
        float attackPower;
        int attackAccuracy;
        int attackPoints;
        string attackMessageOnHit;

};

#endif // COMBATATTACK_H
