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
unsigned char game_score_array[] = { 0x30, 0x30, 0x30, 0x30 };
// frames elapsed, reset every 60 frames
int frames = 0;
// seconds elapsed, never reset
int seconds = 0;

// goop
UBYTE goop_coords[] = {0, 0};
UBYTE goop_vel[] = {0, 0};
const int goop_sprites[] = {0, 1};
const int goop_speed = 3;

void render_background()
{
  // load alphanumeric background tiles
  set_bkg_data(0, 47, alpha);
  // blank the entire screen
  set_bkg_tiles(0, 0, 20, 18, blank_screen);
}

void set_goop()
{
  goop_coords[0] = SCREEN_WIDTH / 2;
  goop_coords[1] = SCREEN_HEIGHT - 1;

  set_sprite_data(0, 8, goop_sprite_data);
  set_sprite_tile(goop_sprites[0], 0);
  set_sprite_tile(goop_sprites[1], 2);
  move_sprite(goop_sprites[0], goop_coords[0], goop_coords[1]);
  move_sprite(goop_sprites[1], goop_coords[0] + (SPRITE_SIZE/2), goop_coords[1]);
}

void input()
{
  // goop movement
  if(key & (J_LEFT|J_RIGHT|J_UP|J_DOWN)) {
    if(key & J_LEFT && goop_coords[0] > 0) {
      goop_vel[0] = -1 * goop_speed;
    }
    if(key & J_RIGHT && goop_coords[0] < SCREEN_WIDTH) {
      goop_vel[0] = 1 * goop_speed;
    }
    if(key & J_UP) {
      goop_vel[1] = -1 * goop_speed;
    }
    if(key & J_DOWN) {
      goop_vel[1] = 1 * goop_speed;
    }
  }

  if(key & J_A) {
  }
}

void physics()
{
  // goop
  if(key & (J_LEFT|J_RIGHT)) {
    goop_coords[0]+=goop_vel[0];
  }
  if(key & (J_UP|J_DOWN)) {
    goop_coords[1]+=goop_vel[1];
  }
}

void collide() {
}

void move() {
  // goop
  move_sprite(0, goop_coords[0], goop_coords[1]);
  move_sprite(1, goop_coords[0] + 8, goop_coords[1]);
}

void score() {
}

void render_score() {
    if (frames % (FRAME_RATE / 2) == 0) {
  // only render score every half second
    game_score_array[0] = numbers[(game_score / 1000) % 10]; // thousands
    game_score_array[1] = numbers[(game_score / 100) % 10]; // hundreds
    game_score_array[2] = numbers[(game_score / 10) % 10]; // tens
    game_score_array[3] = numbers[game_score % 10]; // ones
  }

  // write the score
  set_bkg_tiles(
    16, // xrow
    0, // yrow
    4, // num tiles width (columns)
    1, // num tiles height (rows)
    game_score_array
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
  set_goop();
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
