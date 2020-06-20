#include <player.h>
#include <bullet.h>
#include <stdlib.h>
#include <f3d_lcd_sd.h>

int PLAYER_ATTACK_SPEED = 20;

int max(int x, int y) {
  return x > y ? x : y;
}

int min(int x, int y) {
  return x < y ? x : y;
}

player_t* init_player() {
  player_t *player = (player_t*) malloc(sizeof(player_t));
  player->x_pos = ST7735_width / 2;
  player->health = PLAYER_HP;
  player->powerup = 0;
  player->time_last_fire = PLAYER_ATTACK_SPEED;

  return player;
}
void clear_player(player_t *player) {
  int x_pos = player->x_pos;

  f3d_lcd_drawBar(x_pos - PLAYER_WIDTH / 2, ST7735_height - PLAYER_HEIGHT - 10, PLAYER_WIDTH, PLAYER_HEIGHT, BLACK);
}

void draw_player(player_t *player) {
  int x_pos = player->x_pos;

  uint16_t color = player->powerup ? GREEN : WHITE;

  f3d_lcd_drawBar(x_pos - PLAYER_WIDTH / 2, ST7735_height - PLAYER_HEIGHT - 10, PLAYER_WIDTH, PLAYER_HEIGHT, color);
}

void move_player(player_t *player, int distance) {
  clear_player(player);

  int new_x = player->x_pos;

  // Update position and constrain it to the bounds of the screen.
  new_x += distance;
  new_x = (PLAYER_WIDTH / 2) > new_x ? PLAYER_WIDTH / 2 : new_x;
  new_x = ST7735_width < new_x ? ST7735_width : new_x;

  player->x_pos = new_x;

  draw_player(player);
}

bullet_t* fire_player_bullet(player_t *player) {
  if (player->time_last_fire >= PLAYER_ATTACK_SPEED) {
    player->time_last_fire = 0;
    return init_bullet(player->x_pos, ST7735_height - PLAYER_HEIGHT - 10, -1);
  } 

  return NULL;
}
