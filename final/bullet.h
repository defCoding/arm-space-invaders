#ifndef BULLET_H
#define BULLET_H

#define BULLET_WIDTH 4
#define BULLET_HEIGHT 8
#define BULLET_SPEED 3
#define BULLET_DAMAGE 10

typedef struct bullet {
  int x_pos;
  int y_pos;
  int direction;
} bullet_t;

bullet_t* init_bullet(int, int, int);
void clear_bullet(bullet_t*);
void draw_bullet(bullet_t*);
void move_bullet(bullet_t*);
int check_collision(int, int, int, int, int, int, int, int);

#endif
