#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include <math.h>
#include "MapEditor.h"
#include <sys/types.h>
#include <dirent.h>

using namespace std;

MapEditor::MapEditor(sf::RenderWindow& window) : m_gameWindow(window){}

MapEditor::MapEditor(sf::RenderWindow& window, int x, int y)
: m_gameWindow(window)
{
    m_gameWindow.create(sf::VideoMode(WINDOWS_FINAL_SIZE_X, WINDOWS_FINAL_SIZE_Y), "Element Wars", sf::Style::Titlebar | sf::Style::Close);
    loadConfig(x, y);
    loadTextures();
    update();
    cout << "Chargement termine ! " << endl;
}


void MapEditor::run(){
    sf::Music music;

	if (!music.openFromFile("soundtrack/wavfiles/Indoors.wav"))
	{
		std::cout << "ERROR" << std::endl;
	}
	music.setLoop(true);
    music.setVolume(30);
	music.play();
    while(m_gameWindow.isOpen() && !exited){
        processEvents();
        //update();//todo
    }
}

void MapEditor::loadTextures(){
    for(int i = 0; i < SPRITE_AMOUNT; i++){
            ostringstream oss;
            oss << "sprites/Field/" << (i + 1) << ".png";
            string fileName = oss.str();
            if(!m_groundTextures[i].loadFromFile(fileName))
                cout << "Error loading sprite field number " << (i + 1) << endl;
    }
    for(int i = 0; i < OBJECT_SPRITE_AMOUNT; i++){
            ostringstream oss;
            oss << "sprites/Object/" << (i + 1) << ".png";
            string fileName = oss.str();
            if(!m_objectTextures[i].loadFromFile(fileName))
                cout << "Error loading sprite object number " << (i + 1) << endl;
    }
    for(int i = 0; i < NPC_SPRITE_AMOUNT; i++){
            ostringstream oss;
            oss << "sprites/npcs/" << (i) << ".png";
            string fileName = oss.str();
            if(!m_npcTextures[i].loadFromFile(fileName))
                cout << "Error loading sprite object number " << (i + 1) << endl;
    }
    if(!m_loadingScreen.loadFromFile("sprites/loading2.png"))
        cout << "Error loading sprite loading screen " << endl;
    //sets the cursor pointing toward the current sprite id
    cursorLeft.setSize(sf::Vector2f(32, 32));
    cursorLeft.setFillColor(sf::Color::Transparent);
    cursorLeft.setOutlineThickness(2);
    cursorLeft.setOutlineColor(sf::Color::Red);


    cursorRight.setSize(sf::Vector2f(RIGHT_PANEL_SIZE_X, RIGHT_PANEL_SIZE_Y));
    cursorRight.setFillColor(sf::Color::Transparent);
    cursorRight.setOutlineThickness(2);
    cursorRight.setOutlineColor(sf::Color::Blue);


    cursorBottom.setSize(sf::Vector2f(32, 32));
    cursorBottom.setFillColor(sf::Color::Transparent);
    cursorBottom.setOutlineThickness(2);
    cursorBottom.setOutlineColor(sf::Color::Green);

    //loading right panel


}

void MapEditor::loadRightPanel(){

    sf::Texture graphicSprites[6];
    for(int i = 0; i < PHYSIC_PROP_AMOUNT; i++){
        ostringstream oss1;
        oss1 << "sprites/physic/" << (i) << ".png";
        string fileName = oss1.str();
        if(!graphicSprites[i].loadFromFile(fileName))
            cout << "Error loading sprite physic number " << (i) << endl;

        sf::Sprite sprite = sf::Sprite(graphicSprites[i]);
        sprite.setPosition(WINDOWS_FINAL_SIZE_X - SPRITE_PANEL_WIDTH / 2, 20 + i * 60);
        m_gameWindow.draw(sprite);

    }
    sf::Texture save;
    if(!save.loadFromFile("sprites/save.png"))
        cout << "Error loading save button sprite " << endl;
    sf::Sprite saveSprite = sf::Sprite(save);
    saveSprite.setPosition(WINDOWS_FINAL_SIZE_X - SPRITE_PANEL_WIDTH / 2 + 16, 475);
    m_gameWindow.draw(saveSprite);

    sf::Texture load;
    if(!load.loadFromFile("sprites/load.png"))
        cout << "Error loading load button sprite " << endl;
    sf::Sprite loadSprite = sf::Sprite(load);
    loadSprite.setPosition(WINDOWS_FINAL_SIZE_X - SPRITE_PANEL_WIDTH / 2 + 140, 475);
    m_gameWindow.draw(loadSprite);

    sf::Texture clearTxt;
    if(!clearTxt.loadFromFile("sprites/clear.png"))
        cout << "Error loading clear button sprite " << endl;
    sf::Sprite clearSprite = sf::Sprite(clearTxt);
    clearSprite.setPosition(WINDOWS_FINAL_SIZE_X - SPRITE_PANEL_WIDTH / 2 + 264, 475);
    m_gameWindow.draw(clearSprite);

}

void MapEditor::processEvents(){
    sf::Event event;
    while(m_gameWindow.pollEvent(event)){
        switch(event.type) {
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
            case sf::Event::GainedFocus:
                update();
                break;
            case sf::Event::MouseButtonPressed:
                if((event.mouseButton.x < SPRITE_PANEL_WIDTH / 2 || event.mouseButton.x > WINDOWS_FINAL_SIZE_X - (SPRITE_PANEL_WIDTH / 2)) || (event.mouseButton.y < 10 || event.mouseButton.y > MAP_SIZE * TILE_SIZE + 10))
                    handlePanelMouseButton(event.mouseButton.x, event.mouseButton.y);
                else
                    handleMapMouseButton(event.mouseButton.x, event.mouseButton.y, event.mouseButton.button == sf::Mouse::Right);
                update();
                break;
            default:
                break;
        }
    }
}



void MapEditor::handlePanelMouseButton(int mouseX, int mouseY)
{
    if(m_currentSpriteTab <= ceil(SPRITE_AMOUNT / 91)){
        int startIndex = m_currentSpriteTab * 91;
        for(int i = startIndex; i < min(startIndex + 91, SPRITE_AMOUNT); i++){
            int realCounter = i - startIndex;
            if(mouseX > m_sprites_panel_pos_x[realCounter] && mouseX < m_sprites_panel_pos_x[realCounter] + TILE_SIZE
            && mouseY > m_sprites_panel_pos_y[realCounter] && mouseY < m_sprites_panel_pos_y[realCounter] + TILE_SIZE){
                m_currentGraphicId = i + 1;
            }
        }
    } else {
        double amnt = (double)SPRITE_AMOUNT / 91;
        int startIndex = (m_currentSpriteTab - ceil(amnt)) * 91;
        for(int i = startIndex; i < min(startIndex + 91, OBJECT_SPRITE_AMOUNT); i++){
            int realCounter = i - startIndex;
            if(mouseX > m_sprites_panel_pos_x[realCounter] && mouseX < m_sprites_panel_pos_x[realCounter] + TILE_SIZE
            && mouseY > m_sprites_panel_pos_y[realCounter] && mouseY < m_sprites_panel_pos_y[realCounter] + TILE_SIZE){
                m_currentObjectId = i + 1;
            }
        }
    }
    //right panel
    for(int i = 0; i < PHYSIC_PROP_AMOUNT; i++){
        if(mouseX > RIGHT_PANEL_MIN_X && mouseX < RIGHT_PANEL_MIN_X + RIGHT_PANEL_SIZE_X){
            if(mouseY > 24 + i * RIGHT_PANEL_SCALE && mouseY < 24 + i * RIGHT_PANEL_SCALE + RIGHT_PANEL_SIZE_Y){
                m_currentPhysicId = i;
            }
        }
    }
    //bottom pannel
    for(int i = 0; i < NPC_SPRITE_AMOUNT; i++){
    int startX = 20 + SPRITE_PANEL_WIDTH / 2;
    int startY = 20 + MAP_SIZE * TILE_SIZE;
        if(mouseX > startX + i * (TILE_SIZE + 5) && mouseX < startX + (i+1) * (TILE_SIZE + 5)
            && mouseY > startY && mouseY < startY + TILE_SIZE){
            m_currentNpcId = i;
        }
    }
    if(mouseX > 967 && mouseX < 1082 && mouseY > 475 && mouseY < 520){
        saveConfig();
        cout << "Map (" << m_currentMap.getX() << ", " << m_currentMap.getY() << ") saved ! " << endl;
    }
    if(mouseX > 1092 && mouseX < 1207 && mouseY > 475 && mouseY < 520){
        sf::Sprite sprite = sf::Sprite(m_loadingScreen);
        sprite.setPosition(0, 0);
        m_gameWindow.draw(sprite);
        m_gameWindow.display();
        int x, y;
        cout << "Initiation de la phase de chargement de map." << endl;
        cout << "Veuillez choisir la coordonnée X de la map a charger : " << endl;
        cin >> x;
        cout << endl;
        cout << "Veuillez choisir la coordonnée Y de la map a charger : " << endl;
        cin >> y;
        cout << endl;
        cout << "Chargement de la carte (" << x << ", " << y << ")..." << endl;
        loadConfig(x, y);
        update();
    }
    if(mouseX > 1215 && mouseX < 1324 && mouseY > 475 && mouseY < 520){
        m_currentMap = Map(m_currentMap.getX(), m_currentMap.getY());
        resetNpcArray();
    }

}

void MapEditor::handleMapMouseButton(int mouseX, int mouseY, bool rightClick)
{
    int y = (mouseX - SPRITE_PANEL_WIDTH / 2) / TILE_SIZE;
    int x = (mouseY - 10) / TILE_SIZE;

    if(rightClick){
        m_currentMap.modifyTile(x, y, m_currentMap.defaultMap[x][y], 1, -1, -1, -1);
        //removeNpc(y, x);
        resetNpcArray();
    } else {
        if(m_currentMap.getTile(x, y).getLinkId() != -1){
            loadConfig(m_currentMap.getX(), m_currentMap.getY(), m_currentMap.getTile(x, y).getLinkId());
            update();
            return;
        }
        if(x == 17 && (y == 8 || y == 9) && m_currentMap.getLinkedId()!=-1){
            loadConfig(m_currentMap.getX(), m_currentMap.getY(), -1);
            update();
            return;
        }
        //ajouter un npc est prioritaire sur les entités de la map, on ne peut pas placer de npc en meme
        //temps que l'on place un élément de map.
        if(m_currentNpcId != 0){
            addNpc(m_currentNpcId, y, x, m_currentMap.getLinkedId());
            return;
        }
        if(m_currentSpriteTab <= ceil(SPRITE_AMOUNT / 91)){

            if(m_currentPhysicId == 3){
                DIR *dp;
                int i = 0;
                struct dirent *ep;
                ostringstream oss;
                oss << "maps/" << m_currentMap.getX() << "_" << m_currentMap.getY() << "/";
                dp = opendir(oss.str().c_str());

                if(dp != NULL)
                {
                    while(ep = readdir(dp))
                        i++;
                    (void) closedir(dp);
                } else perror("Couldn't open the directory.");
                i -= 2;//le nombre de fichiers dans map/ est i - 2
                //gere les changements de map cote à cote (exemple double porte)
                int linkId = i + 1;
                if(m_currentMap.getTile(x + 1, y).getPhysicParam().getPhysicId() == 3)
                    linkId = m_currentMap.getTile(x + 1, y).getLinkId();
                if(m_currentMap.getTile(x - 1, y).getPhysicParam().getPhysicId() == 3)
                    linkId = m_currentMap.getTile(x - 1, y).getLinkId();
                if(m_currentMap.getTile(x, y + 1).getPhysicParam().getPhysicId() == 3)
                    linkId = m_currentMap.getTile(x, y + 1).getLinkId();
                if(m_currentMap.getTile(x, y - 1).getPhysicParam().getPhysicId() == 3)
                    linkId = m_currentMap.getTile(x, y - 1).getLinkId();
                m_currentMap.modifyTile(x, y, m_currentGraphicId, m_currentPhysicId, linkId, m_currentMap.getTile(x, y).getSecondLevelObject(), m_currentMap.getTile(x, y).getThirdLevelObject());
                saveConfig();
            } else {
                m_currentMap.modifyTile(x, y, m_currentGraphicId, m_currentPhysicId, m_currentMap.getTile(x, y).getLinkId(), m_currentMap.getTile(x, y).getSecondLevelObject(), m_currentMap.getTile(x, y).getThirdLevelObject());
            }
        } else {
            //on s'occupe ici de la construction des object AU DESSU des sprites de terrains
            //ou sur d'autres object (niveau 0(terrain) niveau 1(objet) niveau 2(objet)
            if(m_currentMap.getTile(x, y).getSecondLevelObject() == -1){
                m_currentMap.modifyTile(x, y, m_currentMap.getTile(x, y).getGraphicParam().getGraphicId(), 0, m_currentMap.getTile(x, y).getLinkId(), m_currentObjectId, m_currentMap.getTile(x, y).getThirdLevelObject());
            } else {
                m_currentMap.modifyTile(x, y, m_currentMap.getTile(x, y).getGraphicParam().getGraphicId(), 0, m_currentMap.getTile(x, y).getLinkId(), m_currentMap.getTile(x, y).getSecondLevelObject(), m_currentObjectId);

            }
        }

        }
}

void MapEditor::drawNpcs(){
    for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++){
        if(npc_array[i].getNpcId() == 0)
            break;
            if(npc_array[i].getLinkId() != m_currentMap.getLinkedId()){
                continue;
            }
            int startX = (WINDOWS_FINAL_SIZE_X - (TILE_SIZE * MAP_SIZE)) / 2;
            int startY = 10;
            sf::Sprite npcSprite = sf::Sprite(m_npcTextures[npc_array[i].getNpcId()]);
            npcSprite.setPosition(startX + TILE_SIZE * npc_array[i].getX(), startY + TILE_SIZE * npc_array[i].getY());
            m_gameWindow.draw(npcSprite);
    }
}

void MapEditor::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed)
{
    int value = (SPRITE_AMOUNT % 91 == 0 ? SPRITE_AMOUNT / 91 - 1 : SPRITE_AMOUNT / 91)
                                        + 1 + (OBJECT_SPRITE_AMOUNT % 91 == 0 ? OBJECT_SPRITE_AMOUNT / 91 - 1 : OBJECT_SPRITE_AMOUNT / 91);
    if(isPressed) return;
    switch(key){
        case sf::Keyboard::Left:
            if(m_currentSpriteTab > 0)
                m_currentSpriteTab--;
            else
                m_currentSpriteTab = value;

            break;
        case sf::Keyboard::Right:
            if(m_currentSpriteTab < value)
                m_currentSpriteTab++;
            else
                m_currentSpriteTab = 0;
            break;
        case sf::Keyboard::Escape:
            exited = true;
            break;
        default:
            break;
    }
}

void MapEditor::update()
{
    sf::Sprite sprite[MAP_SIZE][MAP_SIZE];
    sf::Sprite secondObjectSprites[MAP_SIZE][MAP_SIZE];
    sf::Sprite thirdObjectSprites[MAP_SIZE][MAP_SIZE];
    int startX = (WINDOWS_FINAL_SIZE_X - (TILE_SIZE * MAP_SIZE)) / 2;
    int startY = 10;

    sf::RectangleShape physics[7]; //physic 1 ??
    int opacity = 150;
    physics[0].setFillColor(sf::Color(237, 28, 36, opacity));
    physics[1].setFillColor(sf::Color(0, 0, 0, 0));
    physics[2].setFillColor(sf::Color(0, 162, 232, opacity));
    physics[3].setFillColor(sf::Color(255, 174, 201, opacity));
    physics[4].setFillColor(sf::Color(163, 73, 164, opacity));
    physics[5].setFillColor(sf::Color(255, 242, 0, opacity));
    physics[6].setFillColor(sf::Color(27, 30, 139, opacity));

    m_gameWindow.clear();
    //updating map
    for(int i = 0; i < MAP_SIZE; i++) {
        for(int j = 0; j < MAP_SIZE; j++)
        {
            int spriteId = m_currentMap.getTile(i, j).getGraphicParam().getGraphicId();
            int graphicId = m_currentMap.getTile(i, j).getPhysicParam().getPhysicId();
            int secondObjectId = m_currentMap.getTile(i, j).getSecondLevelObject();
            int thirdObjectId = m_currentMap.getTile(i, j).getThirdLevelObject();
            sprite[i][j] = sf::Sprite(m_groundTextures[spriteId - 1]);
            sprite[i][j].setPosition(startX + TILE_SIZE * j, startY + TILE_SIZE * i);
            physics[graphicId].setPosition(startX + TILE_SIZE * j, startY + TILE_SIZE * i);
            physics[graphicId].setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            m_gameWindow.draw(sprite[i][j]);
            if(secondObjectId != -1){
                secondObjectSprites[i][j] = sf::Sprite(m_objectTextures[secondObjectId - 1]);
                secondObjectSprites[i][j].setPosition(sprite[i][j].getPosition());
                m_gameWindow.draw(secondObjectSprites[i][j]);
            }
            if(thirdObjectId != -1){
                thirdObjectSprites[i][j] = sf::Sprite(m_objectTextures[thirdObjectId - 1]);
                thirdObjectSprites[i][j].setPosition(sprite[i][j].getPosition());
                m_gameWindow.draw(thirdObjectSprites[i][j]);
            }
            m_gameWindow.draw(physics[graphicId]);
        }
    }
    drawNpcs();

    //updating sprite panel
    sf::Sprite diff_sprites[91];
    if(m_currentSpriteTab <= ceil(SPRITE_AMOUNT / 91)){
        int startSpriteId = m_currentSpriteTab * 91;
        for(int i = startSpriteId; i < min(startSpriteId + 91, SPRITE_AMOUNT); i++){
            int lineLength = 13;
            int newIndex = i - startSpriteId;
            diff_sprites[newIndex] = sf::Sprite(m_groundTextures[i]);
            m_sprites_panel_pos_x[newIndex] = 20 + (newIndex / lineLength) * 50;
            m_sprites_panel_pos_y[newIndex] = (37 + TILE_SIZE * (newIndex % lineLength) + (7 * (newIndex%lineLength)));
            diff_sprites[newIndex].setPosition(m_sprites_panel_pos_x[newIndex], m_sprites_panel_pos_y[newIndex]);
            m_gameWindow.draw(diff_sprites[newIndex]);

            //cursor
            if(newIndex + 1 == m_currentGraphicId - m_currentSpriteTab * 91){
                cursorLeft.setPosition(m_sprites_panel_pos_x[newIndex], m_sprites_panel_pos_y[newIndex]);
            }
        }
        if(m_currentGraphicId - m_currentSpriteTab * 91 >= 0)
            m_gameWindow.draw(cursorLeft);
    } else {
        int startSpriteId = (m_currentSpriteTab - ceil(SPRITE_AMOUNT / 91) - 1) * 91;
        for(int i = startSpriteId; i < min(startSpriteId + 91, OBJECT_SPRITE_AMOUNT); i++){
            int lineLength = 13;
            int newIndex = i - startSpriteId;
            diff_sprites[newIndex] = sf::Sprite(m_objectTextures[i]);
            m_sprites_panel_pos_x[newIndex] = 20 + (newIndex / lineLength) * 50;
            m_sprites_panel_pos_y[newIndex] = (37 + TILE_SIZE * (newIndex % lineLength) + (7 * (newIndex%lineLength)));
            diff_sprites[newIndex].setPosition(m_sprites_panel_pos_x[newIndex], m_sprites_panel_pos_y[newIndex]);
            m_gameWindow.draw(diff_sprites[newIndex]);

            //cursor
            if(newIndex + 1 == m_currentObjectId - (m_currentSpriteTab - ceil((double)(SPRITE_AMOUNT) / 91)) * 91){
                cursorLeft.setPosition(m_sprites_panel_pos_x[newIndex], m_sprites_panel_pos_y[newIndex]);
            }
        }
        if(m_currentObjectId - (m_currentSpriteTab - ceil((double)SPRITE_AMOUNT / 91)) * 91 >= 0)
            m_gameWindow.draw(cursorLeft);
    }
    //right panel
    loadRightPanel();
    loadNpcPanel();
    for(int i = 0; i < PHYSIC_PROP_AMOUNT; i++){
            if(i == m_currentPhysicId)
                cursorRight.setPosition(RIGHT_PANEL_MIN_X, 24 + i * RIGHT_PANEL_SCALE);
    }
        m_gameWindow.draw(cursorRight);

    m_gameWindow.display();
}

void MapEditor::setMap(int x, int y)
{
    setMap(x, y, -1);
}

void MapEditor::setMap(int x, int y, int linkedId)
{
    m_currentMap = Map(x, y, linkedId);
}

void MapEditor::saveConfig(){
    ostringstream oss;
    if(m_currentMap.getLinkedId() == -1){
        oss << "maps/" << m_currentMap.getX() << "_" << m_currentMap.getY() << ".txt";
    } else {
        oss << "maps/" << m_currentMap.getX() << "_" << m_currentMap.getY() << "/" << m_currentMap.getLinkedId() << ".txt";
    }
    string fileName = oss.str();
    ofstream myStream(fileName.c_str());

    if(myStream)
    {

        for(int i = 0; i < MAP_SIZE; i++){
            for(int j = 0; j < MAP_SIZE; j++){
                myStream << m_currentMap.getTile(i, j).getGraphicParam().getGraphicId();
                myStream << "," << m_currentMap.getTile(i, j).getPhysicParam().getPhysicId();
                myStream << "," << m_currentMap.getTile(i, j).getLinkId();
                myStream << "," << m_currentMap.getTile(i, j).getSecondLevelObject();
                myStream << "," << m_currentMap.getTile(i, j).getThirdLevelObject();
                myStream << ";";
            }
            myStream << endl;
        }
    }
    else
    {
        cout << "ERROR : Cannot open the file." << endl;
    }
    //creer un fichier pour chaque maps
    ostringstream oss1;
    oss1 << "maps/" << m_currentMap.getX() << "_" << m_currentMap.getY();
    string folderName = oss1.str();
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    mkdir(folderName.c_str());
    #else
    mkdir(folderName.c_str(),0777);
    #endif



    saveNpcConfig();
}

void MapEditor::saveNpcConfig(){
    ostringstream oss;
    oss << "maps/" << m_currentMap.getX() << "_" << m_currentMap.getY() << "/entity.txt";

    string fileName = oss.str();
    ofstream myStream(fileName.c_str());

    if(myStream)
    {

        for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++){
                if(npc_array[i].getNpcId() == 0)
                    break;
                myStream << npc_array[i].getNpcId();
                myStream << "," << npc_array[i].getX();
                myStream << "," << npc_array[i].getY();
                myStream << "," << npc_array[i].getLinkId();

            myStream << endl;
        }
    }
    else
    {
        cout << "ERROR : Cannot open the file." << endl;
    }
}


void split(const string& s, char c,
           vector<string>& v) {
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}
void MapEditor::loadConfig(int x, int y){
    loadConfig(x, y, -1);
}
void MapEditor::loadConfig(int x, int y, int linkedId)
{
    resetNpcArray();
    ostringstream oss;
    if(linkedId == -1)
        oss << "maps/" << x << "_" << y << ".txt";
    else
        oss << "maps/" << x << "_" << y << "/" << linkedId << ".txt";
    string fileName = oss.str();
    ifstream myStream(fileName.c_str());

    setMap(x, y, linkedId);
    if(myStream)
    {
        for(int i = 0; i < MAP_SIZE; i++)
        {

                vector<string> v;
                string s;
                getline(myStream, s);
                split(s, ';', v);
                for(int j = 0; j < (int) (v.size() - 1); j++){
                    string s2 = v[j];
                    vector<string> v2;
                    split(s2, ',', v2);
                    m_currentMap.modifyTile(i, j, atoi(v2[0].c_str()), atoi(v2[1].c_str()), atoi(v2[2].c_str()), atoi(v2[3].c_str()), atoi(v2[4].c_str()));
                }

        }

    }else
    {
        cout << "ERROR: Cannot open file. Creating a new file for that map." << endl;
        saveConfig();
    }
    loadNpcConfig(x, y);
}

void MapEditor::loadNpcPanel(){
    int startX = 20 + SPRITE_PANEL_WIDTH / 2;
    int startY = 20 + MAP_SIZE * TILE_SIZE;
    for(int i = 0; i < NPC_SPRITE_AMOUNT; i++){
        sf::Sprite sprite = sf::Sprite(m_npcTextures[i]);
        sprite.setPosition(startX + (5 + TILE_SIZE) * i, startY);
        m_gameWindow.draw(sprite);
        //cursor
        if(i == m_currentNpcId){
            cursorBottom.setPosition(startX + (5 + TILE_SIZE) * i, startY);
        }
    }
        m_gameWindow.draw(cursorBottom);
}

void MapEditor::loadNpcConfig(int x, int y)
{
    ostringstream oss;
        oss << "maps/" << x << "_" << y << "/entity.txt";
    string fileName = oss.str();
    ifstream myStream(fileName.c_str());

    if(myStream)
    {
        string s;
        int counter = 0;
        while(getline(myStream, s)){
            vector<string> v;
            split(s, ',', v);
            npc_array[counter] = Npc(atoi(v[0].c_str()), atoi(v[1].c_str()), atoi(v[2].c_str()), atoi(v[3].c_str()));
            counter++;
        }

    }else
    {
        cout << "ERROR: Cannot open file. Creating a new file for that map." << endl;
        saveConfig();
    }
}

void MapEditor::addNpc(int id, int x, int y, int linkId){
    for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++){
        if(npc_array[i].getNpcId() == 0){
            npc_array[i] = Npc(id, x, y, linkId);
            break;
        }
    }
}

void MapEditor::removeNpc(int x, int y){
    for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++){
        if(npc_array[i].getNpcId() == 0){
            break;
        }
        if(npc_array[i].getX() == x && npc_array[i].getY() == y){
            npc_array[i] = Npc();
            break;
        }
    }
}

void MapEditor::resetNpcArray(){
    for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++){
        if(npc_array[i].getNpcId() == 0)
            break;
        npc_array[i] = Npc();
    }
}


Tile MapEditor::getTileWithMouse(int mouseX, int mouseY)
{
    int x = (mouseX - SPRITE_PANEL_WIDTH) / TILE_SIZE;
    int y = mouseY / TILE_SIZE;

    return m_currentMap.getTile(x, y);
}

void MapEditor::displayMapInfo()
{
    for(int i = 0; i < MAP_SIZE; i++)
        {
            for(int j = 0; j < MAP_SIZE; j++)
            {
                cout << m_currentMap.getTile(i, j).getGraphicParam().getGraphicId()
                << "_" << m_currentMap.getTile(i, j).getPhysicParam().getPhysicId() << ";";
            }
            cout << endl;
        }
}
