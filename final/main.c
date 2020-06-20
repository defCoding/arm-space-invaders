// Board files
#include <stdio.h>
#include <f3d_lcd_sd.h>
//#include <stm32f30x.h>
#include <f3d_i2c.h>
#include <f3d_mag.h>
#include <f3d_accel.h>
#include <f3d_user_btn.h>
#include <f3d_delay.h>
#include <f3d_systick.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <f3d_uart.h>

// Game files
#include <player.h>
#include <bullet.h>
#include <array_ops.h>
#include <enemy.h>
#include <powerup.h>

#define X 0
#define Y 1
#define Z 2

#define MAX_ENEMIES 8
#define MAX_PLAYER_BULLETS 10
#define MAX_ENEMY_BULLETS MAX_ENEMIES * 5

void process_accel(float *mag_data);
void on_game_tick();

static int processed_interval = 1;
static uint16_t elapsed_intervals = 0;

extern int PLAYER_ATTACK_SPEED;
static player_t* player;
static powerup_t* powerup;
static int num_player_bullets = 0;
static int num_enemies = 0;
static int num_enemy_bullets = 0;
static bullet_t* player_bullet_list[MAX_PLAYER_BULLETS];
static enemy_t* enemy_list[MAX_ENEMIES];
static bullet_t* enemy_bullet_list[MAX_ENEMY_BULLETS];

static int has_powerup = 0;
static int game_state = 1; // 0 if lost.

// Timer for powerup.
static int time_received_powerup = 0;

int main(void) {
  f3d_i2c1_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_lcd_init();
  f3d_uart_init();
  f3d_user_btn_init();
  f3d_systick_init();

  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_lcd_fillScreen2(BLACK);
  float accel_data[3] = {0};

  player = init_player(); // Create player.

  int i;

  char lookup[101][8];
  for (i = 0; i <= 100; i++) {
    sprintf(lookup[i], "HP: %3d", i);
  }

  while (game_state) {

    f3d_accel_read(accel_data);
    process_accel(accel_data);

    int move_distance = (int) (accel_data[1] * -2);

    if (!processed_interval) {
      processed_interval = 1;
      player->time_last_fire++;

      if (elapsed_intervals % ENEMY_ATTACK_SPEED == 0) {
        num_enemy_bullets = all_enemies_shoot(enemy_list, num_enemies, enemy_bullet_list, num_enemy_bullets);
      }
      
      if (elapsed_intervals % ENEMY_MOVE_INTERVAL == 0) {
        change_all_enemies_direction(enemy_list, num_enemies);
      }

      if (elapsed_intervals % ENEMY_SPAWN_INTERVAL == 0 && num_enemies < MAX_ENEMIES) {
        int x = rand() % ST7735_width;
        int y = rand() % (ST7735_height - LOWER_BOUNDARY);
        int axis = rand() % 2;
        int direction = rand() % 2 ? 1 : -1;

        enemy_list[num_enemies++] = init_enemy(x, y, axis, direction);
      }

      if (!has_powerup && !player->powerup) {
        if (rand() % 100 == 0) {
          int x = rand() % (ST7735_width - 2 * POWERUP_WIDTH) + POWERUP_WIDTH;
          int y = rand() % (ST7735_height - LOWER_BOUNDARY - POWERUP_HEIGHT) + POWERUP_HEIGHT;
          has_powerup = 1;
          powerup = init_powerup(x, y);
        }
      }

    }

    if (user_btn_read()) {
      bullet_t* bullet = fire_player_bullet(player);

      if (bullet) {
        player_bullet_list[num_player_bullets++] = bullet;
      }
    }


    move_player(player, move_distance);
    num_player_bullets = move_all_bullets(player_bullet_list, num_player_bullets);
    num_enemy_bullets = move_all_bullets(enemy_bullet_list, num_enemy_bullets);
    move_all_enemies(enemy_list, num_enemies);

    // Check to see if player hit powerup.
    if (player->powerup && (elapsed_intervals - time_received_powerup) % POWERUP_LENGTH == 0) {
      PLAYER_ATTACK_SPEED *= 2;
      player->powerup = 0;
    }

    if (has_powerup) {
      draw_powerup(powerup);

      if (check_player_bullet_powerup(player_bullet_list, num_player_bullets, powerup)) {
        player->powerup = 1;
        has_powerup = 0;
        num_player_bullets--;
        time_received_powerup = elapsed_intervals;
        PLAYER_ATTACK_SPEED /= 2;
      }
    }

    int *counts = check_player_bullet_collision(player_bullet_list, num_player_bullets, enemy_list, num_enemies);

    num_player_bullets = counts[0];
    num_enemies = counts[1]; free(counts);

    num_enemy_bullets = check_enemy_bullet_collision(enemy_bullet_list, num_enemy_bullets, player);

    f3d_lcd_drawString(0, 0, lookup[player->health], WHITE, BLACK);
    if (player->health <= 0) {
      f3d_lcd_drawString(ST7735_width / 2 - 25, ST7735_height / 2, "GAME OVER", RED, BLACK);
      game_state = 0;
    }
  }
}

void process_accel(float *accel_data) {
  int i;
  for (i = 0; i < 3; i++) {
    accel_data[i] = 9.81 * sin(accel_data[i]);
  }
}

void on_game_tick() {
  processed_interval = 0;
  elapsed_intervals++;
}

void assert_failed(uint8_t* file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
    while (1);
}
