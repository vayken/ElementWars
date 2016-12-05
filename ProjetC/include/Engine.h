#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include "Configuration.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>
#include "Map.h"
#include "Combat.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Npc.h"

using namespace std;

class Engine{
    public:
        Engine(sf::RenderWindow& window);
        void    run();
        void    saveWorld();
        void    loadWorld();
        void    quit();
        void    reset();
        void    update(sf::Clock deltaTime);
        void    render();
        void    processEvents();
        void    handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);

        void    setMap(int x, int y, int linkedId = -1);
        void    loadConfig(int x, int y, int linkedId = -1);
        void    loadTextures();
        void    loadRightPanel();
        void    split(const string& s, char c, vector<string>& v);
        void    updateBackground();
        void    endAnimation(sf::Clock deltaTime);
        void    borderControl();
        bool    isTraversable(sf::Vector2f pos);
        void    resetNpcArray();
        void    loadNpcConfig(int x, int y);
        void    drawNpcs();
        void    fightController(sf::Clock deltaTime);
        void    save();
        void    load();
        void    transition();
        void    pause();
        ~Engine();
    private:
        sf::RenderWindow&    m_gameWindow;
        sf::Sprite    m_Player;


        Map m_currentMap;
        sf::Texture m_groundTextures[SPRITE_AMOUNT];
        sf::Texture m_objectTextures[OBJECT_SPRITE_AMOUNT];
        sf::Texture m_npcTextures[NPC_SPRITE_AMOUNT];

        bool m_run = true;
        int m_sprites_panel_pos_x[SPRITE_AMOUNT];
        int m_sprites_panel_pos_y[SPRITE_AMOUNT];
        int m_mapX=1;
        int m_mapY=1;
        int m_movement = 0;
        bool m_animationEnded = false;
        int randFight=0;

        Npc npc_array[MAP_SIZE * MAP_SIZE];
        int m_animationCount=0;
        sf::Texture m_playerTextures[12];

        /*** TEMP ****/
        sf::Vector2f position;
        sf::Vector2f savedPosition;
        sf::Vector2f velocity;

        float maxspeed = 1.5f;
        float accel = 1.5f;
        float decel = 0.01f;
        sf::Vector2f m_lastSpeed;
        sf::Music music;

        //GametStat, SoundEngine
};




#endif // ENGINE_H_INCLUDED
