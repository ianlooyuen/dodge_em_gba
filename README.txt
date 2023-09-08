CS2110 Homework 8
Name: Ian Loo
GTID: 903532081
***************************************************************************************************************************
GBA Program: Dodge Em
DOCUMENTATION:
- Game Description
  The concept is simple: manipulate your red player orb, and dodge the eight flying yellow orbs as long as you can.
  The longer you last, the higher your score! It's very much like dodgeball but with 8 balls.
***************************************************************************************************************************
- States
  There are six states in total, each of which would be elaborated on.
  1. GS_START:
     Title screen state. Use BUTTON_START to go to GS_INITPLAY.
     [GS_START -> GS_INITPLAY]
  2. GS_INITPLAY:
     Initializes the game. Will create entities and prepare the background.
     Will go to GS_PLAY afterwards automatically.
     [GS_INITPLAY -> GS_PLAY]
  3. GS_PLAY:
     Main state of the game where player gets to play. If player gets hit, go to GS_END. If player pauses using BUTTON_A,
     go to GS_PAUSE.
     [GS_PLAY -> GS_PAUSE, GS_PLAY -> GS_PAUSE]
  4. GS_PAUSE:
     Pause gameplay. BUTTON_A to pause, BUTTON_B to continue playing. Will go back to GS_REDRAW to redraw background.
     [GS_PAUSE -> GS_REDRAW]
  5. GS_REDRAW:
     Temporary state to redraw background. Goes automatically to GS_PLAY.
     [GS_REDRAW -> GS_PLAY]
  6. GS_END
     Game over screen state. Press BUTTON_SELECT to restart from title screen.
     [GS_END -> GS_START]
***************************************************************************************************************************
- BUTTONS
  1. BUTTON_UP
     Direction key for upward movement.
  2. BUTTON_DOWN
     Direction key for downward movement.
  3. BUTTON_LEFT
     Direction key for leftward movement.
  4. BUTTON_RIGHT
     Direction key for rightward movement.
  5. BUTTON_A
     Pause key.
  6. BUTTON_B
     Resume key.
  7. BUTTON_START
     Key to start game at beginning.
  8. BUTTON_SELECT
     Key to return to title screen at any point in game.
***************************************************************************************************************************
- ASSIGNMENT REQUIREMENTS
  Images: titlescreen.h, gameoverscreen.h, pausescreen.h.
     - The first two screens are full screen images, and the third is a smaller image of dimensions of 20 by 60 pixels.
  Object Collision: enemy entities and player entity
     - When either entity collide, game is over.
  Text: score counter
     - Increments for each iteration, to keep track of score.
  Button movement: arrow keys