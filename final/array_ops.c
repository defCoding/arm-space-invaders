#include <stdlib.h>
#include <array_ops.h>
#include <f3d_lcd_sd.h>

int move_all_bullets(bullet_t **bullet_list, int size) {
  int i;
  // Move all bullets.
  for (i = 0; i < size; i++) {
    bullet_t* bullet = bullet_list[i]; move_bullet(bullet);

    // Check if bullet went out of bounds and if so, remove.
    if (bullet->y_pos < 0 || bullet->y_pos > ST7735_height) {
      clear_bullet(bullet);
      remove_bullet(bullet_list, i, size);
      i--;
      size--;
    }
  }

  return size;
}


void remove_bullet(bullet_t **bullet_list, int index, int size) {
  free(bullet_list[index]);
  // Shift other elements backwards.
  for (++index; index < size; index++) {
    bullet_list[index - 1] = bullet_list[index];
  }
}

void move_all_enemies(enemy_t **enemy_list, int size) {
  int i;
  // Move all enemies.
  for (i = 0; i < size; i++) {
    enemy_t* enemy = enemy_list[i];
    move_enemy(enemy);
  }
}

void change_all_enemies_direction(enemy_t **enemy_list, int size) {
  int i;
  // Attempt to change direction of each enemy.
  for (i = 0; i < size; i++) {
    enemy_change_direction(enemy_list[i]);
  }
}

void remove_enemy(enemy_t **enemy_list, int index, int size) {
  free(enemy_list[index]);
  // Shift other elements backwards.
  for (++index; index < size; index++) {
    enemy_list[index - 1] = enemy_list[index];
  }
}

int all_enemies_shoot(enemy_t **enemy_list, int num_enemies, bullet_t **bullet_list, int num_bullets) {
  int i;

  for (i = 0; i < num_enemies; i++) {
    bullet_t *bullet = fire_enemy_bullet(enemy_list[i]);

    if (bullet) {
      bullet_list[num_bullets++] = bullet;
    }
  }

  return num_bullets;
}

int* check_player_bullet_collision(bullet_t **bullet_list, int num_bullets, enemy_t **enemy_list, int num_enemies) {
  int i, j;
  
  for (i = 0; i < num_bullets; i++) {
    bullet_t *bullet = bullet_list[i];
    
    for (j = 0; j < num_enemies; j++) {
      enemy_t *enemy = enemy_list[j];

      if (check_collision(bullet->x_pos, bullet->y_pos, BULLET_WIDTH, BULLET_HEIGHT, enemy->x_pos, enemy->y_pos, ENEMY_WIDTH, ENEMY_HEIGHT)) {
          enemy->health -= BULLET_DAMAGE;

          clear_bullet(bullet);
          remove_bullet(bullet_list, i--, num_bullets--);

          if (enemy->health <= 0) {
            clear_enemy(enemy);
            remove_enemy(enemy_list, j, num_enemies--);
          }
          break;
      }
    }
  }

  int *ret = (int *) calloc(2, sizeof(int));

  ret[0] = num_bullets;
  ret[1] = num_enemies;

  return ret;
}

int check_enemy_bullet_collision(bullet_t **bullet_list, int num_bullets, player_t *player) {
  int i;

  for (i = 0; i < num_bullets; i++) {
    bullet_t *bullet = bullet_list[i];

    if (check_collision(bullet->x_pos, bullet->y_pos, BULLET_WIDTH, BULLET_HEIGHT, player->x_pos, ST7735_height - PLAYER_HEIGHT - 10, PLAYER_WIDTH, PLAYER_HEIGHT)) {
      player->health -= BULLET_DAMAGE;

      clear_bullet(bullet);
      remove_bullet(bullet_list, i--, num_bullets--);

      if (player->health <= 0) {
        return num_bullets;
      }
    }
  }

  return num_bullets;
}

int check_player_bullet_powerup(bullet_t **bullet_list, int num_bullets, powerup_t *powerup) {
  int i;
  
  for (i = 0; i < num_bullets; i++) {
    bullet_t *bullet = bullet_list[i];

    if (check_collision(bullet->x_pos, bullet->y_pos, BULLET_WIDTH, BULLET_HEIGHT, powerup->x_pos, powerup->y_pos, POWERUP_WIDTH, POWERUP_HEIGHT)) {
      clear_bullet(bullet);
      remove_bullet(bullet_list, i--, num_bullets--);
      clear_powerup(powerup);      
      return 1;
    }
  }

  return 0;
}




