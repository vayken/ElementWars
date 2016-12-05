#include "Engine.h"
#include "Entity.h"

#define WINDOW_SIZE_X WINDOWS_FINAL_SIZE_X - SPRITE_PANEL_WIDTH
#define WINDOW_SIZE_Y WINDOWS_FINAL_SIZE_Y

using namespace std;


Engine::Engine(sf::RenderWindow &window)
: m_gameWindow(window){
    m_gameWindow.setFramerateLimit(60);
    load();
    loadConfig(m_mapX, m_mapY);
    loadTextures();
}

void Engine::setMap(int x, int y, int linkedId){
    m_currentMap = Map(x, y, linkedId);
}

void Engine::load(){
    ifstream fichier( "save.txt" );
    if (fichier )
    {
        string ligne;
        getline( fichier, ligne );
        position.x = atoi(ligne.c_str());
        getline( fichier, ligne );
        position.y = atoi(ligne.c_str());

        getline( fichier, ligne );
        m_mapX = atoi(ligne.c_str());
        getline( fichier, ligne );
        m_mapY = atoi(ligne.c_str());

    }
    else{
        position.x = 64;
        position.y = 64;
        m_mapX = 1;
        m_mapY=1;
    }
}

void Engine::save(){
    if( remove( "save.txt" ) != 0 )
        cout << "Error while updating save file !" <<endl;
    ofstream file( "save.txt", std::ios_base::app );

    if(m_currentMap.getLinkedId() != -1){
        file << savedPosition.x <<"\n";
        file << savedPosition.y <<"\n";
    }
    else{
        file << position.x <<"\n";
        file << position.y <<"\n";
    }
    file << m_mapX <<"\n";
    file << m_mapY <<"\n";
    file << m_currentMap.getLinkedId() <<"\n";
}

void Engine::run(){
    sf::Clock deltaTime;
    sf::Texture texture;


	if (!music.openFromFile("soundtrack/wavfiles/Indoors.wav"))
	{
		std::cout << "ERROR" << std::endl;
	}
	music.setLoop(true);
    music.setVolume(30);
	music.play();

    for(int i = 0; i < 12; i++){
            ostringstream oss;
            oss << "sprites/characters/" << i << ".png";
            string fileName = oss.str();
            if(!m_playerTextures[i].loadFromFile(fileName, sf::IntRect(0, 0, 24, 32)))
                cout << "ERROR loading Player texture" << endl;
    }

    m_Player.setTexture(m_playerTextures[1]);
    m_Player.setPosition(position.x, position.y);
    m_gameWindow.draw(m_Player);


    while(m_gameWindow.isOpen() && m_run){
        processEvents();
        update(deltaTime);
        render();
    }
}
Engine::~Engine(){}

void Engine::processEvents(){
    sf::Event event;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        save();
        m_run=false;
    }

    while(m_gameWindow.pollEvent(event)){
        if(event.type == sf::Event::LostFocus)
                pause();

        if(event.type == sf::Event::Closed){
                save();
                m_run=false;
        }
    }
}

void Engine::handleKeyboardInput(sf::Keyboard::Key key, bool isPressed){
    if(!isPressed){

    }
    /*switch(key){
        case sf::Keyboard::Z
            mIsMovingUp = isPressed;
            break;
        case sf::Keyboard::S
            mIsMovingDown = isPressed;
            break;
        case sf::Keyboard::Q
            mIsMovingLeft = isPressed;
            break;
        case sf::Keyboard::D)
            mIsMovingRight = isPressed;
            break;
    }*/
}

void Engine::borderControl(){
    int currentTileX_top, currentTileY_top,currentTileX_bot, currentTileY_bot;
    bool left,right,top,bot;
    top = (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    bot = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    left = (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
    right = (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

    if(position.x < 0 && left){
        if (m_mapX>1){
            position.x = 550;
            m_mapX--;
            loadConfig(m_mapX, m_mapY);
            m_lastSpeed.x=0.f;
            m_lastSpeed.y=0.f;
          //  transition();
        }
        else
            position.x = 0;
        return;
    }
    if(position.y < 0 && top){

        if (m_mapY>1){
            position.y = 550;
            m_mapY--;
            setMap(m_mapX,m_mapY);
            loadConfig(m_mapX, m_mapY);
            m_lastSpeed.x=0.f;
            m_lastSpeed.y=0.f;
           // transition();
        }
        else
            position.y = 0;
        return;
    }
    if(position.x > 550 && right){

            position.x = 0;
            m_mapX++;
            setMap(m_mapX,m_mapY);
            loadConfig(m_mapX, m_mapY);
            m_lastSpeed.x=0.f;
            m_lastSpeed.y=0.f;
          //  transition();
            return;
    }
    if(position.y > 550 && bot){

            position.y = 0;
            m_mapY++;
            setMap(m_mapX,m_mapY);
            loadConfig(m_mapX, m_mapY);
            m_lastSpeed.x=0.f;
            m_lastSpeed.y=0.f;
           // transition();
            return;
    }

    currentTileX_top = (position.x)/32;
    currentTileY_top = (position.y)/32;
    currentTileX_bot = (position.x+23)/32;
    currentTileY_bot = (position.y+31)/32;

/***************** ENTREE DANS UN BATIMENT ***********************/
    if(m_currentMap.getTile(currentTileY_top,currentTileX_top).getPhysicParam().getPhysicId() == 3){
        int id;
        id = m_currentMap.getTile(currentTileY_top,currentTileX_top).getLinkId();
        if(id==-1){
            loadConfig(m_mapX, m_mapY,-1);
            position = savedPosition;
            m_Player.setPosition(position.x,position.y);
            m_lastSpeed.x=0.f;
            m_lastSpeed.y=0.f;
            return;
        }
        m_lastSpeed.x=0.f;
        m_lastSpeed.y=0.f;
        loadConfig(m_mapX, m_mapY,id);
        savedPosition = position;
        position.x = 9*32.f;
        position.y = 16*32.f;
        return;
    }
    else if(m_currentMap.getTile(currentTileY_bot,currentTileX_bot).getPhysicParam().getPhysicId() == 3){
        int id;
        id = m_currentMap.getTile(currentTileY_top,currentTileX_top).getLinkId();
        if(id==-1){
            loadConfig(m_mapX, m_mapY,-1);
            position = savedPosition;
            m_Player.setPosition(position.x,position.y);
            m_lastSpeed.x=0.f;
            m_lastSpeed.y=0.f;
            return;
        }
        m_lastSpeed.x=0.f;
        m_lastSpeed.y=0.f;
        savedPosition = position;
        position.x = 9*32.f;
        position.y = 17*32.f;
        return;
    }


}

void Engine::update(sf::Clock deltaTime){
    bool left,right,top,bot,singleD;
    //float fps, currentTime;
    m_gameWindow.clear();

/********************* DETECTION DE FIN DE DEPLACEMENT - Finalisation animation ******************************/
    top = (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    bot = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    left = (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
    right = (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right));

    singleD = ((top & !bot & !left & !right) | ( !top & bot & !left & !right) | ( !top & !bot & left & !right) | ( !top & !bot & !left & right));

    if(singleD){
        if( m_movement!=0 && (((m_movement!=1) & top) || ((m_movement!=2) & bot) || ((m_movement!=3) & left) || ((m_movement!=4) & right)))
            endAnimation(deltaTime);
    }


    sf::Vector2f movement(0.f, 0.f);

    /***** Movement (0=none, 1=top, 2=down, 3=left, 4=right) ****/
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (m_movement == 0 || m_movement==1)){
        movement.y -= 1.5f;
        m_movement = 1;
        m_animationCount++;
        if(m_animationCount>20) m_animationCount=1;
        m_Player.setTexture(m_playerTextures[m_animationCount / 7 + 9]);
    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (m_movement == 0 || m_movement==2)){
        movement.y += 1.5f;
        m_movement = 2;
        m_animationCount++;
        if(m_animationCount>20) m_animationCount=1;
        m_Player.setTexture(m_playerTextures[m_animationCount / 7 ]);

    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (m_movement == 0 || m_movement==3)){
        movement.x -= 1.5f;
        m_movement = 3;
        m_animationCount++;
        if(m_animationCount>20) m_animationCount=1;
        m_Player.setTexture(m_playerTextures[m_animationCount / 7 + 3]);

    }
    else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (m_movement == 0 || m_movement==4)){
        movement.x += 1.5f;
        m_movement = 4;
        m_animationCount++;
        if(m_animationCount>20) m_animationCount=1;
        m_Player.setTexture(m_playerTextures[m_animationCount / 7 + 6]);
    }

    else{
        if(!m_animationEnded)
            endAnimation(deltaTime);
        m_movement = 0;
    }



    velocity = movement*deltaTime.restart().asSeconds();
    if(velocity.x < -maxspeed) velocity.x = -maxspeed;
    if(velocity.x >  maxspeed) velocity.x =  maxspeed;
    if(velocity.y < -maxspeed) velocity.y = -maxspeed;
    if(velocity.y >  maxspeed) velocity.y =  maxspeed;

    position += velocity;


 //  cout << "x : " << currentTileX << "(" << position.x << ")" << endl << "y : " << currentTileY << endl << "Physic : " << m_currentMap.getTile(currentTileX,currentTileY).getPhysicParam().getPhysicId() << endl <<  endl;

/***************** GESTION DES PROPRIETES PHYSIQUES (Détection des cases non traversable) ************************************/
    if(!isTraversable(position)){
        position -= velocity;
    }

/***************** GESTION DES BORDS DE L ECRAN ************************************/
    borderControl();

    m_animationEnded = (velocity.x==0 && velocity.y==0) ? true : false;

    fightController(deltaTime);

    m_lastSpeed=velocity;
    m_Player.setPosition(position);
    updateBackground();
}
void Engine::pause(){
    sf::Event event;
    bool isPaused = true;
    while(isPaused){
        while(m_gameWindow.pollEvent(event)){
            if(event.type == sf::Event::GainedFocus)
                isPaused = false;
        }
    }
    return;
}
void Engine::transition(){
    /*sf::Clock clock;
    int delay;
    m_gameWindow.clear();
    m_gameWindow.display();
    while(delay < 400){
        delay += clock.restart().asMilliseconds();
    }
    return;*/
}
void Engine::fightController(sf::Clock deltaTime){
    int currentTileX_top, currentTileY_top,currentTileX_bot, currentTileY_bot;
    currentTileX_top = (position.x)/32;
    currentTileY_top = (position.y)/32;
    currentTileX_bot = (position.x+23)/32;
    currentTileY_bot = (position.y+31)/32;
    if(m_currentMap.getTile(currentTileY_top,currentTileX_top).getPhysicParam().getPhysicId() == 6 && m_movement != 0){
        randFight += rand() % 100;

    }
    else if(m_currentMap.getTile(currentTileY_bot,currentTileX_bot).getPhysicParam().getPhysicId() == 6 && m_movement != 0){
        randFight += rand() % 100;
    }


    if(randFight > 10000){
        endAnimation(deltaTime);
       // transition();
        music.pause();
        Combat combat(m_gameWindow);
        music.play();
        randFight=0;
    }
}

bool Engine::isTraversable(sf::Vector2f pos){
    int currentTileX_top, currentTileY_top,currentTileX_bot, currentTileY_bot;
    currentTileX_top = (pos.x)/32;
    currentTileY_top = (pos.y)/32;
    currentTileX_bot = (pos.x+23)/32;
    currentTileY_bot = (pos.y+31)/32;
    if(m_currentMap.getTile(currentTileY_top,currentTileX_top).getPhysicParam().getPhysicId() == 0 || m_currentMap.getTile(currentTileY_top,currentTileX_top).getPhysicParam().getPhysicId() == 2){
        return false;
    }
    else if(m_currentMap.getTile(currentTileY_bot,currentTileX_bot).getPhysicParam().getPhysicId() == 0 || m_currentMap.getTile(currentTileY_top,currentTileX_top).getPhysicParam().getPhysicId() == 2){
        return false;
    }
    return true;
}

void Engine::endAnimation(sf::Clock deltaTime){
    bool tv =true;
    sf::Vector2f pos;
    int caseToReach;
    float Xrel, Yrel;
    if(m_movement == 0)
        return;
/********** HAUT ***************/
    if(m_movement==1){
        caseToReach = (int) (position.y)/32.f; // Interception bord gauche virtuel de la case avatar (case avatar 24x32, tile 32x32)
        pos.x = position.x;
        pos.y = caseToReach*32;
        if(!isTraversable(pos))
            tv = false;

        Yrel = caseToReach*32.f;

        while(m_gameWindow.isOpen() && position.y != Yrel && tv ){
            processEvents();
            position += m_lastSpeed;
            if(Yrel - position.y > 0)
                position.y = Yrel;

            m_animationCount++;
            if(m_animationCount>20) m_animationCount=1;
            m_Player.setTexture(m_playerTextures[m_animationCount / 7 + 9]);
            m_Player.setPosition(position);
            borderControl();
            updateBackground();
            render();
        }
        m_animationCount=0;
        m_Player.setTexture(m_playerTextures[10]);
    }
/********** BAS ***************/
    if(m_movement==2){
        caseToReach = (int) (position.y)/32.f+1; // Interception bord gauche virtuel de la case avatar (case avatar 24x32, tile 32x32)
        Yrel = caseToReach*32.f;
        pos.x = position.x;
        pos.y = caseToReach*32;
        if(!isTraversable(pos))
            tv = false;

        while(m_gameWindow.isOpen() && position.y != Yrel && tv){
            processEvents();
            position += m_lastSpeed;
            if(Yrel - position.y < 0)
                position.y = Yrel;
            m_animationCount++;
            if(m_animationCount>20) m_animationCount=1;
            m_Player.setTexture(m_playerTextures[m_animationCount / 7]);
            m_Player.setPosition(position);
            borderControl();
            updateBackground();
            render();
        }
        m_animationCount=0;
        m_Player.setTexture(m_playerTextures[1]);
    }
/************* GAUCHE **************/
    if(m_movement==3){
        caseToReach = (int) (position.x-4.f)/32.f; // Interception bord gauche virtuel de la case avatar (case avatar 24x32, tile 32x32)
        Xrel = caseToReach*32.f+4.f;
        pos.y = position.y;
        pos.x = caseToReach*32;
        if(!isTraversable(pos))
            tv = false;

        while(m_gameWindow.isOpen() && position.x != Xrel && tv){
            processEvents();
            position += m_lastSpeed;
            if(Xrel - position.x > 0)
                position.x = Xrel;
            m_animationCount++;
            if(m_animationCount>20) m_animationCount=1;
            m_Player.setTexture(m_playerTextures[m_animationCount / 7 + 3]);
            m_Player.setPosition(position);
            borderControl();
            updateBackground();
            render();
        }
        m_animationCount=0;
        m_Player.setTexture(m_playerTextures[4]);
    }
/************* DROITE **************/
    if(m_movement==4){
        caseToReach = (int) (position.x-4.f)/32.f+1; // Interception bord gauche virtuel de la case avatar (case avatar 24x32, tile 32x32)
        Xrel = caseToReach*32.f+4.f;
        pos.y = position.y;
        pos.x = caseToReach*32;
        if(!isTraversable(pos))
            tv = false;

        while(m_gameWindow.isOpen() && position.x != Xrel && tv){
            processEvents();
            position += m_lastSpeed;
            if(Xrel - position.x < 0)
                position.x = Xrel;
            m_animationCount++;
            if(m_animationCount>20) m_animationCount=1;
            m_Player.setTexture(m_playerTextures[m_animationCount / 7 + 6]);
            m_Player.setPosition(position);
            borderControl();
            updateBackground();
            render();
        }
        m_animationCount=0;
        m_Player.setTexture(m_playerTextures[7]);
    }


    m_lastSpeed.x=0.f;
    m_lastSpeed.y=0.f;
  /*  while(position.x != Xrel*32.f){
        movement.x += 1.5f;
        velocity = movement*deltaTime.restart().asSeconds();
        if(velocity.x >  maxspeed) velocity.x =  maxspeed;
        m_Player.setPosition(position);
    }*/

    updateBackground();
    m_animationEnded = true;
}

void Engine::updateBackground(){
    sf::Sprite sprite[MAP_SIZE][MAP_SIZE];
    sf::Sprite secondObjectSprites[MAP_SIZE][MAP_SIZE];
    sf::Sprite thirdObjectSprites[MAP_SIZE][MAP_SIZE];

    //updating map
    for(int i = 0; i < MAP_SIZE; i++) {
        for(int j = 0; j < MAP_SIZE; j++)
        {
            int spriteId = m_currentMap.getTile(i, j).getGraphicParam().getGraphicId();
           // int graphicId = m_currentMap.getTile(i, j).getPhysicParam().getPhysicId();
            int secondObjectId = m_currentMap.getTile(i, j).getSecondLevelObject();
            int thirdObjectId = m_currentMap.getTile(i, j).getThirdLevelObject();

            sprite[i][j] = sf::Sprite(m_groundTextures[spriteId - 1]);
            sprite[i][j].setPosition( TILE_SIZE * j,  TILE_SIZE * i);
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
        }
    }
    drawNpcs();
}

void Engine::render(){

    m_gameWindow.draw(m_Player);
    m_gameWindow.display();
}

void Engine::split(const string& s, char c, vector<string>& v) {
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

void Engine::loadConfig(int x, int y, int linkedId){
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
                for(int j = 0; j < (int)(v.size() - 1); j++){
                    string s2 = v[j];
                    vector<string> v2;
                    split(s2, ',', v2);
                    m_currentMap.modifyTile(i, j, atoi(v2[0].c_str()), atoi(v2[1].c_str()), atoi(v2[2].c_str()), atoi(v2[3].c_str()), atoi(v2[4].c_str()));
                }

        }

    }else
    {
        cout << "ERROR: Cannot open file. - Creating a new file for that map." << endl;
    }
    loadNpcConfig(x, y);
}

void Engine::resetNpcArray(){
    for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++){
        if(npc_array[i].getNpcId() == 0)
            break;
        npc_array[i] = Npc();
    }
}

void Engine::loadNpcConfig(int x, int y)
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
        cout << "ERROR: Cannot open file. -- Creating a new file for that map." << endl;
    }
}

void Engine::drawNpcs(){
    for(int i = 0; i < MAP_SIZE * MAP_SIZE; i++){
        if(npc_array[i].getNpcId() == 0)
            break;

        if(npc_array[i].getLinkId() != m_currentMap.getLinkedId())
            continue;

        sf::Sprite npcSprite = sf::Sprite(m_npcTextures[npc_array[i].getNpcId()]);
        npcSprite.setPosition(TILE_SIZE * npc_array[i].getX(), TILE_SIZE * npc_array[i].getY());
        m_gameWindow.draw(npcSprite);
    }
}

void Engine::loadTextures(){

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
    //sets the cursor pointing toward the current sprite id

    //loading right panel
}
