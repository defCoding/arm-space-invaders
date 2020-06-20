#ifndef POWERUP_H
#define POWERUP_H

#define POWERUP_WIDTH 10
#define POWERUP_HEIGHT 10
#define POWERUP_LENGTH 300

typedef struct {
  int x_pos;
  int y_pos;
} powerup_t;

powerup_t* init_powerup(int, int);
void clear_powerup(powerup_t*);
void draw_powerup(powerup_t*);

#endif
