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
struct Fireball_enemy {
	CircleShape shape;
	Vector2f velocity;
	float startX;
};
enum enemy_State
{
	Idle, Walk, Follow, Attack, Getready, attacked, attack2, attackanim, attack2anim, hurt, death
};
int limitx[3] = { 300 ,300, VideoMode::getDesktopMode().width / 2.0f - 100 };
float e_gravity = 0.8f;
float followSpeed[3] = { 6.0f ,12.0f, 18.0f };
float acceleration = 0.1f;
float AttackRange[3] = { 300.0f,400.0f,VideoMode::getDesktopMode().width / 2.0f - 100 };
float FollowRange[3] = { 500.0f,500.0f,VideoMode::getDesktopMode().width / 2.0f - 100 };
float walkSpeed[3] = { 5.0f,20.0f, 20.0f };
Vector2f current_walk_speed[3] = { {5.0f, -15.0f}, {10.0f, -15.0f}, {7.0f, -15.0f} };
struct first_e {
	float wantedspeed[3] = { 5 ,5, 10 };
	int enemy_type;
	RectangleShape box;
	RectangleShape boxarm;
	Vector2f orginpoint;
	Sprite sprite;
	Vector2f speed = { 0, 0 };
	int enemy_state = enemy_State::Walk;
	Clock enemy_attack_timer;
	Clock attackgap;
	bool reachedpoint = false;
	int attack_type = 0;
	bool isAttacking = false;
	bool onground = true;
	bool dead = false;
	Clock death_timer;
	bool remove_me = false;
	bool enemythrown = false;
	int brevious_state = -100;
	int health = 150;
	int origin_health = 150;
	int frame = 0;
	Clock animClock;
	bool attack_animation_started = false;
	bool idle = false;
	float keep_scale = 1.0f;
	bool damage = false;
	Clock bossStart;
	bool changed = false;
	Clock hitCooldown;
	Clock hitFlashClock;
	bool hitFlash = false;
};

vector<first_e> enemies;
vector<Fireball_enemy> fireballs;
void fire_enemy_generate(first_e& e) {
	Fireball_enemy fb;
	fb.shape.setRadius(10.0f);
	if(currentEditorLevel>=4)
	{
		fb.shape.setFillColor(Color::Yellow);
		fb.shape.setOutlineColor(Color::Color(139, 128, 0));
		fb.shape.setPosition(e.boxarm.getPosition().x, e.boxarm.getPosition().y - 15);
	}

	else
	{
		fb.shape.setFillColor(Color::Red);
		fb.shape.setPosition(e.boxarm.getPosition().x, e.boxarm.getPosition().y-e.box.getSize().y+30);
	}

	Vector2f playerPos = player[current_player].getPosition();
	Vector2f enemyPos = e.box.getPosition();
	int direction = (e.sprite.getScale().x > 0) ? 1 : -1;
	fb.velocity = Vector2f(direction * 20.0f, 0);
	fb.startX = e.boxarm.getPosition().x;

	fireballs.push_back(fb);
	e.enemy_attack_timer.restart();
}
void handle_collision(first_e& e) {
	FloatRect enemyBounds = e.box.getGlobalBounds();
	for (int x = 0; x < mapW; x++) {
		for (int y = 0; y < mapH; y++) {
			if (mapData[x][y].hasCollision) {
				FloatRect tileBounds(x * tileSize, y * tileSize, mapData[x][y].textureRect.width, mapData[x][y].textureRect.height);
				if (enemyBounds.intersects(tileBounds)) {
					if (e.speed.y > 0 && enemyBounds.top < tileBounds.top) {
						e.box.setPosition(e.box.getPosition().x, tileBounds.top - (enemyBounds.height - e.box.getOrigin().y));
						e.sprite.setPosition(e.box.getPosition());
						e.speed.y = 0;
						e.enemythrown = false;
						e.onground = true;
					}
				}
			}
		}
	}
}

void update_fireball(Fireball_enemy& fb) {
	fb.shape.move(fb.velocity);
}

void Enemy_Generate(float x, float y, int type) {
	first_e new_enemy;
	new_enemy.enemy_type = type;
	if (type == Enemy_type::First) {
		new_enemy.box.setSize(Vector2f(90.0f, 190.f));
		new_enemy.box.setOrigin(new_enemy.box.getLocalBounds().width / 2.0f, 0);
		new_enemy.box.setFillColor(Color::Red);
		new_enemy.boxarm.setSize(Vector2f(new_enemy.box.getLocalBounds().width * 3 - 40, new_enemy.box.getLocalBounds().height / 2.0f));
		new_enemy.boxarm.setOrigin(new_enemy.boxarm.getLocalBounds().width / 2.0f, new_enemy.boxarm.getLocalBounds().height / 2.0f-40);
	

		new_enemy.boxarm.setFillColor(Color::Green);
	}
	else if (type == Enemy_type::Second) {
		new_enemy.box.setSize(Vector2f(60.0f, 125.0f));
		new_enemy.box.setOrigin(new_enemy.box.getLocalBounds().width / 2.0f, new_enemy.box.getLocalBounds().height);
		new_enemy.box.setFillColor(Color::Blue);
		new_enemy.boxarm.setSize(Vector2f(0, 0));
		new_enemy.boxarm.setFillColor(Color::Green);
		new_enemy.boxarm.setOrigin(new_enemy.boxarm.getLocalBounds().width / 2.0f, new_enemy.boxarm.getLocalBounds().height / 2.0f);
	}
	else if (type == Enemy_type::Level1Boss) {
		new_enemy.box.setSize(Vector2f(75.0f, 150.0f));
		new_enemy.box.setOrigin(new_enemy.box.getLocalBounds().width / 2.0f, new_enemy.box.getLocalBounds().height / 2.0f);
		new_enemy.box.setFillColor(Color::Black);
		new_enemy.boxarm.setSize(Vector2f(new_enemy.box.getLocalBounds().width * 2.5, new_enemy.box.getLocalBounds().height));
		new_enemy.boxarm.setFillColor(Color::Green);
		new_enemy.health = 600;
		new_enemy.boxarm.setOrigin(new_enemy.boxarm.getLocalBounds().width / 2.0f, new_enemy.boxarm.getLocalBounds().height / 2.0f);
	}
	
	new_enemy.box.setPosition(x, y);
	if (new_enemy.enemy_type != Enemy_type::Level1Boss)
		new_enemy.orginpoint = Vector2f(x, y);
	else {
		new_enemy.orginpoint = Vector2f(x , y);
		new_enemy.box.setPosition(x+900, (y - new_enemy.box.getLocalBounds().height / 4.0f));
	}
	new_enemy.origin_health = new_enemy.health;
	enemies.push_back(new_enemy);
}
float diff[7]{ 125.0f / 4 + 10,  -50.0f / 2,0 ,0,0,125.0f / 4 + 10,0 };
void Enemy_animation(first_e& e) {
	int add = (currentEditorLevel <= 3 || e.enemy_type == Enemy_type::Level1Boss) ? 0 : 3;
	add += (currentEditorLevel >=5 ) ? 2 : 0;
	if (currentEditorLevel >=4  && !e.changed) {
		if (e.enemy_type == Enemy_type::Second) {
			e.box.setSize(Vector2f(75.0f, 150.0f));
			e.box.setOrigin(e.box.getLocalBounds().width / 2.0f, e.box.getLocalBounds().height / 2.0f);
			e.box.setFillColor(Color::Blue);
			e.boxarm.setSize(Vector2f(0, 0));
			e.boxarm.setFillColor(Color::Green);
		}

		else if (e.enemy_type == Enemy_type::First && currentEditorLevel == 4) {
			e.box.setSize(Vector2f(75.0f, 270.0f));
			e.box.setOrigin(e.box.getLocalBounds().width / 2.0f+20, 0);
			e.boxarm.setSize(Vector2f(e.box.getLocalBounds().width * 3+10, e.box.getLocalBounds().height ));
			e.boxarm.setOrigin(e.boxarm.getLocalBounds().width / 2.0f, 50);
		}
		else if (e.enemy_type == Enemy_type::First && (currentEditorLevel == 5|| currentEditorLevel==6)) {
			e.box.setOrigin(e.box.getOrigin().x, e.box.getOrigin().y + 30);
			e.boxarm.setSize(Vector2f(e.box.getLocalBounds().width * 2 - 40, e.box.getLocalBounds().height / 3.0f));
			e.boxarm.setOrigin(e.boxarm.getLocalBounds().width / 2.0f, e.boxarm.getLocalBounds().height / 2.0f);
		}
		e.changed = true;
	}
	float scaleX = (e.box.getPosition().x - player[current_player].getPosition().x > 0) ? -1.f : 1.f;
	if (e.health <= 0) {
		if (e.brevious_state != enemy_State::death) {
			e.frame = 0;
			e.brevious_state = enemy_State::death;
			e.animClock.restart();
			e.keep_scale = scaleX;
		}
		float gap;
		if (e.enemy_type != Enemy_type::Level1Boss)
			gap = 0.1f;
		else gap = 0.2f;
		if (e.animClock.getElapsedTime().asSeconds() > gap && e.frame < Enemy_die_animation_counter[e.enemy_type + add] - 1) {
			e.frame = (e.frame + 1) % Enemy_die_animation_counter[e.enemy_type + add];
			e.animClock.restart();
		}
		if (e.enemy_type == Enemy_type::Level1Boss && e.frame == Enemy_die_animation_counter[e.enemy_type + add] - 1) {
			if (e.dead && !dialogue2) {
				dialogue2 = true;
				triggerDialogue(1);
			}
		}
		e.sprite.setTexture(Enemy_animation_die[e.enemy_type + add], true);
		int frameWidth = Enemy_animation_die[e.enemy_type + add].getSize().x / Enemy_die_animation_counter[e.enemy_type + add];
		int frameHeight = Enemy_animation_die[e.enemy_type + add].getSize().y;
		e.sprite.setTextureRect(IntRect(e.frame * frameWidth, 0, frameWidth, frameHeight));
		scaleX = e.keep_scale;
	}
	else if ((e.enemy_type == Enemy_type::Level1Boss || e.enemy_type == Enemy_type::First) && e.enemy_state == enemy_State::Attack && e.attack_animation_started) {
		if (e.attack_type == 0) {
			if (e.brevious_state != enemy_State::attackanim) {
				e.frame = 0;
				e.brevious_state = enemy_State::attackanim;
				e.animClock.restart();
				e.keep_scale = scaleX;
			}
			e.sprite.setTexture(Enemy_animation_attack[e.enemy_type + add], true);
			if (e.animClock.getElapsedTime().asSeconds() > 0.1f) {
				e.frame = (e.frame + 1) % Enemy_attack_animation_counter[e.enemy_type + add];
				e.animClock.restart();
			}
			int frameWidth = Enemy_animation_attack[e.enemy_type + add].getSize().x / Enemy_attack_animation_counter[e.enemy_type + add];
			int frameHeight = Enemy_animation_attack[e.enemy_type + add].getSize().y;
			e.sprite.setTextureRect(IntRect(e.frame * frameWidth, 0, frameWidth, frameHeight));
			scaleX = e.keep_scale;
			if (e.frame == Enemy_attack_animation_counter[e.enemy_type + add] - 1) {
				e.attack_animation_started = false;

				e.attackgap.restart();
			}
			if (e.frame > int(Enemy_attack_animation_counter[e.enemy_type + add] / 3.0f) && e.frame < int((Enemy_attack_animation_counter[e.enemy_type + add] * 2.0f) / 3)) {
				e.damage = true;
			}
			else {
				e.damage = false;
			}
		}

		else
		{
			if (e.brevious_state != enemy_State::attack2anim) {
				e.frame = 0;
				e.brevious_state = enemy_State::attack2anim;
				e.animClock.restart();
			}
			if (e.animClock.getElapsedTime().asSeconds() > 0.1f) {
				e.frame = (e.frame + 1) % Enemy_attack2_animation_counter[e.enemy_type + add];
				e.animClock.restart();
			}
			if (e.frame == int(Enemy_attack2_animation_counter[e.enemy_type + add] > 3)) {
				e.damage = true;
			}
			else {
				e.damage = false;
			}
			e.sprite.setTexture(Enemy_animation_attack2[e.enemy_type + add], true);
			int frameWidth = Enemy_animation_attack2[e.enemy_type + add].getSize().x / Enemy_attack2_animation_counter[e.enemy_type + add];
			int frameHeight = Enemy_animation_attack2[e.enemy_type + add].getSize().y;
			e.sprite.setTextureRect(IntRect(e.frame * frameWidth, 0, frameWidth, frameHeight));
		}
	}
	else if (e.enemy_type == Enemy_type::Second && e.attack_animation_started) {
		if (e.brevious_state != enemy_State::attackanim) {
			e.frame = 0;
			e.brevious_state = enemy_State::attackanim;
			e.animClock.restart();
			e.keep_scale = scaleX;
		}
		e.sprite.setTexture(Enemy_animation_attack[e.enemy_type + add], true);
		if (e.animClock.getElapsedTime().asSeconds() > 0.1f) {
			e.frame = (e.frame + 1) % Enemy_attack_animation_counter[e.enemy_type + add];
			e.animClock.restart();
		}

		int frameWidth = Enemy_animation_attack[e.enemy_type + add].getSize().x / Enemy_attack_animation_counter[e.enemy_type + add];
		int frameHeight = Enemy_animation_attack[e.enemy_type + add].getSize().y;
		e.sprite.setTextureRect(IntRect(e.frame * frameWidth, 0, frameWidth, frameHeight));
		scaleX = e.keep_scale;
		if (e.frame == Enemy_attack_animation_counter[e.enemy_type + add] - 1) {
			e.attack_animation_started = false;
			e.attackgap.restart();
		}
	}
	else if (e.enemy_state == enemy_State::Idle || e.idle) {
		if (e.brevious_state != enemy_State::Idle) {
			e.frame = 0;
			e.brevious_state = enemy_State::Idle;
			e.sprite.setTexture(Enemy_animation_idle[e.enemy_type + add], true);
			e.animClock.restart();
		}
		if (e.animClock.getElapsedTime().asSeconds() > 0.1f) {
			e.frame = (e.frame + 1) % Enemy_idle_animation_counter[e.enemy_type + add];
			e.animClock.restart();
		}
		int frameWidth = Enemy_animation_idle[e.enemy_type + add].getSize().x / Enemy_idle_animation_counter[e.enemy_type + add];
		int frameHeight = Enemy_animation_idle[e.enemy_type + add].getSize().y;

		e.sprite.setTextureRect(IntRect(e.frame * frameWidth, 0, frameWidth, frameHeight));
	}
	else if (e.enemythrown) {
		if (e.brevious_state != enemy_State::hurt) {
			e.frame = 0;
			e.brevious_state = enemy_State::hurt;
			e.sprite.setTexture(Enemy_animation_hurt[e.enemy_type + add], true);
			e.animClock.restart();
		}

		if (e.animClock.getElapsedTime().asSeconds() > 0.1f) {
			e.frame = (e.frame + 1) % Enemy_hurt_animation_counter[e.enemy_type + add];
			e.animClock.restart();
		}
		int frameWidth = Enemy_animation_hurt[e.enemy_type + add].getSize().x / Enemy_hurt_animation_counter[e.enemy_type + add];
		int frameHeight = Enemy_animation_hurt[e.enemy_type + add].getSize().y;
		e.sprite.setTextureRect(IntRect(e.frame * frameWidth, 0, frameWidth, frameHeight));
	}
	else {
		if (e.brevious_state != Walk) {
			e.frame = 0;
			e.brevious_state = Walk;
			e.sprite.setTexture(Enemy_animation_walk[e.enemy_type + add], true);
			e.animClock.restart();
		}

		if (e.animClock.getElapsedTime().asSeconds() > 0.1f) {
			e.frame = (e.frame + 1) % Enemy_walk_animation_counter[e.enemy_type + add];
			e.animClock.restart();
		}
		int frameWidth = Enemy_animation_walk[e.enemy_type + add].getSize().x / Enemy_walk_animation_counter[e.enemy_type + add];
		int frameHeight = Enemy_animation_walk[e.enemy_type + add].getSize().y;
		e.sprite.setTextureRect(IntRect(e.frame * frameWidth, 0, frameWidth, frameHeight));
		scaleX = (e.speed.x < 0) ? -1.f : 1.f;
	}
	e.sprite.setOrigin(e.sprite.getLocalBounds().width / 2.f,
		e.sprite.getLocalBounds().height / 2.f);
	if (e.brevious_state == enemy_State::attack2anim && e.speed.x < 0) scaleX = -1.f;
	if (e.brevious_state == enemy_State::attack2anim && e.speed.x > 0) scaleX = 1.f;
	float scaleY = 1.3f;
	if (e.enemy_type == Enemy_type::First) {
		scaleX *= 2.3f; scaleY *= 2.3f; 
		if (currentEditorLevel == 4) { scaleY *= 1.0f; scaleX *= 1.0f; }
	}
	e.sprite.setScale(scaleX * 2, scaleY * 2);
	if (e.enemy_type == Level1Boss) {
		e.sprite.setScale(e.sprite.getScale().x*1.5,e.sprite.getScale().y*1.5);

	}
	e.sprite.setPosition(e.box.getPosition());
	if ((currentEditorLevel == 1 || currentEditorLevel == 2)&& e.enemy_type == Enemy_type::Second)
		e.sprite.setPosition(e.box.getPosition().x, e.box.getPosition().y - e.box.getLocalBounds().height / 2.0f - 20.0f);

	if (currentEditorLevel == 4)
	{
		if (e.enemy_type == Enemy_type::Second)
		{
		e.sprite.setPosition(e.box.getPosition().x, e.sprite.getPosition().y - 22);
		e.sprite.setScale(scaleX * 3, scaleY * 3.2);
		}
		else if (e.enemy_type == Enemy_type::First) e.sprite.setPosition(e.box.getPosition().x, e.sprite.getPosition().y - 10);
	}
	if (currentEditorLevel == 5|| currentEditorLevel == 6)
	{
		if (e.enemy_type == Enemy_type::Second) {
			e.sprite.setPosition(e.box.getPosition().x, e.sprite.getPosition().y - 22);
			e.sprite.setScale(scaleX * 3, scaleY * 3.2);
		}
	}

	if (e.hitFlash) {
		if (e.hitFlashClock.getElapsedTime().asSeconds() < 0.12f) {
			e.sprite.setColor(Color::Red);
		}
		else {
			e.sprite.setColor(Color(255, 255, 255, 255));
			e.hitFlash = false;
		}
	}
	else {
		e.sprite.setColor(Color(255, 255, 255, 255));
	}
}
void update_enemy_movement(first_e& e) {
	if (e.health <= 0 && !e.dead) { e.dead = true; e.death_timer.restart(); }
	if (e.dead) {
		if (e.death_timer.getElapsedTime().asSeconds() > 5.0f) {
			e.remove_me = true;

			return;
		}
		else {
			e.box.setFillColor(Color(128, 128, 128));
			e.speed.y += e_gravity;
			e.box.move(0, e.speed.y);
			handle_collision(e);
			Enemy_animation(e);
			return;
		}
	}
	if (e.enemy_type == Enemy_type::Level1Boss && e.bossStart.getElapsedTime().asSeconds() < 5.0f) {
		e.enemy_state = Idle;
		Enemy_animation(e);
		handle_collision(e);
		return;
	}
	float distanceToPlayer = abs(player[current_player].getPosition().x - e.box.getPosition().x);
	float offset = e.box.getPosition().x - e.orginpoint.x;
	bool isOnGround = (e.box.getGlobalBounds().intersects(ground.getGlobalBounds()));

	if ((!e.isAttacking) || (abs(e.box.getPosition().x - e.orginpoint.x) > limitx[e.enemy_type] && !e.attack_animation_started && !(e.attack_type == 1))) {
		if (distanceToPlayer <= AttackRange[e.enemy_type] && abs(player[current_player].getPosition().x - e.orginpoint.x) <= limitx[e.enemy_type])
			e.enemy_state = Attack;
		else if (distanceToPlayer <= FollowRange[e.enemy_type] && abs(player[current_player].getPosition().x - e.orginpoint.x) <= limitx[e.enemy_type])
			e.enemy_state = Follow;
		else
			e.enemy_state = Walk;
		e.isAttacking = false;
	}

	if (BenAttacking && e.box.getGlobalBounds().intersects(characterboxarm[current_player].getGlobalBounds()) && e.onground) {
		if (!e.enemythrown && e.hitCooldown.getElapsedTime().asSeconds() >= 0.9f) {
			int Attacktype = (kPressedNow) ? 0 : 1;
			if (kPressedNow && !kWasPressed)
			{
				int combBonus = (combo_frame_count - 1) * 10;
				e.health -= (Ben_Power[current_player][Attacktype] + combBonus);
				e.hitFlash = true;
				e.hitFlashClock.restart();
			}
			else {
				e.health -= (Ben_Power[current_player][Attacktype]);
				e.hitFlash = true;
				e.hitFlashClock.restart();
			}

			e.hitCooldown.restart();

			if (combo_frame_count == 3)
				e.enemythrown = true;
		}
	}

	float timer = e.enemy_attack_timer.getElapsedTime().asSeconds();
	float dir = (player[current_player].getPosition().x > e.box.getPosition().x) ? 1.0f : -1.0f;

	if (e.enemy_state == Attack) {
		if (e.enemy_type == Enemy_type::First) {
			if (e.attackgap.getElapsedTime().asSeconds() >= 2.0f) {
				if (!e.isAttacking) {
					e.isAttacking = true;
					e.reachedpoint = false;
				}
				if (e.isAttacking) {
					if (!e.reachedpoint) {
						if (distanceToPlayer > 100.0f) {
							e.speed.x = dir * current_walk_speed[e.enemy_type].x;
						}
						else {
							float dir = (player[current_player].getPosition().x > e.box.getPosition().x) ? 1.0f : -1.0f;
							e.speed.x += (dir * 5.0f - e.speed.x) * 0.1f;

							if (timer > 0.50f) {
								e.reachedpoint = true;
								e.enemy_attack_timer.restart();
								e.attack_animation_started = true;
								e.speed.x = 0;
							}
						}
					}
					else {
						e.speed.x = 0;
						if (!e.attack_animation_started) {
							e.isAttacking = false;
							e.enemy_state = Walk;
						}
					}
				}
			}
		}
		else if (e.enemy_type == Enemy_type::Second) {
			if (e.enemy_attack_timer.getElapsedTime().asSeconds() >= 1.5f && !e.attack_animation_started) {
				e.isAttacking = true;
				e.attack_animation_started = true;
			}
			e.speed.x = 0;
		}

		else if (e.enemy_type == Enemy_type::Level1Boss) {
			if (!e.isAttacking) {
				e.isAttacking = true;
				e.reachedpoint = false;
				e.enemy_attack_timer.restart();
				e.attack_type = (e.health < e.origin_health / 2.0f) ? (rand() % 2) : 0;
			}

			if (e.attack_type == 0) {
				if (!e.reachedpoint) {
					if (distanceToPlayer > 100.0f && !e.idle) { e.speed.x = dir * current_walk_speed[e.enemy_type].x; e.idle = false; }//charge towards player
					else {
						e.speed.x = 0;
						e.idle = true;
						if (timer > 1.0f) {
							e.reachedpoint = true;
							e.enemy_attack_timer.restart();
							e.attack_animation_started = true;
							e.idle = false;
						}
					}
				}
				else {
					if (abs(e.box.getPosition().x - e.orginpoint.x) > limitx[e.enemy_type]) { e.enemy_state = Walk; }
					e.speed.x = dir * -1.5f;
					if (timer > 3.0f) {
						e.isAttacking = false;
						e.reachedpoint = false;
						e.enemy_attack_timer.restart();
					}
				}
			}
			else {
				if (!e.reachedpoint) {
					e.speed.x = current_walk_speed[e.enemy_type].x;
					if (offset >= limitx[e.enemy_type]) e.reachedpoint = true;
					e.attack_animation_started = true;
				}
				else {
					e.speed.x = -current_walk_speed[e.enemy_type].x * 1.5f;
					if (offset <= -limitx[e.enemy_type]) { e.isAttacking = false; e.enemy_attack_timer.restart(); e.attack_animation_started = false; }
				}
			}
		}
	}

	else if (e.enemy_state == Walk) {
		if (offset >= limitx[e.enemy_type]) e.wantedspeed[e.enemy_type] = -current_walk_speed[e.enemy_type].x;
		else if (offset <= -limitx[e.enemy_type]) e.wantedspeed[e.enemy_type] = current_walk_speed[e.enemy_type].x;
		e.speed.x += (e.wantedspeed[e.enemy_type] - e.speed.x) * 0.1f;
	}
	else if (e.enemy_state == Follow) {
		float dir = (player[current_player].getPosition().x > e.box.getPosition().x) ? 1.0f : -1.0f;
		e.speed.x += (dir * 5.0f - e.speed.x) * 0.1f;
	}
	if (e.enemythrown && e.health >= 0) {
		if (e.onground) {
			e.speed.y = -10; e.onground = false;
		}
		float dir = (player[current_player].getPosition().x > e.box.getPosition().x) ? -1.0f : 1.0f;
		e.speed.x = 5 * dir;
	}
	e.speed.y += e_gravity;
	e.box.move(e.speed);

	handle_collision(e);
	if (e.box.getPosition().y > 1800)
		e.health = 0;
	if (e.speed.x != 0) e.idle = false;
	if (e.speed.x == 0 && !e.attack_animation_started) { e.idle = true; }
	Enemy_animation(e);
	int dirr = (e.sprite.getScale().x > 0) ? 1 : -1;
	e.boxarm.setPosition(e.box.getPosition().x + dirr * (e.box.getLocalBounds().width / 2 + e.boxarm.getLocalBounds().width / 2), e.box.getPosition().y + diff[e.enemy_type]);
	FloatRect playerBounds = characterbox[current_player].getGlobalBounds();
	FloatRect enemyBounds = e.box.getGlobalBounds();
	if ((currentEditorLevel == 5|| currentEditorLevel == 6) &&e.enemy_type!=Enemy_type::Second) {
		e.boxarm.setSize(Vector2f(e.box.getLocalBounds().width * 2-20, e.box.getLocalBounds().height / 4.0f));
	}


	if (recoveryClock.getElapsedTime().asSeconds() >= 3.0f && (playerBounds.intersects(enemyBounds)
		|| (playerBounds.intersects(e.boxarm.getGlobalBounds()) && e.damage))&& !cheatCodeHealthActive) {
		if (e.enemy_type < 2) { hp -= 10; }
		else hp -= 10;
		recoveryClock.restart();
		cout << hp << ' ';
		if (velocity.y > 0 && playerBounds.top < enemyBounds.top) {
			float pushDir = (playerBounds.left < enemyBounds.left) ? -5.0f : 5.0f;
			characterbox[current_player].move(pushDir, 0);
		}
	}
	if (((currentEditorLevel >= 4 && e.frame == 2)|| (currentEditorLevel == 1 || currentEditorLevel==2 && e.frame == 8)) && e.enemy_type == Enemy_type::Second && e.isAttacking) {
		fire_enemy_generate(e);
		e.isAttacking = false;
	}
	if (e.enemy_type == Enemy_type::Level1Boss)
		e.orginpoint = view.getCenter();
}
