#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility> 
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <SFML/Audio.hpp>
#include <iomanip>
#include<cstdlib>
#include<algorithm>
#include<numeric>
#include<queue>
#include<stack>
#include<set>
#include<iterator>
#include<cmath>

using namespace std;
using namespace sf;


void save_map(const string& filename, const GridTile mapData[mapW][mapH], const vector<Entity>& levelObjects) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "i feel just like Dora" << filename << endl;
        return;
    }
    //saving grids with ground (am dying)
    for (int x = 0; x < mapW; x++) {
        for (int y = 0; y < mapH; y++) {
            if (mapData[x][y].textureRect.width > 0) {
                file << "T " << x << " " << y << " "
                    << mapData[x][y].textureRect.left << " "
                    << mapData[x][y].textureRect.top << " "
                    << mapData[x][y].textureRect.width << " "
                    << mapData[x][y].textureRect.height << " "
                    << mapData[x][y].hasCollision << "\n";
            }
        }
    }
    //saving ground that wasn't put based on grids ;(
    for (const auto& obj : levelObjects) {
        file << "E " << obj.sprite.getPosition().x << " "
            << obj.sprite.getPosition().y << " "
            << obj.sprite.getTextureRect().left << " "
            << obj.sprite.getTextureRect().top << " "
            << obj.sprite.getTextureRect().width << " "
            << obj.sprite.getTextureRect().height << " "
            << obj.hasCollision << "\n";
    }

    //save spawn points
    for (const auto& sp : points) {
        file << "S " << sp.type << " " << sp.position.x << " " << sp.position.y << "\n";
    }
    for (int i = 0; i < itemCount; i++) {
        file << "I " << itemPoints[i].type << " "
            << itemPoints[i].position.x << " "
            << itemPoints[i].position.y << "\n";
    }
    file.close();
    cout << "YAY , the map has loaded" << filename << endl;
}
void load_map(const string& filename, GridTile mapData[mapW][mapH], vector<Entity>& levelObjects, const Texture& tileset) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "i feel just like Dora" << filename << endl;
        return;
    }
    //قرار ازاله لكل ما مضى
    for (int x = 0; x < mapW; x++) {
        for (int y = 0; y < mapH; y++) {
            mapData[x][y].textureRect = IntRect(0, 0, 0, 0);
            mapData[x][y].hasCollision = false;
        }
    }
    levelObjects.clear();
    points.clear();

    string type;
    //reading file
    while (file >> type) {
        if (type == "T") {
            // بيحمل الارض
            int x, y, rL, rT, rW, rH;
            bool col;
            file >> x >> y >> rL >> rT >> rW >> rH >> col;

            if (x >= 0 && x < mapW && y >= 0 && y < mapH) {
                mapData[x][y].textureRect = IntRect(rL, rT, rW, rH);
                mapData[x][y].hasCollision = col;
            }
        }
        else if (type == "E") {
            //بيحمل الارض برده بس الارض الحره
            float px, py;
            int rL, rT, rW, rH;
            bool col;
            file >> px >> py >> rL >> rT >> rW >> rH >> col;

            Entity newObj;
            newObj.sprite = Sprite(tileset);
            newObj.sprite.setTextureRect(IntRect(rL, rT, rW, rH));
            newObj.sprite.setPosition(px, py);
            newObj.hitbox = newObj.sprite.getGlobalBounds();
            newObj.hasCollision = col;

            levelObjects.push_back(newObj);
        }
        else if (type == "S") {
            int spawnType;
            float spawnX, spawnY;
            file >> spawnType >> spawnX >> spawnY;

            points.push_back({ spawnType, Vector2f(spawnX, spawnY) });
            bool isEnemy = spawnDetails[spawnType].isEnemy;
            int gameID = spawnDetails[spawnType].gameID;

            if (isEnemy) {
                Enemy_Generate(spawnX, spawnY, gameID);
            }
            else {
                for (int i = 0; i < 8; i++) {
                    player[i].setPosition(spawnX, spawnY);
                    characterbox[i].setPosition(spawnX, spawnY);
                    characterboxarm[i].setPosition(spawnX, spawnY);
                }
            }
        }
        else if (type == "I") {
            int iType;
            float ix, iy;
            file >> iType >> ix >> iy;
            if (itemCount < MAX_ITEMS) {
                itemPoints[itemCount++] = { iType, Vector2f(ix, iy) };
            }
            Items(ix, iy, iType);
        }

    }


    file.close();
    cout << "map successfully loaded alhamdulilah" << filename << endl;
}

void clear_map(GridTile mapData[mapW][mapH], vector<Entity>& levelObjects) {
    //gridقرار ازاله لكل الي في ال
    for (int x = 0; x < mapW; x++) {
        for (int y = 0; y < mapH; y++) {
            mapData[x][y].textureRect = IntRect(0, 0, 0, 0);
            mapData[x][y].hasCollision = false;
        }
    }
    // بشيل الارض الحره
    levelObjects.clear();
}

void load_game_level(int levelIndex) {
    //بعمل اسم متغير بشكل معين بحيث اقدر احدد كل حاجه بالارقم في سترينج
    string mapName = "level" + to_string(levelIndex) + ".txt";
    string bgName = "Map/bg" + to_string(levelIndex) + ".png";
    string tileName = "Map/ts" + to_string(levelIndex) + ".png";

    // يتم تحميل الخلفيه
    if (!bgTexture.loadFromFile(bgName)) {
        cout << "Oops , bg didn't load (big L) " << bgName << "using the common bg loser." << endl;
        bgTexture.loadFromFile(bgName);
    }

    bgTexture.setRepeated(true);
    //ba7sb el repeation bta3 el background
    bgSprite.setTexture(bgTexture, true);
    float exactMapHeight = mapH * tileSize;
    float bgScale = exactMapHeight / bgTexture.getSize().y;
    bgSprite.setScale(bgScale, bgScale);

    int repeatWidth = (mapW * tileSize) / bgScale;
    int repeatHeight = bgTexture.getSize().y;
    bgSprite.setTextureRect(IntRect(0, 0, repeatWidth, repeatHeight));

    //tile set load
    if (!tileset.loadFromFile(tileName)) {
        cout << "Oops , tileset didn't load (big L) " << tileName << "using the common tileset loser." << endl;
        tileset.loadFromFile("ts1.png");
    }
    itemCount = 0;
    itemss.clear();

    //تنضيف عشان نبدأ علي نضيف
    clear_map(mapData, levelObjects);
    enemies.clear();
    fireballs.clear();
    points.clear();
    load_map(mapName, mapData, levelObjects, tileset);
    cout << "aywa b2a el level loaded!!! " << levelIndex << " level" << endl;
}

void map_editor() {
    string startTs = "Map/ts" + to_string(currentEditorLevel) + ".png";
    if (!tileset.loadFromFile(startTs)) {
        tileset.loadFromFile("Map/Enviroment.png");
    }
    RenderWindow Tile_Control(VideoMode(tileset.getSize().x, tileset.getSize().y), "tiles");
    RenderWindow Big_Editor(VideoMode(1280, 720), "editing_level");

    string startingBg = "Map/bg" + to_string(currentEditorLevel) + ".png";

    if (!bgTexture.loadFromFile(startingBg)) {
        cout << "background not working , shit..." << startingBg << "using the default" << endl;
    }
    bgTexture.setRepeated(true);
    bgSprite.setTexture(bgTexture);

    //بقيس ارتفاع الماب بالبكسلز
    float exactMapHeight = mapH * tileSize;
    float bgScale = exactMapHeight / bgTexture.getSize().y;
    bgSprite.setScale(bgScale, bgScale);
    int repeatWidth = (mapW * tileSize) / bgScale;
    int repeatHeight = bgTexture.getSize().y;
    bgSprite.setTextureRect(IntRect(0, 0, repeatWidth, repeatHeight));
    for (int x = 0; x < mapW; x++) {
        for (int y = 0; y < mapH; y++) {
            mapData[x][y].textureRect = IntRect(0, 0, 0, 0);
            mapData[x][y].hasCollision = false;
        }
    }
    load_game_level(currentEditorLevel);
    while (Tile_Control.isOpen() || Big_Editor.isOpen())
    {
        Event event;

        while (Tile_Control.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                menuIndex = 2;
                Big_Editor.close();
                Tile_Control.close();
            }

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
            {
                isDragging = true;
                grabStart = Mouse::getPosition(Tile_Control);
            }
            if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
            {
                isDragging = false;
                Vector2i mPos = Mouse::getPosition(Tile_Control);

                int diffX = abs(mPos.x - grabStart.x);
                int diffY = abs(mPos.y - grabStart.y);

                //كل ده عشان اعرف هل انا دايس علي الماوس و انا بتحرك ولا لا 
                if (diffX > 5 || diffY > 5)
                {
                    selectedRect.left = min(grabStart.x, mPos.x);
                    selectedRect.top = min(grabStart.y, mPos.y);
                    selectedRect.width = diffX;
                    selectedRect.height = diffY;
                }

                else
                {
                    selectedRect.left = (grabStart.x / tileSize) * tileSize;
                    selectedRect.top = (grabStart.y / tileSize) * tileSize;
                    selectedRect.width = tileSize;
                    selectedRect.height = tileSize;
                }
            }
        }
        //======================//=======================//
        while (Big_Editor.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                menuIndex = 2;
                Big_Editor.close();
                Tile_Control.close();
            }
            if (event.type == Event::KeyPressed)
            {
                //collisionبقفل و افتح ال
                if (event.key.code == Keyboard::T)
                {
                    collisionMode = !collisionMode;
                    if (collisionMode) cout << "Collision mode --> ON" << endl;
                    else cout << "Collision mode --> OFF" << endl;
                }

                // + / - عشان اتحرك ما بين اللفلات
                if (event.key.code == sf::Keyboard::Equal)
                {
                    currentEditorLevel++;
                    cout << "Current Editor Level ---> " << currentEditorLevel << endl;
                    load_game_level(currentEditorLevel);
                }
                if (event.key.code == sf::Keyboard::Dash)
                {
                    if (currentEditorLevel > 1) {
                        currentEditorLevel--;
                        cout << "Editor level --> " << currentEditorLevel << endl;
                        load_game_level(currentEditorLevel);
                    }
                    else
                    {
                        cout << "It's level 1, you can't go any lower." << endl;
                    }
                }
                // بسيف بشكل dynamic
                if (event.key.code == sf::Keyboard::S)
                {
                    string filename = "level" + to_string(currentEditorLevel) + ".txt";
                    save_map(filename, mapData, levelObjects);
                }
                //هنا بعمل load
                if (event.key.code == sf::Keyboard::L)
                {
                    string filename = "level" + to_string(currentEditorLevel) + ".txt";
                    load_map(filename, mapData, levelObjects, tileset);
                }
                if (event.key.code == Keyboard::E)
                {
                    currentSpawnType = (currentSpawnType + 1) % totalSpawnTypes;
                    cout << "Spawning --> " << spawnDetails[currentSpawnType].character_name << " <<<" << endl;
                }
                if (event.key.code == Keyboard::Q)
                {
                    currentSpawnType = (currentSpawnType - 1 + totalSpawnTypes) % totalSpawnTypes;
                    cout << "Spawning -->" << spawnDetails[currentSpawnType].character_name << " <<<" << endl;
                }
                if (event.key.code == Keyboard::F) {
                    currentItemType = (currentItemType + 1) % 5; // 5 = عدد الأنواع في enum
                    string names[] = { "Health","Omnitrix","Box","Fire","Lightning" };
                    cout << "Item --> " << names[currentItemType] << endl;
                }

                if (event.key.code == Keyboard::G) {
                    snapItemsToGround = !snapItemsToGround;
                    if (snapItemsToGround) cout << "Item Snapping --> ON (Items will snap to ground)" << endl;
                    else cout << "Item Snapping --> OFF (Items placed freely)" << endl;
                }
            }
            //هنا بمسح بالماوس الي انا عملته
            if (event.type == Event::MouseButtonPressed)
            {
                Vector2f worldPos = Big_Editor.mapPixelToCoords(Mouse::getPosition(Big_Editor), camera);
                if (event.mouseButton.button == Mouse::Left)
                {
                    // لازم لازم لازم تدوس c عشان تحط الشخصيات
                    if (Keyboard::isKeyPressed(Keyboard::C))
                    {
                        float cx = worldPos.x;
                        float cy = worldPos.y;

                        bool foundGround = false;
                        float groundTop = 0;
                        //spawn logic
                        for (int x = 0; x < mapW; x++)
                        {
                            for (int y = 0; y < mapH; y++)
                            {
                                if (mapData[x][y].hasCollision && mapData[x][y].textureRect.width > 0) {
                                    FloatRect bounds(x * tileSize, y * tileSize, mapData[x][y].textureRect.width, mapData[x][y].textureRect.height);
                                    FloatRect snapZone(bounds.left, bounds.top - 40.0f, bounds.width, bounds.height + 40.0f);
                                    if (snapZone.contains(cx, cy)) {
                                        groundTop = bounds.top;
                                        foundGround = true;
                                        break;
                                    }
                                }
                            }
                            if (foundGround) break;
                        }

                        if (!foundGround)
                        {
                            for (const auto& obj : levelObjects)
                            {
                                if (obj.hasCollision) {
                                    FloatRect bounds = obj.hitbox;
                                    FloatRect snapZone(bounds.left, bounds.top - 40.0f, bounds.width, bounds.height + 40.0f);
                                    if (snapZone.contains(cx, cy)) {
                                        groundTop = bounds.top;
                                        foundGround = true;
                                        break;
                                    }
                                }
                            }
                        }
                        if (foundGround)
                        {
                            float finalSnapY = groundTop - (spawnDetails[currentSpawnType].height / 2.0f);
                            int gx = floor(cx / tileSize);
                            float finalSnapX = (gx * tileSize) + (tileSize / 2.0f);
                            //عشان محطش بن تن مرتين             
                            if (spawnDetails[currentSpawnType].isEnemy == false)
                            {
                                points.erase(remove_if(points.begin(), points.end(),
                                    [](const SpawnPoint& s) { return spawnDetails[s.type].isEnemy == false; }), points.end());
                            }
                            points.push_back({ currentSpawnType, Vector2f(finalSnapX, finalSnapY) });
                            cout << "Placed" << spawnDetails[currentSpawnType].character_name << "!" << endl;
                        }
                        else
                        {
                            cout << "There is no ground." << endl;
                        }
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::V)) {
                        if (itemCount < MAX_ITEMS) {
                            float ix = worldPos.x;
                            float iy = worldPos.y;

                            if (snapItemsToGround) {
                                bool foundGround = false;
                                float groundTop = 0;

                                // 1. Check map grid for ground
                                for (int x = 0; x < mapW; x++) {
                                    for (int y = 0; y < mapH; y++) {
                                        if (mapData[x][y].hasCollision && mapData[x][y].textureRect.width > 0) {
                                            FloatRect bounds(x * tileSize, y * tileSize, mapData[x][y].textureRect.width, mapData[x][y].textureRect.height);
                                            FloatRect snapZone(bounds.left, bounds.top - 40.0f, bounds.width, bounds.height + 40.0f);
                                            if (snapZone.contains(ix, iy)) {
                                                groundTop = bounds.top;
                                                foundGround = true;
                                                break;
                                            }
                                        }
                                    }
                                    if (foundGround) break;
                                }

                                // 2. Check free-placed level objects for ground
                                if (!foundGround) {
                                    for (const auto& obj : levelObjects) {
                                        if (obj.hasCollision) {
                                            FloatRect bounds = obj.hitbox;
                                            FloatRect snapZone(bounds.left, bounds.top - 40.0f, bounds.width, bounds.height + 40.0f);
                                            if (snapZone.contains(ix, iy)) {
                                                groundTop = bounds.top;
                                                foundGround = true;
                                                break;
                                            }
                                        }
                                    }
                                }

                                // 3. Snap item to ground if found
                                if (foundGround) {
                                    // Snap X to center of the tile exactly like the character spawn
                                    int gx = floor(ix / tileSize);
                                    ix = (gx * tileSize) + (tileSize / 2.0f);

                                    // Snap Y depending on item's origin points
                                    if (currentItemType == MP::Box || currentItemType == MP::Fire || currentItemType == MP::Lightning) {
                                        // Origin is at the bottom for these items
                                        iy = groundTop;
                                    }
                                    else {
                                        // Health/Omnitrix radius is 40 (diameter 80), origin is default top-left
                                        iy = groundTop - 80.0f;
                                    }
                                    cout << "Item snapped to the ground!" << endl;
                                }
                                else {
                                    cout << "No ground found nearby! Placed item freely." << endl;
                                }
                            }
                            else {
                                cout << "Item placed freely!" << endl;
                            }

                            // Finalize placement
                            itemPoints[itemCount] = { currentItemType, Vector2f(ix, iy) };

                            // ADD THIS: Actually create the item object live in the editor!
                            Items(ix, iy, currentItemType);

                            itemCount++; // increment count after
                        }
                    }
                    else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                    {
                        Entity newObj;
                        newObj.sprite = Sprite(tileset);
                        newObj.sprite.setTextureRect(selectedRect);
                        newObj.sprite.setPosition(worldPos.x - (selectedRect.width / 2.0f), worldPos.y - (selectedRect.height / 2.0f));
                        newObj.hitbox = newObj.sprite.getGlobalBounds();
                        newObj.hasCollision = collisionMode;
                        levelObjects.push_back(newObj);
                    }

                }


                if (event.mouseButton.button == Mouse::Right)
                {
                    bool deletedSpawn = false;
                    for (int i = itemCount - 1; i >= 0; i--) {
                        FloatRect ib(itemPoints[i].position.x - 20, itemPoints[i].position.y - 20, 40, 40);
                        if (ib.contains(worldPos.x, worldPos.y)) {
                            itemPoints[i] = itemPoints[itemCount - 1];
                            itemCount--;
                            deletedSpawn = true;
                            break;
                        }
                    }
                    for (int i = points.size() - 1; i >= 0; i--)
                    {
                        FloatRect spawnBounds(points[i].position.x - 15, points[i].position.y - 15, 30, 30);
                        if (spawnBounds.contains(worldPos.x, worldPos.y))
                        {
                            points.erase(points.begin() + i);
                            deletedSpawn = true;
                            break;
                        }
                    }
                    if (!deletedSpawn)
                    {
                        for (int i = levelObjects.size() - 1; i >= 0; i--)
                        {
                            if (levelObjects[i].hitbox.contains(worldPos.x, worldPos.y)) {
                                levelObjects.erase(levelObjects.begin() + i);
                                break;
                            }
                        }
                    }
                }
            }
        }
        if (Big_Editor.hasFocus()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                camera.move(40.0f, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                camera.move(-40.0f, 0.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                camera.move(0.0f, 40.0f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                camera.move(0.0f, -40.0f);
            }
        }
        //=======================================//=======================//
        //inserting and deleting map tiles logic with mousee
        if (Big_Editor.hasFocus())
        {
            Vector2f worldPos = Big_Editor.mapPixelToCoords(Mouse::getPosition(Big_Editor), camera);
            int gx = floor(worldPos.x / tileSize);
            int gy = floor(worldPos.y / tileSize);
            if (gx >= 0 && gx < mapW && gy >= 0 && gy < mapH)
            {
                if (Mouse::isButtonPressed(Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                    mapData[gx][gy].textureRect = selectedRect;
                    mapData[gx][gy].hasCollision = collisionMode;
                }
                if (Mouse::isButtonPressed(Mouse::Right)) {
                    mapData[gx][gy].textureRect = IntRect(0, 0, 0, 0);
                    mapData[gx][gy].hasCollision = false;
                    for (int checkX = max(0, gx - 15); checkX <= gx; checkX++)
                    {
                        for (int checkY = max(0, gy - 15); checkY <= gy; checkY++)
                        {
                            if (mapData[checkX][checkY].textureRect.width > 0)
                            {
                                FloatRect tileBounds(checkX * tileSize, checkY * tileSize,
                                    mapData[checkX][checkY].textureRect.width,
                                    mapData[checkX][checkY].textureRect.height);
                                if (tileBounds.contains(worldPos.x, worldPos.y))
                                {
                                    mapData[checkX][checkY].textureRect = IntRect(0, 0, 0, 0);
                                    mapData[checkX][checkY].hasCollision = false;
                                }
                            }
                        }
                    }
                }
            }
        }
        Tile_Control.clear(Color(50, 50, 50));
        Tile_Control.draw(Sprite(tileset));
        if (isDragging) {
            Vector2i mPos = Mouse::getPosition(Tile_Control);
            RectangleShape dragBox;
            dragBox.setPosition((float)min(grabStart.x, mPos.x), (float)min(grabStart.y, mPos.y));
            dragBox.setSize(Vector2f((float)abs(mPos.x - grabStart.x), (float)abs(mPos.y - grabStart.y)));
            dragBox.setFillColor(Color(255, 0, 0, 100));
            Tile_Control.draw(dragBox);
        }
        else {
            RectangleShape box(Vector2f((float)selectedRect.width, (float)selectedRect.height));
            box.setPosition((float)selectedRect.left, (float)selectedRect.top);
            box.setOutlineColor(Color::Cyan);
            box.setOutlineThickness(2);
            box.setFillColor(Color::Transparent);
            Tile_Control.draw(box);
        }
        Tile_Control.display();
        //drawing
        Big_Editor.setView(camera);
        Big_Editor.clear(Color::Black);
        Big_Editor.draw(bgSprite);

        //drawing grid
        for (int x = 0; x < mapW; x++) {
            for (int y = 0; y < mapH; y++) {
                RectangleShape g(Vector2f(tileSize - 1, tileSize - 1));
                g.setPosition((float)x * tileSize, (float)y * tileSize);
                g.setFillColor(Color(0, 255, 0, 15));
                Big_Editor.draw(g);
            }
        }
        for (int x = 0; x < mapW; x++) {
            for (int y = 0; y < mapH; y++) {
                if (mapData[x][y].textureRect.width > 0) {
                    Sprite s(tileset);
                    s.setTextureRect(mapData[x][y].textureRect);
                    s.setPosition((float)x * tileSize, (float)y * tileSize);
                    Big_Editor.draw(s);
                    if (mapData[x][y].hasCollision) {
                        RectangleShape debugBox;
                        debugBox.setPosition((float)x * tileSize, (float)y * tileSize);
                        debugBox.setSize(Vector2f(mapData[x][y].textureRect.width, mapData[x][y].textureRect.height));

                        debugBox.setFillColor(Color::Transparent);
                        debugBox.setOutlineColor(Color::Red);
                        debugBox.setOutlineThickness(1);
                        Big_Editor.draw(debugBox);
                    }
                }
            }
        }
        //الأرض الي بتتحط ;-;
        for (int i = 0; i < levelObjects.size(); i++) {
            Big_Editor.draw(levelObjects[i].sprite);

            if (levelObjects[i].hasCollision) {
                RectangleShape debugBox;
                debugBox.setPosition(levelObjects[i].hitbox.left, levelObjects[i].hitbox.top);
                debugBox.setSize(Vector2f(levelObjects[i].hitbox.width, levelObjects[i].hitbox.height));
                debugBox.setFillColor(Color::Transparent);
                debugBox.setOutlineColor(Color::Red);
                debugBox.setOutlineThickness(1);
                Big_Editor.draw(debugBox);
            }
        }
        //3lamat el spawns
        for (const auto& sp : points) {
            float eHeight = spawnDetails[sp.type].height;
            float eWidth = 32.0f;
            // <3 بيرسم مستطيل نفس طول الشخصيه
            RectangleShape marker(Vector2f(eWidth, eHeight));
            marker.setOrigin(eWidth / 2.0f, eHeight / 2.0f);
            marker.setPosition(sp.position);
            Color mColor = spawnDetails[sp.type].marker_color;
            marker.setFillColor(Color(mColor.r, mColor.g, mColor.b, 100));
            marker.setOutlineColor(mColor);
            marker.setOutlineThickness(2);
            Big_Editor.draw(marker);
        }
        for (int i = 0; i < itemCount; i++) {

            if (itemPoints[i].type == MP::Health || itemPoints[i].type == MP::Omnitrix) {
                CircleShape marker(16);
                marker.setOrigin(16, 16);
                marker.setFillColor(itemPoints[i].type == MP::Health ?
                    Color(255, 0, 0, 150) : Color(0, 200, 255, 150));
                marker.setOutlineColor(Color::White);
                marker.setOutlineThickness(2);
                marker.setPosition(itemPoints[i].position);
                Big_Editor.draw(marker);
            }
            else {
                RectangleShape marker(Vector2f(32, 32));
                marker.setOrigin(16, 16);
                marker.setPosition(itemPoints[i].position);
                marker.setOutlineColor(Color::White);
                marker.setOutlineThickness(2);

                Color itemColors[] = {
                    Color(0,   0,   0,   0),  // Health    - مش هيتنادى
                    Color(0,   0,   0,   0),  // Omnitrix  - مش هيتنادى
                    Color(139, 69,  19,  150),  // Box       - بني
                    Color(255, 100, 0,   150),  // Fire      - برتقالي
                    Color(255, 255, 0,   150)   // Lightning - أصفر
                };

                marker.setFillColor(itemColors[itemPoints[i].type]);
                Big_Editor.draw(marker);
            }
        }

        Big_Editor.display();
    }
}
