

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

// fly mode
bool is_flying = false;
Clock flying;
float flying_time = 13.0f, maxflytime = 13.0f, rororo = 0;
bool fwaspressed = 0, flyhit = 0;
float flyscale = 2.4;

void fly() {
	cout << player[current_player].getScale().x << ' ' << player[current_player].getScale().y;
	velocity = { 0.0f,0.0f };
	float flyspeed = speed[current_player].speedX * 2;
	if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::S))
		velocity = { flyspeed, flyspeed },player[current_player].setScale(flyscale, flyscale) , rororo = 10;

	else if (Keyboard::isKeyPressed(Keyboard::S) && Keyboard::isKeyPressed(Keyboard::A)) 
		velocity = { -flyspeed, flyspeed } ,player[current_player].setScale(-flyscale, flyscale) ,rororo = -10;

	else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::D)) 
		velocity = { flyspeed, -flyspeed } , player[current_player].setScale(flyscale, flyscale) , rororo = -10;
	
	else if (Keyboard::isKeyPressed(Keyboard::W) && Keyboard::isKeyPressed(Keyboard::A)) 
		velocity = { -flyspeed, -flyspeed } ,player[current_player].setScale(-flyscale, flyscale) ,rororo = 10;
	
	else if (Keyboard::isKeyPressed(Keyboard::A)) 
		velocity.x = -flyspeed , player[current_player].setScale(-flyscale, flyscale) , rororo = 0;
	
	else if (Keyboard::isKeyPressed(Keyboard::D)) 
		velocity.x = flyspeed , player[current_player].setScale(flyscale, flyscale) , rororo = 0;
	
	else if (Keyboard::isKeyPressed(Keyboard::W)) velocity.y = -flyspeed, rororo = 0;
	else if (Keyboard::isKeyPressed(Keyboard::S)) velocity.y = flyspeed, rororo = 0;
	else rororo = 0;

	float currentro = player[current_player].getRotation();

	if (currentro > 180.0) {
		currentro -= 360.0;
	}
	if (currentro < rororo) {
		currentro += 1.0f ;
		if (currentro > rororo) currentro = rororo ; 
	}
	else if (currentro > rororo) {
		currentro -= 1.0f ; 
		if (currentro < rororo) currentro = rororo; 
	}

	player[current_player].setRotation(currentro);

	characterbox[current_player].move(velocity);
	FloatRect pb = characterbox[current_player].getGlobalBounds();
	for (int x = 0; x < mapW; x++) {
		for (int y = 0; y < mapH; y++) {
			if (mapData[x][y].hasCollision) {
				FloatRect tb(x * tileSize, y * tileSize,
					mapData[x][y].textureRect.width,
					mapData[x][y].textureRect.height);

				if (pb.intersects(tb)) {
					if (velocity.y > 0 && pb.top < tb.top)
						characterbox[current_player].setPosition(
							characterbox[current_player].getPosition().x, tb.top - (characterbox[current_player].getGlobalBounds().height - characterbox[current_player].getOrigin().y));
					else if (velocity.y < 0)
						characterbox[current_player].setPosition(
							characterbox[current_player].getPosition().x, tb.top + tb.height);
					if (velocity.x > 0 && pb.left < tb.left)
						characterbox[current_player].setPosition(
							tb.left - pb.width, characterbox[current_player].getPosition().y);
					else if (velocity.x < 0 && pb.left > tb.left)
						characterbox[current_player].setPosition(
							tb.left + tb.width, characterbox[current_player].getPosition().y);
				}
			}
		}
	}
	player[current_player].setPosition(characterbox[current_player].getPosition());

	
	 if (velocity.x != 0 || velocity.y != 0 && !flyhit) {
		player[current_player].setTexture(fly_animation[current_player], true);
		int fw = fly_animation[current_player].getSize().x / flyFrameCount[current_player];
		int fh = fly_animation[current_player].getSize().y;
		player[current_player].setOrigin(fw / 2.0f, (float)fh / 2.0f +20.0f );
		if (animClock.getElapsedTime().asSeconds() > 0.1f) {
			flyindex = (flyindex + 1) % flyFrameCount[current_player];
			animClock.restart();
		}
		player[current_player].setTextureRect(IntRect(flyindex * fw, 0, fw, fh));
	}
	else {
		player[current_player].setTexture(fly_idleanimation[current_player], true);
		int fiw = fly_idleanimation[current_player].getSize().x / flyidleframecount[current_player];
		int fih = fly_idleanimation[current_player].getSize().y;
		player[current_player].setOrigin(fiw / 2.0f +20.0f , (float)fih /2.0f +40.0f);
		if (animClock.getElapsedTime().asSeconds() > 0.1f) {
			flyidleindex = (flyidleindex + 1) % flyidleframecount[current_player];
			animClock.restart();
		}
		player[current_player].setTextureRect(IntRect(flyidleindex * fiw, 0, fiw, fih));
	}
}
void flycom() {

	float dt = flying.restart().asSeconds();
	bool f_pressed = Keyboard::isKeyPressed(Keyboard::F);

	if (f_pressed && !fwaspressed && current_player == Transes::jetray) {
		if (!is_flying && flying_time > 0.2f)
			is_flying = true;
		else
			is_flying = false;
	}
	fwaspressed = f_pressed;

	if (is_flying) {
		flying_time -= dt;

		if (flying_time <= 0) {
			flying_time = 0;
			is_flying = false;
		}
		fly();
	}
	else {
		if (flying_time < maxflytime)
			flying_time += (0.5f * dt);
	}
	if (flying_time > maxflytime) flying_time = maxflytime;
}

void movement()
{

	if (is_flying && (hp <= 0 || isWinning)) {
		is_flying = false;
		flying_time = 0;
		flyhit = false;
		velocity.y = 0;
		player[current_player].setRotation(0);
	}

	if (!onground && (hp <= 0 || isWinning))
		isFallingBeforeDeath = true;

	if (isFallingBeforeDeath) {
		velocity.y += 0.5f;
		if (velocity.y > 15.0f) velocity.y = 15.0f;

		characterbox[current_player].move(0, velocity.y);
		player[current_player].setPosition(characterbox[current_player].getPosition());

		FloatRect pb = characterbox[current_player].getGlobalBounds();
		for (int x = 0; x < mapW && isFallingBeforeDeath; x++) {
			for (int y = 0; y < mapH && isFallingBeforeDeath; y++) {
				if (mapData[x][y].hasCollision) {
					FloatRect tb(x * tileSize, y * tileSize,
						mapData[x][y].textureRect.width,
						mapData[x][y].textureRect.height);
					if (pb.intersects(tb) && velocity.y >= 0 && pb.top < tb.top) {
						characterbox[current_player].setPosition(
							characterbox[current_player].getPosition().x,
							tb.top - (pb.height - characterbox[current_player].getOrigin().y));
						velocity.y = 0;
						onground = true;
						touchedGround = true;
						isFallingBeforeDeath = false; 
						player[current_player].setPosition(characterbox[current_player].getPosition());
					}
				}
			}
		}

		if (isFallingBeforeDeath) {
			player[current_player].setTexture(jump_animation[current_player], true);
			int jw = jump_animation[current_player].getSize().x / jumpFramesCount[current_player];
			int jh = jump_animation[current_player].getSize().y;
			player[current_player].setOrigin(jw / 2.0f, (float)jh);
			player[current_player].setTextureRect(IntRect(0, 0, jw, jh));
			return;
		}
	}

	if (isWinning && current_player == Transes::ben && !isTransing) {

		int winW = win_animation.getSize().x / winAnimFrameCount;
		int winH = win_animation.getSize().y;

		player[current_player].setTexture(win_animation, true);
		player[current_player].setOrigin(winW / 2.0f, (float)winH);
		player[current_player].setPosition(characterbox[current_player].getPosition());

		if (winClock.getElapsedTime().asSeconds() > 0.3f) {
			winAnimIndex++;
			winClock.restart();


			if (winAnimIndex >= winAnimFrameCount) {
				isWinning = false;
				menuIndex = 7;
			}
		}

		player[current_player].setTextureRect(
			IntRect(winAnimIndex * winW, 0, winW, winH)
		);

		return;
	}


	if (hp <= 0) {

		if (current_player != Transes::ben && !isTransing) {
			chosen_player = Transes::ben;
			isTransing = true;
			transIndex = 0;
			transClock.restart();
		}

		if (current_player == Transes::ben && !isTransing) {

			if (dieindex + 1 < dieframescount[Transes::ben]) {

				player[current_player].setTexture(diediedie[Transes::ben], true);
				int lw = diediedie[Transes::ben].getSize().x / dieframescount[Transes::ben];
				int lh = diediedie[Transes::ben].getSize().y;
				player[current_player].setOrigin(lw / 2.0f, (float)lh);

				if (animClock.getElapsedTime().asSeconds() > 0.1f) {
					dieindex++;
					animClock.restart();
				}
				player[current_player].setTextureRect(IntRect(dieindex * lw, 0, lw, lh));
				player[current_player].setPosition(characterbox[current_player].getPosition());
			}
			else {

				player[current_player].setTexture(bendie, true);
				player[current_player].setPosition(characterbox[current_player].getPosition());
				static Clock dtimer;
				Time dietime = seconds(1.0f);

				if (dtimer.getElapsedTime() > dietime) {
					ben_die_so.play();
					menuIndex = 8;
					lv1_music_so.stop();
					lv3_soun_so.stop();
					lv4_soun_so.stop();
					boss_soun_so.stop();
					Rain_so.stop();
					thunderSou.stop();
					walk_forest_so.stop();
					win_music_sound.setLoop(true);
					win_music_sound.play();
				}


			}
			return;
		}

	}

	BenAttacking = false;


	if (recoveryClock.getElapsedTime().asSeconds() < 0.1f) {
		player[current_player].setTexture(hit_animation[current_player], true);
		int spFrames = hitframecount[current_player];
		int spWidth = hit_animation[current_player].getSize().x / spFrames;
		int spHeight = hit_animation[current_player].getSize().y;

		player[current_player].setOrigin(spWidth / 2.0f, spHeight);

		if (hit.getElapsedTime().asSeconds() > 0.08f) {

			if (hitindex + 1 < spFrames)
				hitindex++;

			hit.restart();
		}
		player[current_player].setTextureRect(IntRect(hitindex * spWidth, 0, spWidth, spHeight));
		if (!is_flying) {
			velocity.y = 0;
			velocity.x = 0;

			velocity.y += 0.5f;
		}
		characterbox[current_player].move(0, velocity.y);
		player[current_player].setPosition(characterbox[current_player].getPosition());

		FloatRect pb = characterbox[current_player].getGlobalBounds();
		for (int x = 0; x < mapW; x++) {
			for (int y = 0; y < mapH; y++) {
				if (mapData[x][y].hasCollision) {
					FloatRect tb(x * tileSize, y * tileSize,
						mapData[x][y].textureRect.width,
						mapData[x][y].textureRect.height);
					if (pb.intersects(tb) && velocity.y >= 0 && pb.top < tb.top) {
						characterbox[current_player].setPosition(
							characterbox[current_player].getPosition().x, tb.top);
						player[current_player].setPosition(
							characterbox[current_player].getPosition());
						velocity.y = 0;
						onground = true;
					}
				}
			}
		}

		return;
	}
	else
		hitindex = 0;



	if (is_flying)
		return;

	if (isTransing) {


		int TRANS_FRAMES = 6;
		if (transIndex >= TRANS_FRAMES) {
			characterbox[chosen_player].setPosition(characterbox[current_player].getPosition());
			player[chosen_player].setScale(player[current_player].getScale());
			current_player = chosen_player;
			transIndex = 0;
			isTransing = false;
			return;
		}
		player[current_player].setTexture(idle_animation[current_player], true);
		int iw = idle_animation[current_player].getSize().x / idleFramesCount[current_player];
		int ih = idle_animation[current_player].getSize().y;
		player[current_player].setOrigin(iw / 2.0f, (float)ih);
		player[current_player].setTextureRect(IntRect(0, 0, iw, ih));
		player[current_player].setPosition(characterbox[current_player].getPosition());


		transOverlaySp.setTexture(trans_frames[transIndex], true);
		int tw = trans_frames[transIndex].getSize().x;
		int th = trans_frames[transIndex].getSize().y;
		transOverlaySp.setTextureRect(IntRect(0, 0, tw, th));
		float charH = characterbox[current_player].getSize().y;
		float maxScale = (charH * 4.0f) / th;

		float progress = (float)(transIndex + 1) / (float)TRANS_FRAMES;


		transOverlaySp.setOrigin(tw / 2.0f, (float)th);
		transOverlaySp.setPosition(characterbox[current_player].getPosition().x, characterbox[current_player].getPosition().y + 50.0f);

		float dirSign = (player[current_player].getScale().x > 0) ? 1.0f : -1.0f;
		transOverlaySp.setScale(maxScale * dirSign, maxScale);

		if (transClock.getElapsedTime().asSeconds() > 0.08f) {
			transIndex++;
			transClock.restart();
		}

		if (transIndex >= TRANS_FRAMES) {
			characterbox[chosen_player].setPosition(characterbox[current_player].getPosition());
			player[chosen_player].setScale(player[current_player].getScale());
			current_player = chosen_player;
			transIndex = 0;
			isTransing = false;
		}

		return;
	}

	bool spacepressed = Keyboard::isKeyPressed(Keyboard::Space);
	bool justpressed = spacepressed && !spacewaspressed;
	is_gliding = false;

	if (justpressed) {
		if (onground) {
			onground = false;
			velocity.y = -1 * speed[current_player].speedY;
			jump_counter = 1;
			jumpClock.restart();
			if (current_player == Transes::ben) {
				jump_ben_so.play();
			}
			else if (current_player == Transes::SpiderMonkey) {
				jump_spider_so.play();
			}
			else if (current_player == Transes::BigChill) {
				jump_chill_so.play();
			}
			else if (current_player == Transes::swampfire) {
				jump_swamp_so.play();
			}
			else if (current_player == Transes::brainstorm) {
				jump_brain_so.play();
			}
			else if (current_player == Transes::jetray) {
				jump_jetray_so.play();
			}
			
		}
		else if (jump_counter < 2 && jumpClock.getElapsedTime().asSeconds() >= 0.1f) {
			if (current_player != Transes::ben||current_player!=Transes::brainstorm) {
				velocity.y = -1 * speed[current_player].speedY;
				jump_counter = 2;
				jumpClock.restart();
				if (current_player == Transes::ben) {
					jump_ben_so.play();
				}
				else if (current_player == Transes::SpiderMonkey) {
					jump_spider_so.play();
				}
				else if (current_player == Transes::BigChill) {
					jump_chill_so.play();
				}
				else if (current_player == Transes::swampfire) {
					jump_swamp_so.play();
				}
				else if (current_player == Transes::brainstorm) {
					jump_brain_so.play();
				}
				else if (current_player == Transes::jetray) {
					jump_jetray_so.play();
				}
			}
		}
	}
	if (spacepressed && !onground && current_player == Transes::BigChill && jump_counter > 1) {
		if (jumpClock.getElapsedTime().asSeconds() >= 0.4f) {
			is_gliding = true;
			was_gliding = true;
		}
	}
	spacewaspressed = spacepressed;


	if (onground && was_gliding) {
		landing = true;
		was_gliding = false;
	}




	//attack

	kPressedNow = Keyboard::isKeyPressed(Keyboard::K);
	UPressedNow = Keyboard::isKeyPressed(Keyboard::U);


	if (kPressedNow && !kWasPressed) {

		if (current_player != Transes::ben) {

			if (!onground) {
				jumpIndex = 0;
				jump_attack = true;
			}
			else {
				if (comboClock.getElapsedTime().asSeconds() > comboTimeout && combo_frame_count > 0) {
					combo_frame_count = 0;
				}
				combo_frame_count = (combo_frame_count % 3) + 1;
				AttackIndex = 0;
				comboClock.restart();
				isAttacking = true;
				combo_attack_done = false;
				if (current_player == Transes::SpiderMonkey) {
					attack_spider_so.play();
				}
				else if (current_player == Transes::BigChill) {
					attack_chill_so.play();
				}
				else if (current_player == Transes::swampfire) {
					attack_swamp_so.play();
				}
				else if (current_player == Transes::brainstorm) {
					attack_brain_so.play();
				}
				else if (current_player == Transes::jetray) {
					attack_jetray_so.play();
				}
				
			}
		}

		else {
			isAttacking = true;
			AttackIndex = 0;
			if (current_player == Transes::ben) {
				attack_ben_so.play();
			}
			
		}

	}
	kWasPressed = kPressedNow;
	if (UPressedNow && !uWasPressed) {
		if (current_player != Transes::ben) {
			if (!isAttacking && !isSpecialAttacking) {
				isSpecialAttacking = true;
				SpecialAttackIndex = 0;
				specialAttackClock.restart();
			}
		}
	}
	uWasPressed = UPressedNow;
	//move
	ismoving = false;
	velocity.x = 0;

	if (Keyboard::isKeyPressed(Keyboard::A) && !landing && !isAttacking && !isSpecialAttacking)
	{
		ismoving = true;
		velocity.x -= speed[current_player].speedX;
		if (player[current_player].getScale().x != -MC_SCALE) {
			player[current_player].setScale(-MC_SCALE, MC_SCALE);
		}
	}
	if (Keyboard::isKeyPressed(Keyboard::D) && !landing && !isAttacking && !isSpecialAttacking)
	{
		ismoving = true;
		velocity.x += speed[current_player].speedX;
		if (player[current_player].getScale().x != MC_SCALE) {
			player[current_player].setScale(MC_SCALE, MC_SCALE);
		}
	}

	//collision logic
	velocity.y += 0.5f;
	float fall_speed = velocity.y;

	characterbox[current_player].move(velocity);

	if (isAttacking || isSpecialAttacking) BenAttacking = true;
	FloatRect playerBounds = characterbox[current_player].getGlobalBounds();
	FloatRect wallbounds;
	for (int x = 0; x < mapW; x++)
	{
		for (int y = 0; y < mapH; y++)
		{
			if (mapData[x][y].hasCollision)
			{
				FloatRect tileBounds(x * tileSize, y * tileSize, mapData[x][y].textureRect.width, mapData[x][y].textureRect.height);
				wallbounds = tileBounds;
				if (playerBounds.intersects(tileBounds)) {
					if (velocity.y >= 0 && playerBounds.top < tileBounds.top)
					{
						characterbox[current_player].setPosition(
							characterbox[current_player].getPosition().x, tileBounds.top - (characterbox[current_player].getGlobalBounds().height - characterbox[current_player].getOrigin().y));
						velocity.y = 0;
						touchedGround = true;
						canclimb = 0;
					}
					else if (velocity.y < 0 && playerBounds.top > tileBounds.top + 20)
					{
						characterbox[current_player].setPosition(characterbox[current_player].getPosition().x, tileBounds.top + tileBounds.height);
						velocity.y = 0;
						canclimb = 0;
					}
					if (velocity.x > 0 && playerBounds.left < tileBounds.left && playerBounds.top > tileBounds.top + 5)
					{
						characterbox[current_player].setPosition(tileBounds.left - playerBounds.width, characterbox[current_player].getPosition().y);
						velocity.x = 0;
						canclimb = 1;
					}
					else if (velocity.x < 0 && playerBounds.left > tileBounds.left && playerBounds.top > tileBounds.top + 5)
					{
						characterbox[current_player].setPosition(tileBounds.left + tileBounds.width, characterbox[current_player].getPosition().y);
						velocity.x = 0;
						canclimb = 1;
					}
				}
			}
		}
	}
	for (int i = 0; i < levelObjects.size(); i++)
	{
		if (levelObjects[i].hasCollision) {
			FloatRect entBounds = levelObjects[i].hitbox;
			if (playerBounds.intersects(entBounds))
			{
				if (velocity.y >= 0 && playerBounds.top < entBounds.top)
				{
					characterbox[current_player].setPosition(characterbox[current_player].getPosition().x, entBounds.top - (characterbox[current_player].getGlobalBounds().height - characterbox[current_player].getOrigin().y));
					velocity.y = 0;
					touchedGround = true;
				}
			}
		}
	}
	
	if (canclimb && current_player == Transes::SpiderMonkey) {
		onground = 1;
		bool wall = 0;

		FloatRect playerBounds = characterbox[current_player].getGlobalBounds();
		FloatRect WALL = playerBounds;
		WALL.left += 8;
		WALL.top -= 50;
		for (int x = 0; x < mapW; x++)
		{
			for (int y = 0; y < mapH; y++)
			{
				if (mapData[x][y].hasCollision)
				{
					FloatRect tileBounds(x * tileSize, y * tileSize, mapData[x][y].textureRect.width, mapData[x][y].textureRect.height);
					if (WALL.intersects(tileBounds)) {
						wall = true; break;
					}
				}

			}
		}

		if (!wall) canclimb = 0;
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			velocity.y = 2.0f;

			player[current_player].setTexture(climbdown, true);
			int fw = climbdown.getSize().x / climbdownframecount;
			int fh = climbdown.getSize().y;
			player[current_player].setOrigin(fw / 2.0f, (float)fh);
			if (animClock.getElapsedTime().asSeconds() > 0.1f) {
				climbdownindex = (climbdownindex + 1) % climbdownframecount;
				animClock.restart();
			}
			player[current_player].setTextureRect(IntRect(climbdownindex * fw, 0, fw, fh));
		}
		else if (Keyboard::isKeyPressed(Keyboard::W)) {
			velocity.y = -2.0f;

			player[current_player].setTexture(climbup, true);
			int fw = climbup.getSize().x / climbupframecount;
			int fh = climbup.getSize().y;
			player[current_player].setOrigin(fw / 2.0f, (float)fh);
			if (animClock.getElapsedTime().asSeconds() > 0.1f) {
				climbupindx = (climbupindx + 1) % climbupframecount;
				animClock.restart();
			}
			player[current_player].setTextureRect(IntRect(climbupindx * fw, 0, fw, fh));
		}
		else if (Keyboard::isKeyPressed(Keyboard::A) || Keyboard::isKeyPressed(Keyboard::D) || Keyboard::isKeyPressed(Keyboard::Space)) canclimb = 0;
		else {
			velocity.y = 0.0f;

			player[current_player].setTexture(climb, true);
			int fw = climb.getSize().x / climbframecount;
			int fh = climb.getSize().y;
			player[current_player].setOrigin(fw / 2.0f, (float)fh);
			if (animClock.getElapsedTime().asSeconds() > 0.1f) {
				climbindex = (climbindex + 1) % climbframecount;
				animClock.restart();
			}
			player[current_player].setTextureRect(IntRect(climbindex * fw, 0, fw, fh));

		}
		characterbox[current_player].move(0, velocity.y);
		player[current_player].setPosition(characterbox[current_player].getPosition().x - 20.f, characterbox[current_player].getPosition().y);
		return;
	}

	// 3. Update Jumping State
	if (touchedGround) {
		if (!onground) {
			
				if (was_gliding) {
					landing = true, landindex = 0, was_gliding = false;
					if (current_player == Transes::BigChill)
						land_chill_so.play();

				}
			else if (fall_speed > 0.2f && landFrameCount[current_player] > 0) {
				landing = true;
				landindex = 0;
				if (current_player == Transes::ben) {
					land_ben_so.play();
				}
				else if (current_player == Transes::BigChill) {
					land_chill_so.play();
				}
				else if (current_player == Transes::swampfire) {
					land_swamp_so.play();
				}
				else if (current_player == Transes::brainstorm) {
					land_brain_so.play();
				}
				else if (current_player == Transes::jetray) {
					land_jetray_so.play();
				}
				
			}
			jumpClock.restart();
			onground = true;
			jump_attack = false;
			jump_counter = 0;
			canclimb = 0;
		}
	}
	else {
		onground = false;
	}
	onground = touchedGround;
	float direction = (player[current_player].getScale().x > 0) ? 1.0f : -1.0f;

	float dynamicOffset = -25.0f * direction;
	if (current_player != Transes::ben) {
		characterbox[current_player].setOrigin(
			dynamicOffset + characterbox[current_player].getLocalBounds().width / 2.0f,
			characterbox[current_player].getLocalBounds().height
		);
		characterboxarm[current_player].setOrigin(
			dynamicOffset + characterboxarm[current_player].getLocalBounds().width / 2.0f,
			characterboxarm[current_player].getLocalBounds().height / 2.0f
		);
	}
	//player move

	player[current_player].setPosition(characterbox[current_player].getPosition());
	
	characterboxarm[current_player].setPosition(characterbox[current_player].getPosition().x + player[current_player].getScale().x * characterboxarm[current_player].getLocalBounds().width / 2.0f, characterbox[current_player].getPosition().y - characterbox[current_player].getSize().y * 2 / 3.0f);
	if (current_player == ben&& player[current_player].getScale().x<0) {
		characterboxarm[current_player].setPosition(characterbox[current_player].getPosition().x - (characterboxarm[current_player].getLocalBounds().width / 4.0f), characterbox[current_player].getPosition().y - characterbox[current_player].getSize().y * 2 / 3.0f);
	}
	if (isSpecialAttacking) {
		walk_forest_so.stop();
		player[current_player].setTexture(Special_Attack_animation[current_player], true);
		int spFrames = special_AttackFramesCount[current_player];
		int spWidth = Special_Attack_animation[current_player].getSize().x / spFrames;
		int spHeight = Special_Attack_animation[current_player].getSize().y;

		player[current_player].setOrigin(spWidth / 2.0f, spHeight);

		if (specialAttackClock.getElapsedTime().asSeconds() > 0.1f) {
			SpecialAttackIndex++;
			specialAttackClock.restart();
			if (SpecialAttackIndex >= spFrames) {
				SpecialAttackIndex = 0;
				isSpecialAttacking = false;
			}
		}
		player[current_player].setTextureRect(IntRect(SpecialAttackIndex * spWidth, 0, spWidth, spHeight));
	}

	else if (isAttacking) {
		walk_forest_so.stop();
		Texture* currentAttackTex = &Attack_animation[current_player];

		int attFrames = AttackFramesCount[current_player];

		if (current_player != Transes::ben) {
			if (combo_frame_count == 2) {
				currentAttackTex = &Attack_animation_B[current_player];
				attFrames = AttackFramesCount_B[current_player];
			}
			else if (combo_frame_count == 3) {
				currentAttackTex = &Attack_animation_C[current_player];
				attFrames = AttackFramesCount_C[current_player];
			}
		}
		player[current_player].setTexture(*currentAttackTex, true);
		int attWidth = currentAttackTex->getSize().x / attFrames;
		int attHeight = currentAttackTex->getSize().y;
		player[current_player].setOrigin(attWidth / 2.0f, attHeight);


		if (animClock.getElapsedTime().asSeconds() > 0.1f) {
			AttackIndex++;
			animClock.restart();
			if (AttackIndex >= attFrames) {
				AttackIndex = 0;
				isAttacking = false;
				combo_attack_done = true;

				if (combo_frame_count >= 3) {
					combo_frame_count = 0;
				}
			}
		}
		player[current_player].setTextureRect(IntRect(AttackIndex * attWidth, 0, attWidth, attHeight));
	}
	else if (is_gliding && current_player == Transes::BigChill) {
		walk_forest_so.stop();
		velocity.y += 0.08f;
		if (velocity.y > 2.0f) velocity.y = 2.0f;

		player[current_player].setTexture(glide_animation[current_player], true);

		int gw = glide_animation[current_player].getSize().x / glideFramesCount[current_player];
		int gh = glide_animation[current_player].getSize().y;
		player[current_player].setOrigin(gw / 2.0f, (float)gh - 20.0f);

		if (animClock.getElapsedTime().asSeconds() > 0.3f) {
			glide_index = (glide_index + 1) % glideFramesCount[current_player];
			animClock.restart();
		}
		player[current_player].setTextureRect(IntRect(glide_index * gw, 0, gw, gh));
		is_gliding = true;
		was_gliding = true;
	}
	else if (landing) {
		walk_forest_so.stop();
		player[current_player].setTexture(land_animation[current_player], true);

		int lw = land_animation[current_player].getSize().x / landFrameCount[current_player];
		int lh = land_animation[current_player].getSize().y;

		player[current_player].setOrigin(lw / 2.0f, (float)lh);

		if (animClock.getElapsedTime().asSeconds() > 0.05f) {
			landindex++;
			animClock.restart();

			if (landindex >= landFrameCount[current_player])
				landing = false;
		}

		player[current_player].setTextureRect(IntRect(landindex * lw, 0, lw, lh));
	}
	else if (!onground) {
		walk_forest_so.stop();

		if (current_player != Transes::ben) {
			if (jump_attack) {
				int Jump_attack_frames = Jump_AttackFramesCount[current_player];
				if (animClock.getElapsedTime().asSeconds() > 0.1f) {
					jumpIndex = (jumpIndex + 1) % Jump_attack_frames;
					animClock.restart();

					player[current_player].setTexture(Jump_Attack_animation[current_player], true);
					int jumpWidth = Jump_Attack_animation[current_player].getSize().x / Jump_attack_frames;
					int jumpHeight = Jump_Attack_animation[current_player].getSize().y;

					player[current_player].setOrigin(jumpWidth / 2.0f, jumpHeight);
					player[current_player].setTextureRect(IntRect(jumpIndex * jumpWidth, 0, jumpWidth, jumpHeight));
				}
			}
			else {
				bool useSecondJump = (jump_counter >= 2) &&
					(secondjump_animation[current_player].getSize().x > 0);

				Texture& currentJumpTex = useSecondJump ?
					secondjump_animation[current_player] : jump_animation[current_player];

				int jumpFrames = useSecondJump ?
					secondjumpFramesCount[current_player] : jumpFramesCount[current_player];

				if (animClock.getElapsedTime().asSeconds() > 0.1f) {
					jumpIndex = (jumpIndex + 1) % jumpFrames;
					animClock.restart();
				}
				player[current_player].setTexture(currentJumpTex, true);
				int jumpWidth = currentJumpTex.getSize().x / jumpFrames;
				int jumpHeight = currentJumpTex.getSize().y;
				player[current_player].setOrigin(jumpWidth / 2.0f, jumpHeight);
				player[current_player].setTextureRect(IntRect(jumpIndex * jumpWidth, 0, jumpWidth, jumpHeight));
			}
		}
		else {
			int jumpFrames = jumpFramesCount[current_player];

			if (animClock.getElapsedTime().asSeconds() > 0.1f) {
				jumpIndex = (jumpIndex + 1) % jumpFrames;
				animClock.restart();

				player[current_player].setTexture(jump_animation[current_player], true);
				int jumpWidth = jump_animation[current_player].getSize().x / jumpFrames;
				int jumpHeight = jump_animation[current_player].getSize().y;

				player[current_player].setOrigin(jumpWidth / 2.0f, jumpHeight);
				player[current_player].setTextureRect(IntRect(jumpIndex * jumpWidth, 0, jumpWidth, jumpHeight));
			}
		}
	}

	else if (ismoving && !landing) {
		player[current_player].setTexture(walk_animation[current_player], true);

		int framesCount = walkFramesCount[current_player];
		int frameWidth = walk_animation[current_player].getSize().x / framesCount;
		int frameHeight = walk_animation[current_player].getSize().y;

		player[current_player].setOrigin(frameWidth / 2.0f, frameHeight);

		if (animClock.getElapsedTime().asSeconds() > 0.1f) {
			walkIndex = (walkIndex + 1) % framesCount;
			animClock.restart();
		}

		player[current_player].setTextureRect(IntRect(walkIndex * frameWidth, 0, frameWidth, frameHeight));
		if (currentEditorLevel == 1 || currentEditorLevel == 2 || currentEditorLevel == 3) {
			if (walk_forest_so.getStatus() != Sound::Playing) {
				walk_forest_so.setLoop(true);
				walk_forest_so.play();
			}
		}
	}
	else {
		walk_forest_so.stop();
		player[current_player].setTexture(idle_animation[current_player], true);

		int iFrames = idleFramesCount[current_player];
		int iWidth = idle_animation[current_player].getSize().x / iFrames;
		int iHeight = idle_animation[current_player].getSize().y;

		player[current_player].setOrigin((iWidth / 2.0f), iHeight);

		if (animClock.getElapsedTime().asSeconds() > 0.15f) {

			idleIndex = (idleIndex + 1) % iFrames;
			animClock.restart();
		}

		player[current_player].setTextureRect(IntRect(idleIndex * iWidth, 0, iWidth, iHeight));

	}
	float is_void = (mapH * tileSize) + 100.0f;
	if (characterbox[current_player].getPosition().y > is_void)
	{
		ben_die_so.play();
		menuIndex = 8;
		lv1_music_so.stop();
		lv3_soun_so.stop();
		lv4_soun_so.stop();
		boss_soun_so.stop();
		Rain_so.stop();
		thunderSou.stop();
		walk_forest_so.stop();
		win_music_sound.setLoop(true);
		win_music_sound.play();
	}

}
void update()
{

	if (currentEditorLevel == 3 && enemies.size() > 1) {
		enemies.erase(enemies.begin() + 0, enemies.begin() + (enemies.size() - 1));
	}
	
	touchedGround = false;
	if (levelStart.getElapsedTime().asSeconds() > 2.0f) {
		if (currentEditorLevel == 1 && !dialogue3) {
			dialogue3 = true;
			triggerDialogue(2);

			return;
		}
	}
	if (characterbox[current_player].getGlobalBounds().intersects(CarBox.getGlobalBounds()) && !isWinning && enemies.empty()) {
		
		isWinning = true;
		winAnimIndex = 0;
		winClock.restart();
		lv1_music_so.stop();
		Rain_so.stop();
		walk_forest_so.stop();
		lv1_soun_so.stop();
		lv3_soun_so.stop();
		lv4_soun_so.stop();
		boss_soun_so.stop();
		Rain_so.stop();
		thunderSou.stop();
		
		win_music_sound.setLoop(true);
		win_music_sound.play();

		if (current_player != Transes::ben && !isTransing) {
			chosen_player = Transes::ben;
			isTransing = true;
			transIndex = 0;
			transClock.restart();
		}
	}

	if (characterbox[current_player].getPosition().x >= CarBox.getPosition().x + CarBox.getSize().x / 2.0f) {
		characterbox[current_player].setPosition(CarBox.getPosition().x + CarBox.getSize().x / 2.0f, characterbox[current_player].getPosition().y);
	}
	timerToHealth += HPBubbleanimationClock.restart().asSeconds();
	timerToOmnitrix += OMBubbleanimationClock.restart().asSeconds();

	if (timerToHealth >= 0.1f) {
		frameCounterToHealth = (frameCounterToHealth + 1) % 22;
		timerToHealth = 0.f;
	}
	if (timerToOmnitrix >= 0.1f) {
		frameCounterToOmnitrix = (frameCounterToOmnitrix + 1) % 23;
		timerToOmnitrix = 0.f;
	}
	for (int i = 0; i < itemss.size(); i++) {
		BubbleAnimation(itemss[i]);
		if (itemss[i].collected) {
			itemss.erase(itemss.begin() + i);
			i--;
		}
	}

	if (chosen_player == 0 && current_player == 0)
		Omnitrixsp.setScale(0.6f, 0.6);
	else
		Omnitrixsp.setScale(0.36f, 0.36f);



	updateDialogue();
	if (isDialogueActive) {
		velocity = { 0.f, 0.f };
		return;
	}

	playerHealthGotDamage();
	playomnibar();
	// Omnitrix


	if (current_player == Transes::ben) {
		whiteOmnitrix();
	}
	else {
		GreenOmnitrix();
	}
	float ot = omni.restart().asSeconds();
	if (omnitime >= 30.0f) omnitime = 30.0f;
	if (current_player != Transes::ben) {
		if(!cheatCodeOmnitrixActive)
		omnitime -= ot;

		if (omnitime <= 0) {
			omnitime = 0;
			if (!isTransing) {
				isTransing = true;
				chosen_player = Transes::ben;
				transIndex = 0;
				animClock.restart();
			}
		}
	}
	else {
		if (omnitime < 30.0f) {
			omnitime += ot * (30.0f / recharge);
		}

	}

	view.setSize(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height);
	view.setCenter(characterbox[current_player].getPosition());

	if (currentEditorLevel == 3) {
		view.setCenter(enemies[0].orginpoint.x, enemies[0].orginpoint.y- 700);

		float leftLimit = view.getCenter().x - view.getSize().x / 2.0f + 100;
		float rightLimit = view.getCenter().x + view.getSize().x / 2.0f - 100;

		if (characterbox[current_player].getPosition().x < leftLimit) {
			characterbox[current_player].setPosition(leftLimit, characterbox[current_player].getPosition().y);
			player[current_player].setPosition(characterbox[current_player].getPosition());
		}
		if (characterbox[current_player].getPosition().x > rightLimit) {
			characterbox[current_player].setPosition(rightLimit, characterbox[current_player].getPosition().y);
			player[current_player].setPosition(characterbox[current_player].getPosition());
		}
	}

	window.setView(view);

	// 2. Calculate the boundaries dynamically
	float halfViewX = view.getSize().x / 2.0f;
	float halfViewY = view.getSize().y / 2.0f;
	float mapPixelWidth = mapW * tileSize;      // 500 * 32 = 16000
	float mapPixelHeight = mapH * tileSize;     // 30 * 32 = 960

	// 3. Clamp X and Y so the camera NEVER sees outside the tile grid
	float clampedX = std::max(halfViewX, std::min(view.getCenter().x, mapPixelWidth - halfViewX));
	float clampedY = std::max(halfViewY, std::min(view.getCenter().y, mapPixelHeight - halfViewY));

	view.setCenter(clampedX, clampedY);
	// -------------------------------
	flycom();

	movement();

	for (int i = 0; i < enemies.size(); i++) {
		update_enemy_movement(enemies[i]);
		if (enemies[i].remove_me) {
			if (enemies[i].enemy_type != Enemy_type::Level1Boss || (enemies[i].enemy_type == Enemy_type::Level1Boss && !isDialogueActive)) {
				if (enemies[i].enemy_type == Enemy_type::Level1Boss && !isDialogueActive) { previous_menuIndex = menuIndex; menuIndex = 4; }
				enemies.erase(enemies.begin() + i);
				i--;
			}
		}
	}

	for (int i = 0; i < fireballs.size(); i++) {
		update_fireball(fireballs[i]);
		if (recoveryClock.getElapsedTime().asSeconds() >= 0.1f && characterbox[current_player].getGlobalBounds().intersects(fireballs[i].shape.getGlobalBounds())) {
			if(!cheatCodeHealthActive)
			hp -= 10;

			recoveryClock.restart();
			fireballs.erase(fireballs.begin() + i);
			i--;
		}
	}
	
		if (event.type == Event::TextEntered) {
			char s = static_cast<char>(event.text.unicode);
			if (current_code.empty() || current_code[current_code.size() - 1] != s) {
				current_code.push_back(s);
				if (current_code[current_code.size() - 1] != cheatCode_health[current_code.size() - 1] &&
					current_code[current_code.size() - 1] != cheatCode_omnitrix[current_code.size() - 1]) {
					current_code = "";
				}
				else {
					if (current_code == cheatCode_health) {
						if (!cheatCodeHealthActive)
							cheatCodeHealthActive = true;
						else
							cheatCodeHealthActive = false;
						current_code = "";
					}
					else if (current_code == cheatCode_omnitrix) {
						if (!cheatCodeOmnitrixActive)
							cheatCodeOmnitrixActive = true;
						else
							cheatCodeOmnitrixActive = false;
						current_code = "";
					}
				}
				cout << s << endl;
			}
		}
	
}
void draw() {
	if (currentEditorLevel == 1) {
		window.clear(Color::Color(30, 20, 10));
	}
	else {
		window.clear(Color::White);
	}
	
	window.setView(view);
	window.draw(bgSprite);
	for (int x = 0; x < mapW; x++) {
		for (int y = 0; y < mapH; y++) {
			if (mapData[x][y].textureRect.width > 0) {
				Sprite s(tileset);
				s.setTextureRect(mapData[x][y].textureRect);
				s.setPosition((float)x * tileSize, (float)y * tileSize);
				window.draw(s);
			}
		}
	}

	for (int i = 0; i < levelObjects.size(); i++) {
		window.draw(levelObjects[i].sprite);
	}
	if (current_player == Transes::bigchuck) {
		int dir = (player[current_player].getScale().x > 0) ? 1 : -1;
		player[current_player].setPosition(player[current_player].getPosition().x - dir * 25.0f, player[current_player].getPosition().y);
	}

	if (current_player == Transes::ben) {
		player[current_player].setPosition(characterbox[current_player].getPosition().x, characterbox[current_player].getPosition().y+8);
	}
	
	window.draw(CarSp);
	//window.draw(characterbox[current_player]);
	//window.draw(characterboxarm[current_player]);
	window.draw(player[current_player]);

	// الـ trans overlay فوق الشخصية
	if (isTransing) {
		window.draw(transOverlaySp);
	}

	for (int i = 0; i < bubblenum; i++) {
		window.draw(omniBubbleSp[i]);
		window.draw(hpBubbleSp[i]);
	}

	// Don't forget to draw the fireballs too!
	for (auto& fb : fireballs)
	{
		window.draw(fb.shape);
	}
	for (auto& e : enemies)
	{
		//window.draw(e.box);
		//window.draw(e.boxarm);
		window.draw(e.sprite);
	}
	for (auto& item : itemss) {
		if (!item.collected && (item.type == MP::Health || item.type == MP::Omnitrix)) {
			//window.draw(item.shape);
			window.draw(item.sprite);
		}
	}

	// ثانياً: ارسم الـ boxes فوقيهم
	for (auto& item : itemss) {
		if (!item.collected && (item.type == MP::Box || item.type == MP::Fire || item.type == MP::Lightning)) {
			window.draw(item.sprite);
			//window.draw(item.shape);
		}
	}

	View uiView(FloatRect(0, 0, 1800, 900));
	window.setView(uiView); //ui

	if (currentEditorLevel == 2||currentEditorLevel==5) {
		View uiView(FloatRect(0, 0, 1800, 900));
		window.setView(uiView);
		drawRain();
	}
	
	
	window.draw(Omnitrixsp);
	window.draw(emptyHPBar);
	window.draw(hpBar);

	window.draw(emptyomnibar);
	window.draw(omnibar);
	window.draw(Omnitrixsp);
	drawDialogue(window);
	window.display();
}
