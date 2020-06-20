#ifndef ENEMY_H
#define ENEMY_H

#include <bullet.h>

#define ENEMY_WIDTH 10
#define ENEMY_HEIGHT 8
#define ENEMY_HP 20
#define ENEMY_ATTACK_SPEED 50
#define ENEMY_MOVESPEED 2
#define ENEMY_MOVE_INTERVAL 8
#define ENEMY_SPAWN_INTERVAL 60
#define LOWER_BOUNDARY 80
#define UPPER_BOUNDARY 15

typedef struct enemy {
  int x_pos;
  int y_pos;
  int health;
  int move_axis;
  int move_direction;
} enemy_t;

enemy_t* init_enemy(int, int, int, int);
void clear_enemy(enemy_t*);
void draw_enemy(enemy_t*);
void move_enemy(enemy_t*);
void enemy_change_direction(enemy_t*);
bullet_t* fire_enemy_bullet(enemy_t*);

#endif
