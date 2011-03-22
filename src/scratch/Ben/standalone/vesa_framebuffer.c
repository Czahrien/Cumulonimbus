#include "vesa_framebuffer.h"
#include "vbe_info.h"
#include "gs_io.h"
#include "c_io.h"
#include "util.h"
#include "timer_isr.h"

pixel_t* vesa_video_memory; 
uint32_t vesa_x_resolution;
uint32_t vesa_y_resolution;
uint32_t vesa_red_mask;
uint32_t vesa_red_offset;
uint32_t vesa_blue_mask;
uint32_t vesa_blue_offset;
uint32_t vesa_green_mask;
uint32_t vesa_green_offset;
gs_framebuffer_t framebuffer;

void _vesa_init(void) {
    vbe_mode_info_t* vmi = (vbe_mode_info_t*)VBE_MODE_INFO_LOCATION;
    vesa_x_resolution = vmi->x_res;
    vesa_y_resolution = vmi->y_res; 
    
    //Create the masks, if a mask is of size x that means that x bits are set.
    vesa_red_mask = (1 << (vmi->red_mask_size)) - 1;
    vesa_blue_mask = (1 << (vmi->blue_mask_size)) - 1;
    vesa_green_mask = (1 << (vmi->green_mask_size)) - 1;

    vesa_red_offset = vmi->red_field_position;
    vesa_blue_offset = vmi->blue_field_position;
    vesa_green_offset = vmi->green_field_position;
    vesa_video_memory = (pixel_t*)vmi->physical_base_ptr;
}

void _vesa_text_demo(void) {
    //gs_set_draw_mode( GS_DRAW_MODE_XOR  ); 
    char ch = 0;
    int index = 3*1280;

    gs_puts_at(0,0,"Type on the screen! Hit escape to see a cooler demo!");
    while( ch != '\033' ) {
        gs_putc_at(index%1280,FONT_CHAR_HEIGHT*(index/1280), ch = c_getchar() );
        index += FONT_CHAR_WIDTH;
    }
}

void _print_vesa_demo() {
    vbe_mode_info_t* c = (vbe_mode_info_t*)VBE_MODE_INFO_LOCATION;
    uint32_t iter = 0;
    uint32_t x_res = c->x_res;
    uint32_t y_res = c->y_res;
    uint32_t x_res_over2 = c->x_res >> 1;
    uint32_t max_offset = c->x_res;
 
    // Here's an overoptimized demo!
    while( 1 ) {
        gs_puts_at_buf(0,10,"HELLO WORLD", &framebuffer );
        gs_puts_at_buf(0,84, "0123456789", &framebuffer );
        gs_puts_at_buf(0,100,"ABCDEFGHIJKLMNOPQRSTUVWXYZ", &framebuffer );
        gs_puts_at_buf(0,116,"abcdefghijklmnopqrstuvwxyz", &framebuffer );
        gs_puts_at_buf(0,132,"Timer ticks: ", &framebuffer);
        gs_puts_at_buf(156,132,itoa(_get_time()), &framebuffer);

        gs_draw_buf( &framebuffer );
        double_pixel_t* lol = (double_pixel_t*)&framebuffer;

        // draw the first line of the scene
        uint32_t offset = 0;
        do {   
            uint32_t grey_intensity = (((offset+iter) % x_res) << 7) / (x_res_over2);
            
            if( grey_intensity > 128 ){
                grey_intensity = ~grey_intensity;
                grey_intensity &= 0xFF;
            } else if( grey_intensity == 128 ) {
                grey_intensity = 127;
            }
            uint32_t frac = grey_intensity >> 2;
            pixel_t write = CREATE_PIXEL(frac,frac<<1,frac);

            *lol = CREATE_DOUBLE_PIXEL(write,write);
            ++lol;
            offset += 2;
        } while( offset < max_offset );
        // copy the first line to the rest of the scene
        int i,j;
        double_pixel_t* begin = lol;
        for( i = 1; i < y_res; ++i ) {
            lol = (double_pixel_t*)&framebuffer;
            for( j = 0; j < x_res; ++j ) {
                *begin = *lol;
                ++lol; ++begin;
            }
            
        }
        iter += 10;
    }
}
