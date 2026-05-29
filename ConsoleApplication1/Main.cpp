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
#include "dialogue.h"
#include"Global.h"
#include"Start.h"
#include"Enemies.h"
#include"Map.h"
#include"Menus.h"
#include"Basics&Animation.h"
#include"Update&Draw.h"
#include"Levels.h"
using namespace std;
using namespace sf;


int main()
{
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    scaleX = VideoMode::getDesktopMode().width / 1800.0f;
    scaleY = VideoMode::getDesktopMode().height / 900.0f;
    start();

    window.setVerticalSyncEnabled(true);
    window.setMouseCursorVisible(false);

    Event event;
    

    while (window.isOpen())
    {
        if (menuIndex == 0)mainmenu1(window);
        if (menuIndex == 1)mainmenu2(window);
        if (menuIndex == 2)game();
        if (menuIndex == 3)settings(window);
        if (menuIndex == 4)credits(window);
        if (menuIndex == 5)map_editor();
        if (menuIndex == 6)pausemenu(window);
        if (menuIndex == 7)win(window);
        if (menuIndex == 8)gameover(window);
        if (menuIndex == 9)about_game(window);
        if (menuIndex == 10)aliens_info(window);
        if (menuIndex == 11)how_to_play(window);
        if (menuIndex == 12) {
            if (miniopened == 0) {
                miniclock.restart();
                miniopened = 1;
            }
            minigamescreen(window);
        }
        else {
            miniopened = 0;
        }
    }
    return 0;
}
//