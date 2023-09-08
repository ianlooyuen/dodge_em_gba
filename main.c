#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/gameoverscreen.h"
#include "images/titlescreen.h"
#include "images/pausescreen.h"

int main(void) {
  REG_DISPCNT = BG2_ENABLE | MODE3;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;
  u16 bgcolor = BLACK;

  enum gba_state {
    GS_START,
    GS_INITPLAY,
    GS_PLAY,
    GS_PAUSE,
    GS_REDRAW,
    GS_END,
  };
  // Load initial application state
  enum gba_state state = GS_START;

  struct state currentstate, previousstate;
  struct entity *player, *oldplayer, *enemy, *oldenemy;
  int score = 0;
  char buffer[51];

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons
    previousstate = currentstate;

    // compute graphics
    switch (state) {
      case GS_START:
        score = 0;
        break;
      case GS_INITPLAY:
        // Erase image and fill with bg color

        // Initialize player entity
        currentstate.player.row = 80;
        currentstate.player.col = 120;
        currentstate.player.rd = 2;
        currentstate.player.cd = 2;
        currentstate.player.color = RED;

        for (int i = 0; i < MAX_ENTITIES; i++) {
          currentstate.entities[i].row = randint(0, (HEIGHT + 1));
          currentstate.entities[i].col = randint(0, (WIDTH + 1));
          currentstate.entities[i].rd = 2;
          currentstate.entities[i].cd = 2;
          currentstate.entities[i].color = YELLOW;
        }
        break;
      case GS_PLAY:
        player = &currentstate.player;
        // movement keys
        if (KEY_DOWN(BUTTON_UP, currentButtons)) {
          player->row += -player->rd;
          if (player->row < 0) {
            player->row = 0;
          }
        }
        if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
          player->row += player->rd;
          if (player->row > (150 - PLAYER_SIZE)) {
            player->row = 150 - PLAYER_SIZE;
          }
        }
        if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
          player->col += -player->cd;
          if (player->col < 0) {
            player->col = 0;
          }
        }
        if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
          player->col += player->cd;
          if (player->col > (WIDTH - PLAYER_SIZE)) {
            player->col = WIDTH - PLAYER_SIZE;
          }
        }

        // increment score
        score++;
        // set bouncing enemies
        for (int i = 0; i < MAX_ENTITIES; i++) {
          enemy = &currentstate.entities[i];
          enemy->row += enemy->rd;
          enemy->col += enemy->cd;

          if(enemy->row < 0) {
            enemy->row = 0;
            enemy->rd = -enemy->rd;
          }
          if(enemy->row > (150 - ENEMY_SIZE)) {
            enemy->row = 150 - ENEMY_SIZE;
            enemy->rd = -enemy->rd;
          }
          if(enemy->col < 0) {
            enemy->col = 0;
            enemy->cd = -enemy->cd;
          }
          if(enemy->col > (WIDTH - ENEMY_SIZE)) {
            enemy->col = WIDTH - ENEMY_SIZE;
            enemy->cd = -enemy->cd;
          }
        }
        break;
      case GS_PAUSE:
        break;
      case GS_REDRAW:
        break;
      case GS_END:
        break;
    }

    waitForVBlank();

    switch (state) {
      case GS_START:
        fillScreenDMA(bgcolor);
        drawFullScreenImageDMA(titlescreen);
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons)) {
          state = GS_INITPLAY;
        }
        break;
      case GS_INITPLAY:
        fillScreenDMA(bgcolor);
        state = GS_PLAY;
        break;
      case GS_PLAY:
        // action keys
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = GS_START;
        }        
        if (KEY_JUST_PRESSED(BUTTON_A, currentButtons, previousButtons)) {
          state = GS_PAUSE;
        }
        oldplayer = &previousstate.player;
        //erase previous position
        drawRectDMA(oldplayer->row, oldplayer->col, PLAYER_SIZE, PLAYER_SIZE, bgcolor);
        //draw new position
        drawRectDMA(player->row, player->col, PLAYER_SIZE, PLAYER_SIZE, RED);
        //erase previous positions
        for (int i = 0; i < MAX_ENTITIES; i++) {
          oldenemy = &previousstate.entities[i];
          drawRectDMA(oldenemy->row, oldenemy->col, ENEMY_SIZE, ENEMY_SIZE, bgcolor);
        }
        //draw new position
        for (int i = 0; i < MAX_ENTITIES; i++) {
          enemy = &currentstate.entities[i];
          // checks for collision between enemies and player
          if ((enemy->row >= player->row) && (enemy->col >= player->col) && (enemy->row <= (player->row + PLAYER_SIZE))
               && (enemy->col <= (player->col + PLAYER_SIZE))) {
            state = GS_END;
          }
          if ((player->row >= enemy->row) && (player->col >= enemy->col) && (player->row <= (enemy->row + ENEMY_SIZE))
               && (player->col <= (enemy->col + ENEMY_SIZE))) {
            state = GS_END;
          }
          drawRectDMA(enemy->row, enemy->col, ENEMY_SIZE, ENEMY_SIZE, YELLOW);
        }

        sprintf(buffer, "Score: %d", score);
        drawRectDMA(150, 5, 200, 10, bgcolor);
        drawString(150, 5, buffer, RED);
        break;
      case GS_PAUSE:
        drawImageDMA(50, 90, 60, 20, pausescreen);
        if (KEY_DOWN(BUTTON_B, currentButtons)) {
          state = GS_REDRAW;
        }
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons)) {
          state = GS_START;
        }
        break;
      case GS_REDRAW:
        fillScreenDMA(bgcolor);
        state = GS_PLAY;
        break;
      case GS_END:
        drawFullScreenImageDMA(gameoverscreen);
        sprintf(buffer, "Score: %d", score);
        drawRectDMA(150, 90, 200, 10, bgcolor);
        drawString(150, 90, buffer, RED);

        if (KEY_DOWN(BUTTON_SELECT, BUTTONS)) {
          state = GS_START;
        }
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}
