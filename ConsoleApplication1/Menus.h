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

void menu_start() {

    //loading menus frames
    for (int i = 0; i < 15; i++) {
        string fileName = "menus/menu frames/frame " + to_string(i + 1) + ".jpg";
        if (!menu_frame[i].loadFromFile(fileName)) {
            cout << "Error loading " << fileName << endl;
        }
    }

    //loading loss menu frames
    for (int i = 0; i < 3; i++) {
        string fileName = "menus/lose menu/frame " + to_string(i + 1) + ".png";
        if (!loss_frame[i].loadFromFile(fileName)) {
            cout << "Error loading " << fileName << endl;
        }
    }

    //loading setting frames
    for (int i = 0; i < 5; i++) {
        string fileName = "menus/setting/frame " + to_string(i + 1) + ".png";
        if (!setting_frame[i].loadFromFile(fileName)) {
            cout << "Error loading " << fileName << endl;
        }
    }

    //loading pause frames
    for (int i = 0; i < 4; i++) {
        string fileName = "menus/pause/frame " + to_string(i + 1) + ".jpg";
        if (!pause_frames[i].loadFromFile(fileName)) {
            cout << "Error loading " << fileName << endl;
        }
    }

    //loading aliens menu
    for (int i = 0; i < 7; i++) {
        string fileName = "menus/aliens menu/frame " + to_string(i + 1) + ".png";
        if (!alien_frames[i].loadFromFile(fileName)) {
            cout << "Error loading " << fileName << endl;
        }
    }

    for (int i = 0; i < 8; i++) {
        pass[i].setFont(minigamefont);
        pass[i].setString(passlist[i]);
        pass[i].setCharacterSize(70);
        pass[i].setOrigin(pass[i].getLocalBounds().width / 2.0f, pass[i].getLocalBounds().height / 2.0f);
    }
    pass[0].setPosition(Vector2f(300, 350));
    pass[1].setPosition(Vector2f(400, 350));
    pass[2].setPosition(Vector2f(500, 350));
    pass[3].setPosition(Vector2f(600, 350));
    pass[4].setPosition(Vector2f(700, 350));
    pass[5].setPosition(Vector2f(800, 350));
    pass[6].setPosition(Vector2f(900, 350));
    pass[7].setPosition(Vector2f(1000, 350));

    //loading sound
    mainmenu_mus.loadFromFile("Audios/Ben 10 intro.wav");
    mainmenu_music.setBuffer(mainmenu_mus);
    Play_mu.loadFromFile("Audios/It's hero time.wav");
    Play_sound.setBuffer(Play_mu);
    credit_mu.loadFromFile("Audios/credit music.wav");
    credit_music.setBuffer(credit_mu);
    menupoint_mu.loadFromFile("Audios/menu_points.wav");
    menupoint_sound.setBuffer(menupoint_mu);
    enter_mu.loadFromFile("Audios/enter sound.wav");
    enter_sound.setBuffer(enter_mu);
    settingpoint_mu.loadFromFile("Audios/setting point_sound.wav");
    settingpoint_sound.setBuffer(settingpoint_mu);
    creditpoint_mu.loadFromFile("Audios/credit point_sound.wav");
    creditpoint_sound.setBuffer(creditpoint_mu);
    win_music_mu.loadFromFile("Audios/pause.wav");
    win_music_sound.setBuffer(win_music_mu);
    lv1_music_mu.loadFromFile("Audios/game_music.wav");
    lv1_music_so.setBuffer(lv1_music_mu);
    pausepoint_mu.loadFromFile("Audios/pause_point.wav");
    pausepoint_sou.setBuffer(pausepoint_mu);
    trans_mu.loadFromFile("Audios/trans_sound.wav");
    trans_sou.setBuffer(trans_mu);
    changealien_mu.loadFromFile("Audios/change_between_aliens.wav");
    changealien_sou.setBuffer(changealien_mu);

    swamptrans_buf.loadFromFile("Audios/trans sound/swampfire.wav");
    swamptrans_sou.setBuffer(swamptrans_buf);
    bigchilltrans_buf.loadFromFile("Audios/trans sound/bigchill.wav");
    bigchilltrans_sou.setBuffer(bigchilltrans_buf);
    spidertrans_buf.loadFromFile("Audios/trans sound/spider monkey.wav");
    spidertrans_sou.setBuffer(spidertrans_buf);
    brainstormtrans_buf.loadFromFile("Audios/trans sound/brainstorm.wav");
    brainstormtrans_sou.setBuffer(brainstormtrans_buf);
    jetraytrans_buf.loadFromFile("Audios/trans sound/jetray.wav");
    jetraytrans_sou.setBuffer(jetraytrans_buf);
    bigchucktrans_buf.loadFromFile("Audios/trans sound/bigchuck.wav");
    bigchucktrans_sou.setBuffer(bigchucktrans_buf);
    omnitrix_time_mu.loadFromFile("Audios/omnitrix time_out.wav");
    omnitrix_time_sou.setBuffer(omnitrix_time_mu);

    walk_forest_mu.loadFromFile("Audios/lv1_walk_sound2.wav");
    walk_forest_so.setBuffer(walk_forest_mu);
    lv1_soun_mu.loadFromFile("Audios/lv1_natu.wav");
    lv1_soun_so.setBuffer(lv1_soun_mu);
    Rain_mu.loadFromFile("Audios/Rain.wav");
    Rain_so.setBuffer(Rain_mu);
    thunderBuf.loadFromFile("Audios/thunder.wav");
    thunderSou.setBuffer(thunderBuf);
    lv3_soun_mu.loadFromFile("Audios/lvl3_music.wav");
    lv3_soun_so.setBuffer(lv3_soun_mu);
    lv4_soun_mu.loadFromFile("Audios/lvl4_music.wav");
    lv4_soun_so.setBuffer(lv4_soun_mu);
    boss_soun_mu.loadFromFile("Audios/boss_music.wav");
    boss_soun_so.setBuffer(boss_soun_mu);
    pause_music_mu.loadFromFile("Audios/pause_music.wav");
    pause_music_so.setBuffer(pause_music_mu);
    jump_ben_mu.loadFromFile("Audios/ben 10 jump.wav");
    jump_ben_so.setBuffer(jump_ben_mu);
    land_ben_mu.loadFromFile("Audios/ben 10 land.wav");
    land_ben_so.setBuffer(land_ben_mu);
    attack_ben_mu.loadFromFile("Audios/ben 10 attack.wav");
    attack_ben_so.setBuffer(attack_ben_mu);
    jump_spider_mu.loadFromFile("Audios/spidermonkey jump.wav");
    jump_spider_so.setBuffer(jump_spider_mu);
    attack_spider_mu.loadFromFile("Audios/spidermonkey attack.wav");
    attack_spider_so.setBuffer(attack_spider_mu);
    jump_chill_mu.loadFromFile("Audios/bigchill jump.wav");
    jump_chill_so.setBuffer(jump_chill_mu);
    land_chill_mu.loadFromFile("Audios/bigchill land.wav");
    land_chill_so.setBuffer(land_chill_mu);
    attack_chill_mu.loadFromFile("Audios/bigchill attack.wav");
    attack_chill_so.setBuffer(attack_chill_mu);

    jump_brain_mu.loadFromFile("Audios/brainstorm jump.wav");
    jump_brain_so.setBuffer(jump_brain_mu);
    land_brain_mu.loadFromFile("Audios/brainstorm land.wav");
    land_brain_so.setBuffer(land_brain_mu);
    attack_brain_mu.loadFromFile("Audios/brainstorm attack.wav");
    attack_brain_so.setBuffer(attack_brain_mu);

    jump_swamp_mu.loadFromFile("Audios/swampfire jump.wav");
    jump_swamp_so.setBuffer(jump_swamp_mu);
    land_swamp_mu.loadFromFile("Audios/swampfire land.wav");
    land_swamp_so.setBuffer(land_swamp_mu);
    attack_swamp_mu.loadFromFile("Audios/swampfire attack.wav");
    attack_swamp_so.setBuffer(attack_swamp_mu);

    jump_jetray_mu.loadFromFile("Audios/jetray jump.wav");
    jump_jetray_so.setBuffer(jump_jetray_mu);
    land_jetray_mu.loadFromFile("Audios/jetray land.wav");
    land_jetray_so.setBuffer(land_jetray_mu);
    attack_jetray_mu.loadFromFile("Audios/jetray attack.wav");
    attack_jetray_so.setBuffer(attack_jetray_mu);

    ben_die_mu.loadFromFile("Audios/ben die.wav");
    ben_die_so.setBuffer(ben_die_mu);

    //play menu sound
    mainmenu_music.setLoop(true);
    mainmenu_music.setVolume(60);
    mainmenu_music.play();
    menupoint_sound.setVolume(30);
    settingpoint_sound.setVolume(40);
    creditpoint_sound.setVolume(40);
    lv1_music_so.setVolume(25);
    win_music_sound.setVolume(40);
    omnitrix_time_sou.setVolume(50);
    lv1_soun_so.setVolume(30);
    walk_forest_so.setVolume(40);
    Rain_so.setVolume(50);
    thunderSou.setVolume(40);
    lv3_soun_so.setVolume(40);
    lv4_soun_so.setVolume(40);
    boss_soun_so.setVolume(40);
    pause_music_so.setVolume(40);
    flashOverlay.setSize(Vector2f(1800, 900));
    flashOverlay.setFillColor(Color(255, 255, 255, 0));



    //loading fonts
    if (!credit_font.loadFromFile("fonts/Iceland-Regular.ttf")) {
        cout << "Error loading font! Make sure Iceland-Regular.ttf is in the project folder." << endl;
    }
    if (!menu_font.loadFromFile("fonts/Pixel Game.otf")) {
        cout << "Error loading font2! Make sure Pixel Game.otf is in the project folder." << endl;
    }
    if (!setting_font.loadFromFile("fonts/GrinchedRegular.otf")) {
        cout << "Error loading font2! Make sure GrinchedRegular.otf is in the project folder." << endl;
    }
    if (!back_font.loadFromFile("fonts/HOMOARAK.TTF")) {
        cout << "Error loading font! Make sure HOMOARAK.TTF is in the project folder." << endl;
    }
    if (!setting_word_font.loadFromFile("fonts/Facon.ttf")) {
        cout << "Error loading font! Make sure Facon.ttf is in the project folder." << endl;
    }
    if (!pause_word_font.loadFromFile("fonts/Game Paused DEMO.otf")) {
        cout << "Error loading font! Make sure Game Paused DEMO.otf is in the project folder." << endl;
    }
    if (!pause_list_font.loadFromFile("fonts/Game Paused DEMO.otf")) {
        cout << "Error loading font! Make sure Game Paused DEMO.otf is in the project folder." << endl;
    }
    if (!loss_list_font.loadFromFile("fonts/Game Paused DEMO.otf")) {
        cout << "Error loading font! Make sure Game Paused DEMO.otf is in the project folder." << endl;
    }
    if (!minigamefont.loadFromFile("fonts/Facon.ttf")) {
        cout << "Error loading font! Make sure Iceland-Regular.ttf is in the project folder." << endl;
    }
   
    
    // load menus frames
    menuSprite.setTexture(menu_frame[0]);
    menuSprite.setScale(1800.0f / menuSprite.getLocalBounds().width, 900.0f / menuSprite.getLocalBounds().height);
    menu2sprite.loadFromFile("menus/menu.jpg");
    main_menu2.setTexture(menu2sprite);
    main_menu2.setScale(1800.0f / main_menu2.getLocalBounds().width, 900.0f / main_menu2.getLocalBounds().height);
    creditsprite.loadFromFile("menus/credit_menu.png");
    credit.setTexture(creditsprite);
    credit.setScale(1800.0f / credit.getLocalBounds().width, 900.0f / credit.getLocalBounds().height);
    win_sprite.loadFromFile("menus/win_menu.png");
    win_menu.setTexture(win_sprite);
    win_menu.setScale(1800.0f / win_menu.getLocalBounds().width, 900.0f / win_menu.getLocalBounds().height);
    setting_sprite.setTexture(setting_frame[0]);
    setting_sprite.setScale(1800.0f / setting_sprite.getLocalBounds().width, 900.0f / setting_sprite.getLocalBounds().height);
    loss_sprite.setTexture(loss_frame[0]);
    loss_sprite.setScale(1800.0f / loss_sprite.getLocalBounds().width, 900.0f / loss_sprite.getLocalBounds().height);
    about_game_fra.loadFromFile("menus/about game_menu.png");
    about_game_spr.setTexture(about_game_fra);
    about_game_spr.setScale(1800.0f / about_game_spr.getLocalBounds().width, 900.0f / about_game_spr.getLocalBounds().height);
    alien_sprite.setTexture(alien_frames[0]);
    alien_sprite.setScale(1800.0f / alien_sprite.getLocalBounds().width, 900.0f / alien_sprite.getLocalBounds().height);
    htp_fra.loadFromFile("menus/htp_menu.png");
    htp_spr.setTexture(htp_fra);
    htp_spr.setScale(1800.0f / htp_spr.getLocalBounds().width, 900.0f / htp_spr.getLocalBounds().height);
    miniframe.loadFromFile("minigame.jpeg");
    minisprite.setTexture(miniframe);
    minisprite.setScale(1800.0f / minisprite.getLocalBounds().width, 900.0f / minisprite.getLocalBounds().height);
    movingminitex.loadFromFile("movingmini.png");
    movingminisp.setTexture(movingminitex);
    movingminisp.setScale(220.0f / movingminisp.getLocalBounds().width, 100.0f / movingminisp.getLocalBounds().height);
    //minigamerect.setOutlineColor(Color(255, 255, 255, 50)); 
    movingminisp.setColor(Color(0, 255, 0, 170));
    minitimer.setFont(minigamefont);
    minitimer.setCharacterSize(50);
    minitimer.setFillColor(Color::White);
    minitimer.setPosition(Vector2f(1315.0f, 750.0f));
    //miniwin.setPosition(850, 100);
    
     
    //win texts
    for (int i = 0; i < 4; i++) {
        wintext[i].setFont(pause_list_font);
        wintext[i].setString(winlist[i]);
        wintext[0].setCharacterSize(50);
        wintext[1].setCharacterSize(50);
        wintext[2].setCharacterSize(37);
        wintext[3].setCharacterSize(37);
        wintext[i].setFillColor(Color::White);
        wintext[i].setOrigin(wintext[i].getLocalBounds().width / 2.0f, wintext[i].getLocalBounds().height / 2.0f);
        if (i == 0 || i == 3) {
            wintext[0].setPosition(Vector2f(430, 740));
            wintext[3].setPosition(Vector2f(1400, 740));
        }
        else {
            wintext[1].setPosition(Vector2f(770, 790));
            wintext[2].setPosition(Vector2f(1075, 790));
        }
    }

    //loss text
    for (int i = 0; i < 3; i++) {
        losstext[i].setFont(loss_list_font);
        losstext[i].setString(losslist[i]);
        losstext[i].setCharacterSize(40);
        losstext[i].setFillColor(Color::White);
        losstext[i].setOrigin(losstext[i].getLocalBounds().width / 2.0f, losstext[i].getLocalBounds().height / 2.0f);
        losstext[0].setPosition(Vector2f(900, 470));
        losstext[1].setPosition(Vector2f(900, 585));
        losstext[2].setPosition(Vector2f(900, 700));
    }

    
    //texts menu
    for (int i = 0; i < 4; i++) {
        maintext[i].setFont(menu_font);
        maintext[i].setString(mainlist[i]);
        maintext[i].setCharacterSize(100);
        maintext[i].setFillColor(Color::White);
        maintext[i].setOrigin(maintext[i].getLocalBounds().width / 2.0f, maintext[i].getLocalBounds().height / 2.0f);
        maintext[i].setPosition(Vector2f(1400, 325 + (i * 120)));
    }

    //texts credit
    for (int i = 0; i < 7; i++) {
        credittext[i].setFont(credit_font);
        credittext[i].setString(nameslist[i]);
        credittext[i].setCharacterSize(80);
        credittext[i].setFillColor(Color::Green);
        credittext[i].setPosition(Vector2f(800, 160 + (i * 100)));
        credittext[i].setOrigin(credittext[i].getLocalBounds().width / 2.0f, credittext[i].getLocalBounds().height / 2.0f);
    }


    //texts setting
    for (int i = 0; i < 5; i++) {
        setting_text[i].setFont(setting_font);
        setting_text[i].setString(setting_list[i]);
        setting_text[i].setCharacterSize(70);
        setting_text[i].setFillColor(Color::White);
        setting_text[i].setOrigin(setting_text[i].getLocalBounds().width / 2.0f, setting_text[i].getLocalBounds().height / 2.0f);
        setting_text[i].setPosition(Vector2f(300, 260 + (i * 115)));
    }
    Setting_word.setFont(setting_word_font);
    Setting_word.setCharacterSize(100);
    Setting_word.setFillColor(Color::Black);
    Setting_word.setString("Settings");
    Setting_word.setPosition(Vector2f(150, 50));

    //texts pause
    for (int i = 0; i < 4; i++) {
        pause_text[i].setFont(pause_list_font);
        pause_text[i].setString(pause_list[i]);
        pause_text[i].setFillColor(Color::Color(180, 255, 150));
        pause_text[i].setOrigin(pause_text[i].getLocalBounds().width / 2.0f, pause_text[i].getLocalBounds().height / 2.0f);

    }
    pause_text[0].setCharacterSize(50);
    pause_text[1].setCharacterSize(65);
    pause_text[2].setCharacterSize(70);
    pause_text[3].setCharacterSize(50);
    pause_text[0].setPosition(Vector2f(395, 365 + (0 * 115)));
    pause_text[1].setPosition(Vector2f(370, 350 + (1 * 115)));
    pause_text[2].setPosition(Vector2f(370, 345 + (2 * 115)));
    pause_text[3].setPosition(Vector2f(440, 350 + (3 * 115)));
    pause_word.setFont(pause_word_font);
    pause_word.setCharacterSize(130);
    pause_word.setFillColor(Color::Color(150, 255, 150));
    pause_word.setString("GAME PAUSED");
    pause_word.setPosition(Vector2f(130, 420));
    pause_word.setOrigin(pause_word.getLocalBounds().width / 2.0f, pause_word.getLocalBounds().height / 2.0f);
    pause_word.setRotation(-90.f);

    
    


    //texts sounds
    sound_text[0].setFont(menu_font);
    sound_text[0].setString(sound_muted[0]);
    sound_text[0].setCharacterSize(80);
    sound_text[0].setFillColor(Color::Green);
    sound_text[0].setOrigin(sound_text[0].getLocalBounds().width / 2.0f, sound_text[0].getLocalBounds().height / 2.0f);
    sound_text[0].setPosition(Vector2f(725, 350));
    sound_text[2].setFont(menu_font);
    sound_text[2].setString(sound_muted[2]);
    sound_text[2].setCharacterSize(80);
    sound_text[2].setFillColor(Color::Red);
    sound_text[2].setOrigin(sound_text[2].getLocalBounds().width / 2.0f, sound_text[2].getLocalBounds().height / 2.0f);
    sound_text[2].setPosition(Vector2f(725, 350));
    sound_text[1].setFont(menu_font);
    sound_text[1].setString(sound_muted[1]);
    sound_text[1].setCharacterSize(35);
    sound_text[1].setFillColor(Color(200, 200, 200));
    sound_text[1].setOrigin(sound_text[1].getLocalBounds().width / 2.0f, sound_text[1].getLocalBounds().height / 2.0f);
    sound_text[1].setPosition(Vector2f(740, 500));
    sound_text[3].setFont(menu_font);
    sound_text[3].setString(sound_muted[3]);
    sound_text[3].setCharacterSize(35);
    sound_text[3].setFillColor(Color(200, 200, 200));
    sound_text[3].setOrigin(sound_text[3].getLocalBounds().width / 2.0f, sound_text[3].getLocalBounds().height / 2.0f);
    sound_text[3].setPosition(Vector2f(740, 500));
    for (int i = 0; i < 2; i++) {
        flavor_text[i].setFont(menu_font);
        flavor_text[i].setString(flavor_words[i]);
        flavor_text[i].setCharacterSize(40);
        flavor_text[i].setFillColor(Color(0, 255, 0, 100));
        flavor_text[i].setPosition(Vector2f(525, 600));
    }


    //back texts
    for (int i = 0; i < 4; i++) {
        back_list[i].setFont(back_font);
        back_list[i].setString(back_word[i]);
        back_list[i].setCharacterSize(85);
        back_list[i].setFillColor(Color(200, 200, 200));
        back_list[i].setOrigin(back_list[i].getLocalBounds().width / 2.0f, back_list[i].getLocalBounds().height / 2.0f);
        back_list[i].setPosition(Vector2f(740, 300 + (i * 120)));
    }
}

// menu 1 
void mainmenu1(RenderWindow& window) {
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::A) {
                menuIndex = 1;
            }
        }
    }

    if (menu1Clock.getElapsedTime().asSeconds() > 0.06f) {
        menu1FrameIndex += menuDirection;
        if (menu1FrameIndex >= 14) {
            menu1FrameIndex = 14;
            menuDirection = -1;
        }
        else if (menu1FrameIndex <= 0) {
            menu1FrameIndex = 0;
            menuDirection = 1;
        }
        menu1Clock.restart();

    }
    window.clear();

    menuSprite.setTexture(menu_frame[menu1FrameIndex]);

    FloatRect bounds = menuSprite.getLocalBounds();
    menuSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    menuSprite.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    float sX = (float)window.getSize().x / bounds.width;
    float sY = (float)window.getSize().y / bounds.height;
    menuSprite.setScale(sX, sY);

    window.draw(menuSprite);
    window.display();
}

// menu 2
void mainmenu2(RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        maintext[menu_point].setFillColor(Color::White);
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Down) {
                menu_point++;
                menu_point %= 4;
                current_player = 0;
                menupoint_sound.play();

            }
            else if (event.key.code == Keyboard::Up)
            {
                menu_point--;
                if (menu_point < 0) { menu_point = 3; }
                menupoint_sound.play();
            }
            if (event.key.code == Keyboard::Enter) {
                previous_menuIndex = menuIndex;
                

                if (menu_point == 0) {
                    load_game_level(currentEditorLevel);
                    menuIndex = 2;
                    Play_sound.play();
                    mainmenu_music.stop();  
                    if (currentEditorLevel == 1) {
                        lv1_soun_so.setLoop(true);
                        lv1_soun_so.play();
                        lv1_music_so.setLoop(true);
                        lv1_music_so.play();
                    }
                    if (currentEditorLevel == 2) {
                        initRain();
                        Rain_so.setLoop(true);
                        Rain_so.play();
                        lv1_music_so.setLoop(true);
                        lv1_music_so.play();
                    }
                    if (currentEditorLevel == 4) {
                        initRain();
                        Rain_so.setLoop(true);
                        Rain_so.play();
                        lv3_soun_so.setLoop(true);
                        lv3_soun_so.play();
                    }
                    if (currentEditorLevel == 5) {
                        lv4_soun_so.setLoop(true);
                        lv4_soun_so.play();
                    }
                    if (currentEditorLevel == 3) {
                        boss_soun_so.setLoop(true);
                        boss_soun_so.play();
                    }
					levelStart.restart();
                }
                if (menu_point == 1) {
                    menuIndex = 3;
                    enter_sound.play();
                }
                if (menu_point == 2) {
                    menuIndex = 4;
                    credit_music.setLoop(true);
                    credit_music.play();
                    mainmenu_music.stop();
                    enter_sound.play();
                }
                if (menu_point == 3) {
                    window.close();

                }
                maintext[menu_point].setFillColor(Color::White);
                menu_point = 0;
            }
        }
    }
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);
    window.draw(main_menu2);
    for (int i = 0; i < 4; i++) {
        if (i == menu_point) maintext[i].setFillColor(Color::Green);
        else maintext[i].setFillColor(Color::White);
        window.draw(maintext[i]);
    }
    window.display();
}


void settings(RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        setting_text[setting_point].setFillColor(Color::White);
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Down) {
                setting_point++;
                setting_point %= 5;
                setting_Index++;
                setting_Index %= 5;
                setting_sprite.setTexture(setting_frame[setting_point]);
                settingpoint_sound.play();
            }
            else if (event.key.code == Keyboard::Up)
            {
                setting_point--;
                setting_Index--;
                if (setting_point < 0) { setting_point = 4; }
                if (setting_Index < 0) { setting_Index = 4; }
                setting_sprite.setTexture(setting_frame[setting_point]);
                settingpoint_sound.play();
            }
            if (event.key.code == Keyboard::Enter) {
                enter_sound.play();
                if (setting_point == 0) {
                    window.clear();
                    window.draw(sound_text[sound_point]);
                    sound_point++;
                    sound_point %= 2;
                    if (sound_point == 1) {
                        mainmenu_music.setVolume(0);
                        credit_music.setVolume(0);
                        win_music_sound.setVolume(0);
                        lv1_music_so.setVolume(0);
                        lv3_soun_so.setVolume(0);
                        lv4_soun_so.setVolume(0);
                        boss_soun_so.setVolume(0);
                        pause_music_so.setVolume(0);
                    }
                    else {
                        mainmenu_music.setVolume(60);
                        credit_music.setVolume(60);
                        win_music_sound.setVolume(40);
                        lv1_music_so.setVolume(25);
                        lv3_soun_so.setVolume(40);
                        lv4_soun_so.setVolume(40);
                        boss_soun_so.setVolume(40);
                        pause_music_so.setVolume(40);
                    }
                }
                if (setting_point == 1) {
                    menuIndex = 11;
                    mainmenu_music.pause();
                    credit_music.setLoop(true);
                    credit_music.play();
                }
                if (setting_point == 2) {
                    menuIndex = 10;
                    bigchilltrans_sou.play();
                    mainmenu_music.pause();
                }
                if (setting_point == 3) {
                    menuIndex = 9;
                    credit_music.setLoop(true);
                    credit_music.play();
                    mainmenu_music.pause();
                    alien_sprite.setTexture(alien_frames[alien_menupoint]);
                }
                if (setting_point == 4) {
                    setting_text[setting_point].setFillColor(Color::White);
                    setting_point = 0;
                    setting_sprite.setTexture(setting_frame[setting_point]);
                    menuIndex = previous_menuIndex;
                    if (previous_menuIndex == 6) {
                        mainmenu_music.stop();
                        pause_music_so.setLoop(true);
                        pause_music_so.play();
                    }
                    if (menuIndex == 8) {
                        mainmenu_music.stop();
                        win_music_sound.setLoop(true);
                        win_music_sound.play();
                    }
                }
            }
        }
    }
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);
    window.draw(setting_sprite);
    for (int i = 0; i < 5; i++) {
        if (i == setting_point) setting_text[i].setFillColor(Color::Green);
        else setting_text[i].setFillColor(Color::White);
        window.draw(setting_text[i]);
    }
    if (setting_point == 0) {
        if (sound_point == 0) {
            window.draw(sound_text[0]);
            window.draw(sound_text[1]);
            window.draw(flavor_text[0]);
        }
        else {
            window.draw(sound_text[2]);
            window.draw(sound_text[3]);
            window.draw(flavor_text[1]);
        }
    }
    if (setting_point == 4) {
        for (int i = 0; i < 4; i++) {
            window.draw(back_list[i]);
        }
    }

    window.draw(Setting_word);
    window.display();
}
void pausemenu(RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        pause_text[pause_point].setFillColor(Color::Color(180, 255, 150));
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Down) {
                pause_point++;
                pause_point %= 4;
                pause_sprite.setTexture(pause_frames[pause_point]);
                pausepoint_sou.play();
            }
            else if (event.key.code == Keyboard::Up)
            {
                pause_point--;
                if (pause_point < 0) { pause_point = 3; }
                pause_sprite.setTexture(pause_frames[pause_point]);
                pausepoint_sou.play();
            }
            if (event.key.code == Keyboard::Enter) {
                enter_sound.play();
                previous_menuIndex = menuIndex;
                pause_music_so.stop();
                if (pause_point == 0) {
                    menuIndex = 2;
                    pause_point = 0;
                    pause_sprite.setTexture(pause_frames[pause_point]);
                    if (currentEditorLevel == 1) {
                        lv1_soun_so.setLoop(true);
                        lv1_soun_so.play();
                        lv1_music_so.setLoop(true);
                        lv1_music_so.play();
                    }
                    if (currentEditorLevel == 2) {
                        Rain_so.setLoop(true);
                        Rain_so.play();
                        lv1_music_so.setLoop(true);
                        lv1_music_so.play();
                    }
                    if (currentEditorLevel == 4) {
                        lv3_soun_so.setLoop(true);
                        lv3_soun_so.play();
                    }
                    if (currentEditorLevel == 5) {
                        Rain_so.setLoop(true);
                        Rain_so.play();
                        lv4_soun_so.setLoop(true);
                        lv4_soun_so.play();
                    }
                    if (currentEditorLevel == 3) {
                        boss_soun_so.setLoop(true);
                        boss_soun_so.play();
                    }
                }
                else if (pause_point == 1) {
                    menuIndex = 3;
                    pause_point = 0;
                    pause_sprite.setTexture(pause_frames[pause_point]);
                    mainmenu_music.setLoop(true);
                    mainmenu_music.play();
                }
                else if (pause_point == 2) {
                    previous_menuIndex = menuIndex;
                    menuIndex = 4;
                    pause_point = 0;
                    credit_music.setLoop(true);
                    credit_music.play();
                    pause_sprite.setTexture(pause_frames[pause_point]);
                }
                else if (pause_point == 3) {
                    menuIndex = 1;
                    hp = 60;
                    load_game_level(currentEditorLevel);
                    current_player = Transes::ben;
                    chosen_player = Transes::ben;
                    pause_point = 0;
                    pause_sprite.setTexture(pause_frames[pause_point]);
                    mainmenu_music.setLoop(true);
                    win_music_sound.stop();
                    mainmenu_music.play();
                }
            }
        }
    }
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);
    window.draw(pause_sprite);
    for (int i = 0; i < 4; i++) {
        window.draw(pause_text[i]);
    }
    window.draw(pause_word);
    window.display();
}
void gameover(RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        losstext[loss_point].setFillColor(Color::White);
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Down) {
                loss_point++;
                loss_point %= 3;
                loss_index++;
                loss_index %= 3;
                loss_sprite.setTexture(loss_frame[loss_point]);
                creditpoint_sound.play();
            }
            else if (event.key.code == Keyboard::Up)
            {
                loss_point--;
                loss_index--;
                if (loss_point < 0) { loss_point = 2; }
                if (loss_index < 0) { loss_index = 2; }
                loss_sprite.setTexture(loss_frame[loss_point]);
                creditpoint_sound.play();
            }
            if (event.key.code == Keyboard::Enter) {
                win_music_sound.stop();
                enter_sound.play();
                current_player = 0;
                omnitime = 30;
                hp = 60; 
                if (loss_point == 0) {
                    load_game_level(currentEditorLevel);
                    resetItems();
                    menuIndex = 2;
                    if (currentEditorLevel == 1) {
                        lv1_soun_so.setLoop(true);
                        lv1_soun_so.play();
                        lv1_music_so.setLoop(true);
                        lv1_music_so.play();
                    }
                    if (currentEditorLevel == 2) {
                        initRain();
                        Rain_so.setLoop(true);
                        Rain_so.play();
                        lv1_music_so.setLoop(true);
                        lv1_music_so.play();
                    }
                    if (currentEditorLevel == 4) {
                        lv3_soun_so.setLoop(true);
                        lv3_soun_so.play();
                    }
                    if (currentEditorLevel == 5) {
                        initRain();
                        Rain_so.setLoop(true);
                        Rain_so.play();
                        lv4_soun_so.setLoop(true);
                        lv4_soun_so.play();
                    }
                    if (currentEditorLevel == 3) {
                        boss_soun_so.setLoop(true);
                        boss_soun_so.play();
                    }
                }
                if (loss_point == 1) {
                    previous_menuIndex = menuIndex;
                    menuIndex = 3;
                    mainmenu_music.setLoop(true);
                    mainmenu_music.play();
                }

                if (loss_point == 2) {
                    menuIndex = 1;
                    mainmenu_music.setLoop(true);
                    mainmenu_music.play();
                    win_music_sound.stop();
                }
                losstext[loss_point].setFillColor(Color::White);
                loss_point = 0;
                loss_sprite.setTexture(loss_frame[loss_point]);
            }
        }
    }
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);
    window.draw(loss_sprite);
    for (int i = 0; i < 3; i++) {
        if (i == loss_point) {
            if (loss_point == 0) {
                losstext[i].setFillColor(Color::Green);
            }
            else if (loss_point == 1) {
                losstext[i].setFillColor(Color::Blue);
            }
            else if (loss_point == 2) {
                losstext[i].setFillColor(Color::Red);
            }
            
        }
        else losstext[i].setFillColor(Color::White);
        window.draw(losstext[i]);
    }
    window.display();
}
void win(RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        
        wintext[win_point].setFillColor(Color::White);
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Right) {
                win_point++;
                win_point %= 4;
                creditpoint_sound.play();
            }
            else if (event.key.code == Keyboard::Left)
            {
                win_point--;
                if (win_point < 0) { win_point = 3; }
                creditpoint_sound.play();
            }
            if (event.key.code == Keyboard::Enter) {
                win_music_sound.stop();
                enter_sound.play();
                if (win_point == 0) {
                    if (currentEditorLevel == 2) {
                        currentEditorLevel = 4;
                        initRain();
                        load_game_level(currentEditorLevel);
                        menuIndex = 2;
                        lv3_soun_so.setLoop(true);
                        lv3_soun_so.play();
                        current_player = 0;
                        omnitime = 30;
                        hp = 60;
                        win_music_sound.stop();
                        return;
                    }
                    if (currentEditorLevel == 5) {
                        currentEditorLevel = 3;
                        load_game_level(currentEditorLevel);
                        menuIndex = 2;
                        boss_soun_so.setLoop(true);
                        boss_soun_so.play();
                        current_player = 0;
                        omnitime = 30;
                        hp = 60;
                        win_music_sound.stop();
                        return;
                    }
                    if (currentEditorLevel == 3) {
                        menuIndex = 4;
                        credit_music.setLoop(true);
                        credit_music.play();
                        return;
                    }
                    currentEditorLevel++; 

                    
                    
                    if (currentEditorLevel == 2) {
                        initRain();
                        Rain_so.setLoop(true);
                        Rain_so.play();
                        lv1_music_so.setLoop(true);
                        lv1_music_so.play();
                    }
                    
                    if (currentEditorLevel == 5) {
                        lv4_soun_so.setLoop(true);
                        lv4_soun_so.play();
                    }
                    if (currentEditorLevel == 4) {
                        unlockedaliens = 7;
                    }
                    load_game_level(currentEditorLevel);
                    menuIndex = 2;
                    current_player = 0;
                    omnitime = 30;
                    hp = 60;
                    win_music_sound.stop();
                }
                if (win_point == 1) {
                    load_game_level(currentEditorLevel);
                    menuIndex = 2;
                    current_player = 0;
                    omnitime = 30;
                    resetItems();
                    hp = 60;
                    if (currentEditorLevel == 1) {
                        lv1_soun_so.setLoop(true);
                        lv1_soun_so.play();
                        lv1_music_so.setLoop(true);
                        lv1_music_so.play();
                    }
                    if (currentEditorLevel == 2) {
                        Rain_so.setLoop(true);
                        Rain_so.play();
                        lv1_music_so.setLoop(true);
                        lv1_music_so.play();
                    }
                    if (currentEditorLevel == 4) {
                        Rain_so.setLoop(true);
                        Rain_so.play();
                        lv3_soun_so.setLoop(true);
                        lv3_soun_so.play();
                    }
                    if (currentEditorLevel == 5) {
                        lv4_soun_so.setLoop(true);
                        lv4_soun_so.play();
                    }
                    if (currentEditorLevel == 3) {
                        boss_soun_so.setLoop(true);
                        boss_soun_so.play();
                    }
                    win_music_sound.stop();
                }
                if (win_point == 2) {
                    previous_menuIndex = menuIndex;
                    menuIndex = 3;
                    mainmenu_music.setLoop(true);
                    mainmenu_music.play();
                    win_music_sound.stop();
                }
                if (win_point == 3) {
                    menuIndex = 1;
                    win_music_sound.stop();
                    mainmenu_music.setLoop(true);
                    mainmenu_music.play();
                }
                maintext[win_point].setFillColor(Color::White);
                win_point = 0;
            }
        }
    }
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);
    window.draw(win_menu);
    for (int i = 0; i < 4; i++) {
        if (i == win_point) {
            if (i == 0) {
                wintext[i].setFillColor(Color::Green);
            }
            else if (i==1) {
                wintext[i].setFillColor(Color::Color(0, 45, 90));
            }
            else if (i == 2) {
                wintext[i].setFillColor(Color::Color(130, 50, 0));
            }
            else if (i == 3) {
                wintext[i].setFillColor(Color::Color(80, 0, 80));
            }
            
        }
        else wintext[i].setFillColor(Color::White);
        window.draw(wintext[i]);
    }
    window.display();
}
void credits(RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                enter_sound.play();
                menuIndex = previous_menuIndex;
                
                credit_music.stop();
                if (menuIndex == 2) {
                    menuIndex = 1;
                    mainmenu_music.setLoop(true);
                    mainmenu_music.play();
                }
                if (menuIndex == 6) {
                    pause_music_so.setLoop(true);
                    pause_music_so.play();
                }
                if (menuIndex == 1) {
                    mainmenu_music.setLoop(true);
                    mainmenu_music.play();
                }
            }
            
        }
    }
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);
    window.draw(credit);
    for (int i = 0; i < 7; i++) {
        window.draw(credittext[i]);
    }
    window.display();
}
void about_game(RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                enter_sound.play();
                menuIndex = 3;
                mainmenu_music.setLoop(true);
                mainmenu_music.play();
                credit_music.stop();
            }

        }
    }
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);
    window.draw(about_game_spr);
    window.display();
}

void aliens_info(RenderWindow& window) {
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                alien_menupoint = 0;
                alien_sprite.setTexture(alien_frames[alien_menupoint]);
                enter_sound.play();
                menuIndex = 3;
                mainmenu_music.setLoop(true);
                mainmenu_music.play();
            }
            
            if (event.key.code == Keyboard::Right) {
                alien_menupoint++;
                alien_menupoint %= 7;
                creditpoint_sound.play();
                alien_sprite.setTexture(alien_frames[alien_menupoint]);
                if (alien_menupoint == 0) {
                    bigchilltrans_sou.play();
                    swamptrans_sou.stop();
                    spidertrans_sou.stop();
                    brainstormtrans_sou.stop();
                    jetraytrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 1) {
                    swamptrans_sou.play();
                    bigchilltrans_sou.stop();
                    spidertrans_sou.stop();
                    brainstormtrans_sou.stop();
                    jetraytrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 2) {
                    spidertrans_sou.play();
                    bigchilltrans_sou.stop();
                    swamptrans_sou.stop();
                    brainstormtrans_sou.stop();
                    jetraytrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 3) {
                    brainstormtrans_sou.play();
                    bigchilltrans_sou.stop();
                    swamptrans_sou.stop();
                    spidertrans_sou.stop();
                    jetraytrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 4) {
                    jetraytrans_sou.play();
                    bigchilltrans_sou.stop();
                    swamptrans_sou.stop();
                    spidertrans_sou.stop();
                    brainstormtrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 5) {
                    bigchucktrans_sou.play();
                    bigchilltrans_sou.stop();
                    swamptrans_sou.stop();
                    spidertrans_sou.stop();
                    brainstormtrans_sou.stop();
                    jetraytrans_sou.stop();
                }
            }
            else if (event.key.code == Keyboard::Left)
            {
                alien_menupoint--;
                if (alien_menupoint < 0) { alien_menupoint = 6; }
                alien_sprite.setTexture(alien_frames[alien_menupoint]);
                creditpoint_sound.play();
                if (alien_menupoint == 0) { 
                    bigchilltrans_sou.play();
                    swamptrans_sou.stop();
                    spidertrans_sou.stop();
                    brainstormtrans_sou.stop();
                    jetraytrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 1) { 
                    swamptrans_sou.play(); 
                    bigchilltrans_sou.stop();
                    spidertrans_sou.stop();
                    brainstormtrans_sou.stop();
                    jetraytrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 2) {
                    spidertrans_sou.play(); 
                    bigchilltrans_sou.stop();
                    swamptrans_sou.stop();
                    brainstormtrans_sou.stop();
                    jetraytrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 3) {
                    brainstormtrans_sou.play();
                    bigchilltrans_sou.stop();
                    swamptrans_sou.stop();
                    spidertrans_sou.stop();
                    jetraytrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 4) {
                    jetraytrans_sou.play();
                    bigchilltrans_sou.stop();
                    swamptrans_sou.stop();
                    spidertrans_sou.stop();
                    brainstormtrans_sou.stop();
                    bigchucktrans_sou.stop();
                }
                else if (alien_menupoint == 5) {
                    bigchucktrans_sou.play();
                    bigchilltrans_sou.stop();
                    swamptrans_sou.stop();
                    spidertrans_sou.stop();
                    brainstormtrans_sou.stop();
                    jetraytrans_sou.stop();
                }
            }
        }
    }
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);
    window.draw(alien_sprite);
    window.display();
}
void how_to_play(RenderWindow& window)
{
    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
        if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::Escape) {
                enter_sound.play();
                menuIndex = 3;
                mainmenu_music.setLoop(true);
                mainmenu_music.play();
                credit_music.stop();
            }

        }
    }
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);
    window.draw(htp_spr);
    window.display();
}

void minigamescreen(RenderWindow& window)
{
    if (omnitime <= 3) omnitime = 5;
    if (countcount >= 100) {
        countcount = 0;
        done = 0;
        miniindx = 0;
        miniclock.restart();
    }
    if (!done)
        remainingml = (timefortheminigame * 1000) - miniclock.getElapsedTime().asMilliseconds();

    if (remainingml < 0)
        remainingml = 0;

    int remaningsec = remainingml / 1000;
    int disml = (remainingml % 1000) / 10;

    if (Keyboard::isKeyPressed(Keyboard::Enter)) {
        if (!minienterpressed) {
            float currentpo = minigamerect.getPosition().x;
            for (int i = 0; i < 7; i++) {
                if (currentpo == minitext[i].getPosition().x || currentpo == minitext[i].getPosition().x - 100) {
                    swap(minilist[i], minilist[i + 1]);
                    break;
                    //minilist[i] = fnum[i][0];
                }
            }
            minienterpressed = 1;
        }
    }
    else {
        minienterpressed = 0;
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        if (!miniright) {
            if (miniindx < 6) miniindx++;
            miniright = true;
        }
    }
    else
        miniright = false;


    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        if (!minileft) {
            if (miniindx > 0) miniindx--;
            minileft = true;
        }
    }
    else
        minileft = false;

    minirectpx = 300.0f + (miniindx * 100.0f);


    while (window.pollEvent(event)) {
        if (event.type == Event::Closed) {
            window.close();
        }
    }

    miniword.setFont(minigamefont);
    miniword.setCharacterSize(70);

    minigamerect.setSize(Vector2f(70, 70));
    minigamerect.setFillColor(Color::White);
    minigamerect.setOrigin(minigamerect.getLocalBounds().width / 2.0f, minigamerect.getLocalBounds().height / 2.0f);
    minigamerect.setPosition(Vector2f(minirectpx, minirectpy));
    movingminisp.setPosition(minigamerect.getPosition().x - 70, minigamerect.getPosition().y - 37);

    for (int i = 0; i < 8; i++) {
        minitext[i].setFont(minigamefont);
        minitext[i].setString(minilist[i]);
        minitext[i].setCharacterSize(70);
        minitext[i].setOrigin(minitext[i].getLocalBounds().width / 2.0f, minitext[i].getLocalBounds().height / 2.0f);
        minitext[i].setPosition(Vector2f(100 * (i + 3), 490));
        minitext[i].setFillColor(Color(180, 255, 150));
        pass[i].setFillColor(Color(180, 255, 150));
    }

    if (remaningsec >= 10 && disml >= 10)
        minitimer.setString(to_string(remaningsec) + ":" + to_string(disml));
    else if (remaningsec < 10)
        minitimer.setString('0' + to_string(remaningsec) + ":" + to_string(disml));
    else if (remaningsec < 10 && disml < 10)
        minitimer.setString('0' + to_string(remaningsec) + ":0" + to_string(disml));

    if (remainingml == 0)
        minitimer.setString('0' + to_string(remaningsec) + ":0" + to_string(disml));

    pass[0].setPosition(Vector2f(300, 350));
    pass[1].setPosition(Vector2f(400, 350));
    pass[2].setPosition(Vector2f(500, 350));
    pass[3].setPosition(Vector2f(600, 350));
    pass[4].setPosition(Vector2f(700, 350));
    pass[5].setPosition(Vector2f(800, 350));
    pass[6].setPosition(Vector2f(900, 350));
    pass[7].setPosition(Vector2f(1000, 350));
    window.clear();
    View uiView(FloatRect(0, 0, 1800, 900));
    window.setView(uiView);

    window.draw(minisprite);
    for (int i = 0; i < 8; i++) {
        window.draw(minitext[i]);
        window.draw(pass[i]);
    }
    //window.draw(minigamerect);

    window.draw(minitimer);
    window.draw(movingminisp);
    if (passlist[0] == minilist[0] && passlist[1] == minilist[1] && passlist[2] == minilist[2] && passlist[3] == minilist[3] && passlist[4] == minilist[4] && passlist[5] == minilist[5] && passlist[6] == minilist[6] && passlist[7] == minilist[7])
    {
        done = 1;
        miniword.setString("boom");
        miniword.setFillColor(Color(27, 94, 32));
        miniword.setOrigin(miniword.getLocalBounds().width / 2.0f, miniword.getLocalBounds().height / 2.0f);
        miniword.setPosition(Vector2f(900, 135));
        int currentMs = miniclock.getElapsedTime().asMilliseconds();
        if ((currentMs / 250) % 2 == 0) {
            window.draw(miniword);
            countcount++;
        }
        window.display();
        openlock = 1;
        if (countcount >= 100) {
            menuIndex = 2;
  
            isTransing = false;
        }
    }
    else if (remainingml == 0 && disml == 0) {
        miniword.setString("haha");

        miniword.setFillColor(Color(200, 30, 30));
        miniword.setOrigin(miniword.getLocalBounds().width / 2.0f, miniword.getLocalBounds().height / 2.0f);
        miniword.setPosition(Vector2f(900, 135));
        int currentMs = miniclock.getElapsedTime().asMilliseconds();
        if ((currentMs / 250) % 2 == 0) {
            window.draw(miniword);
            countcount++;
        }

        window.display();
        if (countcount >= 100) {
            minilist[0] = "4 ";
            minilist[1] = "R ";
            minilist[2] = "8 ";
            minilist[3] = "E ";
            minilist[4] = "A ";
            minilist[5] = "4 ";
            minilist[6] = "9 ";
            minilist[7] = "F ";
            
            menuIndex = 2;
            
        }
    }
    else

        window.display();


}