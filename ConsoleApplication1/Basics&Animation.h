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



void OmnitrixBubbleTospriteFun() {
	OmniBubbleTex[0].loadFromFile("omnitrixbubbleframe1.png");
	OmniBubbleTex[1].loadFromFile("omnitrixbubbleframe2.png");
	OmniBubbleTex[2].loadFromFile("omnitrixbubbleframe3.png");
	OmniBubbleTex[3].loadFromFile("omnitrixbubbleframe4.png");
	OmniBubbleTex[4].loadFromFile("omnitrixbubbleframe5.png");
	OmniBubbleTex[5].loadFromFile("omnitrixbubbleframe6.png");
	OmniBubbleTex[6].loadFromFile("omnitrixbubbleframe7.png");
	OmniBubbleTex[7].loadFromFile("omnitrixbubbleframe8.png");
	OmniBubbleTex[8].loadFromFile("omnitrixbubbleframe9.png");
	OmniBubbleTex[9].loadFromFile("omnitrixbubbleframe10.png");
	OmniBubbleTex[10].loadFromFile("omnitrixbubbleframe11.png");
	OmniBubbleTex[11].loadFromFile("omnitrixbubbleframe12.png");
	OmniBubbleTex[12].loadFromFile("omnitrixbubbleframe13.png");
	OmniBubbleTex[13].loadFromFile("omnitrixbubbleframe14.png");
	OmniBubbleTex[14].loadFromFile("omnitrixbubbleframe15.png");
	OmniBubbleTex[15].loadFromFile("omnitrixbubbleframe16.png");
	OmniBubbleTex[16].loadFromFile("omnitrixbubbleframe17.png");
	OmniBubbleTex[17].loadFromFile("omnitrixbubbleframe18.png");
	OmniBubbleTex[18].loadFromFile("omnitrixbubbleframe19.png");
	OmniBubbleTex[19].loadFromFile("omnitrixbubbleframe20.png");
	OmniBubbleTex[20].loadFromFile("omnitrixbubbleframe21.png");
	OmniBubbleTex[21].loadFromFile("omnitrixbubbleframe22.png");
	for (int i = 0; i < 4; i++) {
		omniBubbleSp[i].setScale(1.5, 1.5);
		omniBubbleSp[i].setPosition(OmnitrixBubble[i].getPosition().x - 50, OmnitrixBubble[i].getPosition().y - 60);
	}
}

//health bubble

void hpBubbleTospriteFun() {
	hpBubbleTex[0].loadFromFile("hpbubbleframe1.png");
	hpBubbleTex[1].loadFromFile("hpbubbleframe2.png");
	hpBubbleTex[2].loadFromFile("hpbubbleframe3.png");
	hpBubbleTex[3].loadFromFile("hpbubbleframe4.png");
	hpBubbleTex[4].loadFromFile("hpbubbleframe5.png");
	hpBubbleTex[5].loadFromFile("hpbubbleframe6.png");
	hpBubbleTex[6].loadFromFile("hpbubbleframe7.png");
	hpBubbleTex[7].loadFromFile("hpbubbleframe8.png");
	hpBubbleTex[8].loadFromFile("hpbubbleframe9.png");
	hpBubbleTex[9].loadFromFile("hpbubbleframe10.png");
	hpBubbleTex[10].loadFromFile("hpbubbleframe11.png");
	hpBubbleTex[11].loadFromFile("hpbubbleframe12.png");
	hpBubbleTex[12].loadFromFile("hpbubbleframe13.png");
	hpBubbleTex[13].loadFromFile("hpbubbleframe14.png");
	hpBubbleTex[14].loadFromFile("hpbubbleframe15.png");
	hpBubbleTex[15].loadFromFile("hpbubbleframe16.png");
	hpBubbleTex[16].loadFromFile("hpbubbleframe17.png");
	hpBubbleTex[17].loadFromFile("hpbubbleframe18.png");
	hpBubbleTex[18].loadFromFile("hpbubbleframe19.png");
	hpBubbleTex[19].loadFromFile("hpbubbleframe20.png");
	hpBubbleTex[20].loadFromFile("hpbubbleframe21.png");
	hpBubbleTex[21].loadFromFile("hpbubbleframe22.png");
	for (int i = 0; i < 4; i++) {
		hpBubbleSp[i].setScale(1.5, 1.5);
		hpBubbleSp[i].setPosition(HealthBubble[i].getPosition().x - 50, HealthBubble[i].getPosition().y - 60);
	}
}
void BubbleAnimation(Item& I) {
	if (I.type == MP::Omnitrix)
		I.sprite.setTexture(OmniBubbleTex[frameCounterToOmnitrix], true);
	else if (I.type == MP::Health)
		I.sprite.setTexture(hpBubbleTex[frameCounterToHealth], true);

	if (characterbox[current_player].getGlobalBounds().intersects(I.shape.getGlobalBounds()) && !I.collected) {
		if (I.type == MP::Health)
		{
			if (hp < 60) {
				hp += 10;
				I.collected = true;
			}
		}
		else if (I.type == MP::Omnitrix) {
			if (omnitime < 30) {
				omnitime += 10;
				I.collected = true;
			}
		}
	}
	if (I.type == MP::Box) {
		I.sprite.setScale(0.4, 0.4);

		if (isAttacking) {
			if (characterboxarm[current_player].getGlobalBounds().intersects(I.box.getGlobalBounds())) {
				if (I.boxclock.getElapsedTime().asSeconds() >= 0.01f) {
					I.boxclock.restart();
					I.BoxHit++;


					if (I.BoxHit < 5) {
						I.sprite.setTexture(boxtx[I.BoxHit]);
					}

					if (I.BoxHit >= 4) {
						I.collected = true;
					}
				}
			}
		}

		FloatRect playerBounds = characterbox[current_player].getGlobalBounds();
		FloatRect boxBounds = I.box.getGlobalBounds();
		FloatRect intersection;

		if (playerBounds.intersects(boxBounds, intersection)) {


			if (intersection.width < intersection.height) {

				if (playerBounds.left + playerBounds.width / 2.f < boxBounds.left + boxBounds.width / 2.f) {
					characterbox[current_player].setPosition(
						boxBounds.left - (playerBounds.width - characterbox[current_player].getOrigin().x),
						characterbox[current_player].getPosition().y
					);
					touchedGround = true;
				}
				else {
					characterbox[current_player].setPosition(
						boxBounds.left + boxBounds.width + characterbox[current_player].getOrigin().x,
						characterbox[current_player].getPosition().y
					);
					touchedGround = true;
				}
			}
			else {

				if (playerBounds.top + playerBounds.height / 2.f < boxBounds.top + boxBounds.height / 2.f) {
					characterbox[current_player].setPosition(
						characterbox[current_player].getPosition().x,
						boxBounds.top - (playerBounds.height - characterbox[current_player].getOrigin().y)
					);
					velocity.y = 0;
					onground = true;
					touchedGround = true;
				}
				else {
					characterbox[current_player].setPosition(
						characterbox[current_player].getPosition().x,
						boxBounds.top + boxBounds.height + characterbox[current_player].getOrigin().y
					);
					if (velocity.y < 0) velocity.y = 0;
				}
			}
		}
	}
	if (I.type == MP::Fire) {
		if (characterbox[current_player].getGlobalBounds().intersects(I.box.getGlobalBounds())) {
			if (current_player == swampfire && I.lightactive.getElapsedTime().asSeconds() >= 1.0f) {
				I.BoxHit--;

				if (I.BoxHit > 0) {
					I.sprite.setTexture(firetx[4 - I.BoxHit], true); 
					I.lightactive.restart();
					I.frame = 0;
					float frameWidth = firetx[4 - I.BoxHit].getSize().x / 8.0f;
					float frameHeight = I.sprite.getLocalBounds().height;

					I.sprite.setTextureRect(IntRect(I.frame * frameWidth, 0, frameWidth, frameHeight));
					I.frame = (I.frame + 1) % 8;
					I.boxclock.restart();
				}
				else {
					I.collected = true;
				}
			}
			else {
				
				if (current_player != swampfire &&hit.getElapsedTime().asSeconds() > 2.0f) {
					hp -= 10;
					hit.restart();
				}
			}
		}


		if (I.boxclock.getElapsedTime().asSeconds() >= 0.1f) {
			float frameWidth = firetx[4 - I.BoxHit].getSize().x / 8.0f;
			float frameHeight = I.sprite.getLocalBounds().height;

			I.sprite.setTextureRect(IntRect(I.frame * frameWidth, 0, frameWidth, frameHeight));
			I.frame = (I.frame + 1) % 8;
			I.boxclock.restart();
		}

	}
	if (I.type == MP::Lightning) {

		if (!I.actrive) {

			if (I.boxclock.getElapsedTime().asSeconds() >= 0.1f) {
				float frameWidth = light.getSize().x / 6.0f;
				float frameHeight = I.sprite.getLocalBounds().height;

				I.frame = (I.frame ) % 4 +1;
				I.sprite.setTextureRect(IntRect(I.frame * frameWidth, 0, frameWidth, frameHeight));
				I.boxclock.restart();
			}
			if (characterbox[current_player].getGlobalBounds().intersects(I.box.getGlobalBounds())) {
				if (hit.getElapsedTime().asSeconds() > 2.0f && I.frame >= 2) {
					hp -= 30;
					hit.restart();
				}
			}
			if (I.lightactive.getElapsedTime().asSeconds() > 3.0f) {
				I.actrive = true;
				I.lightactive.restart();
			}
		}
		else if (I.actrive) {
			I.sprite.setTextureRect(IntRect(0, 0, 0, 0));
			if (I.lightactive.getElapsedTime().asSeconds() > 3.0f) {
				I.actrive = false;
				I.lightactive.restart();
				I.boxclock.restart();
				I.frame = 0;
				float frameWidth = light.getSize().x / 6.0f;
				float frameHeight = light.getSize().y;
				I.sprite.setTextureRect(IntRect(0, 0, frameWidth, frameHeight));
			}
		}
	}
	if (I.type > 2) {
		I.sprite.setOrigin(I.sprite.getLocalBounds().width / 2, I.sprite.getLocalBounds().height);
		I.sprite.setPosition(I.box.getPosition());
	}
}
		


void boxes() {
	characterbox[Transes::ben].setSize(Vector2f(50, 110));
	characterbox[Transes::ben].setFillColor(Color::Green);
	characterbox[Transes::ben].setOrigin(characterbox[Transes::ben].getLocalBounds().width / 2.0f, characterbox[Transes::ben].getLocalBounds().height);
	characterboxarm[Transes::ben].setSize(Vector2f(characterbox[Transes::ben].getLocalBounds().width * 1.2+5, characterbox[Transes::ben].getLocalBounds().height / 2.0f ));
	characterboxarm[Transes::ben].setFillColor(Color::Green);
	characterboxarm[Transes::ben].setOrigin(characterboxarm[Transes::ben].getLocalBounds().width /2.0f +40, characterboxarm[Transes::ben].getLocalBounds().height-20);

	characterbox[Transes::jetray].setSize(Vector2f(50, 90));
	characterbox[Transes::jetray].setFillColor(Color::Black);
	characterbox[Transes::jetray].setOrigin(characterbox[Transes::jetray].getLocalBounds().width / 2.0f, characterbox[Transes::jetray].getLocalBounds().height / 2.0f);
	characterboxarm[Transes::jetray].setSize(Vector2f(characterbox[Transes::jetray].getLocalBounds().width+20, characterbox[Transes::jetray].getLocalBounds().height / 2.0f));
	characterboxarm[Transes::jetray].setFillColor(Color::Green);
	characterboxarm[Transes::jetray].setOrigin(characterboxarm[Transes::jetray].getLocalBounds().width / 2.0f, characterboxarm[Transes::jetray].getLocalBounds().height / 2.0f);

	characterbox[Transes::bigchuck].setSize(Vector2f(35, 69));
	characterbox[Transes::bigchuck].setFillColor(Color::Color(112, 240, 240));
	characterbox[Transes::bigchuck].setOrigin(characterbox[Transes::bigchuck].getLocalBounds().width / 2.0f, characterbox[Transes::bigchuck].getLocalBounds().height / 2.0f);
	characterboxarm[Transes::bigchuck].setSize(Vector2f(characterbox[Transes::bigchuck].getLocalBounds().width +10, characterbox[Transes::bigchuck].getLocalBounds().height / 2.0f));
	characterboxarm[Transes::bigchuck].setFillColor(Color::Green);
	characterboxarm[Transes::bigchuck].setOrigin(characterboxarm[Transes::bigchuck].getLocalBounds().width / 2.0f, characterboxarm[Transes::bigchuck].getLocalBounds().height / 2.0f);

	characterbox[Transes::BigChill].setSize(Vector2f(40, 130));
	characterbox[Transes::BigChill].setFillColor(Color::Color(211, 211, 211));
	characterbox[Transes::BigChill].setOrigin(characterbox[Transes::BigChill].getLocalBounds().width / 2.0f, characterbox[Transes::BigChill].getLocalBounds().height / 2.0f);
	characterboxarm[Transes::BigChill].setSize(Vector2f(characterbox[Transes::BigChill].getLocalBounds().width * 1.40f, characterbox[Transes::BigChill].getLocalBounds().height / 2.0f));
	characterboxarm[Transes::BigChill].setFillColor(Color::Green);
	characterboxarm[Transes::BigChill].setOrigin(characterboxarm[Transes::BigChill].getLocalBounds().width / 2.0f, characterboxarm[Transes::BigChill].getLocalBounds().height / 2.0f);

	characterbox[Transes::SpiderMonkey].setSize(Vector2f(65, 65));
	characterbox[Transes::SpiderMonkey].setFillColor(Color::Color(70, 130, 180));
	characterbox[Transes::SpiderMonkey].setOrigin(characterbox[Transes::SpiderMonkey].getLocalBounds().width / 2.0f, characterbox[Transes::SpiderMonkey].getLocalBounds().height / 2.0f);
	characterboxarm[Transes::SpiderMonkey].setSize(Vector2f(characterbox[Transes::SpiderMonkey].getLocalBounds().width, characterbox[Transes::SpiderMonkey].getLocalBounds().height / 2.0f));
	characterboxarm[Transes::SpiderMonkey].setFillColor(Color::Green);
	characterboxarm[Transes::SpiderMonkey].setOrigin(characterboxarm[Transes::SpiderMonkey].getLocalBounds().width / 2.0f, characterboxarm[Transes::SpiderMonkey].getLocalBounds().height / 2.0f);

	characterbox[Transes::brainstorm].setSize(Vector2f(50, 65));
	characterbox[Transes::brainstorm].setFillColor(Color::Yellow);
	characterbox[Transes::brainstorm].setOrigin(characterbox[Transes::brainstorm].getLocalBounds().width / 2.0f, characterbox[Transes::brainstorm].getLocalBounds().height / 2.0f);
	characterboxarm[Transes::brainstorm].setSize(Vector2f(characterbox[Transes::brainstorm].getLocalBounds().width, characterbox[Transes::brainstorm].getLocalBounds().height / 2.0f));
	characterboxarm[Transes::brainstorm].setFillColor(Color::Green);
	characterboxarm[Transes::brainstorm].setOrigin(characterboxarm[Transes::brainstorm].getLocalBounds().width / 2.0f, characterboxarm[Transes::brainstorm].getLocalBounds().height / 2.0f);

	characterbox[Transes::swampfire].setSize(Vector2f(50, 150));
	characterbox[Transes::swampfire].setFillColor(Color::Color(255, 140, 0));
	characterbox[Transes::swampfire].setOrigin(characterbox[Transes::swampfire].getLocalBounds().width / 2.0f, characterbox[Transes::swampfire].getLocalBounds().height / 2.0f);
	characterboxarm[Transes::swampfire].setSize(Vector2f(characterbox[Transes::swampfire].getLocalBounds().width + 10, characterbox[Transes::swampfire].getLocalBounds().height / 2.0f));
	characterboxarm[Transes::swampfire].setFillColor(Color::Green);
	characterboxarm[Transes::swampfire].setOrigin(characterboxarm[Transes::swampfire].getLocalBounds().width / 2.0f, characterboxarm[Transes::swampfire].getLocalBounds().height / 2.0f);
}

//omnitrix
void OmnitrixUI() {
	//green
	greenOmnitrixTex[Transes::ben].loadFromFile("therealemptyomnitrix.png");
	greenOmnitrixTex[Transes::BigChill].loadFromFile("aliens/Bigchill/BigChill(green).jpg");
	greenOmnitrixTex[Transes::brainstorm].loadFromFile("aliens/brainstorm/Brainstorm(green).jpg");
	greenOmnitrixTex[Transes::bigchuck].loadFromFile("aliens/green/green(green).jpg");
	greenOmnitrixTex[Transes::jetray].loadFromFile("aliens/jetray/jetray(green).jpg");
	greenOmnitrixTex[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/Spidermonkey(green).jpg");
	greenOmnitrixTex[Transes::swampfire].loadFromFile("aliens/Swampfire/Swampfire(green).jpg");

	//white
	whiteOmnitrixTex[Transes::ben].loadFromFile("therealemptyomnitrix.png");
	whiteOmnitrixTex[Transes::BigChill].loadFromFile("aliens/Bigchill/BigChill(gray).jpg");
	whiteOmnitrixTex[Transes::brainstorm].loadFromFile("aliens/brainstorm/Brainstorm(gray).jpg");
	whiteOmnitrixTex[Transes::bigchuck].loadFromFile("aliens/green/green(gray).jpg");
	whiteOmnitrixTex[Transes::jetray].loadFromFile("aliens/jetray/jetray(gray).jpg");
	whiteOmnitrixTex[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/Spider(gray).jpg");
	whiteOmnitrixTex[Transes::swampfire].loadFromFile("aliens/Swampfire/Swampfire(gray).jpg");
}
void whiteOmnitrix() {
	if (chosen_player >= 0 && chosen_player < 8) {
		Omnitrixsp.setTexture(whiteOmnitrixTex[chosen_player]);
	}
	Omnitrixsp.setTextureRect(sf::IntRect(0, 0, whiteOmnitrixTex[chosen_player].getSize().x, whiteOmnitrixTex[chosen_player].getSize().y));
}
void GreenOmnitrix() {
	if (current_player >= 0 && current_player < 8) {
		Omnitrixsp.setTexture(greenOmnitrixTex[current_player]);
	}
}
//health bar
void HealthBarFunction() {
	hpBar.setPosition(160.6, 55);
	emptyHPBar.setPosition(160.6, 55);
	hpBar.setScale(2.29, 3);
	emptyHPBar.setScale(2.29, 3);
	// hp bar load from file
	emptyHPBarTex.loadFromFile("Map/emptyBoredBar.png");
	emptyHPBar.setTexture(emptyHPBarTex);
	BarsTex[Bars::first].loadFromFile("Map/FullBoredBar.png");
	BarsTex[Bars::second].loadFromFile("Map/SecondBoredBar.png");
	BarsTex[Bars::third].loadFromFile("Map/ThirdBoredBar.png");
	BarsTex[Bars::fourth].loadFromFile("Map/FourthBoredBar.png");
	BarsTex[Bars::fifth].loadFromFile("Map/FifthBoredBar.png");
	BarsTex[Bars::last].loadFromFile("Map/lastBoredBar.png");
}

void omnibarrrr() {
	omnibar.setPosition(145, -60);
	omnibar.setOrigin(0, 0);
	emptyomnibar.setPosition(130, 50);
	omnibar.setScale(0.535, 0.70);
	emptyomnibar.setScale(0.35, 0.37);

	emptyomnibartex.loadFromFile("Map/emptyBoredBarw.png");
	emptyomnibar.setTexture(emptyomnibartex);
	omnibartex.loadFromFile("Map/FullBoredBarw.png");
	omnibar.setTexture(omnibartex);
	emptyomnibar.setColor(Color(2, 89, 15));
}
void playomnibar() {
	float xx = aaa.restart().asSeconds();

	visualOmni += (omnitime - visualOmni) * sspeed * xx;

	float percent = visualOmni / all;

	omnibar.setScale(percent * 0.535, 0.70);
}
void playerHealthGotDamage() {
	if (hp >= 60)
		hpBar.setTexture(BarsTex[Bars::first], true);
	else if (hp < 60 && hp >= 50)
		hpBar.setTexture(BarsTex[Bars::second], true);
	else if (hp < 50 && hp >= 40)
		hpBar.setTexture(BarsTex[Bars::third], true);
	else if (hp < 40 && hp >= 30)
		hpBar.setTexture(BarsTex[Bars::fourth], true);
	else if (hp < 30 && hp >= 20)
		hpBar.setTexture(BarsTex[Bars::fifth], true);
	else if (hp < 20 && hp >= 1)
		hpBar.setTexture(BarsTex[Bars::last], true);
	else
		hpBar.setTexture(emptyHPBarTex);
}

void animation() {
	//speed
	speed[Transes::ben] = { 6.0f,6.0f };
	speed[Transes::jetray] = { 9.0f,11.0f };
	speed[Transes::bigchuck] = { 4.0f,10.0f };
	speed[Transes::BigChill] = { 7.0f,10.0f };
	speed[Transes::SpiderMonkey] = { 8.0f,10.0f };
	speed[Transes::brainstorm] = { 6.0f,10.0f };
	speed[Transes::swampfire] = { 7.0f,11.0f };

	//idle load
	idle_animation[Transes::ben].loadFromFile("ben/ben idle.png");
	idle_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray idle.png");
	idle_animation[Transes::bigchuck].loadFromFile("aliens/green/green idle.png");
	idle_animation[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill idle.png");
	idle_animation[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey idle.png");
	idle_animation[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm idle.png");
	idle_animation[Transes::swampfire].loadFromFile("aliens/Swampfire/swampfire idle3.png");

	// extra
	glide_animation[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill glide.png");
	land_animation[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill double_jump_land.png");
	land_animation[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm jump_land.png");
	land_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray Jump_land.png");
	land_animation[Transes::bigchuck].loadFromFile("aliens/green/green Jump_land.png");
	land_animation[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey jump land.png");
	fly_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray attack (Jump+S) Fly.png");
	fly_idleanimation[Transes::jetray].loadFromFile("aliens/jetray/fly_idle.png");
	flya_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray attack (Jump+S+Down+Right) Fly.png");
	flyw_animation.loadFromFile("aliens/jetray/jetray attack (Jump+S+UP+Right) Fly.png");

	// hit
	hit_animation[Transes::ben].loadFromFile("ben/ben hit.png");
	hit_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray hit.png");
	hit_animation[Transes::bigchuck].loadFromFile("aliens/green/green hit.png");
	hit_animation[Transes::BigChill].loadFromFile("aliens/bigchill/bigchill hit.png");
	hit_animation[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey hit.png");
	hit_animation[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm hit2.png");
	hit_animation[Transes::swampfire].loadFromFile("aliens/Swampfire/swampfire hit.png");

	win_animation.loadFromFile("ben/ben win.png");

	//walk load
	walk_animation[Transes::ben].loadFromFile("ben/ben run.png");
	walk_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray run.png");
	walk_animation[Transes::bigchuck].loadFromFile("aliens/green/green run.png");
	walk_animation[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill run.png");
	walk_animation[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey run.png");
	walk_animation[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm run.png");
	walk_animation[Transes::swampfire].loadFromFile("aliens/Swampfire/swampfire run.png");

	//attack load
	Attack_animation[Transes::ben].loadFromFile("ben/ben attack.png");

	Attack_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray attack (A).png");
	Attack_animation_B[Transes::jetray].loadFromFile("aliens/jetray/jetray attack (A+A).png");
	Attack_animation_C[Transes::jetray].loadFromFile("aliens/jetray/jetray attack (A+A+A).png");
	Jump_Attack_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray attack (Jump+A).png");
	Special_Attack_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray attack (A+S).png");

	Attack_animation[Transes::bigchuck].loadFromFile("aliens/green/green attack(A).png");
	Attack_animation_B[Transes::bigchuck].loadFromFile("aliens/green/green attack(A+A).png");
	Attack_animation_C[Transes::bigchuck].loadFromFile("aliens/green/green attack(A+A+A).png");
	Jump_Attack_animation[Transes::bigchuck].loadFromFile("aliens/green/green attack(Jump+A).png");
	Special_Attack_animation[Transes::bigchuck].loadFromFile("aliens/green/green attack(A+S).png");

	Attack_animation[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill attack (A).png");
	Attack_animation_B[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill attack (A+A).png");
	Attack_animation_C[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill attack (A+A+A).png");
	Jump_Attack_animation[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill jump_attack.png");
	Special_Attack_animation[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill attack (S).png");

	Attack_animation[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey attack(A).png");
	Attack_animation_B[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey attack(A+A).png");
	Attack_animation_C[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey attack(A+A+A).png");
	Jump_Attack_animation[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey attack(Jump+A).png");
	Special_Attack_animation[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey attack(A+S).png");

	Attack_animation[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm attack (A).png");
	Attack_animation_B[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm attack (A+A).png");
	Attack_animation_C[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm attack (A+A+A).png");
	Jump_Attack_animation[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm attack (Jump+A).png");
	Special_Attack_animation[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm attack (S).png");

	Attack_animation[Transes::swampfire].loadFromFile("aliens/Swampfire/swampfire attack(A).png");
	Attack_animation_B[Transes::swampfire].loadFromFile("aliens/Swampfire/swampfire attack (A+A).png");
	Attack_animation_C[Transes::swampfire].loadFromFile("aliens/Swampfire/swampfire attack(A+A+A).png");
	Jump_Attack_animation[Transes::swampfire].loadFromFile("aliens/Swampfire/swampfire attack Jump.png");
	Special_Attack_animation[Transes::swampfire].loadFromFile("aliens/Swampfire/swampfire attack(s).png");

	//trans load
	trans_frames[0].loadFromFile("aliens/trans/trans 1.png");
	trans_frames[1].loadFromFile("aliens/trans/trans 2.png");
	trans_frames[2].loadFromFile("aliens/trans/trans 3.png");
	trans_frames[3].loadFromFile("aliens/trans/trans 4.png");
	trans_frames[4].loadFromFile("aliens/trans/trans 5.png");
	trans_frames[5].loadFromFile("aliens/trans/trans 6.png");

	//jump load
	jump_animation[Transes::ben].loadFromFile("ben/ben jump.png");
	jump_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray Jump_peak.png");
	jump_animation[Transes::bigchuck].loadFromFile("aliens/green/green Jump_peak.png");
	jump_animation[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill jump_peak.png");
	jump_animation[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey jump peak.png");
	jump_animation[Transes::brainstorm].loadFromFile("aliens/brainstorm/brainstorm jump_peak.png");
	jump_animation[Transes::swampfire].loadFromFile("aliens/Swampfire/swampfire jump.png");

	secondjump_animation[Transes::BigChill].loadFromFile("aliens/Bigchill/bigchill double_jump.png");
	secondjump_animation[Transes::bigchuck].loadFromFile("aliens/green/green Jump_double.png");
	secondjump_animation[Transes::jetray].loadFromFile("aliens/jetray/jetray Jump_double.png");
	secondjump_animation[Transes::SpiderMonkey].loadFromFile("aliens/spider monkey/spidermonkey double jump.png");

	//player set tex
	player[Transes::ben].setTexture(idle_animation[Transes::ben]);
	player[Transes::jetray].setTexture(idle_animation[Transes::jetray]);
	player[Transes::bigchuck].setTexture(idle_animation[Transes::bigchuck]);
	player[Transes::BigChill].setTexture(idle_animation[Transes::BigChill]);
	player[Transes::SpiderMonkey].setTexture(idle_animation[Transes::SpiderMonkey]);
	player[Transes::brainstorm].setTexture(idle_animation[Transes::brainstorm]);
	player[Transes::swampfire].setTexture(idle_animation[Transes::swampfire]);

	diediedie[Transes::ben].loadFromFile("ben/ben die.png");
	dieframescount[Transes::ben] = 3;

	//walkframes cnt
	walkFramesCount[Transes::ben] = 8;
	walkFramesCount[Transes::jetray] = 9;
	walkFramesCount[Transes::bigchuck] = 4;
	walkFramesCount[Transes::BigChill] = 11;
	walkFramesCount[Transes::SpiderMonkey] = 8;
	walkFramesCount[Transes::brainstorm] = 12;
	walkFramesCount[Transes::swampfire] = 11;

	hitframecount[Transes::ben] = 3;
	hitframecount[Transes::jetray] = 8;
	hitframecount[Transes::bigchuck] = 11;
	hitframecount[Transes::BigChill] = 5;
	hitframecount[Transes::SpiderMonkey] = 5;
	hitframecount[Transes::brainstorm] = 10;
	hitframecount[Transes::swampfire] = 5;

	//idleframes cnt
	idleFramesCount[Transes::ben] = 4;
	idleFramesCount[Transes::jetray] = 18;
	idleFramesCount[Transes::bigchuck] = 12;
	idleFramesCount[Transes::BigChill] = 16;
	idleFramesCount[Transes::SpiderMonkey] = 18;
	idleFramesCount[Transes::brainstorm] = 18;
	idleFramesCount[Transes::swampfire] = 29;

	// extra
	landFrameCount[Transes::ben] = 1;
	landFrameCount[1] = 1;
	glideFramesCount[Transes::BigChill] = 13;
	landFrameCount[Transes::BigChill] = 6;
	landFrameCount[Transes::SpiderMonkey] = 5;
	landFrameCount[Transes::brainstorm] = 6;
	landFrameCount[Transes::jetray] = 5;
	landFrameCount[Transes::bigchuck] = 5;
	flyFrameCount[Transes::jetray] = 3;
	flyidleframecount[Transes::jetray] = 5;
	bendie.loadFromFile("ben/ben die1.png");
	climb.loadFromFile("aliens/spider monkey/spidermonkey attack(climb_idle).png");
	climbup.loadFromFile("aliens/spider monkey/spidermonkey attack(climb_up).png");
	climbdown.loadFromFile("aliens/spider monkey/spidermonkey attack(climb_down).png");
	climbframecount = 14;
	climbupframecount = 12;
	climbdownframecount = 12;
	flyaframecount = 3;
	flywframecount = 3;

	//attackframes cnt
	AttackFramesCount[Transes::ben] = 5;

	AttackFramesCount[Transes::jetray] = 7;
	AttackFramesCount_B[Transes::jetray] = 8;
	AttackFramesCount_C[Transes::jetray] = 10;
	Jump_AttackFramesCount[Transes::jetray] = 7;
	special_AttackFramesCount[Transes::jetray] = 10;

	AttackFramesCount[Transes::bigchuck] = 8;
	AttackFramesCount_B[Transes::bigchuck] = 11;
	AttackFramesCount_C[Transes::bigchuck] = 10;
	Jump_AttackFramesCount[Transes::bigchuck] = 8;
	special_AttackFramesCount[Transes::bigchuck] = 10;

	AttackFramesCount[Transes::BigChill] = 8;
	AttackFramesCount_B[Transes::BigChill] = 11;
	AttackFramesCount_C[Transes::BigChill] = 12;
	Jump_AttackFramesCount[Transes::BigChill] = 7;
	special_AttackFramesCount[Transes::BigChill] = 18;

	AttackFramesCount[Transes::SpiderMonkey] = 6;
	AttackFramesCount_B[Transes::SpiderMonkey] = 11;
	AttackFramesCount_C[Transes::SpiderMonkey] = 12;
	Jump_AttackFramesCount[Transes::SpiderMonkey] = 7;
	special_AttackFramesCount[Transes::SpiderMonkey] = 15;

	AttackFramesCount[Transes::brainstorm] = 5;
	AttackFramesCount_B[Transes::brainstorm] = 6;
	AttackFramesCount_C[Transes::brainstorm] = 10;
	Jump_AttackFramesCount[Transes::brainstorm] = 12;
	special_AttackFramesCount[Transes::brainstorm] = 12;

	AttackFramesCount[Transes::swampfire] = 6;
	AttackFramesCount_B[Transes::swampfire] = 4;
	AttackFramesCount_C[Transes::swampfire] = 8;
	Jump_AttackFramesCount[Transes::swampfire] = 7;
	special_AttackFramesCount[Transes::swampfire] = 7;

	//enemy load

	//enemy walk frames count
	enemywalkingFrameCount = 4;
	// enemy attack frames count
	enemyAttackFrameCount = 2;
	jumpFramesCount[Transes::ben] = 2;
	jumpFramesCount[Transes::jetray] = 5;
	jumpFramesCount[Transes::bigchuck] = 6;
	jumpFramesCount[Transes::BigChill] = 6;
	jumpFramesCount[Transes::SpiderMonkey] = 4;
	jumpFramesCount[Transes::brainstorm] = 5;
	jumpFramesCount[Transes::swampfire] = 5;
	secondjumpFramesCount[Transes::BigChill] = 7;
	secondjumpFramesCount[Transes::bigchuck] = 7;
	secondjumpFramesCount[Transes::jetray] = 5;
	secondjumpFramesCount[Transes::SpiderMonkey] = 8;
	secondjumpFramesCount[Transes::brainstorm] = 8;

	//player position
	player[0].setPosition(745, 425);
	for (int i = 0; i < aliensnumber; i++) {
		player[i].setOrigin(player[i].getLocalBounds().width / 2, player[i].getLocalBounds().height / 2);
	}
}
void GeddoCarFun() {
	CarBox.setSize(Vector2f(500.0f, 200.0f));
	CarBox.setFillColor(Color::Blue);
	CarBox.setPosition(15500, 836);
	CarTex.loadFromFile("car1removebg.png");
	CarSp.setTexture(CarTex);
	CarSp.setPosition(CarBox.getPosition().x, CarBox.getPosition().y - 20);
	CarSp.setScale(0.7, 0.7);
}
void start()
{
	OmnitrixBubbleTospriteFun();
	hpBubbleTospriteFun();
	playerHealthGotDamage();
	GeddoCarFun();
	OmnitrixUI();
	HealthBarFunction();
	boxes();
	animation();
	menu_start();
	omnibarrrr();
	initDialogue();

	if (!bgTexture.loadFromFile("Map/bg1.png")) cout << "Failed to load background!!" << endl;
	bgTexture.setRepeated(true);
	bgSprite.setTexture(bgTexture);
	// 1. Calculate the exact height of your map in pixels (30 * 32 = 960)
	float exactMapHeight = mapH * tileSize;

	// 2. Scale the background so its height perfectly matches the map height
	float bgScale = exactMapHeight / bgTexture.getSize().y;
	bgSprite.setScale(bgScale, bgScale);

	// 3. Stretch the repeating box horizontally across the ENTIRE map width
	int totalWorldWidth = mapW * tileSize;
	int repeatWidth = totalWorldWidth / bgScale;
	int repeatHeight = bgTexture.getSize().y; // Full texture height
	bgSprite.setTextureRect(IntRect(0, 0, repeatWidth, repeatHeight));
	// 1. Load the tileset FIRST
	if (!tileset.loadFromFile("Map/ts1.png")) cout << "Failed to load tileset!" << endl;

	// 2. Load the map blueprint you saved from the editor
	load_map("level1.txt", mapData, levelObjects, tileset);
	for (int i = 0; i < 8; i++) {
		player[i].setScale(MC_SCALE, MC_SCALE);
		if (i == Transes::bigchuck)player[i].setScale(0.8f, 0.8f);
	}
	Enemy_animation_idle[Enemy_type::Level1Boss].loadFromFile("enemy/Idlefs.png");
	Enemy_animation_walk[Enemy_type::Level1Boss].loadFromFile("enemy/Runfss.png");
	Enemy_animation_attack[Enemy_type::Level1Boss].loadFromFile("enemy/Attack2fs.png");
	Enemy_animation_attack2[Enemy_type::Level1Boss].loadFromFile("enemy/Attack1fs.png");
	Enemy_animation_hurt[Enemy_type::Level1Boss].loadFromFile("enemy/Take Hitfs.png");
	Enemy_animation_die[Enemy_type::Level1Boss].loadFromFile("enemy/Deathfs.png");

	Enemy_animation_idle[Enemy_type::First].loadFromFile("enemy/yellowNinja - idle.png");
	Enemy_animation_walk[Enemy_type::First].loadFromFile("enemy/yellowNinja - walk.png");
	Enemy_animation_attack[Enemy_type::First].loadFromFile("enemy/yellowNinja - attack.png");
	Enemy_animation_hurt[Enemy_type::First].loadFromFile("enemy/yellowNinja - hit.png");
	Enemy_animation_die[Enemy_type::First].loadFromFile("enemy/yellowNinja - Death.png");

	Enemy_animation_idle[Enemy_type::Second].loadFromFile("enemy/enemy idle.png");
	Enemy_animation_walk[Enemy_type::Second].loadFromFile("enemy/enemy run.png");
	Enemy_animation_attack[Enemy_type::Second].loadFromFile("enemy/enemy attack.png");
	Enemy_animation_hurt[Enemy_type::Second].loadFromFile("enemy/enemy hit.png");
	Enemy_animation_die[Enemy_type::Second].loadFromFile("enemy/enemy dead.png");

	Enemy_animation_idle[3].loadFromFile("enemy/idlea.png");
	Enemy_animation_walk[3].loadFromFile("enemy/runa.png");
	Enemy_animation_attack[3].loadFromFile("enemy/attacka.png");
	Enemy_animation_hurt[3].loadFromFile("enemy/hurta.png");
	Enemy_animation_die[3].loadFromFile("enemy/deatha.png");

	Enemy_animation_idle[4].loadFromFile("enemy/player-stand.png");
	Enemy_animation_walk[4].loadFromFile("enemy/player-run.png");
	Enemy_animation_attack[4].loadFromFile("enemy/player-stand.png");
	Enemy_animation_hurt[4].loadFromFile("enemy/player-hurt.png");
	Enemy_animation_die[4].loadFromFile("enemy/player-die.png");

	Enemy_animation_idle[5].loadFromFile("enemy/spr_Idle_strip.png");
	Enemy_animation_walk[5].loadFromFile("enemy/spr_Walk_strip.png");
	Enemy_animation_attack[5].loadFromFile("enemy/spr_Attack_strip.png");
	Enemy_animation_hurt[5].loadFromFile("enemy/spr_hurt_strip.png");
	Enemy_animation_die[5].loadFromFile("enemy/spr_Death_strip.png");

	Enemy_animation_idle[6].loadFromFile("enemy/player-stand.png");
	Enemy_animation_walk[6].loadFromFile("enemy/player-run.png");
	Enemy_animation_attack[6].loadFromFile("enemy/player-stand.png");
	Enemy_animation_hurt[6].loadFromFile("enemy/player-hurt.png");
	Enemy_animation_die[6].loadFromFile("enemy/player-die.png");

	boxtx[0].loadFromFile("1.png");
	boxtx[1].loadFromFile("2.png");
	boxtx[2].loadFromFile("3.png");
	boxtx[3].loadFromFile("4.png");
	boxtx[4].loadFromFile("5.png");

	firetx[0].loadFromFile("f1.png");
	firetx[1].loadFromFile("f2.png");
	firetx[2].loadFromFile("f4.png");
	firetx[3].loadFromFile("f3.png");

	light.loadFromFile("light.png");
}

void ben10transformation()
{
	if (event.type == Event::KeyPressed) {
		if (event.key.code == Keyboard::Right && current_player == Transes::ben) {
			chosen_player = (chosen_player + 1) % unlockedaliens;
			changealien_sou.play();
		}
		if (event.key.code == Keyboard::Left && current_player == Transes::ben) {
			chosen_player = (chosen_player - 1);
			if (chosen_player < 0) chosen_player = unlockedaliens - 1;
			changealien_sou.play();
		}

		if (event.key.code == Keyboard::Enter && current_player == Transes::ben && chosen_player != Transes::ben) {
			trans_sou.play();
			if (!isTransing) {
				isTransing = true;
				transIndex = 0;
				transClock.restart();
			}
			if (chosen_player == Transes::swampfire) {
				swamptrans_sou.play();
			}
			else if (chosen_player == Transes::BigChill) {
				bigchilltrans_sou.play();
			}
			else if (chosen_player == Transes::SpiderMonkey) {
				spidertrans_sou.play();
			}
			else if (chosen_player == Transes::brainstorm) {
				brainstormtrans_sou.play();
			}
			else if (chosen_player == Transes::jetray) {
				jetraytrans_sou.play();
			}

			else if (chosen_player == Transes::bigchuck) {
				bigchucktrans_sou.play();
			}
		}
		if (event.key.code == Keyboard::R && current_player != Transes::ben) {
			trans_sou.play();
			if (!isTransing) {
				chosen_player = Transes::ben;
				isTransing = true;
				transIndex = 0;
				transClock.restart();
			}
		}
	}
	ground.setSize(Vector2f(window.getSize().x, 50));
	ground.setFillColor(Color::Green);
	ground.setOrigin(ground.getLocalBounds().width / 2.0f, ground.getLocalBounds().height / 2.0f);
	ground.setPosition(window.getSize().x / 2.0f, window.getSize().y - 100);
}
