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

const unsigned char small_ball_sprite_data[] =
{
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x18,0x18,0x7E,0x7E,0x7E,0x7E,0xFF,0xFF,
  0xFF,0xFF,0x7E,0x7E,0x7E,0x7E,0x18,0x18,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
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
int BALL_SIZE = 8;
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
const int paddle_speed = 3;

UBYTE ball_x;
UBYTE ball_y;
UBYTE ball_vel_x;
UBYTE ball_vel_y;
const int ball_sprite = 2;
const int ball_speed = 1;

// array holding block sprite indexes, x, y coords
// [[index, x_coord, y_coord]]
int block_sprites[24][3];

const int lives_sprite_begin = 3;

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

void set_blocks()
{
  int i, j, a, b, a_x, b_x, a_y, b_y, offset_x, offset_y;

  int sp = lives_sprite_begin + (INITIAL_LIVES * 2 * 2);
  int init_sp = sp;

  int width = 4;
  int height = 3;

  set_sprite_data(32, 8, block_sprite_data);

  for (i=0; i<height; i++) {
    offset_x = i * 16;
    for (j=0; j<width; j++) {
      offset_y = j * 16;
      a = sp++;
      b = sp++;
      a_x = 56 + offset_y;
      a_y = 48 + offset_x;
      b_x = 56 + 8 + offset_y;
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
    game_started = 1;
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
  if(key & (J_UP|J_DOWN)) {
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

int abs(int num)
{
  if (num < 0) {
    return num * -1;
  } else {
    return num;
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
      block_x + block_y != 0 &&
      ball_x <= block_x + 8 && ball_x >= block_x - 8 &&
      ball_y <= block_y + 8 && ball_y >= block_y - 16
    ) {
      collided = 1;
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
      }
      if (ball_x < block_x) {
        hit_left = 1;
      } else if (ball_x > block_x) {
        hit_right = 1;
      }

      if (hit_top) {
        ball_vel_y = -1;
      } else if (hit_bottom) {
        ball_vel_y = 1;
      }
      if (hit_left) {
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
  // if (ball_y >= SCREEN_HEIGHT - (BALL_SIZE / 2)) {
  if (ball_y + 2 >= paddle_y && ball_y -2 <= paddle_y) {
    if (
      paddle_x > ball_x - 12 &&
      paddle_x < ball_x + 4
    ) {
      ball_vel_y = -1;
    }
  // ball collision with cieling
  } else if (ball_y <= 0 + BALL_SIZE) {
    ball_vel_y = 1;
  }
  // ball collision with floor
  if (ball_y >= SCREEN_HEIGHT + BALL_SIZE) {
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

void score()
{
  if (game_over) {
    set_paddle();
    set_ball(1);
    set_blocks();
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
    physics();
    collide();
    move();
    score();

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
