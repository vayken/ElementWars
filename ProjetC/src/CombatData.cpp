#include "CombatData.h"

CombatData::CombatData(string name, string path, int hitpoints, int level)
{
    fighterName = name;
    fighterSpritePath = path;
    fighterHitpoints = hitpoints;
    fighterLevel = level;
    //todo entity
}

CombatData::CombatData()
{
}

void CombatData::setAttacks(string attackTab[4]){
    for(int i = 0; i < 4; i++){
        attacks[i] = CombatAttack(attackTab[i]);
    }
}

CombatData CombatData::getCombatData(string fighterName)
{
    CombatData data = CombatData();
    data.setFighterName(fighterName);
    data.setHitPoints(150);
    data.setCurrentHitPoints(150);
    data.setLevel(100);
    data.setAttack(250);
    data.setDefense(500);

    if(fighterName == "Avatar Aang"){
        data.setFighterSprite("sprites/combat/aang.png");
    } else if(fighterName == "Avatar Korra"){
        data.setFighterSprite("sprites/combat/korra.png");
    } else if(fighterName == "King Zuko"){
        data.setFighterSprite("sprites/combat/zuko.png");
    } else if(fighterName == "Master Toph"){
        data.setFighterSprite("sprites/combat/toph.png");
    } else if(fighterName == "Firebender Azula"){
        data.setFighterSprite("sprites/combat/ennemy1.png");
    } else if(fighterName == "Airbender Jinora"){
        data.setFighterSprite("sprites/combat/ennemy2.png");
    }
    return data;
}

CombatAttack CombatData::getAttack(int i){
    return attacks[i];
}

string CombatData::getFighterName(){
    return fighterName;
}

string CombatData::getFighterSprite(){
    return fighterSpritePath;
}

int CombatData::getHitPoints(){
    return fighterHitpoints;
}
int CombatData::getCurrentHitPoints(){
    return currentHitPoints;
}

int CombatData::getLevel(){
    return fighterLevel;
}
int CombatData::getAttack(){
    return attack;
}
int CombatData::getDefense(){
    return defense;
}

void CombatData::setHitPoints(int hp){
    fighterHitpoints = hp;
}
void CombatData::setCurrentHitPoints(int hp){
    currentHitPoints = hp;
}
void CombatData::setLevel(int lv){
    fighterLevel = lv;
}
void CombatData::setAttack(int n){
    attack = n;
}
void CombatData::setDefense(int n){
    defense = n;
}

void CombatData::setFighterName(string name){
    fighterName = name;
}

void CombatData::setFighterSprite(string path){
    fighterSpritePath = path;
}
