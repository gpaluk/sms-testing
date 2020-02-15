#include "SMSlib.h"
#include "bank1.h"

#define BG_TILE_POSITION 0
#define SPRITE_TILES_POSITION 256

unsigned char scroll_x;
unsigned char scroll_y;
unsigned char player_x;
unsigned char player_y;

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
  for(j=0; j<3; j++)
  {
    for(i=0; i<2; i++)
    {
      SMS_addSprite(player_x+(i<<3), player_y+(j<<3), SPRITE_TILES_POSITION + 2*j + i);
    }
  }
}
int falling = 0;

void main (void)
{
  scroll_x = 0;
  scroll_y = 0;
  player_x = 0;
  player_y = 0;

  init_console();
  loadGraphics2vram();

  while (1)
  {
    scroll_y--;
    //scroll_x++;

    SMS_setSpritePaletteColor(0, RGB(0, 0, 0));
    SMS_initSprites();
    draw_main_character();
    SMS_finalizeSprites();
    SMS_waitForVBlank();
    SMS_setBGScrollX(scroll_x);
    SMS_setBGScrollY(scroll_y);
    SMS_copySpritestoSAT();
  }
}

SMS_EMBED_SEGA_ROM_HEADER(9999, 0);
SMS_EMBED_SDSC_HEADER(1, 0, 2020, 1,8, "Plugin.IO Ltd", "Hello World", "Simple Sega Master System demo to run on real hardware!");