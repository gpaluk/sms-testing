#include "SMSlib.h"
#include "PSGlib.h"
#include "bank1.h"

#define BG_TILE_POSITION 0
#define SPRITE_TILES_POSITION 256
#define NUMBER_FRAMES 3
#define NUMBER_FRAMES_BOTH_DIRECTIONS 6
#define NUMBER_TILES_BY_FRAME 2
#define NUMBER_TILES_FRAMES_BOTH_DIRECTIONS 12

#define DIRECTION_RIGHT 0
#define DIRECTION_LEFT 1

unsigned char scroll_x;
unsigned char scroll_y;
unsigned char player_x;
unsigned char player_y;
unsigned char current_frame;
unsigned char frame_counter;
unsigned char direction;
unsigned char volume_atenuation;

void init_console(void)
{
  SMS_init();
  SMS_displayOff();
  SMS_setSpriteMode(SPRITEMODE_NORMAL);
  SMS_zeroBGPalette();
  SMS_displayOn();
}

void loadGraphics2vram(void)
{
  SMS_loadBGPalette(backgroundpalette_bin);
  SMS_loadPSGaidencompressedTiles(backgroundtiles_psgcompr, 0);
  SMS_loadTileMap(0,0, backgroundtilemap_bin, backgroundtilemap_bin_size);

  SMS_loadSpritePalette(spritepalette_bin);
  SMS_loadPSGaidencompressedTiles (spritetiles_psgcompr,SPRITE_TILES_POSITION);
}

void draw_main_character(void)
{
  unsigned char i, j;
  unsigned char direction_offset;

  if(direction == DIRECTION_RIGHT)
  {
    direction_offset = 0;
  }
  else
  {
    direction_offset = NUMBER_FRAMES * NUMBER_TILES_BY_FRAME;
  }
  
  for(j=0; j<3; j++)
  {
    for(i=0; i<2; i++) {
      SMS_addSprite(player_x+(i<<3), player_y+(j<<3), SPRITE_TILES_POSITION + direction_offset + current_frame * NUMBER_TILES_BY_FRAME + NUMBER_TILES_FRAMES_BOTH_DIRECTIONS *j + i);
    }
  }
  if((frame_counter%16) == 0) {
    current_frame++;
    if(current_frame == NUMBER_FRAMES) {
      current_frame = 0;
    }
  }
}

void main (void)
{
  scroll_x = 0;
  scroll_y = 0;
  player_x = 0;
  player_y = 104;
  current_frame = 0;
  frame_counter = 0;
  direction = DIRECTION_RIGHT;

  init_console();
  loadGraphics2vram();

  PSGPlay(music_psg);
  while (1)
  {
    if(direction == DIRECTION_RIGHT)
    {
      scroll_x--;
      player_x++;
    }
    else
    {
      scroll_x++;
      player_x--;
    }
    
    frame_counter++;
    if(frame_counter == 255)
    {
      direction = !direction;
    }

    if((frame_counter%64) == 0)
    {
      volume_atenuation++;
      if(volume_atenuation > 15)
      {
        volume_atenuation = 0;
      }
    }

    SMS_setSpritePaletteColor(0, RGB(0, 0, 0));
    SMS_initSprites();
    draw_main_character();
    SMS_finalizeSprites();
    SMS_waitForVBlank();

    PSGFrame();
    PSGSFXFrame();

    SMS_copySpritestoSAT();
    SMS_setBGScrollX(scroll_x);
    SMS_setBGScrollY(scroll_y);
  }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER(1, 0, 2020, 1, 8, "Plugin.IO Ltd", "Hello World", "Simple Sega Master System demo to run on real hardware!");