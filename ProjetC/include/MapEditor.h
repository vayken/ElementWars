#ifndef MAPEDITOR_H
#define MAPEDITOR_H
#include "Configuration.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Npc.h"


class MapEditor
{
    public:
        MapEditor(sf::RenderWindow& window);
        MapEditor(sf::RenderWindow& window, int x, int y);
        void    setMap(int x, int y);
        void    setMap(int x, int y, int linkedId);
        void    saveConfig();
        void    saveNpcConfig();
        void    loadConfig(int x, int y);
        void    loadConfig(int x, int y, int linkedId);
        void    loadNpcConfig(int x, int y);
        void    displayMapInfo();
        void    drawNpcs();

        void    run();
        void    update();
        void    processEvents();
        void    handleKeyboardInput(sf::Keyboard::Key key, bool isPressed);
        void    loadTextures();
        Tile    getTileWithMouse(int mouseX, int mouseY);
        void    handlePanelMouseButton(int mouseX, int mouseY);
        void    handleMapMouseButton(int mouseX, int mouseY, bool rightClick);
        void    loadRightPanel();
        void    loadNpcPanel();
        void    addNpc(int npcId, int x, int y, int linkId);
        void    removeNpc(int x, int y);
        void    resetNpcArray();
        //void    split(const string& s, char c, vector<string>& v);
    protected:
    private:
        sf::RenderWindow&    m_gameWindow;
        Map m_currentMap;
        sf::Texture m_groundTextures[SPRITE_AMOUNT];
        sf::Texture m_objectTextures[OBJECT_SPRITE_AMOUNT];
        sf::Texture m_npcTextures[NPC_SPRITE_AMOUNT];
        sf::Texture m_loadingScreen;
        sf::RectangleShape cursorLeft;
        sf::RectangleShape cursorRight;
        sf::RectangleShape cursorBottom;
        int m_sprites_panel_pos_x[SPRITE_AMOUNT];
        int m_sprites_panel_pos_y[SPRITE_AMOUNT];
        int m_currentGraphicId = 10;
        int m_currentObjectId = 1;
        int m_currentPhysicId = 1;
        int m_currentNpcId = 0;
        int m_currentSpriteTab = 0;
        bool exited = false;
        Npc npc_array[MAP_SIZE * MAP_SIZE];
};

#endif // MAPEDITOR_H
