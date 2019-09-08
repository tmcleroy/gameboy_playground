#include <gb/gb.h>
#include <gb/drawing.h>

const unsigned char paddle_sprite_data[] = 
{ 
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,0x3F,0x3F,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFC,0xFC
};

const unsigned char ball_sprite_data[] =
{
  0x07,0x07,0x1F,0x1F,0x3F,0x3F,0x7F,0x7F,
  0x7F,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x7F,0x7F,
  0x7F,0x7F,0x3F,0x3F,0x1F,0x1F,0x07,0x07,
  0xE0,0xE0,0xF8,0xF8,0xFC,0xFC,0xFE,0xFE,
  0xFE,0xFE,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,
  0xFE,0xFE,0xFC,0xFC,0xF8,0xF8,0xE0,0xE0
};

const unsigned char smile_sprite_data[] =
{
  0x07,0x07,0x1F,0x1F,0x3F,0x3F,0x7F,0x7B,
  0x7F,0x73,0xFF,0xF3,0xF3,0xFF,0xF3,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x7F,0x60,
  0x7F,0x70,0x3F,0x3C,0x1F,0x1F,0x07,0x07,
  0xE0,0xE0,0xF8,0xF8,0xFC,0xFC,0xFE,0xDE,
  0xFE,0xCE,0xFF,0xCF,0xCF,0xFF,0xCF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0x07,0xFE,0x06,
  0xFE,0x0E,0xFC,0x3C,0xF8,0xF8,0xE0,0xE0
};

const unsigned char death_sprite_data[] =
{
  0x07,0x07,0x1F,0x1F,0x0F,0x0F,0x67,0x67,
  0x73,0x73,0xF9,0xF9,0xFC,0xFC,0xFE,0xFE,
  0xFC,0xFC,0xF9,0xF9,0xF3,0xF3,0x67,0x67,
  0x4F,0x4F,0x1F,0x1F,0x1F,0x1F,0x07,0x07,
  0xE0,0xE0,0xF8,0xF8,0xF0,0xF0,0xE6,0xE6,
  0xCE,0xCE,0x9F,0x9F,0x3F,0x3F,0x7F,0x7F,
  0x3F,0x3F,0x9F,0x9F,0xCF,0xCF,0xE6,0xE6,
  0xF2,0xF2,0xF8,0xF8,0xF8,0xF8,0xE0,0xE0
};

const unsigned char block_sprite_data[] =
{
  0xFF,0xFF,0xFF,0x80,0xFF,0xBF,0xFF,0xA0,
  0xFF,0xAF,0xFF,0xA8,0xFF,0xAB,0xFF,0xAA,
  0xFF,0xAA,0xFF,0xAB,0xFF,0xA8,0xFF,0xAF,
  0xFF,0xA0,0xFF,0xBF,0xFF,0x80,0xFF,0xFF,
  0xFF,0xFF,0xFF,0x01,0xFF,0xFD,0xFF,0x05,
  0xFF,0xF5,0xFF,0x15,0xFF,0xD5,0xFF,0x55,
  0xFF,0x55,0xFF,0xD5,0xFF,0x15,0xFF,0xF5,
  0xFF,0x05,0xFF,0xFD,0xFF,0x01,0xFF,0xFF
};


int SCREEN_WIDTH = 160;
int SCREEN_HEIGHT = 144;
int SPRITE_SIZE = 16;
const int INITIAL_LIVES = 3;

UBYTE key;
int lives = INITIAL_LIVES;
int game_started = 0;
int game_over = 0;

UBYTE paddle_x;
UBYTE paddle_y;
UBYTE paddle_vel_x;
UBYTE paddle_vel_y;
const int paddle_sprite_left = 0;
const int paddle_sprite_right = 1;
const int paddle_speed = 2;

UBYTE ball_x;
UBYTE ball_y;
UBYTE ball_vel_x;
UBYTE ball_vel_y;
const int ball_sprite_left = 2;
const int ball_sprite_right = 3;

const int lives_sprite_begin = 4;

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
  ball_x = SCREEN_WIDTH / 2;
  ball_y = SCREEN_HEIGHT - 5;

  set_sprite_data(8, 8, ball_sprite_data);
  set_sprite_tile(ball_sprite_left, 8);
  set_sprite_tile(ball_sprite_right, 10);
  move_sprite(ball_sprite_left, ball_x, ball_y);
  move_sprite(ball_sprite_right, ball_x + 8, ball_y);

  // initial ball movement
  if (move) {
    ball_vel_y = -1;
    ball_vel_x = -1;
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

int blocks[24];

void set_blocks()
{
  int i, j, a, b, offset_x, offset_y;
  int sp = lives_sprite_begin + (INITIAL_LIVES * 2 * 2);

  set_sprite_data(32, 8, block_sprite_data);

  for (i=0; i<4; i++) {
    offset_x = i * 16;
    for (j=0; j<3; j++) {
      offset_y = j * 16;
      a = sp++;
      b = sp++;

      if (i==0 && j==0) {
        blocks[0] = a;
        blocks[1] = b;
      } else {
        size_t NumberOfElements = sizeof(blocks)/sizeof(blocks[0]);
        blocks[NumberOfElements] = a;
        blocks[NumberOfElements + 1] = b;
      }

      set_sprite_tile(a, 32);
      set_sprite_tile(b, 34);
      move_sprite(a, 56 + offset_x, 48 + offset_y);
      move_sprite(b, 56 + 8 + offset_x, 48 + offset_y);
    }
  }
}

void input()
{
  // paddle movement
  if(key & (J_LEFT|J_RIGHT)) {
    if(key & J_LEFT && paddle_x > 0) {
      paddle_vel_x = -1 * paddle_speed;
    }
    if(key & J_RIGHT && paddle_x < SCREEN_WIDTH) {
      paddle_vel_x = 1 * paddle_speed;
    }
  }

  if(key & J_A) {
    game_started = 1;
    set_ball(1);
    if (lives <= 0) {
      lives = INITIAL_LIVES;
      set_lives();
    }
  }
}

void physics()
{
  // paddle
  if(key & (J_LEFT|J_RIGHT)) {
    paddle_x+=paddle_vel_x;
  }
  // ball
  ball_x+=ball_vel_x;
  ball_y+=ball_vel_y;
}

void collide()
{
  // paddle collision with walls
  if (paddle_x >= SCREEN_WIDTH) {
    paddle_vel_x = 0;
  }
  if (paddle_x <= 0) {
    paddle_vel_x = 0;
  }


  // ball collision with floor
  // if (ball_y >= SCREEN_HEIGHT) {
  //   ball_vel_y = -1;
  // }
  // ball collision with paddle
  if (ball_y >= SCREEN_HEIGHT - 4) {
    if (
      paddle_x > ball_x - 5 &&
      paddle_x < ball_x + 5
    ) {
      ball_vel_y = -1;
    }
  // ball collision with cieling
  } else if (ball_y <= 0 + SPRITE_SIZE) {
    ball_vel_y = 1;
  }
  // ball collision with floor
  if (ball_y >= SCREEN_HEIGHT + (SPRITE_SIZE - 4)) {
    lives--;
    set_paddle();
    set_ball(1);
    set_lives();
    game_started = 0;
    if (lives <= 0) {
      game_over = 1;
    }
  }
  // ball collision with right wall
  if (ball_x >= SCREEN_WIDTH - (SPRITE_SIZE / 2)) {
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
  move_sprite(3, ball_x + 8, ball_y);
}

void score()
{
  if (game_over) {
    set_paddle();
    set_ball(0);
    game_started = 0;
    game_over = 0;
  }
}

void run()
{
  while(1) {
    wait_vbl_done();

    key = joypad();

    input();
    if (game_started) {
      physics();
      collide();
      move();
      score();
    }

    SHOW_SPRITES;
  }
}

void main()
{
  SPRITES_8x16;

  set_paddle();
  set_ball(1);
  set_lives();
  set_blocks();
  run();
}
