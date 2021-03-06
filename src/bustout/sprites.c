// 0 - 9 referencing the array in alpha.c
const unsigned char numbers[] = {
  0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09
};

// small paddle
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

// small black ball
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

// happy cody with mullet
const unsigned char smile_sprite_data[] =
{
  0x07,0x00,0x0F,0x00,0x1F,0x00,0x10,0x08,
  0x30,0x08,0x20,0x16,0x62,0x14,0x60,0x10,
  0x60,0x14,0x60,0x13,0x70,0x08,0x78,0x04,
  0x3C,0x02,0x3C,0x02,0x00,0x02,0x00,0x02,
  0xE0,0x00,0xF0,0x00,0xF8,0x00,0x08,0x10,
  0x0C,0x10,0x04,0x68,0x46,0x28,0x06,0x08,
  0x06,0x28,0x06,0xC8,0x0E,0x10,0x1E,0x20,
  0x3C,0x40,0x3C,0x40,0x00,0x40,0x00,0x40
};

// sad cody without mullet
const unsigned char death_sprite_data[] =
{
  0xFF,0xF8,0xFF,0xF0,0xFF,0xE0,0xFF,0xE0,
  0xFF,0xC0,0xF9,0xC0,0xE0,0x96,0xE2,0x94,
  0xE0,0x90,0xE0,0xD3,0xE0,0xF4,0xE0,0xF0,
  0xF0,0xFE,0xFC,0xFE,0xFC,0xFE,0xFC,0xFE,
  0xFF,0x1F,0xFF,0x0F,0xFF,0x07,0xFF,0x07,
  0xFF,0x03,0x9F,0x03,0x07,0x69,0x47,0x29,
  0x07,0x09,0x07,0xCB,0x07,0x2F,0x07,0x0F,
  0x0F,0x7F,0x3F,0x7F,0x3F,0x7F,0x3F,0x7F
};

// grey black layered block
const unsigned char block_sprite_data[] =
{
  0x7F,0x7F,0xFF,0xC0,0xFF,0x81,0xFF,0x87,
  0xFF,0x8F,0xFF,0x99,0xFF,0x99,0xFF,0x8F,
  0xFF,0x87,0xFF,0x81,0xFF,0x81,0xFF,0x8F,
  0xFF,0x8F,0xFF,0x81,0xFF,0xC0,0x7F,0x7F,
  0xFE,0xFE,0xFF,0x03,0xFF,0x81,0xFF,0xF1,
  0xFF,0xF1,0xFF,0x81,0xFF,0x81,0xFF,0xC1,
  0xFF,0xF1,0xFF,0x99,0xFF,0x99,0xFF,0xF1,
  0xFF,0xE1,0xFF,0x81,0xFF,0x03,0xFE,0xFE
};
