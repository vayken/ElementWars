#ifndef COMBAT_H
#define COMBAT_H
#include "Configuration.h"
#include <SFML/Graphics.hpp>
#include "CombatData.h"
#include "CombatAttack.h"


class Combat
{
    public:
        Combat(sf::RenderWindow& window);

        void    run();
        void    update();
        void    processEvents();
        void    loadTextures();
        void    loadFighterTextures();
        void    handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);
        void    updateCombatState();
        void    drawSingleMenu();
        void    drawDoubleMenu();
        void    switchCombatState();
        void    endCombat();
        void    setPlayerAttacks();
        void    setOpponentNextAttack();
        void    loadCombatProperties();
        void    updateCombatInfo();
        int     calculateDamage(CombatData attacker, CombatData opponent, bool playerIsAttacker);

    protected:
    private:
        sf::RenderWindow    &m_gameWindow;
        sf::Texture combat_screen;
        sf::Texture player_fighter;
        sf::Texture ennemy_fighter;
        sf::Texture arrow1;
        sf::Texture arrow2;
        sf::Texture menu;
        sf::Texture menu1;
        sf::Texture menu2;
        sf::Texture myHp;
        sf::Texture theirHp;
        sf::Font myFont;
        int combatState;
        int optionChoice;
        int attackChoice;
        int fighterChoice;
        CombatAttack playerAttackUsed;
        CombatAttack opponentAttackUsed;
        CombatData playerCombatData;
        CombatData opponentCombatData;
        bool opponentAttacked = false;
        int opponentDamagePending;
        int playerDamagePending;
        bool combatFinished = false;

};

#endif // COMBAT_H
