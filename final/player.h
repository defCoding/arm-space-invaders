#ifndef PLAYER_H
#define PLAYER_H

#include <bullet.h>

#define PLAYER_WIDTH 8
#define PLAYER_HEIGHT 15
#define PLAYER_HP 100

typedef struct player {
  int x_pos;
  int health;
  int powerup;
  int time_last_fire;
} player_t;

int max(int, int);
int min(int, int);
player_t* init_player();
void clear_player(player_t*);
void draw_player(player_t*);
void move_player(player_t*, int);
bullet_t* fire_player_bullet(player_t* player);

#endif
