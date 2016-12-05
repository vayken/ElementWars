#include "CombatAttack.h"

static map<string, CombatAttack> attackList;

CombatAttack::CombatAttack()
{
}
CombatAttack::CombatAttack(string name, string type, float power, int accuracy, int points)
{
    attackName = name;
    attackType = type;
    attackPower = power;
    attackAccuracy = accuracy;
    attackPoints = points;
    attackMessageOnHit = "";
}
CombatAttack::CombatAttack(string name, string type, float power, int accuracy, int points, string messageOnHit)
{
    attackName = name;
    attackType = type;
    attackPower = power;
    attackAccuracy = accuracy;
    attackPoints = points;
    attackMessageOnHit = messageOnHit;
}

CombatAttack::CombatAttack(string name)
{
    attackName = name;
    attackType = attackList[name].getAttackType();
    attackPower = attackList[name].getAttackPower();
    attackAccuracy = attackList[name].getAttackAccuracy();
    attackPoints = attackList[name].getAttackPoints();
    attackMessageOnHit = attackList[name].getOnHitMessage();
}

void CombatAttack::initializeAttackList(){

    attackList["Aquarmure"] = CombatAttack("Aquarmure", "eau", 1.7, 100, 20, "Une armure d'eau vous entoure !");
    attackList["Tsunami"] = CombatAttack("Tsunami", "eau", 90, 100, 25);
    attackList["Océan"] = CombatAttack("Océan", "eau", 1.6, 100, 35, "Vous dressez un océan qui vous renforce !");
    attackList["EauDeVie"] = CombatAttack("EauDeVie", "eau", -125, 100, 35, "Vous vous soignez de vos blessures !");

    attackList["Feu X"] = CombatAttack("Feu X", "", 30, 100, 25);
    attackList["Lave X"] = CombatAttack("Lave X", "", 70, 100, 25);
    attackList["Armure X"] = CombatAttack("Armure X", "", 1.6, 100, 35, "Vous dressez une armure qui vous renforce !");
    attackList["Soin X"] = CombatAttack("Soin", "", -125, 100, 35, "Vous vous soignez de vos blessures !");

    attackList["Terre X"] = CombatAttack("Terre X", "", 30, 100, 25);
    attackList["Seisme"] = CombatAttack("Seisme", "", 70, 100, 25);

    attackList["Air X"] = CombatAttack("Air X", "", 30, 100, 20);
    attackList["Tornade X"] = CombatAttack("Tornade X", "", 70, 100, 25);

}

string CombatAttack::getAttackName(){
    return attackName;
}
string CombatAttack::getAttackType(){
    return attackType;
}
float CombatAttack::getAttackPower(){
    return attackPower;
}
int CombatAttack::getAttackAccuracy(){
    return attackAccuracy;
}
int CombatAttack::getAttackPoints(){
    return attackPoints;
}
string CombatAttack::getOnHitMessage(){
    return attackMessageOnHit;
}

void CombatAttack::setAttackName(string name){
    attackName = name;
}
