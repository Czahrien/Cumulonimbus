#ifndef GS_IO_H_
#define GS_IO_H_
#include "gs_font.h"
#include "vesa_framebuffer.h"
#define VIDEO_BASE_ADDR 0xB8000
#define	VIDEO_ADDR(x,y)	(( unsigned short * )( VIDEO_BASE_ADDR + 2 * ( (y) * SCREEN_X_SIZE + (x) ) ))
#define SCREEN_X_SIZE 80
#define SCREEN_Y_SIZE 25
#define FONT_CHAR_WIDTH  12
#define FONT_CHAR_HEIGHT 16

// A buffer that allows for compact storage of text
typedef struct _gs_text_buffer_t {
    char buffer[106][64];
} gs_textbuffer_t;

typedef union _gs_frame_buffer_t {
    pixel_t buffer[1280][1024];
    double_pixel_t dpbuffer[640][1024];
} gs_framebuffer_t;

typedef uint32_t gs_draw_mode_t;
#define GS_DRAW_MODE_FLAT 0x0
#define GS_DRAW_MODE_AND 0x1
#define GS_DRAW_MODE_OR 0x2
#define GS_DRAW_MODE_XOR 0x3
#define GS_DRAW_MODE_MASK 0x3
#define GS_DRAW_MODE_DRAW_BLACK 0x4
#define GS_DRAW_MODE_INVERT 0x8

extern gs_draw_mode_t gs_set_draw_mode( gs_draw_mode_t );
extern void gs_draw_pixel( int x, int y, pixel_t color );
extern void gs_draw_double_pixel( int x, int y, pixel_t color_l, pixel_t color_r );
extern void gs_draw_square( int x, int y, int width, int height, pixel_t color );
extern void gs_puts_at( int x, int y, const char* s );
extern void gs_printf_at( int x, int y, const char* s );
extern void gs_putc_at( int x, int y, char c );
extern void gs_puts_at_buf( int x, int y, const char* s, gs_framebuffer_t* buf );
extern void gs_putc_at_buf( int x, int y, char c, gs_framebuffer_t* buf );
extern void gs_draw_buf(const gs_framebuffer_t* buf);
extern void gs_save_buf(gs_framebuffer_t* buf);
extern void gs_put_text_buffer( gs_textbuffer_t* buf );
#endif
