#include <powerup.h>
#include <f3d_lcd_sd.h>
#include <stdlib.h>

powerup_t* init_powerup(int x, int y) {
  powerup_t *powerup = (powerup_t*) malloc(sizeof(powerup_t));
  
  powerup->x_pos = x;
  powerup->y_pos = y;
  
  return powerup;
}

void clear_powerup(powerup_t *powerup) {
  int x_pos = powerup->x_pos;
  int y_pos = powerup->y_pos;

  f3d_lcd_drawBar(x_pos - POWERUP_WIDTH / 2, y_pos - POWERUP_HEIGHT / 2, POWERUP_WIDTH, POWERUP_HEIGHT, BLACK);
}

void draw_powerup(powerup_t *powerup) {
  int x_pos = powerup->x_pos;
  int y_pos = powerup->y_pos;

  f3d_lcd_drawBar(x_pos - POWERUP_WIDTH / 2, y_pos - POWERUP_HEIGHT / 2, POWERUP_WIDTH, POWERUP_HEIGHT, GREEN);
}
