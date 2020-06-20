#include <enemy.h>
#include <bullet.h>
#include <stdlib.h>
#include <f3d_lcd_sd.h>

enemy_t* init_enemy(int x, int y, int move_axis, int move_direction) {
  enemy_t *enemy = (enemy_t*) malloc(sizeof(enemy_t));
  enemy->x_pos = x;
  enemy->y_pos = y;
  enemy->health = ENEMY_HP;
  enemy->move_axis = move_axis;
  enemy->move_direction = move_direction;

  return enemy;
}

void clear_enemy(enemy_t *enemy) {
  int x_pos = enemy->x_pos;
  int y_pos = enemy->y_pos;

  f3d_lcd_drawBar(x_pos - ENEMY_WIDTH / 2, y_pos - ENEMY_HEIGHT / 2, ENEMY_WIDTH, ENEMY_HEIGHT, BLACK);
}

void draw_enemy(enemy_t *enemy) {
  int x_pos = enemy->x_pos;
  int y_pos = enemy->y_pos;

  f3d_lcd_drawBar(x_pos - ENEMY_WIDTH / 2, y_pos - ENEMY_HEIGHT / 2, ENEMY_WIDTH, ENEMY_HEIGHT, RED);
}

void move_enemy(enemy_t *enemy) {
  clear_enemy(enemy);
  if (enemy->move_axis == 0) { // x-axis
    int new_x = enemy->x_pos;
    new_x += enemy->move_direction * ENEMY_MOVESPEED;
    new_x = (ENEMY_WIDTH / 2) > new_x ? ENEMY_WIDTH / 2 : new_x;
    new_x = ST7735_width < new_x ? ST7735_width : new_x;

    enemy->x_pos = new_x;
  } else { // y-axis
    int new_y = enemy->y_pos;
    new_y += enemy->move_direction * ENEMY_MOVESPEED;
    new_y = ((ENEMY_HEIGHT / 2) + UPPER_BOUNDARY) > new_y ? ENEMY_HEIGHT / 2  + UPPER_BOUNDARY: new_y;
    new_y = ST7735_height - LOWER_BOUNDARY < new_y ? ST7735_height - LOWER_BOUNDARY : new_y;

    enemy->y_pos = new_y;
  }

  draw_enemy(enemy);
}

void enemy_change_direction(enemy_t *enemy) {
  if (rand() % 3 == 2) {
    enemy->move_axis = !(enemy->move_axis);
  }

  if (rand() % 4 == 3) {
    enemy->move_direction = enemy->move_direction == 1 ? -1 : 1;
  }
}

bullet_t* fire_enemy_bullet(enemy_t *enemy) {
  if (rand() % 2) { // Only fire an enemy 50% of the time.
    return init_bullet(enemy->x_pos, enemy->y_pos, 1);
  }

  return NULL;
}
