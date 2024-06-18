/* ************************************************************************************* */
/* ************************************************************************************* */
/* **** File: x11test03.cpp                                                         **** */
/* **** Compile: gcc -Wall x11test03.cpp -o prog03 `pkg-config --cflags --libs xcb` **** */
/* **** Debug: gdb                                                                  **** */
/* ************************************************************************************* */
/* ************************************************************************************* */


#include <xcb/xcb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cassert>

#define WINDOW_WIDTH  800 
#define WINDOW_HEIGHT 600

static xcb_gc_t gc_font_get (xcb_connection_t *c, xcb_screen_t *screen, xcb_window_t window, const char *font_name)
{
    uint32_t             value_list[3];
    xcb_void_cookie_t    cookie_font;
    xcb_void_cookie_t    cookie_gc;
    xcb_generic_error_t *error;
    xcb_font_t           font;
    xcb_gcontext_t       gc;
    uint32_t             mask;

    font = xcb_generate_id (c);
    cookie_font = xcb_open_font_checked (c, font, strlen (font_name), font_name);

    error = xcb_request_check (c, cookie_font);

    if (error) {
        fprintf (stderr, "ERROR: can't open font : %d\n", error->error_code);
        xcb_disconnect (c);
        return XCB_GC_FUNCTION;
    }

    gc = xcb_generate_id (c);
    mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
    value_list[0] = screen->black_pixel;
    value_list[1] = screen->white_pixel;
    value_list[2] = font;
    cookie_gc = xcb_create_gc_checked (c, gc, window, mask, value_list);
    error = xcb_request_check (c, cookie_gc);
    if (error) {
        fprintf (stderr, "ERROR: can't create gc : %d\n", error->error_code);
        xcb_disconnect (c);
        exit (-1);
    }

    cookie_font = xcb_close_font_checked (c, font);
    error = xcb_request_check (c, cookie_font);
    if (error) {
        fprintf (stderr, "ERROR: can't close font : %d\n", error->error_code);
        xcb_disconnect (c);
        exit (-1);
    }

    return (xcb_gc_t)gc;
}

static void text_draw (xcb_connection_t *c, xcb_screen_t *screen, xcb_window_t window, int16_t x1, int16_t y1, const char *label)
{
    xcb_void_cookie_t    cookie_gc;
    xcb_void_cookie_t    cookie_text;
    xcb_generic_error_t *error;
    xcb_gcontext_t       gc;
    uint8_t              length;

    length = strlen (label);

    gc = gc_font_get(c, screen, window, "12x24"); // font size
    cookie_text = xcb_image_text_8_checked (c, length, window, gc, x1, y1, label);

    error = xcb_request_check (c, cookie_text);
    if (error) {
        fprintf (stderr, "ERROR: can't paste text : %d\n", error->error_code);
        xcb_disconnect (c);
        exit (-1);
    }

    cookie_gc = xcb_free_gc (c, gc);
    error = xcb_request_check (c, cookie_gc);
    if (error) {
        fprintf (stderr, "ERROR: can't free gc : %d\n", error->error_code);
        xcb_disconnect (c);
        exit (-1);
    }
}

int main(int argc, char *argv[]) 
{
    int screen_number;
    int values[2];
    values[1] =
        XCB_EVENT_MASK_KEY_RELEASE |
        XCB_EVENT_MASK_BUTTON_PRESS |
        XCB_EVENT_MASK_EXPOSURE |
        XCB_EVENT_MASK_POINTER_MOTION;

    xcb_generic_event_t  *genericEvent;

    xcb_connection_t *connection = xcb_connect(NULL, &screen_number); // Create the connection 
    assert(!xcb_connection_has_error(connection)); // Check the connection status

    const xcb_setup_t *setup = xcb_get_setup(connection);
    xcb_screen_iterator_t screen_iterator = xcb_setup_roots_iterator(setup);
    xcb_screen_t *screen = screen_iterator.data; // This will give the first screen

    xcb_window_t window = xcb_generate_id(connection);
    
    values[0] = screen->white_pixel;

    xcb_create_window(connection, 
        screen->root_depth, 
        window, 
        screen->root, 0, 0, WINDOW_WIDTH, WINDOW_WIDTH, 1, 
        XCB_WINDOW_CLASS_INPUT_OUTPUT, 
        screen->root_visual, 
        (XCB_CW_EVENT_MASK),
        values);
   
    xcb_map_window(connection, window);
    xcb_flush(connection);

    while (genericEvent = xcb_wait_for_event(connection)) { // Event loop waiting for an event
        if (genericEvent) {
            switch (genericEvent->response_type & ~0x80) {
                case XCB_EXPOSE: { // onDraw event
                    char *text = "Hello, this is a test on XWindow.";
                    text_draw(connection, screen, window, 100, 100, text);
                    break;
                }
                case XCB_KEY_RELEASE: { // keyboard events
                        xcb_key_release_event_t *ev = (xcb_key_release_event_t *)genericEvent;

                        switch (ev->detail) {
                            case 9: // esc
                                free (genericEvent);
                                xcb_disconnect (connection);
                                printf("key released esc.\n");
                                return 0;
                            case 65: { // space
                                break;
                            }
                            default: // other keys 
                                printf("key released: %d...\n", ev->detail); // print key released
                        } 
                    }
            }

            free(genericEvent);
        }
    }

    xcb_disconnect(connection); // Release the connection
    return EXIT_SUCCESS;
}
