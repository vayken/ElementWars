#include "Combat.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <SFML/Audio.hpp>
using namespace std;


Combat::Combat(sf::RenderWindow& window)
 : m_gameWindow(window)
{

    combatState = 0;
    optionChoice = attackChoice = fighterChoice = 1;
    loadCombatProperties();
    loadTextures();
    run();
}

void Combat::loadCombatProperties(){
    CombatAttack::initializeAttackList();
    playerCombatData = CombatData::getCombatData("Avatar Aang");//todo put it in entity
    opponentCombatData = CombatData::getCombatData("Firebender Azula");//todo randomize
    string opponentAttacksList[4] = {"Feu X", "Armure X", "Lave X", "Soin X"};
    setPlayerAttacks();
    opponentCombatData.setAttacks(opponentAttacksList);
}

void Combat::updateCombatInfo(){
    sf::Sprite myHpSprite = sf::Sprite(myHp);
    sf::Sprite theirHpSprite = sf::Sprite(theirHp);
    myHpSprite.setPosition(278, 300);
    theirHpSprite.setPosition(187, 86);
    m_gameWindow.draw(myHpSprite);
    m_gameWindow.draw(theirHpSprite);

    sf::Text text;
    text.setFont(myFont);
    text.setCharacterSize(15);
    text.setStyle(sf::Text::Regular);
    text.setColor(sf::Color::Black);

    text.setString(opponentCombatData.getFighterName());
    text.setPosition(195, 90);
    m_gameWindow.draw(text);


    ostringstream oss1;
    oss1 << "Lv" << opponentCombatData.getLevel();
    string level1 = oss1.str();
    text.setString(level1);
    text.setPosition(324, 90);
    m_gameWindow.draw(text);

    text.setCharacterSize(20);

    text.setString(playerCombatData.getFighterName());
    text.setPosition(312, 305);
    m_gameWindow.draw(text);

    ostringstream oss2;
    oss2 << "Lv" << playerCombatData.getLevel();
    string level2 = oss2.str();
    text.setString(level2);
    text.setPosition(447, 305);
    m_gameWindow.draw(text);

    ostringstream oss3;
    oss3 << playerCombatData.getCurrentHitPoints() << "/" << playerCombatData.getHitPoints();
    string hp = oss3.str();
    text.setString(hp);
    text.setPosition(425, 345);
    m_gameWindow.draw(text);

    //barre de points de vie
    sf::RectangleShape opponentHp;
    int value = (opponentCombatData.getCurrentHitPoints() * 100) / opponentCombatData.getHitPoints();
    int fullSize = 92;
    opponentHp.setPosition(268, 116);
    opponentHp.setFillColor(value > 50 ? sf::Color(110, 218, 163) : sf::Color::Red);
    opponentHp.setSize(sf::Vector2f(value <= 0 ? 0 : value * fullSize / 100, 5));
    m_gameWindow.draw(opponentHp);

    sf::RectangleShape playerHp;
    value = (playerCombatData.getCurrentHitPoints() * 100) / playerCombatData.getHitPoints();
    playerHp.setPosition(390, 338);
    playerHp.setFillColor(value > 50 ? sf::Color(110, 218, 163) : sf::Color::Red);
    fullSize = 107;
    playerHp.setSize(sf::Vector2f(value <= 0 ? 0 : value * fullSize / 100, 7));
    m_gameWindow.draw(playerHp);
}

void Combat::setPlayerAttacks(){
    string playerAttacksList[4];
    if(playerCombatData.getFighterName() == "Avatar Aang"){
        playerAttacksList[0] = "Air X";
        playerAttacksList[1] = "Armure X";
        playerAttacksList[2] = "Tornade X";
        playerAttacksList[3] = "Soin X";
    } else if(playerCombatData.getFighterName() == "Avatar Korra"){
        playerAttacksList[0] = "Tsunami";
        playerAttacksList[1] = "Aquarmure";
        playerAttacksList[2] = "Océan";
        playerAttacksList[3] = "EauDeVie";
    } else if(playerCombatData.getFighterName() == "King Zuko"){
        playerAttacksList[0] = "Feu X";
        playerAttacksList[1] = "Armure X";
        playerAttacksList[2] = "Lave X";
        playerAttacksList[3] = "Soin X";

    } else {
        playerAttacksList[0] = "Terre X";
        playerAttacksList[1] = "Armure X";
        playerAttacksList[2] = "Seisme X";
        playerAttacksList[3] = "Soin X";
    }
    playerCombatData.setAttacks(playerAttacksList);
}

void Combat::loadFighterTextures(){
    if(!player_fighter.loadFromFile(playerCombatData.getFighterSprite()))
        cout << "Error loading load button sprite " << endl;
    if(!ennemy_fighter.loadFromFile(opponentCombatData.getFighterSprite()))
        cout << "Error loading load button sprite " << endl;
}

void Combat::loadTextures(){
    loadFighterTextures();
    if(!combat_screen.loadFromFile("sprites/combat/battle_background.png"))
        cout << "Error loading load button sprite " << endl;
    if (!myFont.loadFromFile("sprites/fonts/biko.ttf"))
        cout << "Couldn't load font biko regular" << endl;
    if (!arrow1.loadFromFile("sprites/combat/arrow1.png"))
        cout << "Couldn't load sprite arrow" << endl;
    if (!arrow2.loadFromFile("sprites/combat/arrow2.png"))
        cout << "Couldn't load sprite arrow" << endl;
    if (!menu.loadFromFile("sprites/combat/menu.png"))
        cout << "Couldn't load sprite menu" << endl;
    if (!menu1.loadFromFile("sprites/combat/menu1.png"))
        cout << "Couldn't load sprite menu" << endl;
    if (!menu2.loadFromFile("sprites/combat/menu2.png"))
        cout << "Couldn't load sprite menu" << endl;
    if (!myHp.loadFromFile("sprites/combat/myhp.png"))
        cout << "Couldn't load sprite menu" << endl;
    if (!theirHp.loadFromFile("sprites/combat/hp.png"))
        cout << "Couldn't load sprite menu" << endl;

}

void Combat::run(){
    update();

	sf::Music music;

	if (!music.openFromFile("soundtrack/wavfiles/Fight.wav"))
	{
		std::cout << "ERROR" << std::endl;
	}
	music.setLoop(true);
    music.setVolume(20);
	music.play();
    while(m_gameWindow.isOpen() && !combatFinished){
        processEvents();
    }
}

void Combat::drawSingleMenu(){
    sf::Sprite menuSprite = sf::Sprite(menu);
    menuSprite.setPosition(0,392);
    m_gameWindow.draw(menuSprite);

    sf::Sprite arrow2Sprite = sf::Sprite(arrow2);
    arrow2Sprite.setPosition(527,467);
    m_gameWindow.draw(arrow2Sprite);
}

void Combat::drawDoubleMenu(){

    sf::Sprite menu1Sprite = sf::Sprite(menu1);
    menu1Sprite.setPosition(0,392);
    m_gameWindow.draw(menu1Sprite);

    sf::Sprite menu2Sprite = sf::Sprite(menu2);
    menu2Sprite.setPosition(354,392);
    m_gameWindow.draw(menu2Sprite);

}

void Combat::updateCombatState(){

    sf::Text text;
    text.setFont(myFont);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Regular);
    text.setColor(sf::Color::White);
    int counter = 0;
    string fighters[4] = {"Aang", "Korra", "Zuko", "Toph"};
    sf::Sprite arrow1Sprite = sf::Sprite(arrow1);
    switch(combatState){
        case 0://entré en combat
            drawSingleMenu();
            text.setString("Un maître d'élément voudrai vous affronter");
            text.setPosition(75, 425);
            m_gameWindow.draw(text);
            break;

        case 1://choix actions
            drawDoubleMenu();
            text.setString("Quelle action");
            text.setPosition(25, 420);
            m_gameWindow.draw(text);
            text.setString("va faire " + playerCombatData.getFighterName());
            text.setPosition(25, 440);
            m_gameWindow.draw(text);


            arrow1Sprite.setPosition(optionChoice == 1 || optionChoice == 3 ? 368 : 472,
                                     optionChoice == 1 || optionChoice == 2 ? 427 : 455);
            m_gameWindow.draw(arrow1Sprite);

            text.setString("Attaquer");
            text.setPosition(381, 418);
            m_gameWindow.draw(text);
            text.setString("Changer");
            text.setPosition(485, 418);
            m_gameWindow.draw(text);
            text.setString("Objet");
            text.setPosition(381, 448);
            m_gameWindow.draw(text);
            text.setString("Fuir");
            text.setPosition(505, 448);
            m_gameWindow.draw(text);
            break;

        case 2://todo choix attaques
            drawDoubleMenu();
            for(int i = 0; i < 4; i++){
                text.setString(playerCombatData.getAttack(i).getAttackName());
                int firstX = 331 / 4 - text.getLocalBounds().width / 2 + 11;
                int secondX = ((331 / 4) * 3 - text.getLocalBounds().width / 2) + 11;
                int firstY = 95 / 4 - text.getLocalBounds().height / 2 + 402;
                int secondY = ((95 / 3) * 2 - text.getLocalBounds().height / 2) + 402;
                int x = i == 0 || i == 2 ? firstX : secondX;
                int y = i == 0 || i == 1 ? firstY : secondY;
                text.setPosition(x, y);
                m_gameWindow.draw(text);
                if(attackChoice - 1 == i){
                    arrow1Sprite.setPosition((i == 0 || i == 2 ? 0 : 331 / 2) + 30, y + 9);
                    m_gameWindow.draw(arrow1Sprite);
                }
            }

            break;
        case 3://attaque de notre personnage
            drawSingleMenu();
            text.setString(playerCombatData.getFighterName() + " utilise l'attaque ");
            text.setPosition(142, 415);
            m_gameWindow.draw(text);
            text.setString(playerAttackUsed.getAttackName());
            text.setColor(sf::Color::Black);
            text.setPosition((539 - text.getLocalBounds().width) / 2, 445);
            m_gameWindow.draw(text);
            break;
        case 4://actualisation des points de vies/animation
            drawSingleMenu();
            playerCombatData.setCurrentHitPoints(playerCombatData.getCurrentHitPoints() - playerDamagePending);
            opponentCombatData.setCurrentHitPoints(opponentCombatData.getCurrentHitPoints() - opponentDamagePending);
            playerDamagePending = 0;
            opponentDamagePending = 0;
            break;
        case 5://reponse adversaire
            drawSingleMenu();
            text.setString(opponentCombatData.getFighterName() + " ennemi utilise l'attaque ");
            text.setPosition((539 - text.getLocalBounds().width) / 2, 415);
            m_gameWindow.draw(text);
            text.setString(opponentAttackUsed.getAttackName());
            text.setColor(sf::Color::Black);
            text.setPosition((539 - text.getLocalBounds().width) / 2, 445);
            m_gameWindow.draw(text);
            break;
        case 6 : //death of ennemy
            break;
        case 7 : //death of player
            break;
        case 8 : //attack message for special effects
            drawSingleMenu();
            text.setString(playerAttackUsed.getOnHitMessage());
            text.setPosition((539 - text.getLocalBounds().width) / 2, 415);
            m_gameWindow.draw(text);
            break;
        case 9://choix du combatant
            drawDoubleMenu();
            text.setString("Quelle combattant");
            text.setPosition(25, 420);
            m_gameWindow.draw(text);
            text.setString("voulez vous choisir ?");
            text.setPosition(25, 450);
            m_gameWindow.draw(text);


            arrow1Sprite.setPosition(fighterChoice == 1 || fighterChoice == 3 ? 368 : 472,
                                     fighterChoice == 1 || fighterChoice == 2 ? 427 : 455);
            m_gameWindow.draw(arrow1Sprite);
            for(int i = 0; i < 4; i++){
                if(playerCombatData.getFighterName().find(fighters[i]) != string::npos)
                    continue;
                text.setString(fighters[i]);
                text.setPosition(counter == 0 || counter == 2 ? 381 : 485, counter == 0 || counter == 1 ? 418 : 448);
                m_gameWindow.draw(text);
                counter++;
            }
            text.setString("Retour");
            text.setPosition(485, 448);
            m_gameWindow.draw(text);
            break;
        case 10://item list
            drawSingleMenu();
            text.setString("Le système d'objet n'est pas encore implémenté!");
            text.setPosition(75, 425);
            m_gameWindow.draw(text);
            break;
        case 11://end combat (player death)
            drawSingleMenu();
            text.setString("Vous êtes mort...");
            text.setPosition(75, 425);
            m_gameWindow.draw(text);
            break;
        case 12://end combat ennemy seath
            drawSingleMenu();
            text.setString("L'ennemi est mort !");
            text.setPosition(75, 425);
            m_gameWindow.draw(text);
            break;
        case 13://end combat flee
            drawSingleMenu();
            text.setString("Vous prenez la fuite...");
            text.setPosition(75, 425);
            m_gameWindow.draw(text);
            break;
        case 14://changement combatant
            drawSingleMenu();
            text.setString("Vous changez de combattant !");
            text.setPosition(75, 425);
            m_gameWindow.draw(text);
            break;
        case 15://attack mesage
            drawSingleMenu();
            text.setString(playerAttackUsed.getOnHitMessage());
            text.setPosition(75, 425);
            m_gameWindow.draw(text);
            break;
    }
}

void Combat::update(){
    m_gameWindow.clear();
    sf::Sprite combatScreenSprite = sf::Sprite(combat_screen);
    combatScreenSprite.setPosition(0,0);
    m_gameWindow.draw(combatScreenSprite);

    sf::Sprite playerFighterSprite = sf::Sprite(player_fighter);
    playerFighterSprite.setPosition(18,152);
    m_gameWindow.draw(playerFighterSprite);

    sf::Sprite ennemyFighterSprite = sf::Sprite(ennemy_fighter);
    ennemyFighterSprite.setPosition(351,109);
    m_gameWindow.draw(ennemyFighterSprite);

    //les points de vies
    updateCombatInfo();

    updateCombatState();


    m_gameWindow.display();
}

void Combat::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed)
{
    if(!isPressed) return;
    int &choice = combatState == 1 ? optionChoice : combatState == 9 ? fighterChoice : attackChoice;
    switch(key){
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            choice = choice == 1 || choice == 3 ? choice + 1 : choice;
            break;
        case sf::Keyboard::Left:
        case sf::Keyboard::Q:
            choice = choice == 2 || choice == 4 ? choice - 1 : choice;
            break;
        case sf::Keyboard::Up:
        case sf::Keyboard::Z:
            choice = choice == 3 || choice == 4 ? choice - 2 : choice;
            break;
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            choice = choice == 1 || choice == 2 ? choice + 2 : choice;
            break;
        case sf::Keyboard::Space:
        case sf::Keyboard::Return:
            switchCombatState();
            break;
        case sf::Keyboard::Escape:
            //todo state back
            combatState = (combatState == 2 || combatState == 10 || combatState == 9) ? 1 : combatState;
            break;
        default:
            break;
    }
}

int Combat::calculateDamage(CombatData attacker, CombatData opponent, bool attackerIsPlayer){
    //int accuracy = attackerIsPlayer ? playerAttackUsed.getAttackAccuracy() : opponentAttackUsed.getAttackAccuracy();
    int power = attackerIsPlayer ? playerAttackUsed.getAttackPower() : opponentAttackUsed.getAttackPower();
    //a faire : les points d'attaque qui descendent pour pas que le combat dure indéfiniment
    if(power < 0){
        if(attackerIsPlayer)
            playerDamagePending = max(power, attacker.getCurrentHitPoints() - attacker.getHitPoints());
        else
            opponentDamagePending = max(power, attacker.getCurrentHitPoints() - attacker.getHitPoints());

        //attacker.setCurrentHitPoints(min(attacker.getCurrentHitPoints() - power, attacker.getHitPoints()));
        return 0;
    }

    int rand1 = rand() % 15 + 85;
    int rand2 = rand() % 100;
    bool critical = rand2 < 30;
    double level = (double)attacker.getLevel();
    level *= 2;
    level += 10;
    level /= 250;
    double attDefRatio = (double)attacker.getAttack() / (double)attacker.getDefense();
    level *= attDefRatio;
    level *= power;
    level += 2;
    double modifier = (critical ? 2 : 1) * ((double)rand1 / 100);

    return level * modifier;
}

void Combat::switchCombatState(){
    string fighters[4] = {"Avatar Aang", "Avatar Korra", "King Zuko", "Master Toph"};
    int counter = 0;
    switch(combatState){
    case 0:
        combatState = 1;
        break;
    case 1:
        combatState = optionChoice == 1 ? 2 : optionChoice == 2 ? 9 : optionChoice == 3 ? 10 : 13;
        break;
    case 2:
        combatState = 3;
        playerAttackUsed = playerCombatData.getAttack(attackChoice - 1);
        break;
    case 3://todo damages
        combatState = 4;
        opponentDamagePending = calculateDamage(playerCombatData, opponentCombatData, true);
        break;
    case 4:
        if(playerCombatData.getCurrentHitPoints() <= 0){
            combatState = 11;
        } else if(opponentCombatData.getCurrentHitPoints() <= 0){
            combatState = 12;
        } else {
            if(!opponentAttacked){
                combatState = playerAttackUsed.getOnHitMessage() != "" ? 15 : 5;
                setOpponentNextAttack();
            } else {
                combatState = 1;
                opponentAttacked = false;
            }
        }
        optionChoice = attackChoice = fighterChoice = 1;
        break;
    case 5://todo damages
        combatState = 4;
        playerDamagePending = calculateDamage(opponentCombatData, playerCombatData, false);
        break;
    case 8://effets spéciaux
        combatState = 4;
        break;
    case 9:
        combatState = fighterChoice == 4 ? 1 : 14;
        for(int i = 0; i < 4; i++){
            if(playerCombatData.getFighterName().find(fighters[i]) != string::npos)
                continue;
            if(fighterChoice - 1 == counter)
                playerCombatData = CombatData::getCombatData(fighters[i]);
            counter++;
        }
        setPlayerAttacks();
        loadFighterTextures();
        break;
    case 10://handle item list
        break;
    case 14:
        combatState = 5;
        setOpponentNextAttack();
        break;
    case 15:
        combatState = 5;
        break;


    default:
        endCombat();
    }
}

void Combat::setOpponentNextAttack(){
//todo
    opponentAttackUsed = opponentCombatData.getAttack(0);
    opponentAttacked = true;
}

void Combat::endCombat(){//based on current state
    //cout << "combat ended " << endl;
    combatFinished = true;
}

void Combat::processEvents(){
    sf::Event event;
    while(m_gameWindow.pollEvent(event)){
        switch(event.type) {
            case sf::Event::GainedFocus:
                update();
                break;
            case sf::Event::KeyPressed:
                handleKeyboardInput(event.key.code, true);
                update();
                break;
            case sf::Event::KeyReleased:
                handleKeyboardInput(event.key.code, false);
                update();
                break;
            case sf::Event::Closed:
                m_gameWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                update();
                break;
            default:
                break;
        }
    }
}
