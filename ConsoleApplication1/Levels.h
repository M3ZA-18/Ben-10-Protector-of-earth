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



//GAME SET UP 

void game() {

    while (window.pollEvent(event))
    {

        if (event.type == Event::Closed)
            window.close();

            handleDialogueEvents(event);
             
            if (currentEditorLevel == 3 && !dialogue1) { 
                dialogue1 = true;
                triggerDialogue(0);
            }


            if (event.type == Event::KeyPressed) {
            if (event.key.code == Keyboard::P) {
                menuIndex = 6;
                pause_sprite.setTexture(pause_frames[pause_point]);
                window.draw(pause_sprite);
                pause_music_so.setLoop(true);
                pause_music_so.play();
                lv1_music_so.stop();
                Rain_so.stop();
                walk_forest_so.stop();
                lv1_soun_so.stop();
                lv3_soun_so.stop();
                lv4_soun_so.stop();
                boss_soun_so.stop();
                Rain_so.stop();
                thunderSou.stop();
            }
            if (event.key.code == Keyboard::Z) {
                menuIndex = 12;
                minisprite.setTexture(miniframe);
                window.draw(minisprite);
                pause_music_so.setLoop(true);
                pause_music_so.play();
                lv1_music_so.stop();
                Rain_so.stop();
                walk_forest_so.stop();
                lv1_soun_so.stop();
                lv3_soun_so.stop();
                lv4_soun_so.stop();
                boss_soun_so.stop();
                Rain_so.stop();
                thunderSou.stop();
            }

            if (event.key.code == Keyboard::M) {
                menuIndex = 5;
                lv1_music_so.stop();
                Rain_so.stop();
                walk_forest_so.stop();
                lv1_soun_so.stop();
                lv3_soun_so.stop();
                lv4_soun_so.stop();
                boss_soun_so.stop();
                Rain_so.stop();
                thunderSou.stop();
            }
            }
            ben10transformation();
        }
        update();
        draw();
    }


