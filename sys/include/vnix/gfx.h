#ifndef _vnix_gfx_h
#define _vnix_gfx_h

#include <stdint.h>

#define GFX_MEMORY 0x01000000

void gfx_init(uint32_t* pix, uint32_t w, uint32_t h, uint32_t bpp, uint32_t pitch);

void gfx_put_char(uint16_t c, uint32_t x, uint32_t y, uint32_t fg, uint32_t bg);

uint8_t* gfx_get_vidmem(void);
uint32_t gfx_get_width(void);
uint32_t gfx_get_height(void);
uint32_t gfx_get_bpp(void);

void gfx_fill(uint32_t color);

#endif
