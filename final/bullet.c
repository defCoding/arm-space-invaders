#include <bullet.h>
#include <stdlib.h>
#include <f3d_lcd_sd.h>

bullet_t* init_bullet(int x, int y, int direction) {
  bullet_t *bullet = (bullet_t*) malloc(sizeof(bullet_t));
  bullet->x_pos = x;

  // Need to adjust y to be in the center of the bullet.
  bullet->y_pos = y + direction * BULLET_HEIGHT / 2;

  bullet->direction = direction;
  
  return bullet;
}

void clear_bullet(bullet_t *bullet) {
  int x_pos = bullet->x_pos;
  int y_pos = bullet->y_pos;

  f3d_lcd_drawBar(x_pos - BULLET_WIDTH / 2, y_pos - BULLET_HEIGHT / 2, BULLET_WIDTH, BULLET_HEIGHT, BLACK);
}

void draw_bullet(bullet_t *bullet) {
  int x_pos = bullet->x_pos;
  int y_pos = bullet->y_pos;

  f3d_lcd_drawBar(x_pos - BULLET_WIDTH / 2, y_pos - BULLET_HEIGHT / 2, BULLET_WIDTH, BULLET_HEIGHT, WHITE);
}

void move_bullet(bullet_t *bullet) {
  clear_bullet(bullet);

  int new_y = bullet->y_pos;

  // Update position.
  new_y += bullet->direction * BULLET_SPEED;
  
  bullet->y_pos = new_y;

  draw_bullet(bullet);
}

int check_collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
  int pointl1[2] = {x1 - w1 / 2, y1 - h1 / 2};
  int pointr1[2] = {x1 + w1 / 2, y1 + h1 / 2};

  int pointl2[2] = {x2 - w2 / 2, y2 - h2 / 2};
  int pointr2[2] = {x2 + w2 / 2, y2 + h2 / 2};

  if (pointl1[0] >= pointr2[0] || pointl2[0] >= pointr1[0]) {
    return 0;
  }

  if (pointl1[1] >= pointr2[1] || pointl2[1] >= pointr1[1]) {
    return 0;
  }

  return 1;
}
