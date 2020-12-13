#include <gb/gb.h>
#include <gb/drawing.h>
#include "alpha.c"
#include "blank_screen.c"
#include "sprites.c"

static void state_game_over();

// game config
unsigned int SCREEN_WIDTH = 160;
unsigned int SCREEN_HEIGHT = 144;
unsigned int SPRITE_SIZE = 16;
const unsigned int FRAME_RATE = 60;
const unsigned int INITIAL_LIVES = 3;

// currently pressed key
UBYTE key;

// game state
unsigned int lives = INITIAL_LIVES;
unsigned int game_started = 0;
unsigned int game_over = 0;
// frames elapsed, reset every 60 frames
unsigned int frames = 0;
// seconds elapsed, never reset
unsigned int seconds = 0;
// set to 1 to require holding a direction for movement
const unsigned int disable_momentum = 0;
unsigned int left_wall_occupied = 0;
unsigned int right_wall_occupied = 0;
unsigned int top_wall_occupied = 0;
unsigned int bottom_wall_occupied = 0;

// goop
UBYTE goop_coords[] = {0, 0};
UBYTE goop_vel[] = {0, 0};
const unsigned int goop_sprites[] = {0, 1};
const unsigned int goop_speed = 3;

void render_background()
{
  // load alphanumeric background tiles
  set_bkg_data(0, 47, alpha);
  // blank the entire screen
  set_bkg_tiles(0, 0, 20, 18, blank_screen);
}

void init_goop()
{
  goop_coords[0] = SCREEN_WIDTH / 2;
  goop_coords[1] = SCREEN_HEIGHT / 2;

  set_sprite_data(0, 8, goop_neutral_sprites[0]);
  set_sprite_tile(goop_sprites[0], 0);
  set_sprite_tile(goop_sprites[1], 2);
  move_sprite(goop_sprites[0], goop_coords[0], goop_coords[1]);
  move_sprite(goop_sprites[1], goop_coords[0] + (SPRITE_SIZE/2), goop_coords[1]);
}

void input()
{
  // goop movement
  if(key & (J_LEFT|J_RIGHT|J_UP|J_DOWN)) {
    if(key & J_LEFT && !left_wall_occupied) {
      goop_vel[0] = -1 * goop_speed;
    }
    if(key & J_RIGHT && !right_wall_occupied) {
      goop_vel[0] = 1 * goop_speed;
    }
    if(key & J_UP && !top_wall_occupied) {
      goop_vel[1] = -1 * goop_speed;
    }
    if(key & J_DOWN && !bottom_wall_occupied) {
      goop_vel[1] = 1 * goop_speed;
    }
  }
}

void physics()
{
  // goop
  if (disable_momentum) {
    if(key & (J_LEFT|J_RIGHT)) {
      goop_coords[0]+=goop_vel[0];
    }
    if(key & (J_UP|J_DOWN)) {
      goop_coords[1]+=goop_vel[1];
    }
  } else {
    goop_coords[0]+=goop_vel[0];
    goop_coords[1]+=goop_vel[1];
  }
}

void collide() {
  unsigned int stop = 0;

  left_wall_occupied = 0;
  right_wall_occupied = 0;
  top_wall_occupied = 0;
  bottom_wall_occupied = 0;

  // goop collision with walls
  if (goop_coords[0] >= SCREEN_WIDTH - (SPRITE_SIZE/2)) {
    stop = 1;
    right_wall_occupied = 1;
  }
  if (goop_coords[0] <= 0 + (SPRITE_SIZE/2)) {
    stop = 1;
    left_wall_occupied = 1;
  }
  if (goop_coords[1] >= SCREEN_HEIGHT) {
    stop = 1;
    bottom_wall_occupied = 1;
  }
  if (goop_coords[1] <= 0 + (SPRITE_SIZE)) {
    stop = 1;
    top_wall_occupied = 1;
  }

  if (stop) {
    goop_vel[0] = 0;
    goop_vel[1] = 0;
  }
}


void move() {
  // goop
  move_sprite(goop_sprites[0], goop_coords[0], goop_coords[1]);
  move_sprite(goop_sprites[1], goop_coords[0] + 8, goop_coords[1]);
}

void animate() {
  unsigned int neutral =
    !left_wall_occupied && !right_wall_occupied && !top_wall_occupied && !bottom_wall_occupied;

  if (neutral) {
    if (frames <= 15) {
      set_sprite_data(0, 8, goop_neutral_sprites[0]);
    } else if (frames <= 30) {
      set_sprite_data(0, 8, goop_neutral_sprites[1]);
    } else if (frames <= 45) {
      set_sprite_data(0, 8, goop_neutral_sprites[2]);
    } else if (frames <= 60) {
      set_sprite_data(0, 8, goop_neutral_sprites[3]);
    }
    return;
  } else {
    if (left_wall_occupied) {
      set_sprite_data(0, 8, goop_left_sprite_data);
      return;
    }
    if (right_wall_occupied) {
      set_sprite_data(0, 8, goop_right_sprite_data);
      return;
    }
    if (top_wall_occupied) {
      set_sprite_data(0, 8, goop_top_sprite_data);
      return;
    }
    if (bottom_wall_occupied) {
      set_sprite_data(0, 8, goop_bottom_sprite_data);
      return;
    }
  }
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
  init_goop();
  SHOW_SPRITES;
}

void run()
{
  while(1) {

    frames++;
    if (frames == FRAME_RATE) {
      frames = 0;
      seconds++;
    }

    wait_vbl_done();

    key = joypad();

    input();
    if (!game_over) {
      physics();
      move();
      collide();
      animate();
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
