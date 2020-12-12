#include <gb/gb.h>
#include <gb/drawing.h>
#include "alpha.c"
#include "blank_screen.c"
#include "sprites.c"

static void state_game_over();

// game config
int SCREEN_WIDTH = 160;
int SCREEN_HEIGHT = 144;
int SPRITE_SIZE = 16;
const int FRAME_RATE = 60;
const int INITIAL_LIVES = 3;

// currently pressed key
UBYTE key;

// game state
int lives = INITIAL_LIVES;
int game_started = 0;
int game_over = 0;
int current_level = 0;
int game_score = 0;
// frames elapsed, reset every 60 frames
int frames = 0;
// seconds elapsed, never reset
int seconds = 0;

UBYTE paddle_coords[] = {0, 0};
UBYTE paddle_vel[] = {0, 0};
const int paddle_sprites[] = {0, 1};
const int paddle_speed = 3;


unsigned char score_array[] = { 0x30, 0x30, 0x30, 0x30 };

void render_background()
{
  // load alphanumeric background tiles
  set_bkg_data(0, 47, alpha);
  // blank the entire screen
  set_bkg_tiles(0, 0, 20, 18, blank_screen);
}

void set_paddle()
{
  paddle_coords[0] = SCREEN_WIDTH / 2;
  paddle_coords[1] = SCREEN_HEIGHT - 1;

  set_sprite_data(0, 8, paddle_sprite_data);
  set_sprite_tile(paddle_sprites[0], 0);
  set_sprite_tile(paddle_sprites[1], 2);
  move_sprite(paddle_sprites[0], paddle_coords[0], paddle_coords[1]);
  move_sprite(paddle_sprites[1], paddle_coords[0] + (SPRITE_SIZE/2), paddle_coords[1]);
}

void input()
{
  // paddle movement
  if(key & (J_LEFT|J_RIGHT|J_UP|J_DOWN)) {
    if(key & J_LEFT && paddle_coords[0] > 0) {
      paddle_vel[0] = -1 * paddle_speed;
    }
    if(key & J_RIGHT && paddle_coords[0] < SCREEN_WIDTH) {
      paddle_vel[0] = 1 * paddle_speed;
    }
    if(key & J_UP) {
      paddle_vel[1] = -1 * paddle_speed;
    }
    if(key & J_DOWN) {
      paddle_vel[1] = 1 * paddle_speed;
    }
  }

  if(key & J_A) {
  }
}

void physics()
{
  // paddle
  if(key & (J_LEFT|J_RIGHT)) {
    paddle_coords[0]+=paddle_vel[0];
  }
  if(key & (J_UP|J_DOWN)) {
    paddle_coords[1]+=paddle_vel[1];
  }
}

void collide() {
}

void move() {
  // paddle
  move_sprite(0, paddle_coords[0], paddle_coords[1]);
  move_sprite(1, paddle_coords[0] + 8, paddle_coords[1]);
}

void score() {
}

void render_score() {
    if (frames % (FRAME_RATE / 2) == 0) {
  // only render score every half second
    score_array[0] = numbers[(game_score / 1000) % 10]; // thousands
    score_array[1] = numbers[(game_score / 100) % 10]; // hundreds
    score_array[2] = numbers[(game_score / 10) % 10]; // tens
    score_array[3] = numbers[game_score % 10]; // ones
  }

  // write the score
  set_bkg_tiles(
    16, // xrow
    0, // yrow
    4, // num tiles width (columns)
    1, // num tiles height (rows)
    score_array
  );
}

//
// GAME STATE
//

void state_game_over() {
  game_over = 1;
  HIDE_SPRITES;
}

void state_game_init() {
  game_over = 0;
  set_paddle();
  SHOW_SPRITES;
}

void state_game_restart(){
  game_score = 0;
  game_started = 0;
  game_over = 0;
  current_level = 0;
  lives = INITIAL_LIVES;
}

//
// GAME LOOP
//

void run()
{
  // game loop
  while(1) {

    if (frames == FRAME_RATE) {
    frames++;
      frames = 0;
      seconds++;
    }

    wait_vbl_done();

    key = joypad();

    input();
    if (!game_over) {
      physics();
      collide();
      move();
      score();
      render_score();
    }

    SHOW_BKG;
    if (game_over) {
      HIDE_SPRITES;
    } else {
      SHOW_SPRITES;
    }
  }
}

void main()
{
  SPRITES_8x16;
  state_game_init();
  run();
}
