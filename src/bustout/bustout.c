#include <gb/gb.h>
#include <gb/drawing.h>
#include "alpha.c"
#include "blank_screen.c"
#include "sprites.c"
#include "codysad.c"
#include "codysplash.c"

int abs(int num)
{
  if (num < 0) {
    return num * -1;
  } else {
    return num;
  }
}

static void state_life_start();
static void state_life_end();
static void state_blocks_gone();
static void state_game_over();

// each map can only have up to 9 ones
const int block_map[3][4][6] = {
  { // block in middle
    {0,0,0,0,0,0},
    {0,1,1,1,1,0},
    {0,1,1,1,1,0},
    {0,0,0,0,0,0}
  },
  { // smiley
    {0,1,0,0,1,0},
    {0,0,0,0,0,0},
    {1,0,0,0,0,1},
    {0,1,1,1,1,0}
  },
  { // bowed H shape
    {1,0,0,0,0,1},
    {0,1,0,0,1,0},
    {0,1,0,0,1,0},
    {1,0,0,0,0,1}
  }
};

int SCREEN_WIDTH = 160;
int SCREEN_HEIGHT = 144;
int SPRITE_SIZE = 16;
int BALL_SIZE = 8;
const int INITIAL_LIVES = 3;
const int framerate = 60;

UBYTE key;
int lives = INITIAL_LIVES;
int game_started = 0;
int splash_over = 0;
int game_over = 0;
int current_level = 0;

UBYTE paddle_x;
UBYTE paddle_y;
UBYTE paddle_vel_x;
UBYTE paddle_vel_y;
const int paddle_sprite_left = 0;
const int paddle_sprite_right = 1;
const int paddle_speed = 3;

UBYTE ball_x;
UBYTE ball_y;
UBYTE ball_vel_x;
UBYTE ball_vel_y;
const int ball_sprite = 2;
const int ball_speed = 2;
// whether or not you can move the paddle up and down
int vertical_paddle_movement = 1;
// score
int game_score = 0;
// frames elapsed, reset every 60 frames
int frames = 0;
// seconds elapsed
int seconds = 0;
int temp_seconds = 0;

// array holding block sprite indexes, x, y coords
// [[index, x_coord, y_coord]]
int block_sprites[24][3];

const int lives_sprite_begin = 3;

unsigned char score_array[] = { 0x30, 0x30, 0x30, 0x30 };
unsigned char game_over_message_array[] = {
  0xff, 0xff, 0x17, 0x11, 0x1D, 0x15, 0xff, 0x1F, 0x26, 0x15, 0x22, 0xff, 0xff,
  0xff, 0xff, 0x1E, 0x1F, 0xff, 0x1D, 0x25, 0x1C, 0x1C, 0x15, 0x24, 0xff, 0xff,
  0xff, 0x1d, 0x25, 0x23, 0x24, 0xff, 0xff, 0x23, 0x13, 0x1f, 0x22, 0x15, 0xff,
  0x02, 0x00, 0x00, 0x00, 0xff, 0xff, 0x14, 0x1f, 0x1c, 0x1c, 0x11, 0x22, 0x23,
};

void render_background()
{
  // load alphanumeric background tiles
  set_bkg_data(0, 47, alpha);
  // blank the entire screen
  set_bkg_tiles(0, 0, 20, 18, blank_screen);
}

void render_sad_cody()
{
  set_bkg_data(0, 209, codysad_tiledata);
  set_bkg_tiles(4, 0, 13, 16, codysad_tilemap);

  // load alphanumeric background tiles
  set_bkg_data(0, 47, alpha);

  set_bkg_tiles(
    4, // xrow
    0, // yrow
    13, // num tiles width (columns)
    4, // num tiles height (rows)
    game_over_message_array
  );
}

void render_splash()
{
  set_bkg_data(0, 1, codysplash_tiledata);
  set_bkg_tiles(0, 0, 20, 18, blank_screen);
  
  set_bkg_data(0, 256, codysplash_tiledata);
  set_bkg_tiles(0, 3, 20, 13, codysplash_tilemap);
}

void set_paddle()
{
  paddle_x = SCREEN_WIDTH / 2;
  paddle_y = SCREEN_HEIGHT - 1;

  set_sprite_data(0, 8, paddle_sprite_data);
  set_sprite_tile(paddle_sprite_left, 0);
  set_sprite_tile(paddle_sprite_right, 2);
  move_sprite(paddle_sprite_left, paddle_x, paddle_y);
  move_sprite(paddle_sprite_right, paddle_x + 8, paddle_y);
}

void set_ball(int move)
{
  ball_x = (SCREEN_WIDTH / 2) + (BALL_SIZE / 2);
  ball_y = SCREEN_HEIGHT - 5;

  set_sprite_data(8, 8, small_ball_sprite_data);
  set_sprite_tile(ball_sprite, 8);
  move_sprite(ball_sprite, ball_x, ball_y);

  // initial ball movement
  if (move) {
    ball_vel_y = -1;
    ball_vel_x = 1;
  } else {
    ball_vel_x = 0;
    ball_vel_y = 0;
  }
}

void set_lives()
{
  int i, j, a, b, offset;
  int sp = lives_sprite_begin;

  set_sprite_data(16, 8, smile_sprite_data);
  set_sprite_data(24, 8, death_sprite_data);

  for (i=0; i<lives; i++) {
    offset = i * 16;
    a = sp++;
    b = sp++;
    
    set_sprite_tile(a, 16);
    set_sprite_tile(b, 18);
    move_sprite(a, 8 + offset, 16);
    move_sprite(b, 8 + 8 + offset, 16);
  }

  for (j=lives; j<INITIAL_LIVES; j++) {
    offset = j * 16;
    a = sp++;
    b = sp++;

    set_sprite_tile(a, 24);
    set_sprite_tile(b, 26);
    move_sprite(a, 8 + offset, 16);
    move_sprite(b, 8 + 8 + offset, 16);
  }
}

void set_blocks() {
  int i, j, a, b, a_x, b_x, a_y, b_y, offset_x, offset_y;
  int width = 6;
  int height = 4;

  int sp = lives_sprite_begin + (INITIAL_LIVES * 2 * 2);
  int init_sp = sp;

  set_sprite_data(32, 8, block_sprite_data);

  for (i=0; i<height; i++) {
    offset_x = i * 16;
    for (j=0; j<width; j++) {
      if (block_map[current_level][i][j]) {
        offset_y = j * 16;
        a = sp++;
        b = sp++;
        a_x = 40 + offset_y;
        a_y = 48 + offset_x;
        b_x = 40 + 8 + offset_y;
        b_y = 48 + offset_x;

        block_sprites[a - init_sp][0] = a;
        block_sprites[a - init_sp][1] = a_x;
        block_sprites[a - init_sp][2] = a_y;

        block_sprites[b - init_sp][0] = b;
        block_sprites[b - init_sp][1] = b_x;
        block_sprites[b - init_sp][2] = b_y;

        set_sprite_tile(a, 32);
        set_sprite_tile(b, 34);
        move_sprite(a, a_x, a_y);
        move_sprite(b, b_x, b_y);
      }
    }
  }
}

void end_splash() {
  set_paddle();
  set_ball(1);
  set_lives();
  set_blocks();
  render_background();
  splash_over = 1;
}

void input()
{
  // paddle movement
  if(key & (J_LEFT|J_RIGHT|J_UP|J_DOWN)) {
    if(key & J_LEFT && paddle_x > 0) {
      paddle_vel_x = -1 * paddle_speed;
    }
    if(key & J_RIGHT && paddle_x < SCREEN_WIDTH) {
      paddle_vel_x = 1 * paddle_speed;
    }
    if(key & J_UP) {
      paddle_vel_y = -1 * paddle_speed;
    }
    if(key & J_DOWN) {
      paddle_vel_y = 1 * paddle_speed;
    }
  }

  if(key & J_A) {
    state_life_start();
  }

  if(key & J_START) {
    end_splash();
  }
}

void physics()
{
  // paddle
  if(key & (J_LEFT|J_RIGHT)) {
    paddle_x+=paddle_vel_x;
  }
  if(vertical_paddle_movement && key & (J_UP|J_DOWN)) {
    paddle_y+=paddle_vel_y;
  }
  // ball
  if (game_started) {
    // ball only moves on it's own if the game is started
    ball_x+=(ball_vel_x * ball_speed);
    ball_y+=(ball_vel_y * ball_speed);
  } else {
    // ball moves with paddle when game is not started
    ball_x = paddle_x + (BALL_SIZE / 2);
    ball_y = paddle_y - (BALL_SIZE / 2);
  }
}

void collide()
{
  int i;
  int collided = 0;

  // ball collision with blocks
  for (i=0; i<24; i++) {
    int block_i = block_sprites[i][0];
    int block_x = block_sprites[i][1];
    int block_y = block_sprites[i][2];
    int hit_top = 0;
    int hit_bottom = 0;
    int hit_left = 0;
    int hit_right = 0;

    if (
      !collided &&
      // n seconds have elapsed since last collision
      // (temp_seconds == 0 || seconds - temp_seconds > 1) &&
      block_x + block_y != 0 &&
      ball_x <= block_x + 8 && ball_x >= block_x - 8 &&
      ball_y <= block_y + 8 && ball_y >= block_y - 16
    ) {
      collided = 1;
      game_score += 80;
      // temp_seconds = seconds;

      move_sprite(block_i, 0, 0);
      block_sprites[i][1] = 0;
      block_sprites[i][2] = 0;
      if (i % 2 == 0) {
        // even indexes are left side sprites, move the right buddy
        move_sprite(block_i + 1, 0, 0);
        block_sprites[i + 1][1] = 0;
        block_sprites[i + 1][2] = 0;
      } else {
        // odd indexes are right side sprites, move the left buddy
        move_sprite(block_i - 1, 0, 0);
        block_sprites[i - 1][1] = 0;
        block_sprites[i - 1][2] = 0;
      }

      if (ball_y < block_y) {
        hit_top = 1;
      } else if (ball_y > block_y) {
        hit_bottom = 1;
      } else if (ball_x < block_x) {
        hit_left = 1;
      } else if (ball_x > block_x) {
        hit_right = 1;
      }

      if (hit_top) {
        ball_vel_y = -1;
      } else if (hit_bottom) {
        ball_vel_y = 1;
      } else if (hit_left) {
        ball_vel_x = -1;
      } else if (hit_right) {
        ball_vel_x = 1;
      }
    }
  }

  // paddle collision with walls
  if (paddle_x >= SCREEN_WIDTH) {
    paddle_vel_x = 0;
  }
  if (paddle_x <= 0) {
    paddle_vel_x = 0;
  }

  // ball collision with paddle
  if (ball_y + 2 >= paddle_y && ball_y -2 <= paddle_y) {
    if (
      paddle_x > ball_x - 18 &&
      paddle_x < ball_x + 10
    ) {
      ball_vel_y = -1;
    }
  // ball collision with ceiling
  } else if (ball_y <= 0 + BALL_SIZE) {
    ball_vel_y = 1;
  }
  // ball collision with floor
  if (ball_y >= SCREEN_HEIGHT + BALL_SIZE) {
    state_life_end();
    if (lives <= 0) {
      state_game_over();
    }
  }
  // ball collision with right wall
  if (ball_x >= SCREEN_WIDTH) {
    ball_vel_x = -1;
  // ball collision with left wall
  } else if (ball_x <= 0 + (SPRITE_SIZE / 2)) {
    ball_vel_x = 1;
  }
}

void move()
{
  // paddle
  move_sprite(0, paddle_x, paddle_y);
  move_sprite(1, paddle_x + 8, paddle_y);
  // ball
  move_sprite(2, ball_x, ball_y);
}

void score() {
  int i;
  int blocks_remaining = 0;
  for (i=0; i<24; i++) {
    int block_i = block_sprites[i][0];
    int block_x = block_sprites[i][1];
    int block_y = block_sprites[i][2];

    if (block_x + block_y != 0) {
      blocks_remaining++;
    }
  }
  if (blocks_remaining == 0) {
    state_blocks_gone();
  }
  if (game_over) {
    set_paddle();
    set_ball(1);
    set_blocks();
    game_started = 0;
    game_over = 0;
  }
}

void render_score() {
  // only render score every half second
  if (frames % (framerate / 2) == 0) {
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

void state_life_start() {
  game_started = 1;
  if (lives <= 0) {
    lives = INITIAL_LIVES;
    set_lives();
  }
}

void state_blocks_gone() {
  current_level++;
  if (current_level + 1 > 3) {
    current_level = 0;
  }
  game_started = 0;
  ball_vel_x = 0;
  ball_vel_y = 0;
  
  set_paddle();
  set_ball(1);
  set_blocks();
}

void state_life_end() {
  ball_vel_x = 0;
  ball_vel_y = 0;
  lives--;
  set_paddle();
  set_ball(1);
  set_lives();
  game_started = 0;
}

void state_game_over() {
  int i;
  game_over = 1;
  ball_vel_x = 0;
  ball_vel_y = 0;

  render_background();
  if (game_score < 2000) {
    render_sad_cody();
  }

  for (i=0; i<24; i++) {
    int block_i = block_sprites[i][0];
    int block_x = block_sprites[i][1];

    move_sprite(block_i + 1, 0, 0);
    move_sprite(block_i - 1, 0, 0);
  }
}

void run()
{
  // game loop
  while(1) {

    frames++;
    if (frames == framerate) {
      frames = 0;
      seconds++;
    }

    wait_vbl_done();

    key = joypad();

    input();
    if (splash_over) {
      physics();
      collide();
      move();
      score();
      render_score();
    }

    SHOW_BKG;
    SHOW_SPRITES;
  }
}

void main()
{
  SPRITES_8x16;

  // render_background();
  render_splash();
  // render_sad_cody();
  // SHOW_BKG;
  // end_splash();
  // run game loop
  run();
}
