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
RenderWindow window(VideoMode::getDesktopMode(), "SFML works!", Style::Fullscreen);
float scaleX;
float scaleY;
View view(FloatRect(0, 0, VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height));


bool touchedGround = false;

// player
const int aliensnumber = 7;
int transFramesCount[aliensnumber];
int current_player = 0, chosen_player = 0;
bool isTransing = false, ismoving = false, onground = true;
bool isAttacking = false, canclimb = 0;
const float MC_SCALE = 2.4f;

//enemy
int enemyAttackFrameCount;
int enemywalkingFrameCount;

// frames
int transIndex = 0, walkIndex = 0, idleIndex = 0, menuIndex = 0, menu_point = 0,
walkFramesCount[8], glide_index = 0, landindex = 0, flyindex = 0, flyidleindex = 0, alien_menupoint = 0, hitindex = 0;
int idleFramesCount[aliensnumber], menuDirection = 1, menu1FrameIndex = 0, credit_point = 0,
setting_point = 0, setting_Index = 0, alien_menuIndex = 0, climbindex = 0;
int sound_point = 0, credit_exit = 0, pause_point = 0, previous_menuIndex = 0, win_point = 0,
loss_index = 0, loss_point = 0;
int AttackIndex = 0, jumpIndex = 0, secondjumpIndex = 0;
int AttackFramesCount[aliensnumber], jumpFramesCount[aliensnumber], secondjumpFramesCount[aliensnumber],
glideFramesCount[aliensnumber], landFrameCount[aliensnumber], hitframecount[aliensnumber],
climbframecount, climbupframecount, climbdownframecount;
int combo_frame_count = 0, SpecialAttackIndex = 0, dieindex = 0, climbupindx = 0, climbdownindex = 0;
bool kWasPressed = false, combo_attack_done = false, jump_attack = false, uWasPressed = false, isSpecialAttacking = false, is_gliding = false;
float comboTimeout = 0.8f;
Texture Attack_animation_B[aliensnumber], Special_Attack_animation[aliensnumber], Attack_animation_C[aliensnumber],
Jump_Attack_animation[aliensnumber], fly_animation[aliensnumber], fly_idleanimation[aliensnumber], diediedie[aliensnumber],
hit_animation[aliensnumber], climb, climbup, climbdown;
int AttackFramesCount_B[aliensnumber], AttackFramesCount_C[aliensnumber], Jump_AttackFramesCount[aliensnumber],
special_AttackFramesCount[aliensnumber], dieframescount[aliensnumber];

//clock
Clock comboClock;
Clock specialAttackClock;
Clock hit;
Clock transClock;





//bool isminigameinit = false;



int minigameindx = 0, minigamepoint = 0;

Texture miniframe, movingminitex;
Sprite minisprite, movingminisp;
Text minitext[8], pass[8];
Font minigamefont;
Clock miniclock, anotherminiclock;
Text minitimer, miniword;
bool done = 0, openlock = 0;
int remainingml = 0;
int countcount = 0;
RectangleShape minigamerect;
float minirectpx = 300.0f, minirectpy = 490.0f;
bool miniright = 0, minileft = 0, minienterpressed = 0;
int miniindx = 0;

float timefortheminigame = 20.0f;
bool miniopened = 0;

//string fnum[5][2] = { {"3 ", "2 "} , { "4 ", "2 " } , { "7 ", "5 " },  { "1 ", "0 " }, { "6 ", "5 " } } ;
string passlist[8]{ "E ", "8 " , "R ", "4 " , "F " , "9 " , "4 " , "A " };

string minilist[8] = { "4 " , "R " , "8 " , "E " , "A " , "4 " , "9 " , "F " };



Sprite transOverlaySp;
Texture trans_frames[aliensnumber], flya_animation[aliensnumber], flyw_animation;

Texture bendie;
Sprite omnibar, emptyomnibar;
Texture omnibartex, emptyomnibartex;

float all = 30.0f, sspeed = 5.0f, visualOmni = 30.0f;

float omnitime = 30.0f, recharge = 10.0f;
Clock omni, aaa;

int flyaframecount = 3, flyaindx = 0, flywframecount = 3, flywindex = 0;


//sounds
SoundBuffer mainmenu_mus, Play_mu, credit_mu, menupoint_mu,
enter_mu, settingpoint_mu, creditpoint_mu, win_music_mu, lv1_music_mu,
pausepoint_mu, trans_mu, changealien_mu;
Sound mainmenu_music, Play_sound, credit_music, menupoint_sound,
enter_sound, settingpoint_sound, creditpoint_sound, win_music_sound, lv1_music_so, pausepoint_sou, trans_sou, changealien_sou;
SoundBuffer swamptrans_buf, bigchilltrans_buf, brainstormtrans_buf,
spidertrans_buf, jetraytrans_buf, bigchucktrans_buf, omnitrix_time_mu;
Sound swamptrans_sou, bigchilltrans_sou, brainstormtrans_sou,
spidertrans_sou, jetraytrans_sou, bigchucktrans_sou, omnitrix_time_sou;
SoundBuffer walk_forest_mu, lv1_soun_mu, Rain_mu, lv3_soun_mu, lv4_soun_mu, boss_soun_mu,pause_music_mu,
jump_ben_mu,land_ben_mu,attack_ben_mu, jump_spider_mu, attack_spider_mu, jump_chill_mu, attack_chill_mu,land_chill_mu,
jump_swamp_mu, attack_swamp_mu, land_swamp_mu, jump_brain_mu, attack_brain_mu, land_brain_mu,
jump_jetray_mu, attack_jetray_mu, land_jetray_mu,ben_die_mu;
Sound walk_forest_so, lv1_soun_so, Rain_so, lv3_soun_so, lv4_soun_so, boss_soun_so,pause_music_so,
jump_ben_so, land_ben_so, attack_ben_so, jump_spider_so, attack_spider_so, jump_chill_so, attack_chill_so,land_chill_so,
jump_swamp_so, attack_swamp_so, land_swamp_so, jump_brain_so, attack_brain_so, land_brain_so,
jump_jetray_so, attack_jetray_so, land_jetray_so,ben_die_so;


int jump_counter = 0, was_gliding = 0, landing = 0, flyFrameCount[8], flyidleframecount[8];
bool spacewaspressed = false;


//speed
struct moveStats {
    float speedX;
    float speedY;
};
moveStats speed[10];
Vector2f velocity;

//car
RectangleShape CarBox;
Sprite CarSp;
Texture CarTex;
//


bool isFallingBeforeDeath = false;


//texture for player
Sprite player[aliensnumber];
Texture Attack_animation[aliensnumber];
Texture idle_animation[aliensnumber];
Texture walk_animation[aliensnumber];
Texture trans_animation;
Texture jump_animation[aliensnumber];
Texture secondjump_animation[aliensnumber];
Texture glide_animation[aliensnumber], land_animation[aliensnumber];


//win
Texture win_animation;
bool isWinning = false;
int winAnimIndex = 0;
int winAnimFrameCount = 3;
Clock winClock;



// texture for omnitrix
Sprite Omnitrixsp;
Texture greenOmnitrixTex[aliensnumber];
Texture whiteOmnitrixTex[aliensnumber];


//clock & event
Event event;
Clock animClock;
Clock menu1Clock;
Clock damageClock;
float cooldownTime = 1.0f;
Clock jumpClock;

// box 
RectangleShape characterbox[aliensnumber];
RectangleShape characterboxarm[aliensnumber];
RectangleShape ground;

//fonts
Font credit_font;
Font menu_font;
Font setting_font;
Font back_font;
Font setting_word_font;
Font pause_word_font;
Font pause_list_font;
Font loss_list_font;

// menu
Texture menu_frame[15];
Texture menu2sprite;
Sprite main_menu2;
Texture creditsprite;
Sprite credit;
Sprite menuSprite;
Texture setting_frame[5];
Sprite setting_sprite;
Texture pause_frames[4];
Sprite pause_sprite;
Texture win_sprite;
Sprite win_menu;
Texture loss_frame[3];
Sprite loss_sprite;
Texture about_game_fra;
Sprite about_game_spr;
Texture alien_frames[7];
Sprite alien_sprite;
Texture htp_fra;
Sprite htp_spr;

//main menu words
Text maintext[4];
string mainlist[4]{ "It's Hero Time","Setting","Credits","Power Down" };

//loss menu words
Text losstext[3];
string losslist[3]{ "Reboot the Omnitrix","Omnitrix Controls","Ben Needs a Break" };

//credits words
Text credittext[7];
string nameslist[7]{ "Moaz Alaa" , "Ahmed Gharib" , "Mohamed Hisham","Ahmed Mahmoud","Omar Abdullah","Sondos Sherif","Ayman Ehab" };
Text watch_word;

//win menu words
Text wintext[4];
string winlist[4]{ "NEXT MISSION","RESTART","OMNITRIX CONFIG","THE RUST BUCKET" };

//setting words
Text setting_text[5];
String setting_list[5]{ "Sound" , "How to play" , "ALiens" ,"About Game" , "Back" };
Text sound_text[4];
String sound_muted[4]{ "Sound : \n   ON "," Better hear the enemies coming","Sound : \n   OFF ","Silent mode Ben is taking a nap" };
Text flavor_text[2];
String flavor_words[2]{ "OMNITRIX AUDIO SYSTEM v1.0\nSIGNAL: 100% | CORE: STABLE","OMNITRIX AUDIO SYSTEM v1.0\nSIGNAL: 0% | CORE: UNSTABLE" };
Text Setting_word;
Text back_list[4];
String back_word[4]{ "Go","Save","The","World" };
Text pause_text[4];
String pause_list[4]{ "Resume game","settings","credits","back to main menu" };
Text pause_word;

//leveles
int currentEditorLevel = 1;


enum Transes {
    ben, swampfire, BigChill, jetray, SpiderMonkey, bigchuck, brainstorm,
};
enum Enemy_type {
    First = 0, Second = 1, Level1Boss = 2
};
int unlockedaliens = 7;



// Rain and thunder System
Clock thunderClock;
float nextThunderTime = 3.f + rand() % 5;
RectangleShape flashOverlay;
float flashAlpha = 0.f;
SoundBuffer thunderBuf;
Sound thunderSou;
struct Raindrop {
    float x, y;
    float speed;
    float length;
};

const int NUM_DROPS = 300;
Raindrop raindrops[NUM_DROPS];

void initRain() {
    for (int i = 0; i < NUM_DROPS; i++) {
        raindrops[i].x = rand() % 1800;
        raindrops[i].y = (float)(rand() % 2700) - 1800.f;
        raindrops[i].speed = 400.f + rand() % 200;
        raindrops[i].length = 15.f + rand() % 20;
    }
}
Clock rainClock;

void drawRain() {
    float dt = rainClock.restart().asSeconds();

    if (dt > 0.05f) dt = 0.05f;

    RectangleShape drop;
    drop.setFillColor(Color(174, 214, 241, 160));

    for (int i = 0; i < NUM_DROPS; i++) {
        raindrops[i].y += raindrops[i].speed * dt;


        if (raindrops[i].y > 900.f) {
            raindrops[i].y = 0;
            raindrops[i].x = rand() % 1800;
        }
        if (raindrops[i].x > 1800.f)
            raindrops[i].x = 0;

        drop.setSize(Vector2f(2.f, raindrops[i].length));
        drop.setOrigin(1.f, raindrops[i].length / 2.f); 
        drop.setPosition(raindrops[i].x, raindrops[i].y);
        window.draw(drop);
    }
    // Thunder flash
    float thunderDt = thunderClock.getElapsedTime().asSeconds();

    if (thunderDt >= nextThunderTime) {
        thunderSou.play();
        flashAlpha = 180.f; // ابدأ الفلاشة
        thunderClock.restart();
        nextThunderTime = 4.f + rand() % 6; // رعد جاي بعد 4-10 ثواني
    }

    // fade الفلاشة
    if (flashAlpha > 0.f) {
        flashAlpha -= 300.f * dt;
        if (flashAlpha < 0.f) flashAlpha = 0.f;
    }

    flashOverlay.setFillColor(Color(220, 230, 255, (sf::Uint8)flashAlpha));
    window.draw(flashOverlay);
}




//map editor
Texture tileset;
Texture bgTexture;
Sprite bgSprite;
View camera(sf::FloatRect(0, 0, 1800, 900));
const int mapW = 500;
const int mapH = 35;
const int tileSize = 32;
IntRect selectedRect(0, 0, tileSize, tileSize);
Vector2i grabStart;
bool isDragging = false;

struct GridTile {
    IntRect textureRect;
    bool hasCollision;
};
GridTile mapData[mapW][mapH];
struct Entity {
    Sprite sprite;
    FloatRect hitbox;
    bool hasCollision;
};
vector<Entity> levelObjects;
bool collisionMode = true;

struct Background_Details {
    Texture texture;
    Sprite sprite;
};
vector<Background_Details> levelBackgrounds;
struct SpawnPoint {
    int type;
    Vector2f position;
};
vector<SpawnPoint> points;

struct Spawn_req {
    string character_name;
    bool isEnemy;
    int gameID;
    float height;
    Color marker_color;
};
Spawn_req spawnDetails[] = {

    {"Ben 10 (Player)",  false, 0, 60.0f, Color::Green},
    {"Red Enemy (Type 0)",true,  0, 45.0f, Color::Red},
    {"Blue Enemy (Type 1)",true,  1, 45.0f, Color::Blue},
    { "black Enemy (Type 2)",true,  2, 45.0f, Color::Black }
};
int totalSpawnTypes = sizeof(spawnDetails) / sizeof(spawnDetails[0]);
int currentSpawnType = 0;
bool BenAttacking = false;
bool kPressedNow = false;
bool UPressedNow = false;
int Ben_Power[8][2] = {
    {10,0},{15,20},{20,30},{15,30},
    {20,40},{15,30},{20,30},{30,40}
};
Clock recoveryClock;
Texture Enemy_animation_walk[7];
Texture Enemy_animation_idle[7];
Texture Enemy_animation_attack[7];
Texture Enemy_animation_attack2[7];
Texture Enemy_animation_hurt[7];
Texture Enemy_animation_die[7];
int Enemy_idle_animation_counter[7]{ 8,8,8,4,3,16,3 };
int Enemy_walk_animation_counter[7]{ 10,8,8,8,10,8,10 };
int Enemy_attack_animation_counter[7]{ 20,13,6,8,3,30,3 };
int Enemy_attack2_animation_counter[7]{ 1,1,6 ,1,1,1,1 };
int Enemy_hurt_animation_counter[7]{ 4,5,4 ,1,2,16,2 };
int Enemy_die_animation_counter[7]{ 14,9,6 ,8,7,40,7 };
Clock EE;

//health and omnitrix bubbles
const int bubblenum = 4;
CircleShape HealthBubble[bubblenum];
CircleShape OmnitrixBubble[bubblenum];


Vector2f healthBubblePositions[3][4] = {
    // Level 1
    { {4828, 715}, {8175, 835}, {10700, 755 - 70}, {13245, 880} },
    // Level 3
    { {3828, 715}, {3000,400}, {5000,600}, {7000,500} },
    // Level 4
    { {500,800},  {2000,300}, {4000,700}, {6000,400} }
};

Vector2f omnitrixBubblePositions[3][4] = {
    { {4500 - 20, 830}, {8555, 755 - 70}, {11750, 755 - 70}, {13290, 920} },
    { {1500,100}, {3500,400}, {5500,600}, {7500,500} },
    { {800,800},  {2500,300}, {4500,700}, {6500,400} }
};

bool healthCollected[4] = { false,false,false,false };
bool omnitrixCollected[4] = { false,false,false,false };

Sprite omniBubbleSp[4];
Texture OmniBubbleTex[24];

Sprite hpBubbleSp[4];
Texture hpBubbleTex[24];
int frameCounterToHealth = 0;
int frameCounterToOmnitrix = 0;
float timerToHealth = 0.0f;
float timerToOmnitrix = 0.0f;

Clock HPBubbleanimationClock;
Clock OMBubbleanimationClock;

//health bar
enum Bars {
    first, second, third, fourth, fifth, last
};
int hp = 60;
Sprite hpBar;
Texture BarsTex[7];
Sprite emptyHPBar;
Texture emptyHPBarTex;

void resetItems() {
    int lvl = currentEditorLevel - 1;
    for (int i = 0; i < bubblenum; i++) {
        healthCollected[i] = false;
        omnitrixCollected[i] = false;

        HealthBubble[i].setPosition(healthBubblePositions[lvl][i]);
        hpBubbleSp[i].setPosition(
            healthBubblePositions[lvl][i].x - 50,
            healthBubblePositions[lvl][i].y - 60
        );

        OmnitrixBubble[i].setPosition(omnitrixBubblePositions[lvl][i]);
        omniBubbleSp[i].setPosition(
            omnitrixBubblePositions[lvl][i].x - 50,
            omnitrixBubblePositions[lvl][i].y - 60
        );
    }
}




bool dialogue1 = false, dialogue2 = false, startdialogue = false;
Clock levelStart;
bool dialogue3 = false;


Texture boxtx[5];
Texture firetx[5];
Texture light;
enum MP {
    Health, Omnitrix,Box,Fire, Lightning
};
bool snapItemsToGround = true;
const int MAX_ITEMS = 100;

struct ItemPoint {
    int type;
    Vector2f position;
};

ItemPoint itemPoints[MAX_ITEMS];
int itemCount = 0;
int currentItemType = MP::Health;

string cheatCode_health = "unh";
string cheatCode_omnitrix = "unt";
string current_code="";
bool cheatCodeHealthActive = false;
bool cheatCodeOmnitrixActive = false;
struct Item {
    int type;
    CircleShape shape;
    RectangleShape box;
    Sprite sprite;
    bool collected = false;
    int frame = 0;
    Clock boxclock;
    int BoxHit = 4;
    Clock lightactive;
	bool actrive = false;
	bool isHitInThisAttack = false;
};
vector<Item> itemss;
void Items(float x, float y, int type) {
    Item new_item;
	new_item.type = type;
        if (type == MP::Omnitrix) {
        new_item.shape.setRadius(20);
        new_item.shape.setFillColor(Color::Green);
        new_item.sprite.setOrigin(new_item.sprite.getLocalBounds().width / 2, new_item.sprite.getLocalBounds().height/2.0f);
        new_item.shape.setPosition(x, y);
        new_item.sprite.setScale(1.5, 1.5);
        new_item.sprite.setPosition(x-64,y-60);
    }
    else if (type == MP::Health) {
        new_item.shape.setRadius(20);
        new_item.shape.setFillColor(Color::Red);
        new_item.sprite.setOrigin(new_item.sprite.getLocalBounds().width / 2, new_item.sprite.getLocalBounds().height / 2.0f);
        new_item.sprite.setScale(1.5, 1.5);
        new_item.shape.setPosition(x, y);

        new_item.sprite.setPosition(x-64,y-60);
    }
    else if (type == MP::Box) {
        new_item.box.setSize(Vector2f(140.0f, 140.0f));
        new_item.box.setFillColor(Color::Blue);
        new_item.box.setPosition(x, y);
        new_item.sprite.setTexture(boxtx[0]);
        new_item.shape.setPosition(x, y);
        new_item.box.setOrigin(new_item.box.getSize().x / 2, new_item.box.getSize().y);
        new_item.sprite.setOrigin(new_item.sprite.getLocalBounds().width / 2, new_item.sprite.getLocalBounds().height);
        new_item.sprite.setPosition(new_item.box.getPosition());
        new_item.BoxHit = 0;
    }
    else if (type == MP::Fire) {
        new_item.box.setSize(Vector2f(100.0f, 150.0f));
        new_item.box.setFillColor(Color::Red);
        new_item.box.setPosition(x, y);
        new_item.shape.setPosition(x, y);
        new_item.sprite.setTexture(firetx[0]);
        new_item.box.setOrigin(new_item.box.getSize().x / 2, new_item.box.getSize().y);
        new_item.sprite.setOrigin(new_item.sprite.getLocalBounds().width / 2, new_item.sprite.getLocalBounds().height);
        new_item.sprite.setPosition(new_item.box.getPosition());
        new_item.BoxHit = 4;
        new_item.sprite.setScale(4, 4);
    }
    else if (type == MP::Lightning) {
        new_item.box.setSize(Vector2f(50.0f, 1000.0f));
        new_item.box.setFillColor(Color::Black);
        new_item.box.setPosition(x, y);
        new_item.shape.setPosition(x, y);
        new_item.sprite.setTexture(light);
        new_item.box.setOrigin(new_item.box.getSize().x / 2, new_item.box.getSize().y);
        new_item.sprite.setOrigin(new_item.sprite.getLocalBounds().width / 2, new_item.sprite.getLocalBounds().height);
        new_item.sprite.setPosition(new_item.box.getPosition());
        FloatRect boxBounds = new_item.box.getGlobalBounds();
        FloatRect spriteSize = new_item.sprite.getLocalBounds();

        float scaleY = boxBounds.height / spriteSize.height;

        new_item.sprite.setScale(1, scaleY);
    }
    itemss.push_back(new_item);
}

