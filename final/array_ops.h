#ifndef ARRAY_H
#define ARRAY_H

#include <bullet.h>
#include <player.h>
#include <enemy.h>
#include <powerup.h>

// Moves all bullets and returns the number of bullets removed.
int move_all_bullets(bullet_t**, int);

// Moves all enemies according to their movement.
void move_all_enemies(enemy_t**, int);

// Removes bullet from list.
void remove_bullet(bullet_t**, int, int);

// Removes enemy from list.
void remove_enemy(enemy_t**, int, int);

// Attempt to change direction of each enemy.
void change_all_enemies_direction(enemy_t**, int);

// Has all enemies attempt to shoot, and returns the total number of bullets.
int all_enemies_shoot(enemy_t**, int, bullet_t**, int);

// Check if player bullet hits powerup, and returns 1 if there is a collision, 0 otherwise.
int check_player_bullet_powerup(bullet_t**, int, powerup_t*);

// Check if player bullets hit any enemies, returns the remaining number of bullets and enemies in an array.
int* check_player_bullet_collision(bullet_t**, int, enemy_t**, int); 

// Check if enemy bullets hit player. Returns remaining number of bullets.
int check_enemy_bullet_collision(bullet_t**, int, player_t*);
#endif
